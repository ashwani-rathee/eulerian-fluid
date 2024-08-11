#ifndef OPTIONS_H
#define OPTIONS_H

#include "./color.h"

class Options
{
private:
    Color color;

public:
    Options(Color color = Color::Default);
    ~Options();

    Color GetColor();
    void SetColor(Color c);
};

#endif
