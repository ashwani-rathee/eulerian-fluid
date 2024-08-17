#include <iostream>
// #include <fluid3dsim.h>
#include <sys/time.h>
#include <const.h>
#include <simulatorsmoke.h>
#include <smokesim.h>
#include <macgrid.h>
#include <memory>
#define FINISH_TIME 100

int main()
{
    
    Fluid3DSimSmoke sim;
    sim.Run();
    // Fluid3DSim sim;
    // sim.Run();

    // double time = 0.0;
    // int step = 1;
    // std::shared_ptr<MACGrid> grids = std::make_shared<MACGrid>();
    // std::unique_ptr<Simulator> simulator = std::make_unique<Simulator>(grids, time);
    // printf("\n*** SIMULATION START ***\n");
    // struct timeval s, e;

    // while (true)
    // {
    //     printf("\n=== STEP %d ===\n", step);
    //     time += DT;
    //     gettimeofday(&s, NULL);
    //     simulator->update();
    //     gettimeofday(&e, NULL);
    //     printf("time = %lf\n", (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec) * 1.0E-6);

    //     ++step;

    //     if (step >= FINISH_TIME)
    //     {
    //         break;
    //     }
    // }

    // printf("\n*** SIMULATION END ***\n");
    return 0;
}
