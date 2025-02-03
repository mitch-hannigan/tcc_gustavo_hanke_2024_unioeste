#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <vector>
namespace rp3d = reactphysics3d;
class loger
{
    std::vector<char> log;
    const char *filename;

public:
    loger(const char *filename = nullptr);
    void write();
    void add_iteraction(std::vector<rp3d::RigidBody *> &bodies);
    operator bool() const { return filename != nullptr; }
};