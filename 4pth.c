#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4

double n; 
double sum = 0;
typedef struct
{
   
} thread_data;

thread_data thread_data_arr[NUM_THREADS];

void *calc_part(void *threadarg)
{
    
    double h = 0.02;
    double old_I = 0;
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
    pthread_exit(NULL);
}

int main() {

    printf("Enter n: ");
    scanf("%lf", &n);

    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    void *status;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        rc = pthread_create(&threads[i], &attr, calc_part, (void *)&thread_data_arr[i]);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }
    pthread_attr_destroy(&attr);
    for (int i = 0; i < NUM_THREADS; i++)
    {
        rc = pthread_join(threads[i], &status);
        if (rc)
        {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }
    
    printf("%.20lf", sum);
    return 0;
}