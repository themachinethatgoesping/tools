// SPDX-License-Identifier: MPL-2.0

#include "quaternions.hpp"

#include <utility> // move

namespace themachinethatgoesping {
namespace tools {
namespace rotationfunctions {

// Definitions

template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_ypr(std::array<t_float, 3> ypr, bool input_in_degrees)
{
    constexpr t_float to_rad = std::numbers::pi_v<t_float> / t_float{180};

    if (!std::isfinite(ypr[0]) || !std::isfinite(ypr[1]) || !std::isfinite(ypr[2]))
        throw std::invalid_argument("ERROR[quaternion_from_ypr]: NAN or INFINITY yaw/pitch/roll!");

    if (input_in_degrees)
    {
        ypr[0] *= to_rad;
        ypr[1] *= to_rad;
        ypr[2] *= to_rad;
    }

    EigenQuaternion<t_float> q =
        Eigen::AngleAxis<t_float>(ypr[0], Eigen::Matrix<t_float, 3, 1>::UnitZ()) *
        Eigen::AngleAxis<t_float>(ypr[1], Eigen::Matrix<t_float, 3, 1>::UnitY()) *
        Eigen::AngleAxis<t_float>(ypr[2], Eigen::Matrix<t_float, 3, 1>::UnitX());

    q.normalize();
    return q;
}

template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_rpy(std::array<t_float, 3> rpy, bool input_in_degrees)
{
    constexpr t_float to_rad = std::numbers::pi_v<t_float> / t_float{180};

    if (!std::isfinite(rpy[0]) || !std::isfinite(rpy[1]) || !std::isfinite(rpy[2]))
        throw std::invalid_argument("ERROR[quaternion_from_rpy]: NAN or INFINITY roll/pitch/yaw!");

    if (input_in_degrees)
    {
        rpy[0] *= to_rad;
        rpy[1] *= to_rad;
        rpy[2] *= to_rad;
    }

    EigenQuaternion<t_float> q =
        Eigen::AngleAxis<t_float>(rpy[0], Eigen::Matrix<t_float, 3, 1>::UnitX()) *
        Eigen::AngleAxis<t_float>(rpy[1], Eigen::Matrix<t_float, 3, 1>::UnitY()) *
        Eigen::AngleAxis<t_float>(rpy[2], Eigen::Matrix<t_float, 3, 1>::UnitZ());

    q.normalize();
    return q;
}

template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_ypr(t_float yaw, t_float pitch, t_float roll, bool input_in_degrees)
{
    std::array<t_float, 3> ypr{ yaw, pitch, roll };
    return quaternion_from_ypr(std::move(ypr), input_in_degrees);
}

template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_rpy(t_float roll, t_float pitch, t_float yaw, bool input_in_degrees)
{
    std::array<t_float, 3> rpy{ roll, pitch, yaw };
    return quaternion_from_rpy(std::move(rpy), input_in_degrees);
}

template<std::floating_point t_float>
std::array<t_float, 3> ypr_from_quaternion(EigenQuaternion<t_float> q, bool output_to_degrees)
{
    q.normalize();

    auto Me = q.toRotationMatrix().eulerAngles(2, 1, 0);
    std::array<t_float, 3> ypr{ Me[0], Me[1], Me[2] };

    ypr = normalize_angles_rad(ypr);

    constexpr t_float to_deg = t_float{180} / std::numbers::pi_v<t_float>;
    if (output_to_degrees)
    {
        ypr[0] *= to_deg;
        ypr[1] *= to_deg;
        ypr[2] *= to_deg;
    }
    return ypr;
}

template<std::floating_point t_float>
std::array<t_float, 3> rpy_from_quaternion(EigenQuaternion<t_float> q, bool output_to_degrees)
{
    q.normalize();

    auto Me = q.toRotationMatrix().eulerAngles(0, 1, 2);
    std::array<t_float, 3> rpy{ Me[0], Me[1], Me[2] };

    rpy = normalize_angles_rad(rpy);

    constexpr t_float to_deg = t_float{180} / std::numbers::pi_v<t_float>;
    if (output_to_degrees)
    {
        rpy[0] *= to_deg;
        rpy[1] *= to_deg;
        rpy[2] *= to_deg;
    }
    return rpy;
}

template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_ypr(
    const std::vector<std::array<t_float, 3>>& YPR, bool input_in_degrees)
{
    std::vector<EigenQuaternion<t_float>> Q;
    Q.reserve(YPR.size());
    for (const auto& ypr : YPR)
        Q.push_back(quaternion_from_ypr(ypr, input_in_degrees));
    return Q;
}

template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_rpy(
    const std::vector<std::array<t_float, 3>>& RPY, bool input_in_degrees)
{
    std::vector<EigenQuaternion<t_float>> Q;
    Q.reserve(RPY.size());
    for (const auto& rpy : RPY)
        Q.push_back(quaternion_from_rpy(rpy, input_in_degrees));
    return Q;
}

template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_ypr(const std::vector<t_float>& yaw,
                                                          const std::vector<t_float>& pitch,
                                                          const std::vector<t_float>& roll,
                                                          bool input_in_degrees)
{
    if (yaw.size() != pitch.size() || yaw.size() != roll.size())
        throw std::invalid_argument("ERROR[quaternion_from_ypr]: input vectors must have same size!");

    std::vector<EigenQuaternion<t_float>> Q;
    Q.reserve(yaw.size());
    for (size_t i = 0; i < yaw.size(); ++i)
        Q.push_back(quaternion_from_ypr(yaw[i], pitch[i], roll[i], input_in_degrees));
    return Q;
}

template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_rpy(const std::vector<t_float>& roll,
                                                          const std::vector<t_float>& pitch,
                                                          const std::vector<t_float>& yaw,
                                                          bool input_in_degrees)
{
    if (yaw.size() != pitch.size() || yaw.size() != roll.size())
        throw std::invalid_argument("ERROR[quaternion_from_rpy]: input vectors must have same size!");

    std::vector<EigenQuaternion<t_float>> Q;
    Q.reserve(yaw.size());
    for (size_t i = 0; i < yaw.size(); ++i)
        Q.push_back(quaternion_from_rpy(roll[i], pitch[i], yaw[i], input_in_degrees));
    return Q;
}

template<std::floating_point t_float>
std::vector<std::array<t_float, 3>> ypr_from_quaternion(const std::vector<EigenQuaternion<t_float>>& Q,
                                                        bool output_to_degrees)
{
    std::vector<std::array<t_float, 3>> YPR;
    YPR.resize(Q.size());
    for (size_t i = 0; i < Q.size(); ++i)
        YPR[i] = ypr_from_quaternion(Q[i], output_to_degrees);
    return YPR;
}

template<std::floating_point t_float>
std::vector<std::array<t_float, 3>> rpy_from_quaternion(const std::vector<EigenQuaternion<t_float>>& Q,
                                                        bool output_to_degrees)
{
    std::vector<std::array<t_float, 3>> RPY;
    RPY.resize(Q.size());
    for (size_t i = 0; i < Q.size(); ++i)
        RPY[i] = rpy_from_quaternion(Q[i], output_to_degrees);
    return RPY;
}

template<std::floating_point t_float>
EigenQuaternion<t_float> get_quaternion_from_vector(t_float x, t_float y, t_float z, t_float w)
{
    Eigen::Matrix<t_float, 3, 1> vec_to_rotate(x, y, z);
    EigenQuaternion<t_float>     quat;
    quat.w()   = w;
    quat.vec() = vec_to_rotate;
    return quat;
}

template<std::floating_point t_float>
EigenQuaternion<t_float> get_quaternion_from_vector(const std::array<t_float, 3>& xyz, t_float w)
{
    return get_quaternion_from_vector(xyz[0], xyz[1], xyz[2], w);
}

template<std::floating_point t_float>
std::vector<t_float> get_quaternion_wxyz(const EigenQuaternion<t_float>& q)
{
    return { q.w(), q.x(), q.y(), q.z() };
}

template<std::floating_point t_float>
Eigen::Matrix<t_float, 3, 1> rotateXYZ(EigenQuaternion<t_float> q, t_float x, t_float y, t_float z)
{
    q.normalize();
    EigenQuaternion<t_float> v = get_quaternion_from_vector(x, y, z);
    EigenQuaternion<t_float> r = q * v * q.inverse();
    return r.vec();
}

template<std::floating_point t_float>
Eigen::Matrix<t_float, 3, 1> rotateXYZ(EigenQuaternion<t_float> q, EigenQuaternion<t_float> v)
{
    q.normalize();
    EigenQuaternion<t_float> r = q * v * q.inverse();
    return r.vec();
}

// Explicit instantiations (float, double)

template EigenQuaternion<float>  quaternion_from_ypr<float>(std::array<float, 3>, bool);
template EigenQuaternion<double> quaternion_from_ypr<double>(std::array<double, 3>, bool);

template EigenQuaternion<float>  quaternion_from_rpy<float>(std::array<float, 3>, bool);
template EigenQuaternion<double> quaternion_from_rpy<double>(std::array<double, 3>, bool);

template EigenQuaternion<float>  quaternion_from_ypr<float>(float, float, float, bool);
template EigenQuaternion<double> quaternion_from_ypr<double>(double, double, double, bool);

template EigenQuaternion<float>  quaternion_from_rpy<float>(float, float, float, bool);
template EigenQuaternion<double> quaternion_from_rpy<double>(double, double, double, bool);

template std::array<float, 3>  ypr_from_quaternion<float>(EigenQuaternion<float>, bool);
template std::array<double, 3> ypr_from_quaternion<double>(EigenQuaternion<double>, bool);

template std::array<float, 3>  rpy_from_quaternion<float>(EigenQuaternion<float>, bool);
template std::array<double, 3> rpy_from_quaternion<double>(EigenQuaternion<double>, bool);

template std::vector<EigenQuaternion<float>> quaternion_from_ypr<float>(
    const std::vector<std::array<float, 3>>&, bool);
template std::vector<EigenQuaternion<double>> quaternion_from_ypr<double>(
    const std::vector<std::array<double, 3>>&, bool);

template std::vector<EigenQuaternion<float>> quaternion_from_rpy<float>(
    const std::vector<std::array<float, 3>>&, bool);
template std::vector<EigenQuaternion<double>> quaternion_from_rpy<double>(
    const std::vector<std::array<double, 3>>&, bool);

template std::vector<EigenQuaternion<float>> quaternion_from_ypr<float>(
    const std::vector<float>&, const std::vector<float>&, const std::vector<float>&, bool);
template std::vector<EigenQuaternion<double>> quaternion_from_ypr<double>(
    const std::vector<double>&, const std::vector<double>&, const std::vector<double>&, bool);

template std::vector<EigenQuaternion<float>> quaternion_from_rpy<float>(
    const std::vector<float>&, const std::vector<float>&, const std::vector<float>&, bool);
template std::vector<EigenQuaternion<double>> quaternion_from_rpy<double>(
    const std::vector<double>&, const std::vector<double>&, const std::vector<double>&, bool);

template std::vector<std::array<float, 3>>  ypr_from_quaternion<float>(
    const std::vector<EigenQuaternion<float>>&, bool);
template std::vector<std::array<double, 3>> ypr_from_quaternion<double>(
    const std::vector<EigenQuaternion<double>>&, bool);

template std::vector<std::array<float, 3>>  rpy_from_quaternion<float>(
    const std::vector<EigenQuaternion<float>>&, bool);
template std::vector<std::array<double, 3>> rpy_from_quaternion<double>(
    const std::vector<EigenQuaternion<double>>&, bool);

template EigenQuaternion<float>  get_quaternion_from_vector<float>(float, float, float, float);
template EigenQuaternion<double> get_quaternion_from_vector<double>(double, double, double, double);

template EigenQuaternion<float>  get_quaternion_from_vector<float>(const std::array<float, 3>&, float);
template EigenQuaternion<double> get_quaternion_from_vector<double>(const std::array<double, 3>&, double);

template std::vector<float>  get_quaternion_wxyz<float>(const EigenQuaternion<float>&);
template std::vector<double> get_quaternion_wxyz<double>(const EigenQuaternion<double>&);

template Eigen::Matrix<float, 3, 1>  rotateXYZ<float>(EigenQuaternion<float>, float, float, float);
template Eigen::Matrix<double, 3, 1> rotateXYZ<double>(EigenQuaternion<double>, double, double, double);

template Eigen::Matrix<float, 3, 1>  rotateXYZ<float>(EigenQuaternion<float>, EigenQuaternion<float>);
template Eigen::Matrix<double, 3, 1> rotateXYZ<double>(EigenQuaternion<double>, EigenQuaternion<double>);

} // namespace rotationfunctions
} // namespace tools
} // namespace themachinethatgoesping