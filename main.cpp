#include <iostream>
#include <vector>
#include <thread>
#include "Matrix.h"
#include "Utilities.h"

using namespace std;

int main() {
    Matrix <double> M( 5000, 400 );
    M.fillArchive("Xdata.txt");
    sigmoidFunction( M );

}
