#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

// Убираем структуру Node, работаем только с вектором
// template <typename T>
// struct Node {
//     T data;
//     Node* next;
//     Node(T value) : data(value), next(nullptr) {}
// };

// Функция для чтения из файла (возвращает вектор)
template <typename T>
vector<T> readFromFile(const string& filename) {
    ifstream file(filename);
    vector<T> data;

    if (!file) return data;

    T value;
    while (file >> value) {
        data.push_back(value);
    }

    return data;
}

// Функция проверки сортировки для вектора
template <typename T>
bool isSorted(const vector<T>& data) {
    for (size_t i = 0; i < data.size() - 1; i++) {
        if (data[i] > data[i + 1]) return false;
    }
    return true;
}

// Функция печати вектора
template <typename T>
void printList(const vector<T>& data, int limit = 10) {
    int count = 0;
    for (size_t i = 0; i < data.size() && count < limit; i++) {
        cout << data[i] << " ";
        count++;
    }
    if (data.size() > limit) cout << "...";
    cout << endl;
}



// Функция копирования вектора
template <typename T>
vector<T> copyList(const vector<T>& data) {
    return vector<T>(data);  // Простое копирование
}

// Тестирование сортировки с замером времени (для вектора)
template <typename T>
void testSort(const string& name, vector<T>(*sortFunc)(vector<T>), const vector<T>& data) {
    vector<T> copy = copyList(data);

    auto start = high_resolution_clock::now();
    copy = sortFunc(copy);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    double time_ms = duration.count() / 1000.0;

    cout << name << ": " << time_ms << " мс";
    cout << " (Отсортирован: " << (isSorted(copy) ? "Да" : "Нет") << ")" << endl;
}

//Ульяна
template <typename T>
void merge(vector<T>& arr, int left, int mid, int right, vector<T>& temp) { //функция слияния с временным буфером
    int i = left;      // Индекс начала левой части
    int j = mid + 1;   // Индекс начала правой части
    int k = left;      // Индекс в временном массиве
    // Две части во временный массив
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        }
        else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    // Копирование оставшихся элементов левой части, если есть
    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }
    // Копирование оставшихся элементов правой части, если есть
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }
    // Копирование отсортированных данных обратно в исходный массив
    for (int idx = left; idx <= right; idx++) {
        arr[idx] = temp[idx];
    }
}

template <typename T>
void mergeSortHelper(vector<T>& arr, int left, int right, vector<T>& temp) { //вспомогательная функция деления массива
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortHelper(arr, left, mid, temp); // Сортировка первой половины
        mergeSortHelper(arr, mid + 1, right, temp); // Сортировка второй половины

        merge(arr, left, mid, right, temp); // Объединение отсортированных половин
    }
}

template <typename T>
vector<T> mergeSort(vector<T> arr) { //основная функция
    if (arr.size() > 1) {
        vector<T> temp(arr.size()); //временный буфер для всей сортировки
        mergeSortHelper(arr, 0, arr.size() - 1, temp);
    }
    return arr;
}
//Ульяна



//Диана
template <typename T>
vector<T> shellSort(vector<T> arr) {
    int n = arr.size();

    // Начинаем с большого промежутка, затем уменьшаем его
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Для каждого промежутка выполняем сортировку вставками
        for (int i = gap; i < n; i++) {
            // Сохраняем текущий элемент
            T current = arr[i];
            int j = i;

            // Сдвигаем элементы arr[0..i-gap], которые больше current,
            // на позицию gap вперед
            while (j >= gap && arr[j - gap] > current) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            // Вставляем сохраненный элемент в правильную позицию
            arr[j] = current;
        }
    }

    return arr;
}
//Диана



//Влада
template <typename T>
int partition(vector<T>& arr, int low, int high) {
    // Выбираем опорный элемент
    T pivot = arr[high];

    // Индекс для элемента, который будет разделять массив
    int i = low - 1;

    // Проходим по всем элементам от low до high-1
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;  // Увеличиваем индекс разделителя
            swap(arr[i], arr[j]);  // Меняем местами
        }
    }

    // Ставим опорный элемент на правильную позицию
    swap(arr[i + 1], arr[high]);

    // Возвращаем индекс опорного элемента
    return i + 1;
}

template <typename T>
void quickSortHelper(vector<T>& arr, int low, int high) {
    if (low < high) {
        // Находим индекс опорного элемента
        int pivotIndex = partition(arr, low, high);

        // Рекурсивно сортируем левую часть
        quickSortHelper(arr, low, pivotIndex - 1);

        // Рекурсивно сортируем правую часть
        quickSortHelper(arr, pivotIndex + 1, high);
    }
}

template <typename T>
vector<T> quickSort(vector<T> arr) {
    if (arr.size() > 1) {
        quickSortHelper(arr, 0, arr.size() - 1);
    }
    return arr;
}
//Влада



//Лиза
int dndn;
template <typename T>
vector<T> insertionSort(vector<T> arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;

        // Сдвигаем элементы больше key на одну позицию вправо
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Вставляем key на правильную позицию
        arr[j + 1] = key;
    }

    return arr;
}
//Лиза


// Генерация тестовых данных (оставляем без изменений)
void generateDataFile(const string& filename, int type) {
    ofstream file(filename);
    srand(time(0));

    switch (type) {
    case 1:
        for (int i = 0; i < 1000; i++) {
            file << rand() % 10000 - 5000 << " ";
        }
        cout << "Создан файл data1.txt с 1000 целых чисел" << endl;
        break;

    case 2:
        for (int i = 0; i < 10000; i++) {
            file << rand() % 10000 - 5000 << " ";
        }
        cout << "Создан файл data2.txt с 10000 целых чисел" << endl;
        break;

    case 3:
    {
        for (int i = 0; i < 1000; i++) {
            char letter = 'a' + rand() % 26;
            file << letter << " ";
        }
        cout << "Создан файл data3.txt с 1000 английских букв" << endl;
        break;
    }

    case 4:
        for (int i = 1000; i >= 1; i--) {
            file << i << " ";
        }
        cout << "Создан файл data4.txt с 1000 чисел (1000..1)" << endl;
        break;

    case 5:
        for (int i = 0; i < 1000; i++) {
            float val = (rand() % 10000 - 5000) / 100.0f;
            file << val << " ";
        }
        cout << "Создан файл data5.txt с 1000 дробных чисел" << endl;
        break;
    }

    file.close();
}

void showMenu() {
    cout << "\nТЕСТИРОВАНИЕ СОРТИРОВОК НА ВЕКТОРАХ" << endl;
    cout << "1. 1000 целых чисел (data1.txt)" << endl;
    cout << "2. 10000 целых чисел (data2.txt)" << endl;
    cout << "3. 1000 букв (data3.txt)" << endl;
    cout << "4. 1000 чисел в обратном порядке (data4.txt)" << endl;
    cout << "5. 1000 дробных чисел (data5.txt)" << endl;
    cout << "6. Выход" << endl;
    cout << "Ваш выбор (1-6): ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;

    do {
        showMenu();
        cin >> choice;

        if (choice >= 1 && choice <= 5) {
            string filename = "data" + to_string(choice) + ".txt";

            // Генерируем файл, если нужно
            generateDataFile(filename, choice);

            switch (choice) {
            case 1:
            case 2:
            case 4: {
                vector<int> data = readFromFile<int>(filename);
                if (!data.empty()) {
                    cout << "\nПервые 10 элементов: ";
                    printList(data);
                    cout << "\nРезультаты тестирования:" << endl;
                    testSort("Сортировка Шелла", shellSort<int>, data);
                    testSort("Сортировка слиянием", mergeSort<int>, data);
                    testSort("Быстрая сортировка", quickSort<int>, data);
                    testSort("Сортировка вставками", insertionSort<int>, data);

                }
                break;
            }

            case 3: {
                vector<char> data = readFromFile<char>(filename);
                if (!data.empty()) {
                    cout << "\nПервые 10 элементов: ";
                    printList(data);
                    cout << "\nРезультаты тестирования:" << endl;
                    testSort("Сортировка Шелла", shellSort<char>, data);
                    testSort("Сортировка слиянием", mergeSort<char>, data);
                    testSort("Быстрая сортировка", quickSort<char>, data);
                    testSort("Сортировка вставками", insertionSort<char>, data);
                }
                break;
            }

            case 5: {
                vector<float> data = readFromFile<float>(filename);
                if (!data.empty()) {
                    cout << "\nПервые 10 элементов: ";
                    printList(data);
                    cout << "\nРезультаты тестирования:" << endl;
                    testSort("Сортировка Шелла", shellSort<float>, data);
                    testSort("Сортировка слиянием", mergeSort<float>, data);
                    testSort("Быстрая сортировка", quickSort<float>, data);
                    testSort("Сортировка вставками", insertionSort<float>, data);
                }
                break;
            }
            }
        }
    } while (choice != 6);

    return 0;
}