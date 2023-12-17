#include <stdio.h>
#include <stdlib.h>

typedef struct {

    int numOfTerm;
    long double *coefficients;

}diff_Eq;

void printEquation(int numberOfTerms, long double *coefficients, double yCoeff){

    int i;
    printf("\ny' = ");
    printf("%.2lfy + ", yCoeff);
    for (i = numberOfTerms - 1; i > 0; i--) {
        printf("%.2Lf*x^%d + ", coefficients[i-1], i);
        /*
        if (i == numberOfTerms - 1 && numberOfTerms > 4 ) {
            printf("%.2lf", coefficients[i]);
        } else {
            printf(" + %.2lf*x^%d", coefficients[i], i+1);
        }*/
    }

}

int main() {

    int i;
    diff_Eq equation;
    equation.coefficients = (long double *)malloc(sizeof(long double) * equation.numOfTerm);

/*    if (equation.coefficients == NULL) {
        printf("Bellek tahsis hatasi!\n");
        return 1;
    }
*/

    // Kullanıcıdan terim sayısını al
    printf("Denklemin terim sayisini girin: ");
    scanf("%d", &equation.numOfTerm);

    double yCoeff;
    printf("Y'li ifadenin bas katsayisini girin: ");
    scanf("%lf", &yCoeff);


    // Kullanıcıdan her terimin baş katsayısını al
    for (i = 0; i < equation.numOfTerm - 1; i++) {
        printf("Terim %d'in bas katsayisini girin: ", i + 1);
        scanf("%Lf", &equation.coefficients[i]);
    }


    printEquation(equation.numOfTerm, equation.coefficients, yCoeff);

    free(equation.coefficients);
    free(equation.coefficients);

    printf("\n");
    system("pause");
    return 0;
}
