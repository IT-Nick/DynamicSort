#include <iostream>
#include <algorithm>

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

//сортировка пузырьком
void bubbleSort(Matrix& m) {
    std::string hint = m.GetHint();
    int numRows = m.GetNumRows();
    int numColumns = m.GetNumColumns();
    if (hint == "rows") {
        numRows = m.GetNumColumns();
        numColumns = m.GetNumRows();
    }
    for (int k = 0; k < numColumns; k++) {
        for (int i = 0; i < numRows; i++) {
            bool flag = true;
            for (int j = 0; j < numRows - (i + 1); j++) {
                int row = j;
                int column = k;
                int next = j + 1;
                if (hint == "columns") {
                    if (m.At(j, k) > m.At(next, k)) {
                        flag = false;
                        int temp = m.At(j, k);
                        m.At(j, k) = m.At(next, k);
                        m.At(next, k) = temp;
                    }
                } else if (hint == "rows") {
                    if (m.At(k, j) > m.At(k, next)) {
                        flag = false;
                        int temp = m.At(k, j);
                        m.At(k, j) = m.At(k, next);
                        m.At(k, next) = temp;
                    }
                }
            }
            if (flag) {
                break;
            }
        }
    }
}

//сортировка вставками
void insertionSort(Matrix& m) {
    std::string hint = m.GetHint();
    int temp, item;
    if (hint == "columns") {
        for (int k = 0; k < m.GetNumColumns(); k++) {
            for (int counter = 1; counter < m.GetNumRows(); counter++) {
                temp = m.At(counter, k);
                item = counter - 1;
                while (item >= 0 && m.At(item, k) > temp) {
                    m.At(item + 1, k) = m.At(item, k);
                    m.At(item, k) = temp;
                    item--;
                }
            }
        }
    } else if (hint == "rows") {
        for (int k = 0; k < m.GetNumRows(); k++) {
            for (int counter = 1; counter < m.GetNumColumns(); counter++) {
                temp = m.At(k, counter);
                item = counter - 1;
                while (item >= 0 && m.At(k, item) > temp) {
                    m.At(k, item + 1) = m.At(k, item);
                    m.At(k, item) = temp;
                    item--;
                }
            }
        }
    }
}

//быстрая сортировка
void quickSort(Matrix& m, int low, int high) {
    std::string hint = m.GetHint();
    if (hint == "columns") {
        for (int k = 0; k < m.GetNumColumns(); k++) {
            if (low < high) {
                //partition
                int pi;
                int pivot = m.At(high, k);
                int i = (low - 1);
                for (int j = low; j < high; j++) {
                    if (m.At(j, k) <= pivot) {
                        i++;
                        int tmp = m.At(i, k);
                        m.At(i, k) = m.At(j, k);
                        m.At(j, k) = tmp;
                    }
                }
                int tmp = m.At(i + 1, k);
                m.At(i + 1, k) = m.At(high, k);
                m.At(high, k) = tmp;
                pi = i + 1;
                //
                quickSort(m, low, pi - 1);
                quickSort(m, pi + 1, high);
            }
        }
    } else if (hint == "rows") {
        for (int k = 0; k < m.GetNumRows(); k++) {
            if (low < high) {
                //partition
                int pi;
                int pivot = m.At(k, high);
                int i = (low - 1);
                for (int j = low; j < high; j++) {
                    if (m.At(k, j) <= pivot) {
                        i++;
                        int tmp = m.At(k, i);
                        m.At(k, j) = m.At(k, j);
                        m.At(k, j) = tmp;
                    }
                }
                int tmp = m.At(k, i + 1);
                m.At(k, i + 1) = m.At(k, high);
                m.At(k, high) = tmp;
                pi = i + 1;
                //
                quickSort(m, low, pi - 1);
                quickSort(m, pi + 1, high);
            }
        }
    }
}

//рекурсивная процедура сортировки
void mergeSort(Matrix& m, int first, int last) {
    std::string hint = m.GetHint();
    int size = 10000;
    if (first < last) {
        mergeSort(m, first, (first + last) / 2); //сортировка левой части
        mergeSort(m, (first + last) / 2 + 1, last); //сортировка правой части
        if (hint == "columns") {
            for (int k = 0; k < m.GetNumColumns(); k++) {
                int middle, start, final, j;
                int *mas = new int[size];
                middle = (first + last) / 2; //вычисление среднего элемента
                start = first; //начало левой части
                final = middle + 1; //начало правой части
                for (j = first; j <= last; j++) //выполнять от начала до конца
                    if ((start <= middle) && ((final > last) || (m.At(start, k) < m.At(final, k)))) {
                        mas[j] = m.At(start, k);
                        start++;
                    } else {
                        mas[j] = m.At(final, k);
                        final++;
                    }
//возвращение результата в список
                for (j = first; j <= last; j++) m.At(j, k) = mas[j];
                delete[]mas;
            }
        } else if (hint == "rows") {
            for (int k = 0; k < m.GetNumRows(); k++) {
                int middle, start, final, j;
                int *mas = new int[size];
                middle = (first + last) / 2; //вычисление среднего элемента
                start = first; //начало левой части
                final = middle + 1; //начало правой части
                for (j = first; j <= last; j++) //выполнять от начала до конца
                    if ((start <= middle) && ((final > last) || (m.At(k, start) < m.At(k, final)))) {
                        mas[j] = m.At(k, start);
                        start++;
                    } else {
                        mas[j] = m.At(k, final);
                        final++;
                    }
//возвращение результата в список
                for (j = first; j <= last; j++) m.At(k, j) = mas[j];
                delete[]mas;
            }
        }
    }
}

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

enum class RequestType {
    INPUT, //ввод матрицы либо задать рандомно
    OUTPUT, //вывод матрицы или элемента
    SELECTSORT, //выбрать сортировку
    RESET //обнуление матрицы (создание нулевой матрицы)
};

int main() {
    Matrix m;
    RequestType request;
    std::cout << "How many requests do you want?" << std::endl;
    int requests_count;
    std::cin >> requests_count;
    while (requests_count > 0) {
        try {
        std::cout << "Request: INPUT - 0, OUTPUT - 1, SELECTSORT - 2, RESET - 3" << std::endl;
        std::cout << "Enter a request: " << std::endl;
        int request_number;
        std::cin >> request_number;
        request = static_cast<RequestType>(request_number);
        switch (request) {
            case RequestType::INPUT: {
                std::cin >> m;
                break;
            }
            case RequestType::OUTPUT: {
                std::cout << m;
                break;
            }
            case RequestType::SELECTSORT: {
                std::cout << "Select a sort: Bubble - 0, Insertion - 1, Quick - 2, Merge - 3" << std::endl;
                int select_sort;
                std::cin >> select_sort;
                std::cout << "Select: rows or columns" << std::endl;
                std::string select_pos;
                std::cin >> select_pos;
                m.SetHint(select_pos);
                if (select_sort == 0) {
                    bubbleSort(m);
                }
                if (select_sort == 1) {
                    insertionSort(m);
                }
                if (select_sort == 2) {
                    int high = m.GetNumRows() - 1;
                    if (select_pos == "rows") {
                        high = m.GetNumColumns() - 1;
                    }
                    quickSort(m, 0, high);
                }
                if (select_sort == 3) {
                    int high = m.GetNumRows() - 1;
                    if (select_pos == "rows") {
                        high = m.GetNumColumns() - 1;
                    }
                    mergeSort(m,0, high);
                }
                break;
            }
            case RequestType::RESET: {
                std::cout << "Enter a rows and columns your zero matrix, for example 3 5:" << std::endl;
                int reset_row, reset_column;
                std::cin >> reset_row >> reset_column;
                m.Reset(reset_row, reset_column);
                break;
            }
        }
        requests_count--;
        } catch (std::exception& e) {
            std::cerr << std::endl << e.what() << std::endl;
        }
    }
    return 0;
}

/*
3 5
6 4 -1 9 8
12 1 2 9 -5
-4 0 12 8 6

3 5
5 1 0 -8 23
14 5 -6 6 9
8 0 5 4 1
*/

