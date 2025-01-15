#include "loger.h"
#include <sstream>
void loger::write()
{
    for (auto &line : log)
    {
        std::cout << line << std::endl;
    }
}
void loger::add_iteraction(std::vector<rp3d::RigidBody *> &bodies)
{
    std::stringstream str;
    //str.precision(6);
    for (auto &body : bodies)
    {
        rp3d::Vector3 p = body->getTransform().getPosition();
        str << p.x << "\t" << p.y << "\t" << p.z << "\t";
    }
    log.push_back(str.str());
}