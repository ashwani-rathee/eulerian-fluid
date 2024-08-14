#include "../header/container3d.h"
#include "../header/ix.h"
#include <stdlib.h>
#include <iostream>

Container3D::Container3D(int size, float dt, float diff, float visc)
{
    this->size = size;
    int N = size;

    this->size = size;
    this->dt = dt;
    this->diff = diff;
    this->visc = visc;

    this->s = static_cast<float *>(calloc(N * N * N, sizeof(float)));
    this->density = static_cast<float *>(calloc(N * N * N, sizeof(float)));
    this->Vx = static_cast<float *>(calloc(N * N * N, sizeof(float)));
    this->Vy = static_cast<float *>(calloc(N * N * N, sizeof(float)));
    this->Vz = static_cast<float *>(calloc(N * N * N, sizeof(float)));
    this->Vx0 = static_cast<float *>(calloc(N * N * N, sizeof(float)));
    this->Vy0 = static_cast<float *>(calloc(N * N * N, sizeof(float)));
    this->Vz0 = static_cast<float *>(calloc(N * N * N, sizeof(float)));

    this->physics = new Physics3D();
}

Container3D::~Container3D()
{
    free(this->s);
    free(this->density);

    free(this->Vx);
    free(this->Vy);
    free(this->Vz);

    free(this->Vx0);
    free(this->Vy0);
    free(this->Vz0);
}

void Container3D::FluidCubeStep()
{
    this->physics->Diffuse(1, this->Vx0, this->Vx, this->visc, this->dt, 4, this->size);
    this->physics->Diffuse(2, this->Vy0, this->Vy, this->visc, this->dt, 4, this->size);
    this->physics->Diffuse(3, this->Vz0, this->Vz, this->visc, this->dt, 4, this->size);

    this->physics->Project(this->Vx0, this->Vy0, this->Vz0, this->Vx, this->Vy, 4, this->size);

    this->physics->Advect(1, this->Vx, this->Vx0, this->Vx0, this->Vy0, this->Vz0, this->dt, this->size);
    this->physics->Advect(2, this->Vy, this->Vy0, this->Vx0, this->Vy0, this->Vz0, this->dt, this->size);
    this->physics->Advect(3, this->Vz, this->Vz0, this->Vx0, this->Vy0, this->Vz0, this->dt, this->size);

    this->physics->Project(this->Vx, this->Vy, this->Vz, this->Vx0, this->Vy0, 4, this->size);

    this->physics->Diffuse(0, this->s, this->density, this->diff, this->dt, 4, this->size);
    this->physics->Advect(0, this->density, this->s, this->Vx, this->Vy, this->Vz, this->dt, this->size);
}

void Container3D::FluidCubeAddDensity(int x, int y, int z, float amount)
{
    int N = this->size;
    this->density[IX(x, y, z)] += amount;
}

void Container3D::FluidCubeAddVelocity(int x, int y, int z, float amountX, float amountY, float amountZ)
{
    int N = this->size;
    int index = IX(x, y, z);

    this->Vx[index] += amountX;
    this->Vy[index] += amountY;
    this->Vz[index] += amountZ;
}
