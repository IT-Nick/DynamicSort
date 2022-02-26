#include <iostream>
#include <vector>
#include <ctime>

int bubbleSort() {
    int result = 0;
    return result;
}

int insertionSort() {
    int result = 0;
    return result;
}

int quickSort() {
    int result = 0;
    return result;
}

int mergeSort() {
    int result = 0;
    return result;
}

int main() {
    srand(time(NULL));
    std::cout << "Enter sort method:" << std::endl;
    std::cout << "Enter array size:" << std::endl;
    int n = 0;
    std::cin >> n;
    std::cout << "Enter rand range:" << std::endl;
    int a, b = 0;
    std::cin >> a >> b;
    std::cout << "Delete old array:" << std::endl;
    std::cout << "Create new array:" << std::endl;
    std::vector<int> v(n);
    for (auto &i: v) {
        i = a + rand() % (b - a + 1);
    }
    int w = 2;
    while(w > 0) {
        std::cout << "What do you want to show: ALL - array, ONE - element" << std::endl;
        std::string s = "";
        std::cin >> s;
        if (s == "ALL") {
            for (auto i: v) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        if (s == "ONE") {
            int value = 0;
            std::cout << "Enter index of an element:" << std::endl;
            std::cin >> value;
            std::cout << v[value] << std::endl;
        }
        w--;
    }
    return 0;
}
