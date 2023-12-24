#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {

    int numOfTerms; //terim sayisi
    double *coefficients; //katsayilar
    int *powers; //terimlerin kuvvetleri

}Diff_Eq;


// kullanicidan alinan katsayilari ve kuvvetleri print eden fonksiyon.
void printEquation(int numberOfTerms, double *coefficients, double yCoeff, int *powers){
    int i;
    printf("\ny' = ");
    printf("%.2lfy", yCoeff);
    for (i = 0; i < numberOfTerms - 1; i++) {
        printf(" + %.2lfx^%d", coefficients[i], powers[i]);
    }
}

//y' = ay + ... + x seklinde yazilan, runge-kutta methodunda kullanilan fonksiyon.
double f(double x, double y, int numberOfTerms, const double *coefficients, double yCoeff, int *powers) {
    double finalEq = yCoeff * y;
    int i;
    for (i = 0; i < numberOfTerms-1; ++i) {

        finalEq += coefficients[i] * pow(x, powers[i]);
    }
    return finalEq;
}




// runge-kutta-4 methodu
void rungeKutta(double x0, double y0, double h, double x_target, int numberOfTerms, double *coefficients, double yCoeff, int *powers) {

    double k1, k2, k3, k4, y, x;
    x = x0;
    y = y0;

    while (x < x_target) {
        k1 = h * f(x, y, numberOfTerms, coefficients, yCoeff, powers);
        k2 = h * f(x + h/2, y + k1/2, numberOfTerms, coefficients, yCoeff, powers);
        k3 = h * f(x + h/2, y + k2/2, numberOfTerms, coefficients, yCoeff, powers);
        k4 = h * f(x + h, y + k3, numberOfTerms, coefficients, yCoeff, powers);

        y = y + (k1 + 2*k2 + 2*k3 + k4)/6;
        x += h;
        printf("\ny(%.2f) = %.5f", x, y);//her adimdaki hesaplanan sonuclari ekrana bastirmak icin.
    }


}



int main() {

    int i;
    Diff_Eq equation;

    // esitligin sag tarafinda kalacak terim sayisi kullanicidan alinir.
    printf("Enter the number of terms: ");
    scanf("%d", &equation.numOfTerms);

    while(equation.numOfTerms <= 0){
        printf("Minimum number of terms is 1.\n");
        printf("Enter the number of terms again: ");
        scanf("%d", &equation.numOfTerms);
    }//bu dongu ile girilen terim sayisinin kontrolunu yapiyorum.


    //katsayi ve terimlerin kuvvetleri icin bellekte yer ayrilir.
    equation.coefficients = (double * ) malloc(equation.numOfTerms * sizeof(double));
    equation.powers = (int * ) malloc(equation.numOfTerms * sizeof(int));


    // eger katsayi veya kuvvet pointerlari icin yer ayrilmazsa uygulamadan cikis yapilir.
    if (equation.coefficients == NULL || equation.powers == NULL) {
        printf("Memory Allocation Error!\n");
        return 1;
    }


    // kullanicidan terimler ve katsayilar alinir.
    double yCoeff;
    printf("Enter the coefficient of y: ");
    scanf("%lf", &yCoeff);


    for (i = 0; i < equation.numOfTerms - 1; i++) {
        printf("Enter coefficient of %d. expression with x: ", i + 1);
        scanf("%lf", &equation.coefficients[i]);

        printf("Enter power of %d. expression with x: ", i + 1);
        scanf("%d", &equation.powers[i]);
    }


    //print metoduyla yazdirip programin dogru calisip calismadigi kontrol edilir.
    printEquation(equation.numOfTerms, equation.coefficients, yCoeff, equation.powers);


    //kullanicidan inital değerler, adim sayisi ve ulasmak istedigimiz noktanin degeri alinir.
    double x0, y0, h, x_target;
    printf("\nenter the initial value x0: ");
    scanf("%lf", &x0);
    printf("enter the initial value y0: ");
    scanf("%lf", &y0);
    printf("enter the step size h: ");
    scanf("%lf", &h);
    printf("enter the target value: ");
    scanf("%lf", &x_target);


    //runge-kutta-4 methodunu calistir..
    rungeKutta(x0, y0, h, x_target,equation.numOfTerms, equation.coefficients, yCoeff, equation.powers);




    //bellekte ayrilan yerleri temizler.
    free(equation.coefficients);
    free(equation.powers);


    printf("\n");
    system("pause");
    return 0;
}
