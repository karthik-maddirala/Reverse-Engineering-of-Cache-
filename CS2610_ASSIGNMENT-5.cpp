#include <iostream>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <x86intrin.h>
#include <time.h>
using namespace std;


uint64_t **times;

unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;


static __inline__ unsigned long long process_func_start(void)

{
    __asm__ __volatile__ ("CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
            "%rax", "%rbx", "%rcx", "%rdx");
}

static __inline__ unsigned long long process_func_end(void)
{
    __asm__ __volatile__ ("RDTSCP\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
            "%rax", "%rbx", "%rcx", "%rdx");
}



int main(int argc, double* argv[])
{
    uint64_t start, end;

    double c;

    double arr[400];

    for (int i=0;i<400; i++)
    {
        _mm_clflush(&arr[i]);    
    }

    for(int i=0;i<400;i++)
    {
        process_func_start();
        process_func_start();

        c = arr[i];
    
        process_func_end();

        start = ( ((uint64_t)cycles_high << 32) | cycles_low );

        end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );

        cout<< end - start<<","<<i<<endl;
       

    return 0;
}