#include "../header/animationcallback.h"
#include <random>

AnimationCallback::~AnimationCallback()
{
}

void AnimationCallback::Execute(vtkObject *caller, unsigned long eventId, void *callData)
{

    std::mt19937 gen(rd());                            // Seed the generator
    std::uniform_int_distribution<> distr(min2, max2); // Define the ran
    if (vtkCommand::TimerEvent == eventId)
    {
        // std::cout << "Animation callback" << std::endl;
        // FluidCubeStep(this->cube);
        // if (this->cube->density[IX(25, 49, 25)] <= 0)
        // {
        //     //  FluidCubeAddDensity(this->cube, 24,1,22,20);
        //     FluidCubeAddDensity(this->cube, 25, 1, 25, 30);
        //     // FluidCubeAddDensity(this->cube, 25,1,22,10);
        //     // FluidCubeAddDensity(this->cube, 25,1,22,20);
        // }
        // // if(this->cube->density[IX(25,49,25)] <= 0) FluidCubeAddDensity(this->cube, 25,25,1,50);
        // //             if(this->cube->density[IX(25,49,25)] <= 0) FluidCubeAddVelocity(this->cube, 25,25,2,0,0,1);
        // if (this->cube->density[IX(25, 49, 25)] <= 0)
        // {
        //     FluidCubeAddVelocity(this->cube, 25, 2, 25, 0.5, 0.9, 0.2);
        // }
        // if (countAnimate % 500 == 0)
        //     FluidCubeAddVelocity(this->cube, 25, distr(gen), 25, distr(gen), distr(gen), distr(gen));

        // Generate new random values for the volume
        for (int z = 0; z < this->dimensions[2]; ++z)
        {
            for (int y = 0; y < this->dimensions[1]; ++y)
            {
                for (int x = 0; x < this->dimensions[0]; ++x)
                {
                    this->imageData->SetScalarComponentFromFloat(x, y, z, 0, rand());
                }
            }
        }

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

void AnimationCallback::SetImageData(vtkImageData *data)
{
    this->imageData = data;
}

void AnimationCallback::SetDimensions(const int dims[3])
{
    this->dimensions[0] = dims[0];
    this->dimensions[1] = dims[1];
    this->dimensions[2] = dims[2];
}

void AnimationCallback::SetTotalFrames(int frames)
{
    this->totalFrames = frames;
}

void AnimationCallback::SetTimerId(int id)
{
    this->timerId = id;
}
