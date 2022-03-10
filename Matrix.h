#pragma once
#include <stdexcept>
#include <vector>

class Matrix {
public:
    Matrix() {
        num_rows_ = 0;
        num_columns_ = 0;
    }

    Matrix(int num_rows, int num_columns) {
        Reset(num_rows, num_columns);
    }

    void Reset(int num_rows, int num_columns) {
        if (num_rows < 0) {
            throw std::out_of_range("num_rows must be >= 0");
        }
        if (num_columns < 0) {
            throw std::out_of_range("num_columns must be >= 0");
        }
        if (num_rows == 0 || num_columns == 0) {
            num_rows = num_columns = 0;
        }

        num_rows_ = num_rows;
        num_columns_ = num_columns;
        elements_.assign(num_rows, std::vector<int>(num_columns));
    }

    int &At(int row, int column) {
        return elements_.at(row).at(column);
    }

    int At(int row, int column) const {
        return elements_.at(row).at(column);
    }

    int GetNumRows() const {
        return num_rows_;
    }

    int GetNumColumns() const {
        return num_columns_;
    }

    std::string GetHint() const {
        return hint_;
    }

    void SetHint(std::string hint) {
        hint_ = hint;
    }

private:
    std::string hint_;
    int num_rows_;
    int num_columns_;

    std::vector<std::vector<int>> elements_;
};