#pragma once

#include <concepts>
#include <type_traits>

#include <Eigen/Dense>

namespace Internal {
 class SuperVectored{
 protected:
     Eigen::Vector3d m_vector;
 public:
     SuperVectored()
         : m_vector(Eigen::Vector3d(0,0,0)) {}

     SuperVectored(double x, double y, double z)
         : m_vector(Eigen::Vector3d(x, y, z)) {};

     explicit SuperVectored(Eigen::Vector3d vector)
         : m_vector(std::move(vector)){}

     Eigen::Vector3d as_vec() { return  this -> m_vector; };

     template<typename T>
         requires (std::is_base_of_v<SuperVectored, T>)
     explicit SuperVectored( T &vector) { T result(this -> m_vector); }

     template<typename T>
        requires (std::is_base_of_v<SuperVectored, T>)
     T as() { T result(this->as_vec()); return result;}
 };

template <typename Class>
concept VectoredQuantity =
     std::is_base_of<SuperVectored, Class>::value;
} // Internal

#define VECTORED(name) \
class name : public Internal::SuperVectored { \
public:                \
    using Internal::SuperVectored::SuperVectored;  \
                       \
    template<Internal::VectoredQuantity T> \
    name operator+(T &vectored) { this -> m_vector += vectored.as_vec(); return *this;} \
                       \
    template<Internal::VectoredQuantity T>   \
    name operator-(T &vectored) { this -> m_vector -= vectored.as_vec(); return *this;}  \
}

namespace Vectored {
    VECTORED(Acceleration);
    VECTORED(Force);
    VECTORED(Momentum);
    VECTORED(Position);
    VECTORED(Velocity);
}

int main() {
    using namespace Vectored;
    Force force(0,0,0);
    Acceleration acceleration(force);
    acceleration.as<Momentum>();
    Velocity velocity(acceleration);
    auto result = velocity + acceleration;
}
