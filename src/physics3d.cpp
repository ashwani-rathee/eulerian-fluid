#include <physics3d.h>
#include <ix.h>
#include <math.h>

Physics3D::Physics3D()
{
}

Physics3D::~Physics3D()
{
}

void Physics3D::LinSolve(int b, float *x, float *x0, float a, float c, int iter, int N)
{
    float cRecip = 1.0 / c;
    for (int k = 0; k < iter; k++)
    {
        for (int m = 1; m < N - 1; m++)
        {
            for (int j = 1; j < N - 1; j++)
            {
                for (int i = 1; i < N - 1; i++)
                {
                    x[IX(i, j, m)] =
                        (x0[IX(i, j, m)] + a * (x[IX(i + 1, j, m)] + x[IX(i - 1, j, m)] + x[IX(i, j + 1, m)] + x[IX(i, j - 1, m)] + x[IX(i, j, m + 1)] + x[IX(i, j, m - 1)])) * cRecip;
                }
            }
        }
        this->SetBnd(b, x, N);
    }
}

void Physics3D::SetBnd(int b, float *x, int N)
{
    for (int j = 1; j < N - 1; j++)
    {
        for (int i = 1; i < N - 1; i++)
        {
            x[IX(i, j, 0)] = b == 3 ? -x[IX(i, j, 1)] : x[IX(i, j, 1)];
            x[IX(i, j, N - 1)] = b == 3 ? -x[IX(i, j, N - 2)] : x[IX(i, j, N - 2)];
        }
    }
    for (int k = 1; k < N - 1; k++)
    {
        for (int i = 1; i < N - 1; i++)
        {
            x[IX(i, 0, k)] = b == 2 ? -x[IX(i, 1, k)] : x[IX(i, 1, k)];
            x[IX(i, N - 1, k)] = b == 2 ? -x[IX(i, N - 2, k)] : x[IX(i, N - 2, k)];
        }
    }
    for (int k = 1; k < N - 1; k++)
    {
        for (int j = 1; j < N - 1; j++)
        {
            x[IX(0, j, k)] = b == 1 ? -x[IX(1, j, k)] : x[IX(1, j, k)];
            x[IX(N - 1, j, k)] = b == 1 ? -x[IX(N - 2, j, k)] : x[IX(N - 2, j, k)];
        }
    }

    x[IX(0, 0, 0)] = 0.33f * (x[IX(1, 0, 0)] + x[IX(0, 1, 0)] + x[IX(0, 0, 1)]);
    x[IX(0, N - 1, 0)] = 0.33f * (x[IX(1, N - 1, 0)] + x[IX(0, N - 2, 0)] + x[IX(0, N - 1, 1)]);
    x[IX(0, 0, N - 1)] = 0.33f * (x[IX(1, 0, N - 1)] + x[IX(0, 1, N - 1)] + x[IX(0, 0, N)]);
    x[IX(0, N - 1, N - 1)] = 0.33f * (x[IX(1, N - 1, N - 1)] + x[IX(0, N - 2, N - 1)] + x[IX(0, N - 1, N - 2)]);
    x[IX(N - 1, 0, 0)] = 0.33f * (x[IX(N - 2, 0, 0)] + x[IX(N - 1, 1, 0)] + x[IX(N - 1, 0, 1)]);
    x[IX(N - 1, N - 1, 0)] = 0.33f * (x[IX(N - 2, N - 1, 0)] + x[IX(N - 1, N - 2, 0)] + x[IX(N - 1, N - 1, 1)]);
    x[IX(N - 1, 0, N - 1)] = 0.33f * (x[IX(N - 2, 0, N - 1)] + x[IX(N - 1, 1, N - 1)] + x[IX(N - 1, 0, N - 2)]);
    x[IX(N - 1, N - 1, N - 1)] = 0.33f * (x[IX(N - 2, N - 1, N - 1)] + x[IX(N - 1, N - 2, N - 1)] + x[IX(N - 1, N - 1, N - 2)]);
}

void Physics3D::Diffuse(int b, float *x, float *x0, float diff, float dt, int iter, int N)
{
    float a = dt * diff * (N - 2) * (N - 2);
    this->LinSolve(b, x, x0, a, 1 + 6 * a, iter, N);
}

void Physics3D::Project(float *velocX, float *velocY, float *velocZ, float *p, float *div, int iter, int N)
{
    for (int k = 1; k < N - 1; k++)
    {
        for (int j = 1; j < N - 1; j++)
        {
            for (int i = 1; i < N - 1; i++)
            {
                div[IX(i, j, k)] = -0.5f * (velocX[IX(i + 1, j, k)] - velocX[IX(i - 1, j, k)] + velocY[IX(i, j + 1, k)] - velocY[IX(i, j - 1, k)] + velocZ[IX(i, j, k + 1)] - velocZ[IX(i, j, k - 1)]) / N;
                p[IX(i, j, k)] = 0;
            }
        }
    }
    this->SetBnd(0, div, N);
    this->SetBnd(0, p, N);
    this->LinSolve(0, p, div, 1, 6, iter, N);

    for (int k = 1; k < N - 1; k++)
    {
        for (int j = 1; j < N - 1; j++)
        {
            for (int i = 1; i < N - 1; i++)
            {
                velocX[IX(i, j, k)] -= 0.5f * (p[IX(i + 1, j, k)] - p[IX(i - 1, j, k)]) * N;
                velocY[IX(i, j, k)] -= 0.5f * (p[IX(i, j + 1, k)] - p[IX(i, j - 1, k)]) * N;
                velocZ[IX(i, j, k)] -= 0.5f * (p[IX(i, j, k + 1)] - p[IX(i, j, k - 1)]) * N;
            }
        }
    }
    this->SetBnd(1, velocX, N);
    this->SetBnd(2, velocY, N);
    this->SetBnd(3, velocZ, N);
}

void Physics3D::Advect(int b, float *d, float *d0, float *velocX, float *velocY, float *velocZ, float dt, int N)
{
    float i0, i1, j0, j1, k0, k1;

    float dtx = dt * (N - 2);
    float dty = dt * (N - 2);
    float dtz = dt * (N - 2);

    float s0, s1, t0, t1, u0, u1;
    float tmp1, tmp2, tmp3, x, y, z;

    float Nfloat = N;
    float ifloat, jfloat, kfloat;
    int i, j, k;

    for (k = 1, kfloat = 1; k < N - 1; k++, kfloat++)
    {
        for (j = 1, jfloat = 1; j < N - 1; j++, jfloat++)
        {
            for (i = 1, ifloat = 1; i < N - 1; i++, ifloat++)
            {
                tmp1 = dtx * velocX[IX(i, j, k)];
                tmp2 = dty * velocY[IX(i, j, k)];
                tmp3 = dtz * velocZ[IX(i, j, k)];
                x = ifloat - tmp1;
                y = jfloat - tmp2;
                z = kfloat - tmp3;

                if (x < 0.5f)
                    x = 0.5f;
                if (x > Nfloat + 0.5f)
                    x = Nfloat + 0.5f;
                i0 = floorf(x);
                i1 = i0 + 1.0f;
                if (y < 0.5f)
                    y = 0.5f;
                if (y > Nfloat + 0.5f)
                    y = Nfloat + 0.5f;
                j0 = floorf(y);
                j1 = j0 + 1.0f;
                if (z < 0.5f)
                    z = 0.5f;
                if (z > Nfloat + 0.5f)
                    z = Nfloat + 0.5f;
                k0 = floorf(z);
                k1 = k0 + 1.0f;

                s1 = x - i0;
                s0 = 1.0f - s1;
                t1 = y - j0;
                t0 = 1.0f - t1;
                u1 = z - k0;
                u0 = 1.0f - u1;

                int i0i = i0;
                int i1i = i1;
                int j0i = j0;
                int j1i = j1;
                int k0i = k0;
                int k1i = k1;

                d[IX(i, j, k)] =

                    s0 * (t0 * (u0 * d0[IX(i0i, j0i, k0i)] + u1 * d0[IX(i0i, j0i, k1i)]) + (t1 * (u0 * d0[IX(i0i, j1i, k0i)] + u1 * d0[IX(i0i, j1i, k1i)]))) + s1 * (t0 * (u0 * d0[IX(i1i, j0i, k0i)] + u1 * d0[IX(i1i, j0i, k1i)]) + (t1 * (u0 * d0[IX(i1i, j1i, k0i)] + u1 * d0[IX(i1i, j1i, k1i)])));
            }
        }
    }
    this->SetBnd(b, d, N);
}
