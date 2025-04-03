#include "matrix.h"
#include "floating_equal.h"
//#include "test_matrix.h"

#include <iostream>
#include <cassert>
#include <iomanip>
#include <string>
#include <chrono>
#include <iterator>

#include <gsl/util>



void print_column_header(size_t columns) {
    std::cout << std::setfill(' ') << std::setw(7);
    for (size_t x{ 0 }; x < columns; x++) {
        //int padding = static_cast<int>(x / 10);
        std::cout << x << std::setfill(' ') << std::setw(9);
    }
    std::cout << "\n";
}

void print_row_number(int n, size_t columns) {
    if (n == 0) {
        std::cout << std::setfill('0') << std::setw(5) << 0;
    }
    else if ((n + 1) % columns == 0) {
        const size_t column{ (n + 1) / columns };
        std::cout << "\n" << std::setfill('0') << std::setw(5) << column;
    }
}

void print_value(double v) {
    std::cout << "|";
    std::cout << std::fixed;
    std::cout << std::setprecision(6) << v;
}

void print_matrix(Matrix m) {
    //print_column_header(m.columns);
    for (size_t r{ 0 }; r < m.rows;r++) {
        std::cout << std::setfill('0') << std::setw(5) << r;
        for (size_t c{ 0 };c < m.columns;c++) {
            print_value(gsl::at(gsl::at(m.matrix, r), c));
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::pair<Matrix, std::chrono::nanoseconds> test_multiplication() {
    const double l1[9] = { 2.3, 4.0, 3.5, 5.1, 0.8, 9.4, 1.7, 6.2, 7.0 };
    const double l2[9] = { 8.2, 1.4, 5.8, 0.5, 6.0, 4.3, 3.6, 2.1, 0.9 };
    Matrix m = Matrix{ 3, 3, std::vector<double>{std::begin(l1), std::end(l1)} };
    Matrix m2 = Matrix{ 3, 3, std::vector<double>{std::begin(l2), std::end(l2)} };
    // std::vector<double> v{l1, l1 + 3};
    // std::vector<double> v(l1, l1 + sizeof l1 / sizeof l1[0]);

    const std::chrono::time_point start = std::chrono::high_resolution_clock::now();
    Matrix m3{ m * m2 };
    const std::chrono::time_point end = std::chrono::high_resolution_clock::now();
    const std::chrono::nanoseconds elapsed = end - start;

    std::vector<double> test{ 33.46, 34.57, 33.69, 76.06, 31.68, 41.48, 42.24, 54.28, 42.82 };
    for (size_t i{ 0 }; i < test.size();i++) assert(approximatelyEqualAbsRel(gsl::at(test, i), gsl::at(m3.fields, i), absEps, relEps));

    return std::pair{ m3, elapsed };
}


int main()
{
    constexpr int test_repeats{ 10000 };
    std::chrono::nanoseconds total_time{0};
    for (int x{ 0 };x < test_repeats;x++) {
        std::pair result = test_multiplication();
        total_time += result.second;
        //print_matrix(result.first);
    }
    std::cout << "Average time of " << test_repeats << " Matrix multiplications: " << total_time / test_repeats << "\n";
    std::cout << "Total time: " << total_time.count() / 1000.0 / 1000.0 << "ms";
    //Matrix m = Matrix{ 100, 100, MATRIX_DATA_U };
    //Matrix m2 = Matrix{ 100, 100, MATRIX_DATA };

    return 0;
}
