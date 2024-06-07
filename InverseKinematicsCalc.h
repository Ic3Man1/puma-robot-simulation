#pragma once
#include <iostream>
#include <Eigen/Dense>

//using namespace Eigen;
using namespace std;

double degrees_to_radians(double degrees);
double normalize_angle(double angle_degrees);
Eigen::Vector3d equations(const Eigen::Vector3d& angles, const Eigen::Vector3d& xyz);
Eigen::Matrix3d jacobian(const Eigen::Vector3d& angles);
void find_angles(float x, float y, float z, double& alpha, double& beta, double& gamma);