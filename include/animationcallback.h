#ifndef ANIMATIONCALLBACK_H
#define ANIMATIONCALLBACK_H

#include <vtkCommand.h>
#include <vtkMath.h>
#include <random>
#include <iostream>
#include <vtkImageData.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <const.h>
#include <ix.h>
#include <vtkCommand.h>
#include <container3d.h>
#include <physics3d.h>

class AnimationCallback : public vtkCommand
{
private:
    vtkImageData *imageData;
    Container3D *container;
    int dimensions[3];
    int totalFrames = 0;
    int currentFrame = 0;
    int timerId;
    int countAnimate = 0;
    // FluidCube* cube = FluidCubeCreate(50, 0.0, 0.0000001f, 0.2);
    int min2 = 1;
    int max2 = N - 1;
    std::random_device rd; // Obtain a random number from hardware
public:
    static AnimationCallback *New()
    {
        return new AnimationCallback;
    }
    AnimationCallback();
    ~AnimationCallback();
    void Execute(vtkObject *caller, unsigned long eventId, void *callData) override;
    void SetImageData(vtkImageData *data);
    void SetDimensions(const int dims[3]);
    void SetTotalFrames(int frames);
    void SetTimerId(int id);
};

#endif //