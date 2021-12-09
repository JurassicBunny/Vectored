#pragma once

#include <concepts>
#include <type_traits>

#include <Eigen/Dense>

namespace Vectored {

namespace Internal {

class SuperVectored : public Eigen::Vector3d {
public:
    SuperVectored()
            : Eigen::Vector3d() {}

    SuperVectored(double x, double y, double z)
            : Eigen::Vector3d(x, y, z) {}

    explicit SuperVectored(Eigen::Vector3d vector)
            : Eigen::Vector3d(std::move(vector)) {}

    Eigen::Vector3d as_vec() {
        return Eigen::Vector3d{this->x(),
                               this->y(),
                               this->z()};
    }

    template<typename T>
        requires(std::is_base_of_v<SuperVectored, T>)
    explicit SuperVectored(T &vector) { T result(*this); }

    template<typename T>
        requires(std::is_base_of_v<SuperVectored, T>)
    T as() {
        T result(*this);
        return result;
    }
};

template<typename Class>
concept VectoredQuantity =
    std::is_base_of<SuperVectored, Class>::value;

} // Internal

} // Vectored

#define VECTORED(name) \
class name : public Vectored::Internal::SuperVectored {     \
public:                \
    using Vectored::Internal::SuperVectored::SuperVectored; \
                       \
    template<Vectored::Internal::VectoredQuantity T>        \
    name operator+(T &other) { this -> as_vec() += other.as_vec(); return {}; } \
                       \
    template<Vectored::Internal::VectoredQuantity T>        \
    name operator-(T &other) { this -> as_vec() -= other.as_vec(); return {}; } \
}

namespace Vectored {
VECTORED(Acceleration);
VECTORED(Force);
VECTORED(Momentum);
VECTORED(Position);
VECTORED(Velocity);
}