#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "./physics.h"
#include "./const.h"
#include "./options.h"

class Container
{
private:
    Physics physics;

    int size_x;
    int size_y;

    float dt;
    float diff;
    float visc;

    float px[SIZE_X * SIZE_Y];
    float py[SIZE_X * SIZE_Y];

    float x[SIZE_X * SIZE_Y];
    float y[SIZE_X * SIZE_Y];

    float previousDensity[SIZE_X * SIZE_Y];
    float density[SIZE_X * SIZE_Y];

    void InitArr(float arr[], int size);
    float MapToRange(float value, float minIn, float maxIn, float minOut, float maxOut);

public:
    Container();
    Container(float dt, float diff, float visc);
    ~Container();

    void AddDensity(float x, float y, float amount);
    void AddVelocity(float x, float y, float px, float py);
    void Step();
    void Render(sf::RenderWindow &win, Color color);
    void FadeDensity(int size);

    int GetSizeX();
    int GetSizeY();
    float *GetDensityPointer();

    sf::Color Hsv(int hue, float sat, float val, float d);
};

#endif
