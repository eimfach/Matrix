#pragma once
//#pragma warning( disable : 4365 )
#include <vector>
#include <cassert>
#include <iostream>

#include <gsl/util>

class Matrix {
public:
	size_t columns{ 0 };
	size_t rows{ 0 };
	std::vector<double> fields;

	Matrix(size_t r, size_t c) {
		columns = c;
		rows = r;
		fields.resize(r * c);
	}

	Matrix(size_t r, size_t c, std::vector<double> data) {
		columns = c;
		rows = r;
		fields = data;
	}

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

				if (col_y < columns - 1) {
					field -= columns;
					col_y += 1;
				}
				else {
					col_y = 0;
					row_x += 1;
				}
			}

			if (field == fields.size()) 
				break;

			// follow the columns in row of the first matrix
			const double multiplicand{ at(fields, gsl::narrow_cast<gsl::index>(row_x * columns + span_index)) };
			// follow the rows in one column of the second matrix
			const double multiplicator{ at(matrix_y.fields,  gsl::narrow_cast<gsl::index>(span_index * columns + col_y)) };
			at(new_matrix.fields, gsl::narrow_cast<gsl::index>(row_x * columns + col_y)) += multiplicand * multiplicator;
			span_index += 1;
		}

		return new_matrix;
	}

	Matrix operator*(double multiplier) {
		using namespace gsl;
		Matrix new_matrix{ rows, columns };
		for (index field{ 0 };field < narrow_cast<index>(fields.size());field++) {
			at(new_matrix.fields, field) = at(fields, field) * multiplier;
		}

		return new_matrix;
	}

	size_t size() const noexcept {
		return rows * columns;
	}
};