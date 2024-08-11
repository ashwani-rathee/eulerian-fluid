#ifndef CONST_H
#define CONST_H

const int SIZE = 70;
const int SCALE = 8;

const int LOOP_DELAY = 0;

enum EXAMPLE_TYPE {
	TWO_FLUID = 0,
	ONE_FLUID_BASIC_CORNER = 1,
	ONE_FLUID_BASIC_CENTER_ALLDIR = 2,
    ORIGINAL_FLUID = 3,
};

const EXAMPLE_TYPE exampleType = ORIGINAL_FLUID;

#endif
