
#include <iostream>
#include <random>
#include <omp.h>
#include <chrono>
int main() {
   int num_iterations = 10000;
   int num_inside = 0;
   int k = 8;

   std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
#pragma omp parallel num_threads(k) reduction(+:num_inside)
   {
      unsigned int seed = omp_get_thread_num();
      std::mt19937 rng(seed);
      std::uniform_real_distribution<double> dist(0, 1);

#pragma omp for
      for (int i = 0; i < num_iterations; i++) {
         double x = dist(rng);
         double y = dist(rng);
         //std::cout << x << " " << y << std::endl;
         if (x * x + y * y <= 1) {
            num_inside++;
         }
      }
   }

   std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
   std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

   double pi = 4.0 * num_inside / num_iterations;
   std::cout << "pi = " << pi << std::endl;
   std::cout << duration.count() << std::endl;
   return 0;
}