#include "../CSV.h"
#include <iostream>
#include <fstream>

int main(int argc, char const** argv) {
    paracefas::CSV data{argc > 1 ? argv[1] : "data.csv"};
    data.Post("1,2,3");
    std::cout << data.Get("x", 1001);
}