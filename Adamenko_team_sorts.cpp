
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

// Функция для чтения из файла
template <typename T>
Node<T>* readFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) return nullptr;

    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    T value;

    while (file >> value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) head = newNode;
        else tail->next = newNode;
        tail = newNode;
    }

    return head;
}


// Функция проверки сортировки
template <typename T>
bool isSorted(Node<T>* head) {
    while (head && head->next) {
        if (head->data > head->next->data) return false;
        head = head->next;
    }
    return true;
}

// Функция печати списка
template <typename T>
void printList(Node<T>* head, int limit = 10) {
    int count = 0;
    while (head && count < limit) {
        cout << head->data << " ";
        head = head->next;
        count++;
    }
    if (head) cout << "...";
    cout << endl;
}

template <typename T>
void freeList(Node<T>* head) {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
Node<T>* copyList(Node<T>* head) {
    Node<T>* newHead = nullptr;
    Node<T>* tail = nullptr;

    while (head) {
        Node<T>* newNode = new Node<T>(head->data);
        if (!newHead) newHead = newNode;
        else tail->next = newNode;
        tail = newNode;
        head = head->next;
    }

    return newHead;
}

// Тестирование сортировки с замером времени
template <typename T>
void testSort(const string& name, Node<T>* (*sortFunc)(Node<T>*), Node<T>* head) {
    Node<T>* copy = copyList(head);

    auto start = high_resolution_clock::now();
    copy = sortFunc(copy);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    double time_ms = duration.count() / 1000.0;

    cout << name << ": " << time_ms << " мс";
    cout << " (Отсортирован: " << (isSorted(copy) ? "Да" : "Нет") << ")" << endl;

    freeList(copy);
}

//Ульяна

//Ульяна



//Диана

//Диана



//Влада

//Влада



//Лиза

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
    cout << "\nТЕСТИРОВАНИЕ СОРТИРОВОК НА СПИСКАХ" << endl;
    cout << "1. 1000 целых чисел (data1.txt)" << endl;
    cout << "2. 10000 целых чисел (data2.txt)" << endl;
    cout << "3. 1000 букв (data3.txt)" << endl;
    cout << "4. 1000 чисел в обратном порядке (data4.txt)" << endl;
    cout << "5. 1000 дробных чисел (data5.txt)" << endl;
    cout << "6. Выход" << endl;
    cout << "Ваш выбор (1-6): ";
}

int main(){

	setlocale(LC_ALL, "Russian");




    return 0;

}