#pragma once

#include <Eigen/Dense>

namespace Internal {
class Vectored : public Eigen::Vector3d {
public:
    Vectored();
    Vectored(double x, double y, double z);
};
}
