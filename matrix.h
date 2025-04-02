#pragma once
#include <vector>
#include <cassert>
#include <iostream>

#include <gsl/util>

class Matrix {
public:
	uint32_t columns{ 0 };
	uint32_t rows{ 0 };
	std::vector<std::vector<double>> matrix;

	Matrix(uint32_t r, uint32_t c) {
		columns = c;
		rows = r;

		matrix.resize(rows);
		for (uint32_t i{ 0 };i < rows;i++) {
			gsl::at(matrix, i).resize(columns, 0.0f);
		}
	}

	Matrix(uint32_t r, uint32_t c, std::vector<double> data) {
		columns = c;
		rows = r;
		matrix.resize(rows);

		for (uint32_t x{ 0 };x < r;x++) {
			std::vector<double> row;
			row.resize(r);

			for (uint32_t y{ 0 };y < c;y++) {
				gsl::at(row, y) = gsl::at(data, r*x+y);
			}
			gsl::at(matrix, x) = row;
		}
	}

	Matrix operator*(const Matrix &matrix2) {
		assert(columns == matrix2.rows);
		Matrix new_matrix{ rows, matrix2.columns };

		for (uint32_t r{ 0 };r < new_matrix.rows;r++) {
			for (uint32_t c{ 0 };c < new_matrix.columns;c++) {
				double product{ 0.0 };
				for (uint32_t r2{ 0 }; r2 < matrix2.rows; r2++) {
					const double multiplier{ gsl::at(gsl::at(matrix, r), r2) };
					product += multiplier * gsl::at(gsl::at(matrix2.matrix, r2), c);
					//std::cout << "Multiplying: " << multiplier << " x " << matrix2.matrix[r2][c] << "\n";
				}
				gsl::at(gsl::at(new_matrix.matrix, r), c) = product;
			}
		}

		return new_matrix;
	}
};