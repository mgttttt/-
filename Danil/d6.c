#include <stdio.h>
#include <math.h>

int main() {
    double n; double sum = 0;
    double h = 0.02;
    double old_I = 0;
    double x = 0;

    printf("Enter n: ");
    scanf("%lf", &n);

    do {
        old_I = sum;
        sum = 0; h /= 2.0;
        for (int i = 0; i < 2 / h; i++)
        {
            x = i * h + h / 2.0;
            if (i * h <= 1)
                sum += cos(x + pow(x, 3));
            else sum += exp(-x * x) - x * x + 2 * x;
        }
        sum *= h;
    } while (fabs(sum - old_I) / 3.0 >= n);
    printf("%.20lf\n", sum);
    return 0;
}