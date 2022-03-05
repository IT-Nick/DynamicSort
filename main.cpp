#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
//колонки - данно (длинна ключа)
//берем колонку и считаем количество вхождений элементов (далее находим самое большое количество)
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
            throw out_of_range("num_rows must be >= 0");
        }
        if (num_columns < 0) {
            throw out_of_range("num_columns must be >= 0");
        }
        if (num_rows == 0 || num_columns == 0) {
            num_rows = num_columns = 0;
        }

        num_rows_ = num_rows;
        num_columns_ = num_columns;
        elements_.assign(num_rows, vector<int>(num_columns));
    }

    int& At(int row, int column) {
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

private:
    int num_rows_;
    int num_columns_;

    vector<vector<int>> elements_;
};

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
        throw invalid_argument("Mismatched number of rows");
    }

    if (one.GetNumColumns() != two.GetNumColumns()) {
        throw invalid_argument("Mismatched number of columns");
    }

    Matrix result(one.GetNumRows(), one.GetNumColumns());
    for (int row = 0; row < result.GetNumRows(); ++row) {
        for (int column = 0; column < result.GetNumColumns(); ++column) {
            result.At(row, column) = one.At(row, column) + two.At(row, column);
        }
    }

    return result;
}

//сортировка пузырьком
void bubbleSort(Matrix& m, string hint) {
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
void insertionSort(Matrix& m, string hint) {
    int temp, item;
    if (hint == "columns") {
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
    } else if(hint == "rows") {
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
    }
};

//быстрая сортировка
void quickSort(Matrix& m, int low, int high, string hint)  {
    if(hint == "columns") {
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
                quickSort(m, low, pi - 1, hint);
                quickSort(m, pi + 1, high, hint);
            }
        }
    } else if(hint == "rows") {
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
                quickSort(m, low, pi - 1, hint);
                quickSort(m, pi + 1, high, hint);
            }
        }
    }
};

//сортировка слиянием
void mergeSort(Matrix& m, string hint) {
};


istream& operator>>(istream& in, Matrix& matrix) {
    cout << "Do you want to enter - 0 or random - 1?" << endl;
    int input;
    cin >> input;
    cout << "Enter a rows and columns, for example 3 5:" << endl;

    int num_rows, num_columns;
    in >> num_rows >> num_columns;

    matrix.Reset(num_rows, num_columns);
    if(input == 0) {
        cout << "Enter a matrix:" << endl;
        for (int row = 0; row < num_rows; ++row) {
            for (int column = 0; column < num_columns; ++column) {
                in >> matrix.At(row, column);
            }
        }
    } else if(input == 1) {
        cout << "Enter a range, for example 10 100:" << endl;
        int a, b;
        cin >> a >> b;
        srand(time(NULL));
        for (int row = 0; row < num_rows; ++row) {
            for (int column = 0; column < num_columns; ++column) {
                matrix.At(row, column) = a + rand() % (b - a) + 1;
            }
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
    cout << "What do you want: full matrix - 0 or one element - 1?" << endl;
    int index;
    cin >> index;
    if(index == 0) {
        out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
        for (int row = 0; row < matrix.GetNumRows(); ++row) {
            for (int column = 0; column < matrix.GetNumColumns(); ++column) {
                if (column > 0) {
                    out << " ";
                }
                out << matrix.At(row, column);
            }
            out << endl;
        }
    } else if(index == 1) {
        cout << "Enter a position of an element (row, column), for example 1 2:" << endl;
        int row, column;
        cin >> row >> column;
        cout << matrix.At(row, column) << endl;
    }
    return out;
}

enum RequestType {
    INPUT, //ввод матрицы либо задать рандомно
    OUTPUT, //вывод матрицы или элемента
    SELECTSORT, //выбрать сортировку
    RESET //обнуление матрицы (создание нулевой матрицы)
};

int main() {
    Matrix m;
    Matrix m2;
    RequestType request;
    cout << "How many requests do you want?" << endl;
    int requests_count;
    cin >> requests_count;
    while(requests_count > 0) {
    cout << "Request: INPUT - 0, OUTPUT - 1, SELECTSORT - 2, RESET - 3" << endl;
    cout << "Enter a request: " << endl;
    int request_number;
    cin >> request_number;
    request = static_cast<RequestType>(request_number);
        switch (request) {
            case INPUT: {
                cin >> m;
                break;
            }
            case OUTPUT: {
                cout << m;
                break;
            }
            case SELECTSORT: {
                cout << "Select a sort: Bubble - 0, Insertion - 1, Quick - 2, Merge - 3" << endl;
                int select_sort;
                cin >> select_sort;
                cout << "Select: rows or columns" << endl;
                string select_pos;
                cin >> select_pos;
                if(select_sort == 0) {
                    bubbleSort(m, select_pos);
                }
                if(select_sort == 1) {
                    insertionSort(m, select_pos);
                }
                if(select_sort == 2) {
                    int low = 0;
                    int high = m.GetNumRows() - 1;
                    if(select_pos == "rows") {
                        low = 0;
                        high = m.GetNumColumns() - 1;
                    }
                    quickSort(m, low, high, select_pos);
                }
                if(select_sort == 3) {
                    mergeSort(m, select_pos);
                }
                break;
            }
            case RESET: {
                cout << "Enter a rows and columns your zero matrix, for example 3 5:" << endl;
                m.Reset(5, 5);
                break;
            }
        }
        requests_count--;
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

