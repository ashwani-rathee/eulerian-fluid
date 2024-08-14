#ifndef FLUIDSIM_H
#define FLUIDSIM_H

#include <math.h>
#include <container.h>
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
#include <animationcallback.h>

class Fluid3DSim
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
    vtkNew<AnimationCallback> callback;
    vtkFloatArray *scalars;

public:
    static const int numParticles;
    Fluid3DSim();
    ~Fluid3DSim();
    void Run();
};

#endif