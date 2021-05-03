#include <complex>
#include <functional>
#include <iostream>
#include <vector>
#include <thread>

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
    double step = step_val; // 0.01;
    double start = start_val; //-2.0;
    double end = end_val; //2.0;
    // FractalSet m_set;
    for (double i = start; i < end; i += step) {
        for (double j = start; j < end; j += step) {
            ComplexDouble c(i, j);
            m_set.push_back(mandelbrot_process(c));
            }
    }
                

    // return m_set;
}  // namespace fractals


FractalSet thread(){
    // m_set.push_back(0);
    // Pre loop thread setup
    int num_threads = std::thread::hardware_concurrency(); 
    std::vector<std::thread> threads;
    // std::mutex critical;
    std::cout << num_threads << std::endl;
    for(int t=0; t<num_threads; t++) {
        double start_here = -2.0+(t*4/num_threads);
        double end_here = -2.0+((t+1)*4/num_threads);
        threads.push_back(std::thread(mandelbrot, start_here, end_here, 0.01));
        threads[t].join();
    }
    // std::thread first(mandelbrot, -2.0, 2.0, 0.01, m_set);
    // first.join();

    return m_set;
}
}