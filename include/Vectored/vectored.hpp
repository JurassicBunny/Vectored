#pragma once

#include <Eigen/Dense>
#include <concepts>
#include <type_traits>

namespace Vectored {

namespace Internal {

class SuperVectored : public Eigen::Vector3d {
public:
    SuperVectored()
        : Eigen::Vector3d() { }

    SuperVectored(double x, double y, double z)
        : Eigen::Vector3d(x, y, z) { }

    explicit SuperVectored(Eigen::Vector3d vector)
        : Eigen::Vector3d(std::move(vector)) { }

    Eigen::Vector3d as_vec() {
        return Eigen::Vector3d { this->x(), this->y(), this->z() };
    }

    template<typename T>
    requires(std::is_base_of_v<SuperVectored, T>) explicit SuperVectored(
        T& vector)
        : Eigen::Vector3d(vector.as_vec()) { }

    template<typename T>
    requires(std::is_base_of_v<SuperVectored, T>) T as() {
        T result(*this);
        return result;
    }
};

template<typename Class>
concept VectoredQuantity = std::is_base_of<SuperVectored, Class>::value;

} // namespace Internal

} // namespace Vectored

#define VECTORED(name)                                          \
    class name : public Vectored::Internal::SuperVectored {     \
    public:                                                     \
        using Vectored::Internal::SuperVectored::SuperVectored; \
                                                                \
        template<Vectored::Internal::VectoredQuantity T>        \
        name operator+(T& other) {                              \
            name result(this->as_vec() += other.as_vec());      \
            return result;                                      \
        }                                                       \
                                                                \
        template<Vectored::Internal::VectoredQuantity T>        \
        name operator-(T& other) {                              \
            name result(this->as_vec() -= other.as_vec());      \
            return result;                                      \
        }                                                       \
    }

namespace Vectored {
VECTORED(Acceleration);
VECTORED(Force);
VECTORED(Momentum);
VECTORED(Position);
VECTORED(Velocity);
} // namespace Vectored
