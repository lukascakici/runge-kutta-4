#include <stdio.h>
#include <stdlib.h>

typedef struct {

    int numOfTerm;
    float *coefficients;

}Diff_eq;

// Function to calculate the derivative dy/dx for the given ODE
double f(double x, double y) {
    return x*x + y*y;
}

// Fourth-order Runge-Kutta method for numerical integration
double rungeKutta(double x0, double y0, double h, double x_target) {
    double x = x0;
    double y = y0;

    while (x < x_target) {
        double k1 = h * f(x, y);
        double k2 = h * f(x + h/2, y + k1/2);
        double k3 = h * f(x + h/2, y + k2/2);
        double k4 = h * f(x + h, y + k3);

        // Update y using the weighted average of the four slopes
        y = y + (k1 + 2*k2 + 2*k3 + k4)/6;
        x += h;
    }

    return y;
}

int main() {
    // Initial conditions
    double x0 = 1.0;
    double y0 = 1.2;

    // Step size for numerical integration
    double h = 0.05;

    // Target x value
    double x_target = 1.05;

    // Perform Runge-Kutta integration
    double result = rungeKutta(x0, y0, h, x_target);

    // Print the result
    printf("y(%.2f) = %.4f\n", x_target, result);

    return 0;
}
