#include <iostream>
#include <fstream>
#include <complex>
#include <chrono>



#include "../external/qcustomplot/qcustomplot.h"

// QT5
#include <QApplication>
#include <QFileDialog>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

#include "../include/fractals.hpp"

using ComplexDouble = std::complex<double>;
using FractalSet = std::vector<ComplexDouble>;

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    auto m_set = fractals::thread();
    std::cout << "m_set size is: " << m_set.size() << std::endl;
    // std::cout << "{ ";
    // for (auto i : m_set) {
    //     std::cout << i << " ";
    // }
    // std::cout << "}" << std::endl;

    // To output the set (vector m_set) into a text file

    // std::ofstream file;
	// file.open("m_set.txt");
	// for(int i=0;i<m_set.size();++i){
	// 	file<<m_set[i]<<" ";
	// }
	// file.close();

    // QCustomPlot custom_plot;
    // custom_plot.addGraph();
    // custom_plot.graph(0)->setPen(QPen(Qt::blue)); // line color blue for
    // first graph custom_plot.graph(0)->setBrush(QBrush(QColor(0, 0, 255,20))); // first graph will be filled with translucent blue
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Runtime is " << duration.count() << " seconds" <<std::endl;
    return 0;
}
    