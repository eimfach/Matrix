#pragma once
#pragma warning( disable : 4365 )
#include <vector>
#include <cassert>
#include <iostream>

#include <gsl/util>

class Matrix {
public:
	size_t columns{ 0 };
	size_t rows{ 0 };
	std::vector<std::vector<double>> matrix;
	std::vector<double> fields;

	Matrix(size_t r, size_t c) {
		columns = c;
		rows = r;

		//matrix.resize(rows);
		fields.resize(r * c);
		//for (size_t i{ 0 };i < rows;i++) {
		//	gsl::at(matrix, i).resize(columns, 0.0);
		//}
	}

	Matrix(size_t r, size_t c, std::vector<double> data) {
		columns = c;
		rows = r;
		//matrix.resize(rows);
		fields = data;
		//for (size_t x{ 0 };x < r;x++) {
		//	std::vector<double> row;
		//	row.resize(r);

		//	for (size_t y{ 0 };y < c;y++) {
		//		gsl::at(row, y) = gsl::at(data, r*x+y);
		//	}
		//	gsl::at(matrix, x) = row;
		//}
	}

	//Matrix multiply(const Matrix &matrix2) {
	//	assert(columns == matrix2.rows);
	//	Matrix new_matrix{ rows, matrix2.columns };

	//	for (size_t r{ 0 };r < new_matrix.rows;r++) {
	//		for (size_t c{ 0 };c < new_matrix.columns;c++) {
	//			double product{ 0.0 };
	//			for (size_t r2{ 0 }; r2 < matrix2.rows; r2++) {
	//				const double multiplier{ gsl::at(gsl::at(matrix, r), r2) };
	//				product += multiplier * gsl::at(gsl::at(matrix2.matrix, r2), c);
	//				//std::cout << "Multiplying: " << multiplier << " x " << matrix2.matrix[r2][c] << "\n";
	//			}
	//			gsl::at(gsl::at(new_matrix.matrix, r), c) = product;
	//		}
	//	}

	//	return new_matrix;
	//}

	Matrix operator*(const Matrix &matrix_y) {
		using namespace gsl;

		assert(columns == matrix_y.rows);
		Matrix new_matrix{ rows, matrix_y.columns };

		size_t row_x{ 0 };
		size_t col_y{ 0 };
		size_t span_index{ 0 };

		for (size_t field{ 0 };field <= fields.size();field++) {

			if (field > 0 && field % columns == 0) {
				span_index = 0;

				if (col_y < matrix_y.columns - 1) {
					field -= columns;
					col_y += 1;
				}
				else {
					col_y = 0;
					row_x += 1;
				}
			}

			if (field == fields.size()) break;

			// follow the columns in row of the first matrix
			const double multiplicand{ at(fields, row_x * columns + span_index) };
			// follow the rows in one column of the second matrix
			const double multiplicator{ at(matrix_y.fields, span_index * columns + col_y) };
			//std::cout << "Multiplying " << multiplicand << " x " << multiplicator << "\n";
			at(new_matrix.fields, row_x * columns + col_y) += multiplicand * multiplicator;
			span_index += 1;
		}

		return new_matrix;
	}

	size_t size() const noexcept {
		return rows * columns;
	}
};