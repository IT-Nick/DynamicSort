#pragma once

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
    if (first < last) {
        mergeSort(m, first, (first + last) / 2); //сортировка левой части
        mergeSort(m, (first + last) / 2 + 1, last); //сортировка правой части
        if (hint == "columns") {
            for (int k = 0; k < m.GetNumColumns(); k++) {
                int middle, start, final, j;
                int *mas = new int[100];
                middle = (first + last) / 2;
                start = first;
                final = middle + 1;
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
                int *mas = new int[100];
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
/*
//сортировка слиянием
void mergeSort(Matrix& m, int l, int r) {
    std::string hint = m.GetHint();
    if (l < r) {
        int mi = l + (r - l) / 2;
        mergeSort(m, l, mi);
        mergeSort(m, mi + 1, r);
        int n1 = mi - l + 1;
        int n2 = r - mi;
        int L[n1], M[n2];
        for (int i = 0; i < n1; i++)
            L[i] = m.At(l + i, 0);
        for (int j = 0; j < n2; j++)
            M[j] = m.At(mi + 1 + j, 0);
        int i, j, k;
        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= M[j]) {
                m.At(k, 0) = L[i];
                i++;
            } else {
                m.At(k, 0) = M[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            m.At(k, 0) = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            m.At(k, 0) = M[j];
            j++;
            k++;
        }
    }
}
 */