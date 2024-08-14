#include <cmath>
#include <physics.h>
#include <ix.h>

Physics::Physics() {}

Physics::~Physics() {}

void Physics::SetBnd(int b, float x[], int size_x, int size_y)
{
    for (int i = 1; i < size_x - 1; i++)
    {
        x[IX(i, 0, size_x, size_y)] = b == 2 ? -x[IX(i, 1, size_x, size_y)] : x[IX(i, 1, size_x, size_y)];
        x[IX(i, size_y - 1, size_x, size_y)] = b == 2 ? -x[IX(i, size_y - 2, size_x, size_y)] : x[IX(i, size_y - 2, size_x, size_y)];
    }

    for (int j = 1; j < size_y - 1; j++)
    {
        x[IX(0, j, size_x, size_y)] = b == 1 ? -x[IX(1, j, size_x, size_y)] : x[IX(1, j, size_x, size_y)];
        x[IX(size_x - 1, j, size_x, size_y)] = b == 1 ? -x[IX(size_x - 2, j, size_x, size_y)] : x[IX(size_x - 2, j, size_x, size_y)];
    }

    x[IX(0, 0, size_x, size_y)] = 0.33f * (x[IX(1, 0, size_x, size_y)] + x[IX(0, 1, size_x, size_y)] + x[IX(0, 0, size_x, size_y)]);
    x[IX(0, size_y - 1, size_x, size_y)] = 0.33f * (x[IX(1, size_y - 1, size_x, size_y)] + x[IX(0, size_y - 2, size_x, size_y)] + x[IX(0, size_y - 1, size_x, size_y)]);
    x[IX(size_x - 1, 0, size_x, size_y)] = 0.33f * (x[IX(size_x - 2, 0, size_x, size_y)] + x[IX(size_x - 1, 1, size_x, size_y)] + x[IX(size_x - 1, 0, size_x, size_y)]);
    x[IX(size_x - 1, size_y - 1, size_x, size_y)] = 0.33f * (x[IX(size_x - 2, size_y - 1, size_x, size_y)] + x[IX(size_x - 1, size_y - 2, size_x, size_y)] + x[IX(size_x - 1, size_y - 1, size_x, size_y)]);
}

void Physics::LinSolve(int b, float x[], float x0[], float a, float c, int iter, int size_x, int size_y)
{
    float cRecip = 1.0 / c;
    for (int k = 0; k < iter; k++)
    {
        for (int j = 1; j < size_y - 1; j++)
        {
            for (int i = 1; i < size_x - 1; i++)
            {
                x[IX(i, j, size_x, size_y)] = (x0[IX(i, j, size_x, size_y)] + a * (x[IX(i + 1, j, size_x, size_y)] + x[IX(i - 1, j, size_x, size_y)] + x[IX(i, j + 1, size_x, size_y)] + x[IX(i, j - 1, size_x, size_y)] + x[IX(i, j, size_x, size_y)] + x[IX(i, j, size_x, size_y)])) * cRecip;
            }
        }
        this->SetBnd(b, x, size_x, size_y);
    }
}

void Physics::Diffuse(int b, float x[], float x0[], float diff, float dt, int iter, int size_x, int size_y)
{
    float a = dt * diff * (size_x - 2) * (size_y - 2);
    this->LinSolve(b, x, x0, a, 1 + 6 * a, iter, size_x, size_y);
}

void Physics::Project(float vx[], float vy[], float p[], float div[], int iter, int size_x, int size_y)
{
    for (int j = 1; j < size_y - 1; j++)
    {
        for (int i = 1; i < size_y - 1; i++)
        {
            div[IX(i, j, size_x, size_y)] = -0.5f * (vx[IX(i + 1, j, size_x, size_y)] - vx[IX(i - 1, j, size_x, size_y)] + vy[IX(i, j + 1, size_x, size_y)] - vy[IX(i, j - 1, size_x, size_y)]) / (size_x); // this might need change
            p[IX(i, j, size_x, size_y)] = 0;
        }
    }

    this->SetBnd(0, div, size_x, size_y);
    this->SetBnd(0, p, size_x, size_y);
    this->LinSolve(0, p, div, 1, 6, iter, size_x, size_y);

    for (int j = 1; j < size_y - 1; j++)
    {
        for (int i = 1; i < size_x - 1; i++)
        {
            vx[IX(i, j, size_x, size_y)] -= 0.5f * (p[IX(i + 1, j, size_x, size_y)] - p[IX(i - 1, j, size_x, size_y)]) * size_x; // need change
            vy[IX(i, j, size_x, size_y)] -= 0.5f * (p[IX(i, j + 1, size_x, size_y)] - p[IX(i, j - 1, size_x, size_y)]) * size_x; // need change
        }
    }
    this->SetBnd(1, vx, size_x, size_y);
    this->SetBnd(2, vy, size_x, size_y);
}

void Physics::Advect(int b, float d[], float d0[], float vx[], float vy[], float dt, int size_x, int size_y)
{
    float i0, i1, j0, j1;

    float dtx = dt * (size_x - 2);
    float dty = dt * (size_y - 2);

    float s0, s1, t0, t1;
    float tmp1, tmp2, x, y;

    float NfloatX = size_x;
    float NfloatY = size_y;
    float ifloat, jfloat;

    int i, j;

    for (j = 1, jfloat = 1; j < size_y - 1; j++, jfloat++)
    {
        for (i = 1, ifloat = 1; i < size_x - 1; i++, ifloat++)
        {
            tmp1 = dtx * vx[IX(i, j, size_x, size_y)];
            tmp2 = dty * vy[IX(i, j, size_x, size_y)];
            x = ifloat - tmp1;
            y = jfloat - tmp2;

            if (x < 0.5f)
                x = 0.5f;
            if (x > NfloatX + 0.5f)
                x = NfloatX + 0.5f;
            i0 = ::floorf(x);
            i1 = i0 + 1.0f;
            if (y < 0.5f)
                y = 0.5f;
            if (y > NfloatY + 0.5f)
                y = NfloatY + 0.5f;
            j0 = ::floorf(y);
            j1 = j0 + 1.0f;

            s1 = x - i0;
            s0 = 1.0f - s1;
            t1 = y - j0;
            t0 = 1.0f - t1;

            int i0i = i0;
            int i1i = i1;
            int j0i = j0;
            int j1i = j1;

            d[IX(i, j, size_x, size_y)] =
                s0 * (t0 * d0[IX(i0i, j0i, size_x, size_y)] + t1 * d0[IX(i0i, j1i, size_x, size_y)]) +
                s1 * (t0 * d0[IX(i1i, j0i, size_x, size_y)] + t1 * d0[IX(i1i, j1i, size_x, size_y)]);
        }
    }
    this->SetBnd(b, d, size_x, size_y);
}
