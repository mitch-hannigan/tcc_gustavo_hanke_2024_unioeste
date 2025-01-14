#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <vector>
using std::vector;
// wall thickness for closed test areas (we use a relative big value to avoid wall clipping dui to fast moving bodys)
constexpr float thickness = 10.0f;
constexpr float haulf_thickness = thickness/2.0f;
namespace rp3d = reactphysics3d;
/*
create a closed test area, a box made up of 6 boxes, one for each wall.
parameters:
position: the box's center is put at that position
size: box size, internal size, not counting the walls, add thickness*2 for each axis (not haulf size).
world: the react physics world
engine: the PhysicsCommon object.
Return value:
A pointer to the body that was created.
*/
rp3d::RigidBody *CreatClosedTestArea(const rp3d::Vector3 &position, const rp3d::Vector3 &size, rp3d::PhysicsWorld *world, rp3d::PhysicsCommon &engine);
/*
fill one layer with bodys, no shape by default.
parameters:
position:
size:
y:
return value:
*/