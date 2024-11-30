#include <iostream>
#include <cmath>
#include <iomanip>

// Обчислює значення першого рівняння системи: tan(x * y + 0.1) - x^2
double f1(double x, double y) {
    return tan(x * y + 0.1) - x * x;
}

// Обчислює значення другого рівняння системи: x^2 + 2 * y^2 - 1
double f2(double x, double y) {
    return x * x + 2 * y * y - 1;
}

// Обчислює часткову похідну f1 за x: (1 / cos^2(x * y + 0.1)) * y - 2 * x
double df1_dx(double x, double y) {
    return (1 / (cos(x * y + 0.1) * cos(x * y + 0.1))) * y - 2 * x;
}

// Обчислює часткову похідну f1 за y: (1 / cos^2(x * y + 0.1)) * x
double df1_dy(double x, double y) {
    return (1 / (cos(x * y + 0.1) * cos(x * y + 0.1))) * x;
}

// Обчислює часткову похідну f2 за x: 2 * x
double df2_dx(double x, double y) {
    return 2 * x;
}

// Обчислює часткову похідну f2 за y: 4 * y
double df2_dy(double x, double y) {
    return 4 * y;
}

int main() {
    double x = 0.5, y = 0.5;
    const int max_iterations = 5; 
    const double tolerance = 1e-6;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Initial guess: x = " << x << ", y = " << y << "\n";

    // Метод Ньютона для розв'язання системи
    for (int k = 0; k < max_iterations; ++k) {
        // Обчислення значень функцій у поточній точці (x, y)
        double F1 = f1(x, y);
        double F2 = f2(x, y);

        // Обчислення елементів Якобіана
        double J11 = df1_dx(x, y), J12 = df1_dy(x, y);
        double J21 = df2_dx(x, y), J22 = df2_dy(x, y);

        // Обчислення детермінанта Якобіана
        double detJ = J11 * J22 - J12 * J21;
        if (std::abs(detJ) < 1e-10) { // Перевірка на виродженість Якобіана
            std::cerr << "Jacobian determinant is too small, stopping...\n";
            break;
        }

        // Обчислення оберненого Якобіана
        double invJ11 = J22 / detJ, invJ12 = -J12 / detJ;
        double invJ21 = -J21 / detJ, invJ22 = J11 / detJ;

        // Обчислення зміщень (dx, dy) для коригування x і y
        double dx = -(invJ11 * F1 + invJ12 * F2);
        double dy = -(invJ21 * F1 + invJ22 * F2);

        // Оновлення значень x і y
        x += dx;
        y += dy;

        std::cout << "Iteration " << k + 1 << ": x = " << x << ", y = " << y << "\n";

        // Перевірка на досягнення заданої точності
        if (std::abs(dx) < tolerance && std::abs(dy) < tolerance) {
            std::cout << "Converged after " << k + 1 << " iterations.\n";
            break;
        }
    }

    std::cout << "Final solution: x = " << x << ", y = " << y << "\n";
    return 0;
}