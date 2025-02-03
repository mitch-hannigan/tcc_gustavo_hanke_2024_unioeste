#include <reactphysics3d/reactphysics3d.h>
#include <vector>
#include <iostream>
#include "loger.h"
#include "utils.h"
#define ticks_per_second (480.0f)
#define tick_period (1.0f / (ticks_per_second))
// helper macro for simulation time control
#define ticks_to_simulate(time) (ceil((time) / (tick_period)))
namespace rp3d = reactphysics3d;
std::vector<rp3d::RigidBody *> bodies;
loger *l;
rp3d::decimal time_step = tick_period;
void run_simulation(rp3d::PhysicsWorld *w, rp3d::decimal simulate_time)
{
    int ticks = ticks_to_simulate(simulate_time);
    for (int t = 0; t < ticks; t++)
    {
        w->update(tick_period);
        if (l)
            l->add_iteraction(bodies);
    }
    std::cout << "done, I have just run " << ticks << " ticks." << std::endl;
}
int main(int argc, char *argv[])
{
    if (argc == 1)
        l = new loger;
    else
        l = new loger(argv[1]);
    // engine initialization.
    rp3d::PhysicsCommon engine;
    rp3d::PhysicsWorld *w = engine.createPhysicsWorld();
    // first part initialization, constant motion with colisions spheres plus free fall, the motion is started by colisions
    auto area1 = CreateClosedTestArea({-4500, 0, 0}, {1000, 150000, 1000}, w, engine);
    area1->setType(rp3d::BodyType::KINEMATIC);
    area1->setLinearVelocity({0.0f, 0.0f, 40.0f});
    auto bodies1 = FillWithBodies({-4980, 50000, -480}, {40, 40, 40}, 50, 1, 50, w);
    set_to_sphere(bodies1, 15, engine);
    // second part initialization, bodies resting on the floor.
    auto area2 = CreateClosedTestArea({-2500, 0, 0}, {1000, 150000, 1000}, w, engine);
    auto bodies2 = FillWithBodies({-2980, 10, -480}, {40, 40, 40}, 50, 1, 50, w);
    set_to_sphere(bodies2, 10, engine); // the spheres don't colide with each other, only with the floor.
    // third part initialization, bodies resting on boxes resting on the floor
    auto area3 = CreateClosedTestArea({-500, 0, 0}, {1000, 150000, 1000}, w, engine);
    auto bodies3_1 = FillWithBodies({-980, 15, -480}, {40, 40, 40}, 50, 1, 50, w);
    set_to_box(bodies3_1, {15, 15, 15}, engine); // the boxes don't colide with each other, only with the spheres and the ground.
    auto bodies3_2 = FillWithBodies({-980, 40, -480}, {40, 40, 40}, 50, 1, 50, w);
    set_to_sphere(bodies3_2, 10, engine); // the spheres don't colide with each other, only with the boxes.
    bodies.insert(bodies.end(), bodies1.begin(), bodies1.end());
    bodies.insert(bodies.end(), bodies2.begin(), bodies2.end());
    bodies.insert(bodies.end(), bodies3_1.begin(), bodies3_1.end());
    bodies.insert(bodies.end(), bodies3_2.begin(), bodies3_2.end());
    std::cout << "I have created " << bodies.size() << " bodies" << std::endl;
    run_simulation(w, 100);
    l->write();
    delete l;
    std::cout << "sizeof: " << sizeof(rp3d::decimal) << std::endl;
}