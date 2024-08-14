#ifndef CONST_H
#define CONST_H

const int SIZE_X = 50;
const int SIZE_Y = 50;
const int SCALE = 20;

const int LOOP_DELAY = 0;

enum EXAMPLE_TYPE
{
    TWO_FLUID = 0,
    ONE_FLUID_BASIC_CORNER = 1,
    ONE_FLUID_BASIC_CENTER_ALLDIR = 2,
    ORIGINAL_FLUID = 3,
};

const int N = 50;

const EXAMPLE_TYPE exampleType = ONE_FLUID_BASIC_CORNER;

#endif
