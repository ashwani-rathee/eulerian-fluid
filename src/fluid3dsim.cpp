#include <fluid3dsim.h>
#include <container3d.h>
#include <physics3d.h>

Fluid3DSim::Fluid3DSim()
{
    std::srand(std::time(nullptr)); // Initialize random seed
    this->imageData->SetDimensions(this->dimensions);
    this->imageData->AllocateScalars(VTK_FLOAT, 1);
    scalars = vtkFloatArray::SafeDownCast(this->imageData->GetPointData()->GetScalars());
    for (int z = 0; z < dimensions[2]; ++z)
    {
        for (int y = 0; y < dimensions[1]; ++y)
        {
            for (int x = 0; x < dimensions[0]; ++x)
            {
                float value = static_cast<float>(std::rand()) / RAND_MAX;
                this->imageData->SetScalarComponentFromFloat(x, y, z, 0, value);
            }
        }
    }

    this->renWin->AddRenderer(ren1);
    this->iren->SetRenderWindow(renWin);

    this->opacityTransferFunction->AddPoint(0.0, 0.0);
    this->opacityTransferFunction->AddPoint(0.5, 0.1);
    this->opacityTransferFunction->AddPoint(1.0, 0.2);

    this->volumeProperty->SetColor(this->colorTransferFunction);
    this->volumeProperty->SetScalarOpacity(this->opacityTransferFunction);
    this->volumeProperty->ShadeOn();
    this->volumeProperty->SetInterpolationTypeToLinear();

    this->volumeMapper->SetInputDataObject(this->imageData);

    this->outlineFilter->SetInputData(this->imageData); // Use the image data as the input

    this->outlineMapper->SetInputConnection(this->outlineFilter->GetOutputPort());

    this->outlineActor->SetMapper(this->outlineMapper);
    this->outlineActor->GetProperty()->SetColor(0, 0, 0); // Set the outline color to black

    // Add the outline actor to the renderer
    this->ren1->AddActor(this->outlineActor);

    // The volume holds the mapper and the property and
    // can be used to position/orient the volume
    this->volume->SetMapper(this->volumeMapper);
    this->volume->SetProperty(this->volumeProperty);

    this->ren1->AddVolume(this->volume);
    this->ren1->SetBackground(this->colors->GetColor3d("Wheat").GetData());
    // ren1->GetActiveCamera()->Azimuth(45);
    // ren1->GetActiveCamera()->Elevation(30);
    this->ren1->ResetCameraClippingRange();
    this->ren1->ResetCamera();

    this->renWin->SetSize(600, 600);
    this->renWin->SetWindowName("Test");

    this->callback->SetImageData(this->imageData);
    this->callback->SetDimensions(this->dimensions);
    this->callback->SetTotalFrames(10000); // 10 seconds, 1 frame per second

    this->iren->Initialize();
    int timerId = this->iren->CreateRepeatingTimer(10); // 1000ms = 1 second
    this->callback->SetTimerId(timerId);
    this->iren->AddObserver(vtkCommand::TimerEvent, this->callback);
}

Fluid3DSim::~Fluid3DSim()
{
}

void Fluid3DSim::Run()
{
    this->iren->Start();
}
