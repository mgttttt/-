#include <stdio.h>
#include <math.h>
#include <pthread.h>

long double f(long double x) {
    if (x <= 1)
    {
        return sqrt(x + 1) - sqrt(x) - 0.5;
    } 
    return exp(-x - 1.0 / x);
}

typedef struct {
    long double a;
    long double b;
    long double eps;
    long double sum;
} IntegralParams;

void* calculate_integral(void* arg) {
    IntegralParams* params = (IntegralParams*)arg;
    long double a = params->a;
    long double b = params->b;
    long double eps = params->eps;

    long n = 1; 
    long double h = (b - a) / n; 
    long double prev_sum = 0.0; 
    params->sum = 0.0; 

    do {
    prev_sum = params->sum;
    params->sum = 0.0;

    for (int i = 0; i < n; i++) {
        long double x = a + (i + 0.5) * h; 
        long double partial_sum = f(x) * h; 
        params->sum += partial_sum; 
    }

    n *= 2; 
    h /= 2; 
    } while (fabs(params->sum - prev_sum) > eps); 

    return NULL;
}

int main() {
    long double a = 0.00001; 
    long double b = 2.0; 
    long double eps = 1e-15; 

    IntegralParams params;
    params.a = a;
    params.b = b;
    params.eps = eps;

    pthread_t thread;
    pthread_create(&thread, NULL, calculate_integral, (void*)&params);
    pthread_join(thread, NULL);

    long double result = params.sum;

    printf("Значение интеграла: %.20Lf\n", result);
    return 0;
}