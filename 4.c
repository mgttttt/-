#include <stdio.h>
#include <math.h>
#pragma warning(disable : 4996)
int main() {
    double n; double sum = 0;
    double h = 0.02;
    double old_I = 0;

    printf("Enter n: ");
    scanf("%lf", &n);

    do {
        old_I = sum;
        sum = 0; h /= 2.0;
        for (int i = 0; i < 2 / h; i++)
        {
            if (i * h <= 1)
                sum += 8 * pow(i * h + h / 2.0, 3) * cos(i * h + h / 2.0);
            else sum += log(1 + sqrt(i * h + h / 2.0)) - cos(i * h + h / 2.0);
        }
        sum *= h;
    } while (fabs(sum - old_I) / 3.0 >= n);
    printf("%.20lf", sum);
    return 0;
}