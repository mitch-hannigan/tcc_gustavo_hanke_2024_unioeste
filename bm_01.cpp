#include <reactphysics3d/reactphysics3d.h>
#include <vector>
#include <iostream>
#include "utils.h"
#define ticks_per_second (480.0f)
#define tick_period (1.0f / (ticks_per_second))
// helper macro for simulation time control
#define ticks_to_simulate(time) (ceil((time) / (tick_period)))
namespace rp3d = reactphysics3d;
rp3d::decimal time_step = tick_period;
void run_simulation(rp3d::PhysicsWorld *w, rp3d::decimal simulate_time)
{
    int ticks = ticks_to_simulate(simulate_time);
    for (int t = 0; t < ticks; t++)
    {
        w->update(tick_period);
    }
    std::cout << "done, I have just run " << ticks << " ticks." << std::endl;
}
int main()
{
    // engine initialization.
    rp3d::PhysicsCommon engine;
    rp3d::PhysicsWorld *w = engine.createPhysicsWorld();
    // first part initialization, constant motion with colisions spheres
    auto area1 = CreateClosedTestArea({-4500, 0, 0}, {1000, 150000, 1000}, w, engine);
    area1->setType(rp3d::BodyType::KINEMATIC);
    area1->setLinearVelocity({0.0f, 0.0f, 40.0f});
    auto bodis1 = FillWithbodis({-4980, 20, -480}, {40, 40, 40}, 50, 1, 50, w);
    set_to_sphere(bodis1, 20, engine);
    std::cout << "I have created " << bodis1.size() << " bodis" << std::endl;
    run_simulation(w, 50);
}