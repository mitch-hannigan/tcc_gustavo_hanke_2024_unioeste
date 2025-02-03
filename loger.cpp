#include "loger.h"
#include <stdio.h>
loger::loger(const char *filename) : filename(filename)
{
}
void loger::write()
{
    if (filename)
    {
        FILE *f = fopen64(filename, "w");
        fwrite(log.data(), 1, log.size(), f);
        fclose(f);
    }
}
void loger::add_iteraction(std::vector<rp3d::RigidBody *> &bodies)
{
    log.reserve(log.size() + sizeof(rp3d::decimal) * 7); // 7 elementos numericos
    for (auto &body : bodies)
    {
        rp3d::Vector3 p = body->getTransform().getPosition();
        rp3d::Quaternion o = body->getTransform().getOrientation();
        for (int i = 0; i < sizeof(p); i++)
            log.push_back(((char *)(&p))[i]);
        for (int i = 0; i < sizeof(o); i++)
            log.push_back(((char *)(&o))[i]);
    }
}