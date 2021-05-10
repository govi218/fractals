#include <omp.h>
#include <complex>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

namespace fractals {

using ComplexDouble = std::complex<double>;
using FractalSet = std::vector<ComplexDouble>;

FractalSet m_set;

ComplexDouble mandelbrot_process(ComplexDouble c, int boundary = 2,
                                 int max_iterations = 512) {
    using namespace std::complex_literals;

    ComplexDouble z(0, 0);
    ComplexDouble zero_elm(0, 0);
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

void mandelbrot(double i_start_val, double i_end_val, double j_start_val, double j_end_val, double step_val) {
    ComplexDouble m_element;
    ComplexDouble zero_elm(0, 0);
    double step = step_val;    // 0.01;
    double i_start = i_start_val;  //-2.0;
    double i_end = i_end_val;      // 2.0;
    double j_start = j_start_val;  //-2.0;
    double j_end = j_end_val;      // 2.0;
    for (double i = i_start; i < i_end; i += step) {
        for (double j = j_start; j < j_end; j += step) {
            ComplexDouble c(i, j);
            m_element = mandelbrot_process(c);
            if (m_element != zero_elm)
                #pragma omp critical
                m_set.push_back(m_element);
        }
    }
}

FractalSet thread() {
    ComplexDouble zero_elm(0, 0);
    // // Pre loop thread setup
    int num_threads = omp_get_max_threads();
    std::cout << "Number of threads: " << num_threads << std::endl;
    omp_set_num_threads(omp_get_max_threads());
    int break_thread = 1;
    double res = 0.0002;
    // Complexity calc: (4/res)^2/(break_thread*num_threads)
    std::cout << "Each grid has "
              << pow((4 / res), 2) / (num_threads * num_threads) << " points."
              << std::endl;
    // Total steps to take = Max number possible points to evaluate: (4/res)^2
    std::cout << "Total points to investigate: " << pow(4 / res, 2)
              << std::endl;
// #pragma omp parallel
    #pragma omp parallel for schedule(dynamic)
    for (int t = 0; t < num_threads * num_threads; t++) {
        double i_start_here = -2.0 + (floor(t / num_threads) * 4) /num_threads;
        double i_end_here = -2.0 + ((floor(t / num_threads) + 1) * 4) /num_threads;
        double j_start_here = -2.0 + ((t % num_threads) * 4) /num_threads;
        double j_end_here = -2.0 + (((t % num_threads) + 1) * 4)/num_threads;
        // int thread_num = omp_get_thread_num();
        // #pragma omp critical
        // std::cout << "Thread " << thread_num << " is handling t = " << t <<
        // std::endl;
        mandelbrot(i_start_here, i_end_here, j_start_here, j_end_here, res);
    }
    #pragma omp critical
    m_set.push_back(zero_elm);

    return m_set;
}
}  // namespace fractals
