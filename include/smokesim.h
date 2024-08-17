#pragma once

#include <iostream>
// #include <fluid3dsim.h>
#include <sys/time.h>
#include <const.h>
#include <simulatorsmoke.h>
#include <macgrid.h>
#include <memory>
#include <random>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkCamera.h>
#include <vtkColorTransferFunction.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkImageData.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkCommand.h>
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <math.h>
#include <vtkSmartPointer.h>
#include <vtkVolume.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkCamera.h>
#include <vtkCommand.h>
#include <vtkProperty.h>
#include <algorithm>
#include <vtkMultiBlockDataSet.h>
#include <vtkMultiBlockVolumeMapper.h>
#include <random>
class AnimationCallbackSmoke : public vtkCommand
{
public:
    static AnimationCallbackSmoke *New()
    {
        return new AnimationCallbackSmoke;
    }

    AnimationCallbackSmoke()
    {
        grids = std::make_shared<MACGrid>();
        simulator = std::make_unique<Simulator>(grids, time);
    }

    ~AnimationCallbackSmoke()
    {
        // FluidCubeFree(this->cube);
    }

    void Execute(vtkObject *caller, unsigned long eventId, void *callData) override
    {
        std::mt19937 gen(rd());                            // Seed the generator
        std::uniform_int_distribution<> distr(min2, max2); // Define the ran
        if (vtkCommand::TimerEvent == eventId)
        {
            simulator->update();
            // float max_val = -1234567890;
            // float min_val = -max_val;

            // Generate new random values for the volume
            for (int z = 0; z < this->dimensions[2]; ++z)
            {
                for (int y = 0; y < this->dimensions[1]; ++y)
                {
                    for (int x = 0; x < this->dimensions[0]; ++x)
                    {
                        float f = (float)grids->density(x, y, z);
                        // max_val = std::max(max_val, f);
                        // min_val = std::min(max_val, f);
                        // *ptr++ = std::max(0, std::min(255, (int)std::floor(f * 256.0)));
                        this->imageData->SetScalarComponentFromFloat(x, y, z, 0, f);
                    }
                }
            }

            // std::cout << "Min:" << min_val << ",Max:" << max_val << std::endl; 
            // Update the volume data
            this->imageData->Modified();

            // Request render update
            vtkRenderWindowInteractor *iren = static_cast<vtkRenderWindowInteractor *>(caller);
            iren->GetRenderWindow()->Render();

            this->currentFrame++;
            if (this->currentFrame >= this->totalFrames)
            {
                iren->DestroyTimer(this->timerId); // Stop the timer after the total duration
            }
        }
    }

    void SetImageData(vtkImageData *data)
    {
        this->imageData = data;
    }

    void SetDimensions(const int dims[3])
    {
        this->dimensions[0] = dims[0];
        this->dimensions[1] = dims[1];
        this->dimensions[2] = dims[2];
    }

    void SetTotalFrames(int frames)
    {
        this->totalFrames = frames;
    }

    void SetTimerId(int id)
    {
        this->timerId = id;
    }

private:
    vtkImageData *imageData;
    int dimensions[3];
    int totalFrames = 0;
    int currentFrame = 0;
    int timerId;
    int countAnimate = 0;
    std::shared_ptr<MACGrid> grids;
    std::unique_ptr<Simulator> simulator;
    int min2 = 1;
    int max2 = N - 1;
    std::random_device rd; // Obtain a random number from hardware
    struct timeval s, e;
    double time = 0.0;
    int step = 1;
};

class Fluid3DSimSmoke
{
private:
    const int dimensions[3] = {50, 50, 50}; // Dimensions of the volume
    vtkNew<vtkImageData> imageData;
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkRenderer> ren1;
    vtkNew<vtkRenderWindow> renWin;
    vtkNew<vtkRenderWindowInteractor> iren;
    vtkNew<vtkPiecewiseFunction> opacityTransferFunction;
    vtkNew<vtkColorTransferFunction> colorTransferFunction;
    vtkNew<vtkVolumeProperty> volumeProperty;
    vtkNew<vtkMultiBlockVolumeMapper> volumeMapper;
    vtkNew<vtkOutlineFilter> outlineFilter;
    vtkNew<vtkPolyDataMapper> outlineMapper;
    vtkNew<vtkActor> outlineActor;
    vtkNew<vtkVolume> volume;
    vtkNew<AnimationCallbackSmoke> callback;
    vtkFloatArray *scalars;
public:
    Fluid3DSimSmoke();
    ~Fluid3DSimSmoke();
    void Run();
};