#include <reactphysics3d/reactphysics3d.h>
#include <iostream>
using reactphysics3d::Vector3;
int main()
{
    Vector3 v1(10, 10, 10);
    Vector3 v2(1.0, 0.0f, 0.0f), v3(0.0, 1.0, 0.0);
    std::cout << v1.lengthSquare() << std::endl;
    std::cout << v1.length() << std::endl;
    std::cout << v1.getUnit().to_string() << std::endl;
    std::cout << v1.getUnit().dot(v1.getUnit()) << std::endl;
    std::cout << v2.cross(v3).to_string() << std::endl;
    v1.setAllValues(-666, -665, -664);
    std::cout << v1.to_string() << std::endl;
    std::cout << v1.getAbsoluteVector().to_string() << std::endl;
    std::cout << (v1 == v2 ? "yes" : "no") << std::endl;
    std::cout << (2*v1).to_string() << std::endl;
}