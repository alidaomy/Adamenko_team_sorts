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

//Ульяна



//Диана

//Диана



//Влада

//Влада



//Лиза

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

                }
                break;
            }

            case 3: {
                vector<char> data = readFromFile<char>(filename);
                if (!data.empty()) {
                    cout << "\nПервые 10 элементов: ";
                    printList(data);
                    cout << "\nРезультаты тестирования:" << endl;

                }
                break;
            }

            case 5: {
                vector<float> data = readFromFile<float>(filename);
                if (!data.empty()) {
                    cout << "\nПервые 10 элементов: ";
                    printList(data);
                    cout << "\nРезультаты тестирования:" << endl;

                }
                break;
            }
            }
        }
    } while (choice != 6);

    return 0;
}