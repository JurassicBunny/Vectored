#include "library.h"

 namespace Internal {

Vectored::Vectored()
    : Eigen::Vector3d() {}

Vectored::Vectored(double x, double y, double z)
    : Eigen::Vector3d(x, y, z) {}
 }