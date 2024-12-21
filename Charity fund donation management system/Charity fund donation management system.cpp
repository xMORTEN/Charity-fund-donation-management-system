#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

// ��������� ��� ������ ���������� ��� ��������
struct Donation {
    int id;
    string donorName;
    double amount;
    string purpose;
    string date;
};

// ��������� ����� ��� ��������� ������
Donation* donations = nullptr;
int recordCount = 0; // ʳ������ ������
int capacity = 0;    // ������� ������ ������

// ������� ��� ���������� ������
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

// ������� ��� ��������� ������ ������
void addDonation() {
    if (recordCount >= capacity) {
        expandArray();
    }

    Donation newDonation;
    cout << "������ ID: ";
    cin >> newDonation.id;
    cin.ignore(); // �������� ������
    cout << "������ ��'� ������: ";
    getline(cin, newDonation.donorName);
    cout << "������ ���� ��������: ";
    cin >> newDonation.amount;
    cin.ignore();
    cout << "������ �����������: ";
    getline(cin, newDonation.purpose);
    cout << "������ ����: ";
    getline(cin, newDonation.date);

    donations[recordCount++] = newDonation;
    cout << "����� ������!" << endl;
}

// ������� ��� ��������� ������ �� ID
void deleteDonation(int id) {
    int index = -1;
    for (int i = 0; i < recordCount; ++i) {
        if (donations[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "����� � ����� ID �� ��������!" << endl;
        return;
    }

    for (int i = index; i < recordCount - 1; ++i) {
        donations[i] = donations[i + 1];
    }

    --recordCount;
    cout << "����� ��������!" << endl;
}

// ������� ��� ����������� ������ �� ID
void editDonation(int id) {
    for (int i = 0; i < recordCount; ++i) {
        if (donations[i].id == id) {
            cout << "����������� ������ � ID " << id << ":" << endl;
            cout << "���� ��'� ������: ";
            cin.ignore();
            getline(cin, donations[i].donorName);
            cout << "���� ���� ��������: ";
            cin >> donations[i].amount;
            cin.ignore();
            cout << "���� �����������: ";
            getline(cin, donations[i].purpose);
            cout << "���� ���� (YYYY-MM-DD): ";
            getline(cin, donations[i].date);
            cout << "����� ��������!" << endl;
            return;
        }
    }

    cout << "����� � ����� ID �� ��������!" << endl;
}

// ������� ��� ��������� ��� ������
void viewAllDonations() {
    if (recordCount == 0) {
        cout << "���� ������ ��� �����������." << endl;
        return;
    }

    cout << left << setw(5) << "ID"
        << setw(20) << "��'� ������"
        << setw(15) << "����"
        << setw(20) << "�����������"
        << setw(15) << "����" << endl;
    cout << string(75, '-') << endl; // ˳�� ��� ���������

    for (int i = 0; i < recordCount; ++i) {
        cout << left << setw(5) << donations[i].id
            << setw(20) << donations[i].donorName
            << setw(15) << donations[i].amount
            << setw(20) << donations[i].purpose
            << setw(15) << donations[i].date << endl;
    }
}
// ������� ��� ������ �� �����
void searchDonation() {
    int option;
    cout << "������ ���� ��� ������:\n";
    cout << "1. ID\n";
    cout << "2. ��'� ������\n";
    cout << "3. ���� ��������\n";
    cout << "4. �����������\n";
    cout << "5. ����\n";
    cin >> option;
    cin.ignore();

    switch (option) {
    case 1: { // ����� �� ID
        int id;
        cout << "������ ID: ";
        cin >> id;
        for (int i = 0; i < recordCount; ++i) {
            if (donations[i].id == id) {
                cout << "�������� �����: " << donations[i].donorName << ", "
                    << donations[i].amount << ", "
                    << donations[i].purpose << ", "
                    << donations[i].date << endl;
                return;
            }
        }
        break;
    }
    case 2: { // ����� �� ��'�� ������
        string name;
        cout << "������ ��'�: ";
        cin.ignore();
        getline(cin, name);
        for (int i = 0; i < recordCount; ++i) {
            if (donations[i].donorName == name) {
                cout << "�������� �����: " << donations[i].id << ", "
                    << donations[i].amount << ", "
                    << donations[i].purpose << ", "
                    << donations[i].date << endl;
                return;
            }
        }
        break;
    }
    case 3: { // ����� �� ����� ��������
        double amount;
        cout << "������ ����: ";
        cin >> amount;
        for (int i = 0; i < recordCount; ++i) {
            if (donations[i].amount == amount) {
                cout << "�������� �����: " << donations[i].id << ", "
                    << donations[i].donorName << ", "
                    << donations[i].purpose << ", "
                    << donations[i].date << endl;
                return;
            }
        }
        break;
    }
    case 4: { // ����� �� ������������
        string purpose;
        cout << "������ �����������: ";
        cin.ignore();
        getline(cin, purpose);
        for (int i = 0; i < recordCount; ++i) {
            if (donations[i].purpose == purpose) {
                cout << "�������� �����: " << donations[i].id << ", "
                    << donations[i].donorName << ", "
                    << donations[i].amount << ", "
                    << donations[i].date << endl;
                return;
            }
        }
        break;
    }
    case 5: { // ����� �� �����
        string date;
        cout << "������ ���� (YYYY-MM-DD): ";
        cin.ignore();
        getline(cin, date);
        for (int i = 0; i < recordCount; ++i) {
            if (donations[i].date == date) {
                cout << "�������� �����: " << donations[i].id << ", "
                    << donations[i].donorName << ", "
                    << donations[i].amount << ", "
                    << donations[i].purpose << endl;
                return;
            }
        }
        break;
    }
    default:
        cout << "����� �� ��� ����� ���� �� �� �����������." << endl;
    }
    cout << "������ �� ��������." << endl;
}


// ������� ��� ���������� � ����
void saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "������� �������� �����!" << endl;
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
    cout << "��� ��������� � ����!" << endl;
}

// ������� ��� ������������ � �����
void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "������� �������� �����!" << endl;
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
    cout << "��� ����������� � �����!" << endl;
}

// ������� ��� ���������� ������
void sortDonations() {
    int option;
    cout << "������ ������� ��� ����������:\n";
    cout << "1. �� ID\n";
    cout << "2. �� ������ ������\n";
    cout << "3. �� ����� ��������\n";
    cout << "4. �� �����\n";
    cout << "��� ����: ";
    cin >> option;

    switch (option) {
    case 1:
        sort(donations, donations + recordCount, [](const Donation& a, const Donation& b) {
            return a.id < b.id;
            });
        cout << "������ ����������� �� ID." << endl;
        break;
    case 2:
        sort(donations, donations + recordCount, [](const Donation& a, const Donation& b) {
            return a.donorName < b.donorName;
            });
        cout << "������ ����������� �� ������ ������." << endl;
        break;
    case 3:
        sort(donations, donations + recordCount, [](const Donation& a, const Donation& b) {
            return a.amount < b.amount;
            });
        cout << "������ ����������� �� ����� ��������." << endl;
        break;
    case 4:
        sort(donations, donations + recordCount, [](const Donation& a, const Donation& b) {
            return a.date < b.date;
            });
        cout << "������ ����������� �� �����." << endl;
        break;
    default:
        cout << "������������ ����." << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do {
        cout << "\n����:\n";
        cout << "1. ������ ��������\n";
        cout << "2. �������� ��������\n";
        cout << "3. ���������� ��������\n";
        cout << "4. ����� ��������\n";
        cout << "5. �������� � ����\n";
        cout << "6. ����������� � �����\n";
        cout << "7. ��������� ������\n";
        cout << "8. ����������� �� ������\n";
        cout << "0. �����\n";
        cout << "������: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addDonation();
            break;
        case 2: {
            int id;
            cout << "������ ID ��� ���������: ";
            cin >> id;
            deleteDonation(id);
            break;
        }
        case 3: {
            int id;
            cout << "������ ID ��� �����������: ";
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
            cout << "�� ���������!" << endl;
            break;
        default:
            cout << "������������ ����. ��������� �� ���." << endl;
        }
    } while (choice != 0);

    // �������� �������� ���'��
    delete[] donations;
    return 0;
}
