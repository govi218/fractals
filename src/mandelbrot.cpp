#include <iostream>

#include <qcustomplot.h>

//QT5
#include <QApplication>
#include <QFileDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMessageBox>

#include "../include/fractals.hpp"

int main() {
    auto m_set = fractals::mandelbrot();
    std::cout << "{ ";
    for (auto i : m_set) {
        std::cout << i << " ";
    }
    std::cout << "}" << std::endl;

    QCustomPlot custom_plot;
    custom_plot.addGraph();
    custom_plot.graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    custom_plot.graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
}
