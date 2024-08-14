#ifndef PHYSICS3D_H
#define PHYSICS3D_H

class Physics3D
{
private:
    void LinSolve(int b, float *x, float *x0, float a, float c, int iter, int N);
    void SetBnd(int b, float *x, int N);

public:
    Physics3D();
    ~Physics3D();

    void Diffuse(int b, float *x, float *x0, float diff, float dt, int iter, int N);
    void Project(float *velocX, float *velocY, float *velocZ, float *p, float *div, int iter, int N);
    void Advect(int b, float *d, float *d0, float *velocX, float *velocY, float *velocZ, float dt, int N);
};

#endif