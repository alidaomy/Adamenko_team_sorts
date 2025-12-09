#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <vector>
#include <iomanip>

using namespace std;
using namespace std::chrono;

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

// Структура для даты
struct Date {
    int day, month, year;

    Date() : day(1), month(1), year(2000) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    // Операторы сравнения для сортировки
    bool operator>(const Date& other) const {
        if (year != other.year) return year > other.year;
        if (month != other.month) return month > other.month;
        return day > other.day;
    }

    bool operator<=(const Date& other) const {
        return !(*this > other);
    }

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
};

// Операторы ввода/вывода для Date
istream& operator>>(istream& is, Date& date) {
    char dot1, dot2;
    is >> date.day >> dot1 >> date.month >> dot2 >> date.year;
    return is;
}

ostream& operator<<(ostream& os, const Date& date) {
    os << date.day << "." << date.month << "." << date.year;
    return os;
}

// Функция копирования вектора
template <typename T>
vector<T> copyList(const vector<T>& data) {
    return vector<T>(data);
}

// Тестирование сортировки с замером времени
template <typename T>
void testSort(const string& name, vector<T>(*sortFunc)(vector<T>), const vector<T>& data) {
    vector<T> copy = data;

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
void merge(vector<T>& arr, int left, int mid, int right, vector<T>& temp) { 
    int i = left;      
    int j = mid + 1;  
    int k = left;      
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
    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }
    for (int idx = left; idx <= right; idx++) {
        arr[idx] = temp[idx];
    }
}

template <typename T>
void mergeSortHelper(vector<T>& arr, int left, int right, vector<T>& temp) { 
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortHelper(arr, left, mid, temp); 
        mergeSortHelper(arr, mid + 1, right, temp); 

        merge(arr, left, mid, right, temp);
    }
}

template <typename T>
vector<T> mergeSort(vector<T> arr) { 
    if (arr.size() > 1) {
        vector<T> temp(arr.size());
        mergeSortHelper(arr, 0, arr.size() - 1, temp);
    }
    return arr;
}
//Ульяна



//Диана
template <typename T>
vector<T> shellSort(vector<T> arr) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {

        for (int i = gap; i < n; i++) {

            T current = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > current) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = current;
        }
    }

    return arr;
}
//Диана



//Влада
template <typename T>
int partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];

    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    // Ставим опорный элемент на правильную позицию
    swap(arr[i + 1], arr[high]);

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
template <typename T>
vector<T> insertionSort(vector<T> arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }

    return arr;
}
//Лиза


// Генерация тестовых данных
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

    case 3:  // 1000 букв
        for (int i = 0; i < 1000; i++) {
            char letter = 'a' + rand() % 26;
            file << letter << " ";
        }
        cout << "Создан файл data3.txt с 1000 английских букв" << endl;
        break;

    case 4:  // 1000 чисел в обратном порядке  
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

    case 6:
        for (int i = 0; i < 1000; i++) {
            int day = 1 + rand() % 28;
            int month = 1 + rand() % 12;
            int year = 2000 + rand() % 25;
            file << day << "." << month << "." << year << " ";
        }
        cout << "Создан файл data6.txt с 1000 дат" << endl;
        break;

    case 7:
    {
        const char* words[] = {
            "apple", "banana", "cherry", "date", "elderberry",
            "fig", "grape", "honeydew", "kiwi", "lemon",
            "mango", "nectarine", "orange", "pear", "quince",
            "raspberry", "strawberry", "tangerine", "watermelon"
        };
        int wordCount = sizeof(words) / sizeof(words[0]);

        for (int i = 0; i < 1000; i++) {
            file << words[rand() % wordCount] << " ";
        }
        cout << "Создан файл data7.txt с 1000 слов" << endl;
        break;
    }
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
    cout << "6. 1000 дат (data6.txt)" << endl;
    cout << "7. 1000 слов (data7.txt)" << endl;
    cout << "8. Выход" << endl;
    cout << "Ваш выбор (1-8): ";
}

template <typename T>
void testAllSorts(const vector<T>& data) {
    if (!data.empty()) {
        cout << "\nПервые 10 элементов: ";
        printList(data);
        cout << "\nРезультаты тестирования:" << endl;
        testSort("Сортировка Шелла", shellSort<T>, data);
        testSort("Сортировка слиянием", mergeSort<T>, data);
        testSort("Быстрая сортировка", quickSort<T>, data);
        testSort("Сортировка вставками", insertionSort<T>, data);
    }
    else {
        cout << "Файл пуст или не удалось прочитать данные." << endl;
    }
}


int main() {
    setlocale(LC_ALL, "Russian");

    int choice;

    do {
        showMenu();
        cin >> choice;

        if (choice >= 1 && choice <= 7) {
            string filename = "data" + to_string(choice) + ".txt";

            // Проверяем существование файла
            ifstream test(filename);
            if (!test.good()) {
                generateDataFile(filename, choice);
            }
            else {
                cout << "Файл " << filename << " уже существует. Используем его." << endl;
            }
            test.close();

            switch (choice) {
            case 1:
            case 2:
            case 4: {
                vector<int> data = readFromFile<int>(filename);
                testAllSorts(data);
                break;
            }

            case 3: {
                vector<char> data = readFromFile<char>(filename);
                testAllSorts(data);
                break;
            }

            case 5: {
                vector<float> data = readFromFile<float>(filename);
                testAllSorts(data);
                break;
            }

            case 6: {
                vector<Date> data = readFromFile<Date>(filename);
                testAllSorts(data);
                break;
            }

            case 7: {
                vector<string> data = readFromFile<string>(filename);
                testAllSorts(data);
                break;
            }
            }
        }
    } while (choice != 8);

    return 0;
}