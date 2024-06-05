#pragma once
#include <iostream>
#include <cmath>
#include <Eigen/Dense>

#include "InverseKinematicsCalc.h"

using namespace Eigen;
using namespace std;

// Funkcja obliczaj¹ca wartoœci x, y, z na podstawie alpha, beta, gamma
void oblicz_xyz(double alpha, double beta, double gamma, double& x, double& y, double& z) {
    x = 1.85 * sin(alpha) * cos(beta) - 2.55 * sin(alpha) * sin(beta) * sin(gamma) + 2.55 * sin(alpha) * cos(beta) * cos(gamma);
    y = 5.5 - (2.75 + 1.85 * sin(beta) + 2.55 * sin(beta) * cos(gamma) + 2.55 * cos(beta) * sin(gamma));
    z = 1.85 * cos(alpha) * cos(beta) + 2.55 * cos(alpha) * cos(beta) * cos(gamma) - 2.55 * cos(alpha) * sin(beta) * sin(gamma);
}

// Funkcja celu, któr¹ chcemy zminimalizowaæ (kwadraty ró¿nic)
double funkcja_celu(double alpha, double beta, double gamma, double x, double y, double z) {
    double x_calc, y_calc, z_calc;
    oblicz_xyz(alpha, beta, gamma, x_calc, y_calc, z_calc);
    return pow(x - x_calc, 2) + pow(y - y_calc, 2) + pow(z - z_calc, 2);
}

// Funkcja znajduj¹ca k¹ty alpha, beta, gamma minimalizuj¹ce funkcjê celu
void znajdz_katy(double x, double y, double z, double& alpha, double& beta, double& gamma) {
    const double learning_rate = 0.01; // wspó³czynnik uczenia
    const int max_iterations = 1000; // maksymalna liczba iteracji
    const double tolerance = 1e-6; // tolerancja zbie¿noœci

    alpha = 0; // pocz¹tkowe wartoœci k¹tów
    beta = 0;
    gamma = 0;

    for (int i = 0; i < max_iterations; ++i) {
        // Obliczanie gradientu funkcji celu
        double x_calc, y_calc, z_calc;
        oblicz_xyz(alpha, beta, gamma, x_calc, y_calc, z_calc);
        double grad_alpha = -2 * (x - x_calc) * (1.85 * cos(alpha) * cos(beta) - 2.55 * cos(alpha) * sin(beta) * sin(gamma) + 2.55 * cos(alpha) * cos(beta) * cos(gamma));
        double grad_beta = -2 * (x - x_calc) * (-1.85 * sin(beta) * cos(alpha) - 2.55 * sin(beta) * cos(alpha) * cos(gamma) + 2.55 * cos(beta) * sin(gamma));
        double grad_gamma = -2 * (x - x_calc) * (-2.55 * sin(alpha) * sin(beta) * cos(gamma) + 2.55 * sin(alpha) * cos(beta) * sin(gamma));

        // Aktualizacja k¹tów
        alpha -= learning_rate * grad_alpha;
        beta -= learning_rate * grad_beta;
        gamma -= learning_rate * grad_gamma;

        // Sprawdzenie warunku stopu
        if (fabs(grad_alpha) < tolerance && fabs(grad_beta) < tolerance && fabs(grad_gamma) < tolerance) {
            cout << "Metoda gradientowa zbie¿na po " << i + 1 << " iteracjach." << endl;
            return;
        }
    }

    cerr << "Metoda gradientowa nie osi¹gnê³a zbie¿noœci po " << max_iterations << " iteracjach." << endl;
}
