#include <complex>
#include <functional>
#include <iostream>
#include <vector>
#include <thread>
#include <omp.h>

namespace fractals {

using ComplexDouble = std::complex<double>;
using FractalSet = std::vector<ComplexDouble>;

FractalSet m_set;

ComplexDouble mandelbrot_process(ComplexDouble c, int boundary = 2,
                                 int max_iterations = 512) {
    using namespace std::complex_literals;

    ComplexDouble z(0, 0);
    int i = 0;
    while (abs(z) < abs(boundary)) {
        if (i == max_iterations)
            break;
        z = std::pow(z, 2) + c;
        ++i;
    }
    return z;
}

void mandelbrot(double start_val, double end_val, double step_val) {
    FractalSet temp_set;
    double step = step_val; // 0.01;
    double start = start_val; //-2.0;
    double end = end_val; //2.0;
    for (double i = start; i < end; i += step) {
        for (double j = start; j < end; j += step) {
            ComplexDouble c(i, j);
            temp_set.push_back(mandelbrot_process(c));
            }
    }
    #pragma omp critical
    m_set.insert(m_set.end(), temp_set.begin(), temp_set.end());
                

    // return m_set;
}  // namespace fractals


FractalSet thread(){
    // // Pre loop thread setup
    int num_threads = omp_get_max_threads();
    std::cout << num_threads << std::endl;
    omp_set_num_threads(omp_get_max_threads());
    #pragma omp parallel
    #pragma omp for
    for(int t=0; t<num_threads; t++) {
        double start_here = -2.0+(t*4/num_threads);
        double end_here = -2.0+((t+1)*4/num_threads);
        mandelbrot(start_here, end_here, 0.001);
    }

    return m_set;
}
}