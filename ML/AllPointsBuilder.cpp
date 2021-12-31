#include <complex>
#include <functional>
#include <iostream>
#include <vector>
#include <fstream>

using ComplexDouble = std::complex<double>;
using FractalSet = std::vector<ComplexDouble>;
FractalSet grid_set;

FractalSet Fractal() {
    ComplexDouble zero_elm(0, 0);

    double res = 0.002;


    for (double i = -2.0; i < 2.0; i += res) {
            for (double j = -2.0; j < 2.0; j += res) {
                ComplexDouble c(i, j);
                grid_set.push_back(c);
            }
        }
    


    std::cout << "Writing to file..." << std::endl;
    std::ofstream file;
    file.open("grid_set.txt");
    file << "i" << "," << "j" << "\n";
	for(int i=0;i<grid_set.size();++i){
		file << real(grid_set[i]) << "," << imag(grid_set[i]) << "\n";
	}
	file.close();

    std::cout << "Number of points: " << grid_set.size() << std::endl;

    return grid_set;
}

int main() {
    Fractal();
    return 0;
}