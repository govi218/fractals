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
    ComplexDouble zero_elm(0,0);
    int i = 0;
    while (abs(z) < abs(boundary)) {
        if (i == max_iterations)
            // break;
            return c;
        z = std::pow(z, 2) + c;
        ++i;
    }
    return zero_elm;
}

void mandelbrot(double start_val, double end_val, double step_val) {
    FractalSet temp_set;
    ComplexDouble m_element;
    ComplexDouble zero_elm(0,0);
    double step = step_val; // 0.01;
    double start = start_val; //-2.0;
    double end = end_val; //2.0;
    for (double i = start; i < end; i += step) {
        for (double j = -2.0; j < 2.0; j += step) {
            ComplexDouble c(i, j);
            m_element = mandelbrot_process(c);
            if(m_element != zero_elm)
                temp_set.push_back(m_element);
            }
    }
    // int thread_num = omp_get_thread_num();
    #pragma omp critical
    m_set.insert(m_set.end(), temp_set.begin(), temp_set.end());
    
    // #pragma omp critical
    // std::cout << "m_set appende by thread " << thread_num <<std::endl;
                

    // return m_set;
}  // namespace fractals


FractalSet thread(){
    ComplexDouble zero_elm(0,0);
    // // Pre loop thread setup
    int num_threads = omp_get_max_threads();
    std::cout << "Number of threads: " << num_threads << std::endl;
    omp_set_num_threads(omp_get_max_threads());
    int break_thread = 1000;
    double res = 0.001;
    // Complexity calc: (4/res)^2/(break_thread*num_threads)
    std::cout << "Each break thread investigates " << pow((4/res), 2)/(break_thread*num_threads) << " points." << std::endl;
    // Total steps to take = Max number possible points to evaluate: (4/res)^2
    std::cout << "Total points to investigate: " << pow(4/res, 2) << std::endl;
    // #pragma omp parallel
    #pragma omp parallel for
    for(int t=0; t<break_thread*num_threads; t++) {
        double start_here = -2.0+(t*4/(num_threads*break_thread));
        double end_here = -2.0+((t+1)*4/(num_threads*break_thread));
        // int thread_num = omp_get_thread_num();
        // #pragma omp critical
        // std::cout << "Thread " << thread_num << " is handling t = " << t << std::endl;
        mandelbrot(start_here, end_here, res);
    }
    #pragma omp critical
    m_set.push_back(zero_elm);

    return m_set;
}
}