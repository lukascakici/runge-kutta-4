#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {

    int numOfTerms;
    double *coefficients;
    int *powers;

}Diff_Eq;


// kullanıcıdan alınan katsayıları ve kuvvetleri print eden fonksiyon.
void printEquation(int numberOfTerms, double *coefficients, double yCoeff, int *powers){
    int i;
    printf("\ny' = ");
    printf("(%.2lf)y", yCoeff);
    for (i = 0; i < numberOfTerms - 1; i++) {
        printf(" + (%.2lf)x^%d", coefficients[i], powers[i]);
    }
}

//y' = ay + ... + x şeklinde yazılan, runge-kutta methodunda kullanılan fonksiyon.

/*double f(double x, double y, int numberOfTerms, double *coefficients, double yCoeff, int *powers) {

    return yCoeff*y + coefficients[0] * pow(x, powers[0])
           + coefficients[1] * pow(x, powers[1])
           + coefficients[2] * pow(x, powers[2])
           + coefficients[3] * pow(x, powers[3]);
}*/
//döngüsüz method, belli bir sayıdan fazla terim girilirse kafa karışıklığı yaratabilir.

//döngü sayesinde kaç tane terim girildiğiyle alakalı problem yaşamayacağım.
double f(double x, double y, int numberOfTerms, double *coefficients, double yCoeff, int *powers) {
    double result = yCoeff * y;
    int i;

    for (i = 0; i < numberOfTerms; ++i) {
        result += coefficients[i] * pow(x, powers[i]);
    }

    return result;
}



// runge-kutta-4 methodu
/*double rungeKutta(double x0, double y0, double h, double x_target,
                  int numberOfTerms, double *coefficients, double yCoeff, int *powers) {
    double x = x0;
    double y = y0;

    while (x < x_target) {
        double k1 = h * f(x, y, numberOfTerms, coefficients, yCoeff, powers);
        double k2 = h * f(x + h/2, y + k1/2, numberOfTerms, coefficients, yCoeff, powers);
        double k3 = h * f(x + h/2, y + k2/2, numberOfTerms, coefficients, yCoeff, powers);
        double k4 = h * f(x + h, y + k3, numberOfTerms, coefficients, yCoeff, powers);

        y = y + (k1 + 2*k2 + 2*k3 + k4)/6;
        x += h;
    }
    return y;
}*/
//  methoda print fonksiyonu ekleyerek her adımdaki değerleri bastırdım.
void rungeKutta(double x0, double y0, double h, double x_target,
                int numberOfTerms, double *coefficients, double yCoeff, int *powers) {
    double x = x0;
    double y = y0;

    while (x < x_target) {
        double k1 = h * f(x, y, numberOfTerms, coefficients, yCoeff, powers);
        double k2 = h * f(x + h/2, y + k1/2, numberOfTerms, coefficients, yCoeff, powers);
        double k3 = h * f(x + h/2, y + k2/2, numberOfTerms, coefficients, yCoeff, powers);
        double k4 = h * f(x + h, y + k3, numberOfTerms, coefficients, yCoeff, powers);

        y = y + (k1 + 2*k2 + 2*k3 + k4)/6;
        x += h;
        printf("\ny(%.2f) = %.5f", x, y);//her adımdaki hesaplanan sonuçları ekrana bastırmak için.
    }

}



int main() {

    int i;
    Diff_Eq equation;

    // eşitliğin sağ tarafında kalacak terim sayısı kullanıcıdan alınır.
    printf("Enter the number of terms: ");
    scanf("%d", &equation.numOfTerms);

    while(equation.numOfTerms <= 0){
        printf("Minimum number of terms is 1.\n");
        printf("Enter the number of terms again: ");
        scanf("%d", &equation.numOfTerms);
    }//bu döngü ile girilen terim sayısının kontrolünü yapıyorum.

    //katsayı ve terimlerin kuvvetleri için bellekte yer ayrılır.
    equation.coefficients = (double * ) malloc(equation.numOfTerms * sizeof(double));
    equation.powers = (int * ) malloc(equation.numOfTerms * sizeof(int));


    // eğer katsayı veya kuvvet pointerları için yer ayrılmazsa uygulamadan çıkış yapılır.
    if (equation.coefficients == NULL || equation.powers == NULL) {
        printf("Memory Allocation Error!\n");
        return 1;
    }

    // kullanıcıdan terimler ve katsayılar alınır.
    double yCoeff;
    printf("Enter the coefficient of y: ");
    scanf("%lf", &yCoeff);

    for (i = 0; i < equation.numOfTerms - 1; i++) {
        printf("Enter coefficient of %dst term: ", i + 1);
        scanf("%lf", &equation.coefficients[i]);

        printf("Enter power of %dst term: ", i + 1);
        scanf("%d", &equation.powers[i]);
    }

    //print metoduyla yazdırıp programın doğru çalışıp çalışmadığını kontrol edilir.
    printEquation(equation.numOfTerms, equation.coefficients, yCoeff, equation.powers);

    //kullanıcıdan inital değerler, adım sayısı ve ulaşmak istediğimiz noktanın değeri alınır.
    double x0, y0, h, x_target;
    printf("\nenter the initial value x0: ");
    scanf("%lf", &x0);
    printf("enter the initial value y0: ");
    scanf("%lf", &y0);
    printf("enter the step size h: ");
    scanf("%lf", &h);
    printf("enter the target value: ");
    scanf("%lf", &x_target);


    // runge-kutta-4 fonksiyonunu çalıştırır.
    /*double result = rungeKutta(x0, y0, h,
                               x_target,equation.numOfTerms, equation.coefficients, yCoeff, equation.powers);

    // sonucu yazdırır
    printf("\ny(%.2f) = %.4f\n", x_target, result);*/
    //bu adımdaki fonksiyonu çalıştırıp ekrana yazdırma adımlarına ihtiyacım kalmadı çünkü
    //runge-kuttanın içine print ekledim



    //runge-kutta-4 methodunu çalıştır.
    //print etme kısmını döngüyle birlikte direkt olarak runge-kutta fonksiyonunda tanımladım.
    rungeKutta(x0, y0, h, x_target,equation.numOfTerms,
               equation.coefficients, yCoeff, equation.powers);

    //bellekte ayrılan yerleri temizler.
    free(equation.coefficients);
    free(equation.powers);


    return 0;
}
