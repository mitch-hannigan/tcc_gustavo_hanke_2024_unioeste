#include <reactphysics3d/reactphysics3d.h>
#include <vector>
#include <iostream>
// test area information
#define x_length 2000.0f
#define y_length 150000.0f
#define z_length 2000.0f
#define thickness 10.0f
#define ticks_per_second (480.0f)
#define tick_period (1.0f / (ticks_per_second))
// helper macro for simulation time control
#define ticks_to_simulate(time) ((time) / (tick_period))
#define x_bodys 50
#define z_bodys x_bodys
namespace rp3d = reactphysics3d;
rp3d::decimal time_step = 1.0f / ticks_per_second;
rp3d::RigidBody *create_test_area(rp3d::PhysicsCommon &engine, rp3d::PhysicsWorld *w)
{
    rp3d::Transform ground_body_transform = rp3d::Transform::identity();
    rp3d::RigidBody *ground = w->createRigidBody(ground_body_transform);
    ground->setType(rp3d::BodyType::STATIC);
    rp3d::BoxShape *ceiling_ground_shape = engine.createBoxShape(rp3d::Vector3(x_length / 2, thickness / 2, z_length / 2));
    rp3d::Transform ground_shape_transform(rp3d::Vector3(0, -(thickness / 2), 0), rp3d::Quaternion::identity());
    ground->addCollider(ceiling_ground_shape, ground_shape_transform);
    rp3d::Transform ceiling_shape_transform(rp3d::Vector3(0, y_length + (thickness / 2), 0), rp3d::Quaternion::identity());
    ground->addCollider(ceiling_ground_shape, ceiling_shape_transform);
    rp3d::BoxShape *left_right_shape = engine.createBoxShape(rp3d::Vector3(thickness / 2, y_length / 2, z_length / 2));
    rp3d::Transform left_shape_transform(rp3d::Vector3(-(x_length + thickness) / 2, 0, 0), rp3d::Quaternion::identity());
    ground->addCollider(left_right_shape, left_shape_transform);
    rp3d::Transform right_shape_transform(rp3d::Vector3((x_length + thickness) / 2, 0, 0), rp3d::Quaternion::identity());
    ground->addCollider(left_right_shape, right_shape_transform);
    rp3d::BoxShape *front_back_shape = engine.createBoxShape(rp3d::Vector3(x_length / 2, y_length / 2, thickness / 2));
    rp3d::Transform front_shape_transform(rp3d::Vector3(0, 0, (z_length + thickness) / 2), rp3d::Quaternion::identity());
    ground->addCollider(front_back_shape, front_shape_transform);
    rp3d::Transform back_shape_transform(rp3d::Vector3(0, 0, -(z_length + thickness) / 2), rp3d::Quaternion::identity());
    ground->addCollider(front_back_shape, back_shape_transform);
    return ground;
}
std::vector<rp3d::RigidBody *> create_bodys_to_simulate(rp3d::PhysicsCommon &engine, rp3d::PhysicsWorld *w)
{
    std::vector<rp3d::RigidBody *> bodys;
    rp3d::decimal body_size = std::min(x_length / x_bodys, z_length / z_bodys);
    int body_count = 0;
    rp3d::SphereShape *body_shape = engine.createSphereShape(body_size / 2);
    rp3d::decimal y = y_length - body_size / 2;
    rp3d::Transform shape_transform = rp3d::Transform::identity();
    for (rp3d::decimal z = -(z_length - body_size) / 2; z <= (z_length - body_size) / 2; z += body_size)
    {
        for (rp3d::decimal x = -(x_length - body_size) / 2; x <= (x_length - body_size) / 2; x += body_size)
        {
            rp3d::RigidBody *body = w->createRigidBody(rp3d::Transform(rp3d::Vector3(x, y, z), rp3d::Quaternion::identity()));
            body->addCollider(body_shape, shape_transform);
            bodys.push_back(body);
            body_count++;
        }
    }
    std::cout << "I have just created " << body_count << "bodys" << std::endl;
    return bodys;
}
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
    rp3d::PhysicsCommon engine;
    rp3d::PhysicsWorld *w = engine.createPhysicsWorld();
    create_test_area(engine, w);
    auto bodys = create_bodys_to_simulate(engine, w);
    run_simulation(w, 100);
    std::cout << "this is the final position of the first created body: (" << bodys[0]->getTransform().getPosition()[0] << ", " << bodys[0]->getTransform().getPosition()[1] << ", " << bodys[0]->getTransform().getPosition()[2] << ").\n";
}