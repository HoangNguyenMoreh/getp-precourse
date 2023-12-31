#include <chrono>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <sys/times.h>

#define ull unsigned long long
inline ull get_counter_current() {
    unsigned int low, high;
    asm volatile("rdtsc" : "=a" (low), "=d" (high));
    return ((ull)high << 32) | low;
}
inline ull get_counter_since(ull start) {
    unsigned int low, high;
    asm volatile("rdtsc" : "=a" (low), "=d" (high));
    ull end = ((ull)high << 32) | low;
    return end - start;
}

double get_cpu_mhz() {
    int time_to_sleep = 2;
    ull start = get_counter_current();
    sleep(time_to_sleep);
    ull cycles = get_counter_since(start);
    return cycles/(1e6 * time_to_sleep);
}

#define MAXELEMS (1 << 29)/sizeof(ull)
ull data[MAXELEMS];

void test(int elems, int stride) {
    volatile ull result = 0;
    volatile ull sink;
    for (int i = 0; i < elems ; i += stride) {
        result += data[i];
    }
    sink = result;
}

double run(int size, int stride, double Mhz) {
    int elems = size / sizeof(ull);

    test(elems, stride); /* warm up the cache */
    ull start = get_counter_current();
    test(elems, stride);
    ull cycles = get_counter_since(start);

    return (double)(size / stride) / 1024 / 1024 / (cycles / (Mhz * 1e6));
}

double run_latency(int size, int stride, double Mhz) {
    int elems = size / sizeof(ull);

    test(elems, stride); /* warm up the cache */
    ull start = get_counter_current();
    test(elems, stride);
    ull cycles = get_counter_since(start);

    return (double) (cycles / (Mhz * 1e6)) * 1e12 / (elems / stride);
}

double run_storage(int dataSize, double Mhz) {
    char* buffer = new char[dataSize];
    ull start = get_counter_current();
    std::ifstream file("data.bin", std::ios::binary);
    file.read(buffer, dataSize);
    ull cycles = get_counter_since(start);
    return (double)(dataSize) / 1024 / 1024 / (cycles / (Mhz * 1e6));
}

int main()
{
    std::freopen("memory_mountain.txt", "w", stdout);
    for (int i = 0; i < MAXELEMS; i++)
        data[i] = i;

    double cpu_mhz = get_cpu_mhz();
    int iter = 10;

    printf("CPU clock rate: %lf Mhz\n", cpu_mhz);

    // Recovery from sleep
    for (int i = 1 ; i<=iter ; ++i)
    {
        run(256, 1, cpu_mhz);
        run(512, 2, cpu_mhz);
        run(1024, 4, cpu_mhz);
    }

    printf("CPU cache memory throughput benchmark (MiB/s)\n");

    int _size = 2048; // 2 KiB
    for(int i=1 ; i<=17 ; ++i)
    {
        printf("%dBytes: ", _size);
        for(int s=1 ; s<=64 ; ++s)
        {
            double res = 0;
            for (int i = 1 ; i<=iter ; ++i)
            {
                res += run(_size, s, cpu_mhz);
            }
            printf("%lf ", res/iter);
        }
        printf("\n");
        _size *= 2;
    }

    printf("CPU cache memory latency benchmark (picosec)\n");

    _size = 2048; // 2 KiB
    for(int i=1 ; i<=17 ; ++i)
    {
        printf("%dBytes: ", _size);
        for(int s=1 ; s<=64 ; ++s)
        {
            double res_latency = 0;
            for (int i = 1 ; i<=iter ; ++i)
            {
                res_latency += run_latency(_size, s, cpu_mhz);
            }
            printf("%lf ", res_latency/iter);
        }
        printf("\n");
        _size *= 2;
    }

    printf("Storage through put benchmark (MiB/s)\n");

    int dataSize = 128 * 1024 * 1024; // 128 MiB
    double res_ssd = 0;
    for (int i = 1 ; i<=iter ; ++i)
    {
        res_ssd += run_storage(dataSize, cpu_mhz);
    }
    printf("%lf\n", res_ssd/iter);

}
