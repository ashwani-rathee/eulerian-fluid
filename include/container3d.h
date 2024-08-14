#ifndef CONTAINER3D_H
#define CONTAINER3D_H

#include <physics3d.h>

class Container3D
{
private:
    Physics3D *physics;
    int size;
    float dt;
    float diff;
    float visc;

    float *s;

    float *Vx;
    float *Vy;
    float *Vz;

    float *Vx0;
    float *Vy0;
    float *Vz0;

public:
    float *density;
    Container3D(int size, float dt, float diff, float visc);
    ~Container3D();
    void FluidCubeStep();
    void FluidCubeAddDensity(int x, int y, int z, float amount);
    void FluidCubeAddVelocity(int x, int y, int z, float amountX, float amountY, float amountZ);
};

#endif //