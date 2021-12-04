#ifndef VECTORED_H
#define VECTORED_H

#include <Eigen/Dense>

namespace Internal {

class Vectored : public Eigen::Vector3d {
public:
    Vectored();
    Vectored(double x, double y, double z);
};

} // Internal

namespace Vectored {

#define VECTORED(name) \
class name : public Internal::Vectored { \
public:                \
    using Internal::Vectored::Vectored;\
} \

} // Vectored

using namespace Vectored;

#endif