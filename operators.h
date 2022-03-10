#pragma once
#include <ctime>

std::istream& operator>>(std::istream& in, Matrix& matrix) {
    std::cout << "Do you want to enter - 0 or random - 1?" << std::endl;
    int input;
    std::cin >> input;
    std::cout << "Enter a rows and columns, for example 3 5:" << std::endl;

    int num_rows, num_columns;
    in >> num_rows >> num_columns;

    matrix.Reset(num_rows, num_columns);
    if (input == 0) {
        std::cout << "Enter a matrix:" << std::endl;
        for (int row = 0; row < num_rows; ++row) {
            for (int column = 0; column < num_columns; ++column) {
                in >> matrix.At(row, column);
            }
        }
    } else if (input == 1) {
        std::cout << "Enter a range, for example 10 100:" << std::endl;
        int a, b;
        std::cin >> a >> b;
        srand(time(NULL));
        for (int row = 0; row < num_rows; ++row) {
            for (int column = 0; column < num_columns; ++column) {
                matrix.At(row, column) = a + rand() % (b - a) + 1;
            }
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    std::cout << "What do you want: full matrix - 0 or one element - 1?" << std::endl;
    int index;
    std::cin >> index;
    if (index == 0) {
        out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << std::endl;
        for (int row = 0; row < matrix.GetNumRows(); ++row) {
            for (int column = 0; column < matrix.GetNumColumns(); ++column) {
                if (column > 0) {
                    out << " ";
                }
                out << matrix.At(row, column);
            }
            out << std::endl;
        }
    } else if (index == 1) {
        std::cout << "Enter a position of an element (row, column), for example 1 2:" << std::endl;
        int row, column;
        std::cin >> row >> column;
        std::cout << matrix.At(row, column) << std::endl;
    }
    return out;
}


bool operator==(const Matrix& one, const Matrix& two) {
    if (one.GetNumRows() != two.GetNumRows()) {
        return false;
    }

    if (one.GetNumColumns() != two.GetNumColumns()) {
        return false;
    }

    for (int row = 0; row < one.GetNumRows(); ++row) {
        for (int column = 0; column < one.GetNumColumns(); ++column) {
            if (one.At(row, column) != two.At(row, column)) {
                return false;
            }
        }
    }

    return true;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
    if (one.GetNumRows() != two.GetNumRows()) {
        throw std::invalid_argument("Mismatched number of rows");
    }

    if (one.GetNumColumns() != two.GetNumColumns()) {
        throw std::invalid_argument("Mismatched number of columns");
    }

    Matrix result(one.GetNumRows(), one.GetNumColumns());
    for (int row = 0; row < result.GetNumRows(); ++row) {
        for (int column = 0; column < result.GetNumColumns(); ++column) {
            result.At(row, column) = one.At(row, column) + two.At(row, column);
        }
    }

    return result;
}
