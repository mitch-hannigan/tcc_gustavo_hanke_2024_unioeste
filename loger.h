#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <string>
#include <vector>
namespace rp3d = reactphysics3d;
class loger
{
    std::vector<std::string> log;

public:
    void write();
    void add_iteraction(std::vector<rp3d::RigidBody *> &bodies);
};