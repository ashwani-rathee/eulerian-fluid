#ifndef CONST_H
#define CONST_H

#include <cassert>

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

enum E_METHOD
{
    E_LINEAR = 0,
    E_MONOTONIC_CUBIC = 1
};

enum E_ADVECTION
{
    E_SEMI_LAGRANGE = 0,
    E_MAC_CORMACK = 1
};

enum E_EMITTER_POS
{
    E_TOP = 0,
    E_BOTTOM = 1
};

// constexpr int N = 32;
constexpr int ratio[3] = {1, 1, 1}; // X, Y, Z
constexpr E_METHOD INTERPOLATION_METHOD = E_MONOTONIC_CUBIC;
constexpr E_ADVECTION ADVECTION_METHOD = E_MAC_CORMACK;
constexpr E_EMITTER_POS EMITTER_POS = E_BOTTOM;
constexpr bool OFFSCREEN_MODE = false;

constexpr int Nx = ratio[0] * N, Ny = ratio[1] * N, Nz = ratio[2] * N;
constexpr int SOURCE_SIZE_X = (int)(Nx / 4);
constexpr int SOURCE_SIZE_Y = (int)(Ny / 20);
constexpr int SOURCE_SIZE_Z = (int)(Nz / 4);
constexpr int SOURCE_Y_MERGIN = (int)(Ny / 20);
constexpr int SIZE = Nx * Ny * Nz;

constexpr double DT = 0.02;
constexpr double VOXEL_SIZE = 1.0;
constexpr double INIT_DENSITY = 1.0;
constexpr double INIT_VELOCITY = 80.0;
constexpr double VORT_EPS = 0.25;
constexpr double ALPHA = 9.8;
constexpr double BETA = 15.0;
constexpr double T_AMP = 5.0;
constexpr double T_AMBIENT = 50.0;
constexpr double EMIT_DURATION = 2.0;
constexpr double FINISH_TIME = 6.0;

/* Scene Constants */
constexpr int WIN_WIDTH = 800;
constexpr int WIN_HEIGHT = 800;
static const char *WIN_TITLE = "Visual Simulation of Smoke";
constexpr float ABSORPTION = 5.0f;
constexpr bool SAVE_MOVIE = true;

#ifdef _OPENMP
#include <omp.h>
#define OPENMP_FOR _Pragma("omp parallel for")
#define OPENMP_FOR_COLLAPSE _Pragma("omp parallel for collapse(3)")
#else
#define OPENMP_FOR
#define OPENMP_FOR_COLLAPSE
#endif

#endif
