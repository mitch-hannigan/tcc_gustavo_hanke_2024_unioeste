#include "utils.h"
rp3d::RigidBody *CreateClosedTestArea(const rp3d::Vector3 &position, const rp3d::Vector3 &size, rp3d::PhysicsWorld *world, rp3d::PhysicsCommon &engine)
{
    auto haulfSize = size / 2.0;
    rp3d::Transform transform(position, rp3d::Quaternion::identity());
    rp3d::RigidBody *final = world->createRigidBody(transform);
    rp3d::BoxShape *ceiling_ground_shape = engine.createBoxShape(rp3d::Vector3(haulfSize.x, haulf_thickness, haulfSize.z));
    rp3d::BoxShape *left_right_shape = engine.createBoxShape(rp3d::Vector3(haulf_thickness, haulfSize.y, haulfSize.z));
    rp3d::BoxShape *front_back_shape = engine.createBoxShape(rp3d::Vector3(haulfSize.x, haulfSize.y, haulf_thickness));
    rp3d::Transform ground_shape_transform(rp3d::Vector3(0, -haulf_thickness, 0), rp3d::Quaternion::identity());
    rp3d::Transform ceiling_shape_transform(rp3d::Vector3(0, size.y + (haulf_thickness), 0), rp3d::Quaternion::identity());
    rp3d::Transform left_shape_transform(rp3d::Vector3(-(haulfSize.x + haulf_thickness), 0, 0), rp3d::Quaternion::identity());
    rp3d::Transform right_shape_transform(rp3d::Vector3(haulfSize.x + haulf_thickness, 0, 0), rp3d::Quaternion::identity());
    rp3d::Transform front_shape_transform(rp3d::Vector3(0, 0, (haulfSize.z + haulf_thickness)), rp3d::Quaternion::identity());
    rp3d::Transform back_shape_transform(rp3d::Vector3(0, 0, -(haulfSize.z + haulf_thickness)), rp3d::Quaternion::identity());
    final->addCollider(ceiling_ground_shape, ground_shape_transform);
    final->addCollider(ceiling_ground_shape, ceiling_shape_transform);
    final->addCollider(left_right_shape, left_shape_transform);
    final->addCollider(left_right_shape, right_shape_transform);
    final->addCollider(front_back_shape, front_shape_transform);
    final->addCollider(front_back_shape, back_shape_transform);
    final->setType(rp3d::BodyType::STATIC);
    return final;
}
vector<rp3d::RigidBody *> FillWithbodis(const rp3d::Vector3 &position, const rp3d::Vector3 &dist, int x_num, int y_num, int z_num, rp3d::PhysicsWorld *world)
{
    vector<rp3d::RigidBody *> final;
    final.reserve(x_num * y_num * z_num);
    int i, j, k;
    rp3d::Transform transform(position, rp3d::Quaternion::identity());
    for (i = 0; i < x_num; i++)
    {
        for (j = 0; j < y_num; j++)
        {
            for (k = 0; k < z_num; k++)
            {
                transform.setPosition(position + rp3d::Vector3(i * dist.x, j * dist.y, k * dist.z));
                final.emplace_back(world->createRigidBody(transform));
            }
        }
    }
    return final;
}
void set_to_sphere(const vector<rp3d::RigidBody *> &bodis, float radius, rp3d::PhysicsCommon &engine)
{
    rp3d::SphereShape *shape=engine.createSphereShape(radius);
    rp3d::Transform transform(rp3d::Vector3::zero(), rp3d::Quaternion::identity());
    for(auto &it: bodis)
    {
        it->addCollider(shape, transform);
    }
}