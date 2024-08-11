#include "../header/container.h"
#include "../header/ix.h"
#include <iostream>

Container::Container() : physics(Physics()) {}

Container::Container(float dt, float diff, float visc)
{
    this->size_x = SIZE_X;
    this->size_y = SIZE_Y;

    this->dt = dt;
    this->diff = diff;
    this->visc = visc;

    this->InitArr(this->px, SIZE_X * SIZE_Y);
    this->InitArr(this->py, SIZE_X * SIZE_Y);
    this->InitArr(this->x, SIZE_X * SIZE_Y);
    this->InitArr(this->y, SIZE_X * SIZE_Y);
    this->InitArr(this->previousDensity, SIZE_X * SIZE_Y);
    this->InitArr(this->density, SIZE_X * SIZE_Y);
}

Container::~Container() {}

void Container::InitArr(float arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
}

void Container::AddDensity(float x, float y, float amount)
{
    this->density[IX(x, y, this->size_x, this->size_y)] += amount;
}

void Container::AddVelocity(float x, float y, float px, float py)
{
    int index = IX(x, y, this->size_x, this->size_y);

    this->x[index] += px;
    this->y[index] += py;
}

void Container::Step()
{
    // these all need changing
    this->physics.Diffuse(1, this->px, this->x, this->visc, this->dt, 16, this->size_x, this->size_y);
    this->physics.Diffuse(2, this->py, this->y, this->visc, this->dt, 16, this->size_x, this->size_y);

    this->physics.Project(this->px, this->py, this->x, this->y, 16, this->size_x, this->size_y);

    this->physics.Advect(1, this->x, this->px, this->px, this->py, this->dt, this->size_x, this->size_y);
    this->physics.Advect(2, this->y, this->py, this->px, this->py, this->dt, this->size_x, this->size_y);

    this->physics.Project(this->x, this->y, this->px, this->py, 16, this->size_x, this->size_y);

    this->physics.Diffuse(0, this->previousDensity, this->density, this->diff, this->dt, 16, this->size_x, this->size_y);
    this->physics.Advect(0, this->density, this->previousDensity, this->x, this->y, this->dt, this->size_x, this->size_y);
}

sf::Color Container::Hsv(int hue, float sat, float val, float d)
{
    hue %= 360;
    while (hue < 0)
        hue += 360;

    if (sat < 0.f)
        sat = 0.f;
    if (sat > 1.f)
        sat = 1.f;

    if (val < 0.f)
        val = 0.f;
    if (val > 1.f)
        val = 1.f;

    int h = hue / 60;
    float f = float(hue) / 60 - h;
    float p = val * (1.f - sat);
    float q = val * (1.f - sat * f);
    float t = val * (1.f - sat * (1 - f));

    switch (h)
    {
    default:
    case 0:
    case 6:
        return sf::Color(val * 255, t * 255, p * 255, d);
    case 1:
        return sf::Color(q * 255, val * 255, p * 255, d);
    case 2:
        return sf::Color(p * 255, val * 255, t * 255, d);
    case 3:
        return sf::Color(p * 255, q * 255, val * 255, d);
    case 4:
        return sf::Color(t * 255, p * 255, val * 255, d);
    case 5:
        return sf::Color(val * 255, p * 255, q * 255, d);
    }
}

float Container::MapToRange(float val, float minIn, float maxIn, float minOut, float maxOut)
{
    float x = (val - minIn) / (maxIn - minIn);
    float result = minOut + (maxOut - minOut) * x;
    return (result < minOut) ? minOut : (result > maxOut) ? maxOut
                                                          : result;
}

void Container::Render(sf::RenderWindow &win, Color color)
{
    win.clear();
    for (int i = 0; i < this->size_x; i++)
    {
        for (int j = 0; j < this->size_y; j++)
        {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(SCALE, SCALE));
            rect.setPosition(j * SCALE, i * SCALE);

            switch (color)
            {
            case Color::Default:
                rect.setFillColor(sf::Color(255, 255, 255, (this->density[IX(i, j, this->size_x, this->size_y)] > 255) ? 255 : this->density[IX(i, j, this->size_x, this->size_y)]));
                break;
            case Color::Hsb:
                rect.setFillColor(this->Hsv((this->density[IX(i, j, this->size_x, this->size_y)]), 1, 1, 255));
                break;
            case Color::Velocity:
            {
                int r = (int)this->MapToRange(this->x[IX(i, j, this->size_x, this->size_y)], -0.05f, 0.05f, 0, 255);
                int g = (int)this->MapToRange(this->y[IX(i, j, this->size_x, this->size_y)], -0.05f, 0.05f, 0, 255);
                rect.setFillColor(sf::Color(r, g, 255));
                break;
            }
            default:
                break;
            };

            win.draw(rect);
        }
    }
}

void Container::FadeDensity(int size)
{
    for (int i = 0; i < size; i++)
    {
        float d = this->density[i];
        density[i] = (d - 0.05f < 0) ? 0 : d - 0.05f;
    }
}

int Container::GetSizeX()
{
    return size_x;
}

int Container::GetSizeY()
{
    return size_y;
}

// Function to return a pointer to the density array
float *Container::GetDensityPointer()
{
    return density;
}
