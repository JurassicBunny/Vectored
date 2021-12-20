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
        requires(std::is_base_of<SuperVectored, T>::value)
    explicit SuperVectored(
        T& vector)
        : Eigen::Vector3d(vector.as_vec())
    {
    }

    template<typename T>
        requires(std::is_base_of<SuperVectored, T>::value)
    T as()
    {
        T result(*this);
        return result;
    }
};

template<typename Class>
concept VectoredQuantity = std::is_base_of<SuperVectored, Class>::value;

} // namespace Internal

} // namespace Vectored

namespace Scalar {

namespace Internal {

class SuperScalar {
private:
    double m_scalar;

public:
    SuperScalar()
        : m_scalar(0)
    {
    }

    SuperScalar(double value)
        : m_scalar(value)
    {
    }

    double as_value()
    {
        return this->m_scalar;
    }
};

template<typename Class>
concept ScalarQuantity = std::is_base_of<SuperScalar, Class>::value;

} // namespace Internal

} // namespace Scalar

#define VECTORED(name)                                          \
    class name : public Vectored::Internal::SuperVectored {     \
    public:                                                     \
        using Vectored::Internal::SuperVectored::SuperVectored; \
    }

#define SCALAR(name)                                      \
    class name : public Scalar::Internal::SuperScalar {   \
    public:                                               \
        using Scalar::Internal::SuperScalar::SuperScalar; \
    }

namespace Scalar {

namespace Internal {

template<typename T, ScalarQuantity U>
U operator+(T fst, U& other)
{
    U result(fst + other.as_value());
    return result;
}

template<ScalarQuantity T, typename U>
T operator+(T& fst, U other)
{
    T result(fst.as_value() + other);
    return result;
}

template<ScalarQuantity T, ScalarQuantity U>
U operator+(T& fst, U& other)
{
    U result(fst.as_value() + other.as_value());
    return result;
}

template<typename T, ScalarQuantity U>
T operator-(T fst, U& other)
{
    T result(fst - other.as_value());
    return result;
}

template<ScalarQuantity T, typename U>
T operator-(T fst, U other)
{
    T result(fst.as_value() - other);
    return result;
}

template<ScalarQuantity T, ScalarQuantity U>
T operator-(T& fst, U& other)
{
    T result(fst.as_value() - other.as_value());
    return result;
}

template<typename T, ScalarQuantity U>
T operator*(T fst, U& other)
{
    T result(fst * other.as_value());
    return result;
}

template<ScalarQuantity T, typename U>
U operator*(T& fst, U other)
{
    U result(fst.as_value() * other);
    return result;
}

template<ScalarQuantity T, ScalarQuantity U>
T operator*(T& fst, U& other)
{
    T result(fst.as_value() * other.as_value());
    return result;
}

template<ScalarQuantity T, Vectored::Internal::VectoredQuantity U>
U operator*(T& fst, U& other)
{
    U result(fst.as_value() * other.as_vec());
    return result;
}

template<typename T, ScalarQuantity U>
U operator/(T fst, U& other)
{
    U result(fst * other.as_value());
    return result;
}

template<ScalarQuantity T, typename U>
T operator/(T& fst, U other)
{
    T result(fst.as_value() * other);
    return result;
}

template<ScalarQuantity T, ScalarQuantity U>
T operator/(T& fst, U& other)
{
    T result(fst.as_value() * other.as_value());
    return result;
}

} // namespace Scalar

} // namespace Vectored

namespace Vectored {

namespace Internal {

template<VectoredQuantity T, VectoredQuantity U>
T operator+(T& fst, U& other)
{
    T result(fst.as_vec() + other.as_vec());
    return result;
}

template<VectoredQuantity T, VectoredQuantity U>
T operator-(T& fst, U& other)
{
    T result(fst.as_vec() * other.as_vec());
    return result;
}

template<typename T, VectoredQuantity U>
U operator*(T fst, U& other)
{
    U result(fst * other.as_vec());
    return result;
}

template<VectoredQuantity T, typename U>
T operator*(T& fst, U other)
{
    T result(fst.as_vec() * other);
    return result;
}

template<VectoredQuantity T, Scalar::Internal::ScalarQuantity U>
T operator*(T& fst, U& other)
{
    T result(fst.as_vec() * other.as_value());
    return result;
}

} // namespace Internal
} // namespace Vectored

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
} // namespace Scalar

int main()
{
    using namespace Vectored;
    using namespace Scalar;

    Acceleration acceleartion(1, 2, 3);
    Mass mass(1.0);
    Time time(1e-9);

    Time result = 1.0 - time;
    auto result1 = time - 1.0;
    Time result2 = time - time;
    Time result3 = time / time;
    auto result4 = time / mass;
    auto result5 = mass * acceleartion;
}
