//HEADERS
#include "Backend/gates.h"
#include "constants.h"
#include "mainwindow.h"

//QT
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) //At some point organize the #includes
{
    QApplication app(argc, argv);
    MainWindow window {};
    window.resize(constant::WIDTH, constant::HEIGHT);
    window.show();

//    std::cout << "test1" << std::endl;

//    NOTGate circuit1{};
//    NOTGate circuit2{};
//    CircuitIO circuit{1, 1};

//    std::cout << "test2" << std::endl;

//    CircuitComponent::connect(circuit1, 0, circuit2, 0);
//    CircuitComponent::connect(circuit, 0, circuit1, 0);
//    CircuitComponent::connect(circuit2, 0, circuit, 0);

//    std::cout << "test3" << std::endl;

//    bool *input {new bool[1]{false}};


//    circuit.run(input, 1);

//    std::cout << "test4" << std::endl;

//    std::cout << circuit.pinInArray()[0].state() << std::endl;



//    return 0;


    return app.exec();
}
