#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

// Структура для запису інформації про пожертви
struct Donation {
    int id;
    string donorName;
    double amount;
    string purpose;
    string date;
};

// Динамічний масив для зберігання записів
Donation* donations = nullptr;
int recordCount = 0; // Кількість записів
int capacity = 0;    // Поточна ємність масиву

// Функція для розширення масиву
void expandArray() {
    int newCapacity = (capacity == 0) ? 10 : capacity * 2;
    Donation* newDonations = new Donation[newCapacity];

    for (int i = 0; i < recordCount; ++i) {
        newDonations[i] = donations[i];
    }

    delete[] donations;
    donations = newDonations;
    capacity = newCapacity;
}

// Функція для додавання нового запису
void addDonation() {
    if (recordCount >= capacity) {
        expandArray();
    }

    Donation newDonation;
    cout << "Введіть ID: ";
    cin >> newDonation.id;
    cin.ignore(); // Очищення буфера
    cout << "Введіть ім'я донора: ";
    getline(cin, newDonation.donorName);
    cout << "Введіть суму пожертви: ";
    cin >> newDonation.amount;
    cin.ignore();
    cout << "Введіть призначення: ";
    getline(cin, newDonation.purpose);
    cout << "Введіть дату: ";
    getline(cin, newDonation.date);

    donations[recordCount++] = newDonation;
    cout << "Запис додано!" << endl;
}

// Функція для видалення запису за ID
void deleteDonation(int id) {
    int index = -1;
    for (int i = 0; i < recordCount; ++i) {
        if (donations[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Запис з таким ID не знайдено!" << endl;
        return;
    }

    for (int i = index; i < recordCount - 1; ++i) {
        donations[i] = donations[i + 1];
    }

    --recordCount;
    cout << "Запис видалено!" << endl;
}

// Функція для редагування запису за ID
void editDonation(int id) {
    for (int i = 0; i < recordCount; ++i) {
        if (donations[i].id == id) {
            cout << "Редагування запису з ID " << id << ":" << endl;
            cout << "Нове ім'я донора: ";
            cin.ignore();
            getline(cin, donations[i].donorName);
            cout << "Нова сума пожертви: ";
            cin >> donations[i].amount;
            cin.ignore();
            cout << "Нове призначення: ";
            getline(cin, donations[i].purpose);
            cout << "Нова дата (YYYY-MM-DD): ";
            getline(cin, donations[i].date);
            cout << "Запис оновлено!" << endl;
            return;
        }
    }

    cout << "Запис з таким ID не знайдено!" << endl;
}

// Функція для перегляду всіх записів
void viewAllDonations() {
    if (recordCount == 0) {
        cout << "Немає записів для відображення." << endl;
        return;
    }

    cout << left << setw(5) << "ID"
        << setw(20) << "Ім'я донора"
        << setw(15) << "Сума"
        << setw(20) << "Призначення"
        << setw(15) << "Дата" << endl;
    cout << string(75, '-') << endl; // Лінія для розділення

    for (int i = 0; i < recordCount; ++i) {
        cout << left << setw(5) << donations[i].id
            << setw(20) << donations[i].donorName
            << setw(15) << donations[i].amount
            << setw(20) << donations[i].purpose
            << setw(15) << donations[i].date << endl;
    }
}
// Функція для пошуку за полем
void searchDonation() {
    int option;
    cout << "Оберіть поле для пошуку:\n";
    cout << "1. ID\n";
    cout << "2. Ім'я донора\n";
    cout << "3. Сума пожертви\n";
    cout << "4. Призначення\n";
    cout << "5. Дата\n";
    cin >> option;
    cin.ignore();

    switch (option) {
    case 1: { // Пошук за ID
        int id;
        cout << "Введіть ID: ";
        cin >> id;
        for (int i = 0; i < recordCount; ++i) {
            if (donations[i].id == id) {
                cout << "Знайдено запис: " << donations[i].donorName << ", "
                    << donations[i].amount << ", "
                    << donations[i].purpose << ", "
                    << donations[i].date << endl;
                return;
            }
        }
        break;
    }
    case 2: { // Пошук за ім'ям донора
        string name;
        cout << "Введіть ім'я: ";
        cin.ignore();
        getline(cin, name);
        for (int i = 0; i < recordCount; ++i) {
            if (donations[i].donorName == name) {
                cout << "Знайдено запис: " << donations[i].id << ", "
                    << donations[i].amount << ", "
                    << donations[i].purpose << ", "
                    << donations[i].date << endl;
                return;
            }
        }
        break;
    }
    case 3: { // Пошук за сумою пожертви
        double amount;
        cout << "Введіть суму: ";
        cin >> amount;
        for (int i = 0; i < recordCount; ++i) {
            if (donations[i].amount == amount) {
                cout << "Знайдено запис: " << donations[i].id << ", "
                    << donations[i].donorName << ", "
                    << donations[i].purpose << ", "
                    << donations[i].date << endl;
                return;
            }
        }
        break;
    }
    case 4: { // Пошук за призначенням
        string purpose;
        cout << "Введіть призначення: ";
        cin.ignore();
        getline(cin, purpose);
        for (int i = 0; i < recordCount; ++i) {
            if (donations[i].purpose == purpose) {
                cout << "Знайдено запис: " << donations[i].id << ", "
                    << donations[i].donorName << ", "
                    << donations[i].amount << ", "
                    << donations[i].date << endl;
                return;
            }
        }
        break;
    }
    case 5: { // Пошук за датою
        string date;
        cout << "Введіть дату (YYYY-MM-DD): ";
        cin.ignore();
        getline(cin, date);
        for (int i = 0; i < recordCount; ++i) {
            if (donations[i].date == date) {
                cout << "Знайдено запис: " << donations[i].id << ", "
                    << donations[i].donorName << ", "
                    << donations[i].amount << ", "
                    << donations[i].purpose << endl;
                return;
            }
        }
        break;
    }
    default:
        cout << "Пошук за цим полем поки що не реалізований." << endl;
    }
    cout << "Записів не знайдено." << endl;
}


// Функція для збереження у файл
void saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    for (int i = 0; i < recordCount; ++i) {
        file << donations[i].id << ",\t"
            << donations[i].donorName << ",\t"
            << donations[i].amount << ",\t"
            << donations[i].purpose << ",\t"
            << donations[i].date << endl;
    }

    file.close();
    cout << "Дані збережено у файл!" << endl;
}

// Функція для завантаження з файлу
void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    recordCount = 0;
    while (file.good()) {
        if (recordCount >= capacity) {
            expandArray();
        }

        Donation d;
        file >> d.id;
        file.ignore();
        getline(file, d.donorName, ',');
        file >> d.amount;
        file.ignore();
        getline(file, d.purpose, ',');
        getline(file, d.date);

        donations[recordCount++] = d;
    }

    file.close();
    cout << "Дані завантажено з файлу!" << endl;
}

// Функція для сортування записів
void sortDonations() {
    int option;
    cout << "Оберіть критерій для сортування:\n";
    cout << "1. За ID\n";
    cout << "2. За іменем донора\n";
    cout << "3. За сумою пожертви\n";
    cout << "4. За датою\n";
    cout << "Ваш вибір: ";
    cin >> option;

    switch (option) {
    case 1:
        sort(donations, donations + recordCount, [](const Donation& a, const Donation& b) {
            return a.id < b.id;
            });
        cout << "Записи відсортовано за ID." << endl;
        break;
    case 2:
        sort(donations, donations + recordCount, [](const Donation& a, const Donation& b) {
            return a.donorName < b.donorName;
            });
        cout << "Записи відсортовано за іменем донора." << endl;
        break;
    case 3:
        sort(donations, donations + recordCount, [](const Donation& a, const Donation& b) {
            return a.amount < b.amount;
            });
        cout << "Записи відсортовано за сумою пожертви." << endl;
        break;
    case 4:
        sort(donations, donations + recordCount, [](const Donation& a, const Donation& b) {
            return a.date < b.date;
            });
        cout << "Записи відсортовано за датою." << endl;
        break;
    default:
        cout << "Неправильний вибір." << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Додати пожертву\n";
        cout << "2. Видалити пожертву\n";
        cout << "3. Редагувати пожертву\n";
        cout << "4. Пошук пожертви\n";
        cout << "5. Зберегти у файл\n";
        cout << "6. Завантажити з файлу\n";
        cout << "7. Сортувати записи\n";
        cout << "8. Переглянути всі записи\n";
        cout << "0. Вийти\n";
        cout << "Оберіть: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addDonation();
            break;
        case 2: {
            int id;
            cout << "Введіть ID для видалення: ";
            cin >> id;
            deleteDonation(id);
            break;
        }
        case 3: {
            int id;
            cout << "Введіть ID для редагування: ";
            cin >> id;
            editDonation(id);
            break;
        }
        case 4:
            searchDonation();
            break;
        case 5:
            saveToFile("donations.txt");
            break;
        case 6:
            loadFromFile("donations.txt");
            break;
        case 7:
            sortDonations();
            break;
        case 8:
            viewAllDonations();
            break;
        case 0:
            cout << "До побачення!" << endl;
            break;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз." << endl;
        }
    } while (choice != 0);

    // Очищення динамічної пам'яті
    delete[] donations;
    return 0;
}
