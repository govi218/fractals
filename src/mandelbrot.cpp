#include "../include/fractals.hpp"

int main() {
    auto m_set = fractals::mandelbrot();
    std::cout << "{ ";
    for (auto i : m_set) {
        std::cout << i << " ";
    }
    std::cout << "}" << std::endl;
}
