#ifndef PHYSICS_H
#define PHYSICS_H

class Physics
{
private:
    void LinSolve(int b, float x[], float x0[], float a, float c, int iter, int size_x, int size_y);
    void SetBnd(int b, float x[], int size_x, int size_y);

public:
    Physics();
    ~Physics();

    void Diffuse(int b, float x[], float x0[], float diff, float dt, int iter, int size_x, int size_y);
    void Project(float vx[], float vy[], float p[], float div[], int iter, int size_x, int size_y);
    void Advect(int b, float d[], float d0[], float vx[], float vy[], float dt, int size_x, int size_y);
};

#endif
