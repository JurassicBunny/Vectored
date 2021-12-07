#pragma once

#include <Eigen/Dense>

namespace Internal {
class Vectored : public Eigen::Vector3d {
public:
    Vectored();
    Vectored(double x, double y, double z);
};

}

#define VECTORED(name) \
class name : public Internal::Vectored { \
public:                \
    using Internal::Vectored::Vectored;   \
}

namespace Vectored {
    VECTORED(Acceleration);
    VECTORED(Force);
    VECTORED(Momentum);
    VECTORED(Position);
    VECTORED(Velocity);
}
