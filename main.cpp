#include <complex>
#include <functional>
#include <iostream>
#include <vector>

namespace fractals {

using ComplexDouble = std::complex<double>;
using FractalSet = std::vector<ComplexDouble>;

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

FractalSet mandelbrot() {
    double step = 0.01;
    double start = -2.0;
    double end = 2.0;
    FractalSet m_set;
    for (double i = start; i < end; i += step) {
        for (double j = start; j < end; j += step) {
            ComplexDouble c(i, j);
            m_set.push_back(mandelbrot_process(c));
        }
    }
    return m_set;
}

}  // namespace fractals

int main() {
    auto m_set = fractals::mandelbrot();
    std::cout << "{ ";
    for (auto i : m_set) {
        std::cout << i << " ";
    }
    std::cout << "}" << std::endl;
}
