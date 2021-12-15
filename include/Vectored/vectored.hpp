#pragma once

#include <Eigen/Dense>
#include <concepts>
#include <type_traits>

namespace Vectored {

namespace Internal {

class SuperVectored : public Eigen::Vector3d {
public:
    SuperVectored()
        : Eigen::Vector3d()
    {
    }

    SuperVectored(double x, double y, double z)
        : Eigen::Vector3d(x, y, z)
    {
    }

    explicit SuperVectored(Eigen::Vector3d vector)
        : Eigen::Vector3d(std::move(vector))
    {
    }

    Eigen::Vector3d as_vec()
    {
        return Eigen::Vector3d { this->x(), this->y(), this->z() };
    }

    template<typename T>
        requires(std::is_base_of_v<SuperVectored, T>)
    explicit SuperVectored(
        T& vector)
        : Eigen::Vector3d(vector.as_vec())
    {
    }

    template<typename T>
        requires(std::is_base_of_v<SuperVectored, T>)
    T as()
    {
        T result(*this);
        return result;
    }
};

class SuperScalar {
private:
    double m_scalar;

public:
    SuperScalar()
        : m_scalar(0)
    {
    }

    explicit SuperScalar(double value)
        : m_scalar(value)
    {
    }

    double as_value()
    {
        return this->m_scalar;
    }
};

template<typename Class>
concept VectoredQuantity = std::is_base_of<SuperVectored, Class>::value;

template<typename Class>
concept ScalarQuantity = std::is_base_of<SuperScalar, Class>::value;

} // namespace Internal

} // namespace Vectored

#define VECTORED(name)                                          \
    class name : public Vectored::Internal::SuperVectored {     \
    public:                                                     \
        using Vectored::Internal::SuperVectored::SuperVectored; \
                                                                \
        template<Vectored::Internal::VectoredQuantity T>        \
        name operator+(T& other)                                \
        {                                                       \
            name result(this->as_vec() += other.as_vec());      \
            return result;                                      \
        }                                                       \
                                                                \
        template<Vectored::Internal::VectoredQuantity T>        \
        name operator-(T& other)                                \
        {                                                       \
            name result(this->as_vec() -= other.as_vec());      \
            return result;                                      \
        }                                                       \
                                                                \
        template<Vectored::Internal::ScalarQuantity T>          \
        name operator*(T& other)                                \
        {                                                       \
            name result(this->as_vec() * other.as_value());     \
            return result;                                      \
        }                                                       \
    }

#define SCALAR(name)                                          \
    class name : public Vectored::Internal::SuperScalar {     \
    public:                                                   \
        using Vectored::Internal::SuperScalar::SuperScalar;   \
                                                              \
        template<Vectored::Internal::ScalarQuantity T>        \
        name operator+(T& other)                              \
        {                                                     \
            name result(this->as_value() + other.as_value()); \
            return result;                                    \
        }                                                     \
                                                              \
        template<Vectored::Internal::ScalarQuantity T>        \
        name operator-(T& other)                              \
        {                                                     \
            name result(this->as_value() - other.as_value()); \
            return result;                                    \
        }                                                     \
                                                              \
        template<typename T>                                  \
        name operator*(T other)                               \
        {                                                     \
            name result(this->as_value() * other);            \
            return result;                                    \
        }                                                     \
                                                              \
        template<Vectored::Internal::VectoredQuantity T>      \
        T operator*(T& other)                                 \
        {                                                     \
            T result(this->as_value() * other.as_vec());      \
            return result;                                    \
        }                                                     \
                                                              \
        template<Vectored::Internal::ScalarQuantity T>        \
        name operator*(T& other)                              \
        {                                                     \
            name result(this->as_value() * other.as_value()); \
            return result;                                    \
        }                                                     \
                                                              \
        template<Vectored::Internal::ScalarQuantity T>        \
        name operator/(T& other)                              \
        {                                                     \
            name result(this->as_value() / other.as_value()); \
            return result;                                    \
        }                                                     \
    }

namespace Vectored {
VECTORED(Acceleration);
VECTORED(Force);
VECTORED(Momentum);
VECTORED(Position);
VECTORED(Velocity);
} // namespace Vectored

namespace Scalar {
SCALAR(Time);
SCALAR(Mass);
}
