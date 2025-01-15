#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <vector>
using std::vector;
// wall thickness for closed test areas (we use a relative big value to avoid wall clipping dui to fast moving bodies)
constexpr float thickness = 10.0f;
constexpr float haulf_thickness = thickness / 2.0f;
namespace rp3d = reactphysics3d;
/**
 * Create a closed test area, a box made up of 6 boxes, one for each wall.
 *
 * @param position The xz center of the box and the box ground top.
 * @param size The internal size of the box.
 * @param world The ReactPhysics3D physics world.
 * @param engine The PhysicsCommon object.
 *
 * @return A pointer to the body that was created.
 */
rp3d::RigidBody *CreateClosedTestArea(const rp3d::Vector3 &position, const rp3d::Vector3 &size, rp3d::PhysicsWorld *world, rp3d::PhysicsCommon &engine);
/**
 * Fill an area with bodies without shapes by default.
 *
 * @param position The starting position for the bodies. (Bodies are created to the right, up, and forward of this position, using a left-handed system.)
 * @param dist The distance between each body along each axis.
 * @param x_num The number of bodies along the x-axis.
 * @param y_num The number of bodies along the y-axis.
 * @param z_num The number of bodies along the z-axis.
 * @param world The ReactPhysics3D physics world.
 *
 * @return A vector containing pointers to all created bodies.
 */
vector<rp3d::RigidBody *> FillWithBodies(const rp3d::Vector3 &position, const rp3d::Vector3 &dist, int x_num, int y_num, int z_num, rp3d::PhysicsWorld *world);
/**
 * Add sphere colliders to a vector of bodies.
 *
 * @param bodies A vector containing pointers to the bodies.
 * @param radius The radius of the spheres.
 * @param engine The PhysicsCommon object.
 */
void set_to_sphere(const vector<rp3d::RigidBody *> &bodies, float radius, rp3d::PhysicsCommon &engine);