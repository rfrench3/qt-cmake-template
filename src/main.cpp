#include "window.hpp"
#include <QApplication>

//cmake -B build && cmake --build build

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Tester test;
    test.show();

    app.exec();
}