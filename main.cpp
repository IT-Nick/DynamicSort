#include <iostream>
#include <algorithm>

#include <stdexcept>
#include <vector>

#include "Matrix.h"
#include "sorts.h"
#include "operators.h"


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

