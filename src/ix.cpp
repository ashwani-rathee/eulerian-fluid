#include <ix.h>
#include <const.h>

int IX(int x, int y, int z)
{
    if (x < 0)
    {
        x = 0;
    }
    if (x > N - 1)
    {
        x = N - 1;
    }

    if (y < 0)
    {
        y = 0;
    }
    if (y > N - 1)
    {
        y = N - 1;
    }

    if (z < 0)
    {
        z = 0;
    }
    if (z > N - 1)
    {
        z = N - 1;
    }

    return ((x) + (y)*N + (z)*N * N);
}

int IX(int x, int y, int x_size, int y_size)
{
    if (x < 0)
    {
        x = 0;
    }
    if (x > x_size - 1)
    {
        x = x_size - 1;
    }

    if (y < 0)
    {
        y = 0;
    }
    if (y > y_size - 1)
    {
        y = y_size - 1;
    }

    return (y * x_size) + x;
}

/* other definitions */
int POS(int i, int j, int k)
{
    assert((i >= 0 || i < Nx) || (j >= 0 || j < Ny) || (k >= 0 || k < Nz));
    return i + Nx * j + Nx * Ny * k;
}