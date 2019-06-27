#include <iostream>
#include <vector>
#include <thread>
#include "Matriz.h"

using namespace std;

int main() {
    Matrix<double> M1( 2, 4 );
    M1.fillArchive("data.txt");
    cout << M1 << endl;
    return 0;

}
