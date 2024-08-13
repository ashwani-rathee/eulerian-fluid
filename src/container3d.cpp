#include "../header/container3d.h"
#include "../header/ix.h"
#include <stdlib.h>

Container3D::Container3D(int size, float dt, float diff, float visc)
{
    this->size = size;
    int N = size;
    
    this->size = size;
    this->dt = dt;
    this->diff = diff;
    this->visc = visc;
    
    this->s = static_cast<float*>(calloc(N * N * N, sizeof(float)));
    this->density = static_cast<float*>(calloc(N * N * N, sizeof(float)));
    this->Vx = static_cast<float*>(calloc(N * N * N, sizeof(float)));
    this->Vy = static_cast<float*>(calloc(N * N * N, sizeof(float)));
    this->Vz = static_cast<float*>(calloc(N * N * N, sizeof(float)));
    this->Vx0 = static_cast<float*>(calloc(N * N * N, sizeof(float)));
    this->Vy0 = static_cast<float*>(calloc(N * N * N, sizeof(float)));
    this->Vz0 = static_cast<float*>(calloc(N * N * N, sizeof(float)));
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
    int N          = this->size;
    float visc     = this->visc;
    float diff     = this->diff;
    float dt       = this->dt;
    float *Vx      = this->Vx;
    float *Vy      = this->Vy;
    float *Vz      = this->Vz;
    float *Vx0     = this->Vx0;
    float *Vy0     = this->Vy0;
    float *Vz0     = this->Vz0;
    float *s       = this->s;
    float *density = this->density;
    
    this->physics->Diffuse(1, Vx0, Vx, visc, dt, 4, N);
    this->physics->Diffuse(2, Vy0, Vy, visc, dt, 4, N);
    this->physics->Diffuse(3, Vz0, Vz, visc, dt, 4, N);
    
    this->physics->Project(Vx0, Vy0, Vz0, Vx, Vy, 4, N);
    
    this->physics->Advect(1, Vx, Vx0, Vx0, Vy0, Vz0, dt, N);
    this->physics->Advect(2, Vy, Vy0, Vx0, Vy0, Vz0, dt, N);
    this->physics->Advect(3, Vz, Vz0, Vx0, Vy0, Vz0, dt, N);
    
    this->physics->Project(Vx, Vy, Vz, Vx0, Vy0, 4, N);
    
    this->physics->Diffuse(0, s, density, diff, dt, 4, N);
    this->physics->Advect(0, density, s, Vx, Vy, Vz, dt, N);
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
