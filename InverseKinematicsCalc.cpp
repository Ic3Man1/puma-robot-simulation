#pragma once
#include <iostream>
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;
using namespace std;

double degrees_to_radians(double degrees) {
    return degrees * EIGEN_PI / 180.0;
}

double normalize_angle(double angle_degrees) {
    while (angle_degrees > 180.0)
    {
        angle_degrees -= 360.0;
    }
    while (angle_degrees < -180.0) 
    {
        angle_degrees += 360.0;
    }
    return angle_degrees;
}

Vector3d equations(const Vector3d& angles, const Vector3d& xyz) {
    double alpha = degrees_to_radians(angles[0]);
    double beta = degrees_to_radians(angles[1]);
    double gamma = degrees_to_radians(angles[2]);

    double x = xyz[0];
    double y = xyz[1];
    double z = xyz[2];

    double sin_alpha = sin(alpha);
    double cos_alpha = cos(alpha);
    double sin_beta = sin(beta);
    double cos_beta = cos(beta);
    double sin_gamma = sin(gamma);
    double cos_gamma = cos(gamma);

    Vector3d F;
    F[0] = x - (1.85 * sin_alpha * cos_beta - 2.55 * sin_alpha * sin_beta * sin_gamma + 2.55 * sin_alpha * cos_beta * cos_gamma);
    F[1] = y - (5.5 - (2.75 + 1.85 * sin_beta + 2.55 * sin_beta * cos_gamma + 2.55 * cos_beta * sin_gamma));
    F[2] = z - (1.85 * cos_alpha * cos_beta + 2.55 * cos_alpha * cos_beta * cos_gamma - 2.55 * cos_alpha * sin_beta * sin_gamma);

    return F;
}

Matrix3d jacobian(const Vector3d& angles) {
    double alpha = degrees_to_radians(angles[0]);
    double beta = degrees_to_radians(angles[1]);
    double gamma = degrees_to_radians(angles[2]);

    double sin_alpha = sin(alpha);
    double cos_alpha = cos(alpha);
    double sin_beta = sin(beta);
    double cos_beta = cos(beta);
    double sin_gamma = sin(gamma);
    double cos_gamma = cos(gamma);

    Matrix3d J;
    J(0, 0) = 1.85 * cos_alpha * cos_beta - 2.55 * cos_alpha * sin_beta * sin_gamma + 2.55 * cos_alpha * cos_beta * cos_gamma;
    J(0, 1) = -1.85 * sin_alpha * sin_beta - 2.55 * sin_alpha * cos_beta * sin_gamma - 2.55 * sin_alpha * sin_beta * cos_gamma;
    J(0, 2) = -2.55 * sin_alpha * sin_beta * cos_gamma - 2.55 * sin_alpha * cos_beta * sin_gamma;

    J(1, 0) = 0;
    J(1, 1) = -1.85 * cos_beta - 2.55 * cos_beta * cos_gamma + 2.55 * sin_beta * sin_gamma;
    J(1, 2) = 2.55 * sin_beta * sin_gamma - 2.55 * cos_beta * cos_gamma;

    J(2, 0) = -1.85 * sin_alpha * cos_beta - 2.55 * sin_alpha * cos_beta * cos_gamma + 2.55 * sin_alpha * sin_beta * sin_gamma;
    J(2, 1) = -1.85 * cos_alpha * sin_beta - 2.55 * cos_alpha * cos_beta * sin_gamma - 2.55 * cos_alpha * sin_beta * cos_gamma;
    J(2, 2) = -2.55 * cos_alpha * sin_beta * cos_gamma - 2.55 * cos_alpha * cos_beta * sin_gamma;

    return J;
}

void find_angles(float x, float y, float z, double& alpha, double& beta, double& gamma) // Newton-Raphson method
{
    // Input x, y, z
    Vector3d xyz(x, y, z);

    // First guess at alpha, beta and gamma
    Vector3d angles(10.0, 10.0, 10.0);

    const double tolerance = 1e-6;
    const int max_iterations = 300;

    for (int i = 0; i < max_iterations; i++) {
        Vector3d F = equations(angles, xyz); // Set up equations
        Matrix3d J = jacobian(angles); // Set up jacobian

        Vector3d delta = J.colPivHouseholderQr().solve(F);
        angles = angles + delta;

        angles[0] = normalize_angle(angles[0]); // Limit amgles from -180 to 180 degrees
        angles[1] = normalize_angle(angles[1]);
        angles[2] = normalize_angle(angles[2]);

        if (delta.norm() < tolerance) {
            break;
        }
    }
    alpha = int(angles[0]);  // Convert final angles to int
    beta = int(angles[1]);
    gamma = int(angles[2]);
}