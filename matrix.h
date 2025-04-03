#pragma once
#include <vector>
#include <cassert>
#include <iostream>

#include <gsl/util>

class Matrix {
public:
	size_t columns{ 0 };
	size_t rows{ 0 };
	std::vector<std::vector<double>> matrix;

	Matrix(size_t r, size_t c) {
		columns = c;
		rows = r;

		matrix.resize(rows);
		for (size_t i{ 0 };i < rows;i++) {
			gsl::at(matrix, i).resize(columns, 0.0);
		}
	}

	Matrix(size_t r, size_t c, std::vector<double> data) {
		columns = c;
		rows = r;
		matrix.resize(rows);

		for (size_t x{ 0 };x < r;x++) {
			std::vector<double> row;
			row.resize(r);

			for (size_t y{ 0 };y < c;y++) {
				gsl::at(row, y) = gsl::at(data, r*x+y);
			}
			gsl::at(matrix, x) = row;
		}
	}

	Matrix operator*(const Matrix &matrix2) {
		assert(columns == matrix2.rows);
		Matrix new_matrix{ rows, matrix2.columns };

		for (size_t r{ 0 };r < new_matrix.rows;r++) {
			for (size_t c{ 0 };c < new_matrix.columns;c++) {
				double product{ 0.0 };
				for (size_t r2{ 0 }; r2 < matrix2.rows; r2++) {
					const double multiplier{ gsl::at(gsl::at(matrix, r), r2) };
					product += multiplier * gsl::at(gsl::at(matrix2.matrix, r2), c);
					//std::cout << "Multiplying: " << multiplier << " x " << matrix2.matrix[r2][c] << "\n";
				}
				gsl::at(gsl::at(new_matrix.matrix, r), c) = product;
			}
		}

		return new_matrix;
	}

	size_t size() const noexcept {
		return rows * columns;
	}
};