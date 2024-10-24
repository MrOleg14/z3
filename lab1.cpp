#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>

using namespace std;

// Класс Дробь
class Fraction {  
private:
    int numerator;  // Числитель
    int denominator;  // Знаменатель

public:
    Fraction(int num, int denom) : numerator(num), denominator(denom) {}  // Принимает числ и знам

    Fraction multiply(const Fraction& other) const {  // Умножение
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction sum(const Fraction& other) const {  // Сумма
        return Fraction(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
    }

    Fraction div(const Fraction& other) const {  // Деление
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    Fraction minus(int value) const {  // Вычитание
        return Fraction(numerator - value * denominator, denominator);
    }

    string toString() const {  // Преобразование в строку
        return to_string(numerator) + "/" + to_string(denominator);
    }
};

// Класс Дом
class House {
private:
    int floors;

public:
    House(int f) : floors(f) {
        if (floors < 1) {
            throw std::invalid_argument("Количество этажей должно быть положительным.");
        }
    }

    std::string toString() const {  // Формирование строки с инфой о доме
        std::string ending;
        if (floors % 10 == 1 && floors % 100 != 11) {
            ending = "этаж";
        }
        else if ((floors % 10 >= 2 && floors % 10 <= 4) && (floors % 100 < 12 || floors % 100 > 14)) {
            ending = "этажа";
        }
        else {
            ending = "этажей";
        }
        return "дом, в котором " + std::to_string(floors) + " " + ending;
    }

    void print() const {
        std::cout << toString() << std::endl;
    }
};

// Класс Сотрудник
class Department;

class Employee {
private:
    string name;  // Имя сотрудника
    Department* department; // Указатель на отдел

public:
    Employee(const string& name, Department* department = nullptr)
        : name(name), department(department) {}

    void setDepartment(Department* dept) {
        department = dept;
    }

    string toString() const;  // Преобразование в строку

    void print() const {
        cout << toString() << endl;
    }
};

// Определяем класс Отдел
class Department {
private:
    string name;  // Название отдела
    Employee* head;  // Указатель на начальника
    vector<Employee*> employees;

public:
    Department(const string& name, Employee* head) : name(name), head(head) {
        this->head = head;
        head->setDepartment(this);
        employees.push_back(head);
    }

    void addEmployee(Employee* employee) {  // Метод добавления сотрудников
        employees.push_back(employee);
        employee->setDepartment(this);
    }

    Employee* getHead() const { return head; }
    string getName() const { return name; }

    void printEmployees() const {
        for (const auto& emp : employees) {
            emp->print();
        }
    }
};

// Реализуем метод toString после определения класса Department
string Employee::toString() const {
    if (department && department->getHead() == this)
        return name + " начальник отдела " + department->getName();
    else if (department)
        return name + " работает в отделе " + department->getName() + ", начальник которого " + department->getHead()->name;
    return name;
}

// Класс Имена
class Name {
private:
    string name;

public:
    Name(const string& n) : name(n) {}

    string toString() const {  // Возвращаем значение
        return name;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Создание объектов
    Fraction f1(1, 3);
    Fraction f2(2, 3);

    // Заданные этажи
    int floorsArray[] = { 1, 5, 23 };
    const int numberOfHouses = sizeof(floorsArray) / sizeof(floorsArray[0]);

    try {
        // Создаем экземпляры домов с заданным количеством этажей
        House houses[numberOfHouses] = { House(floorsArray[0]), House(floorsArray[1]), House(floorsArray[2]) };

        // Работа с классом Сотрудник и Отдел
        Employee petrov("Петров");
        Employee kozlov("Козлов");
        Employee sidorov("Сидоров");
        Department itDepartment("IT", &kozlov);
        itDepartment.addEmployee(&petrov);
        itDepartment.addEmployee(&sidorov);

        // Работа с классом Имя
        Name клеопатра("Клеопатра");
        Name пушкин("Пушкин Александр Сергеевич");
        Name маяковский("Маяковский Владимир");

        // Меню выбора
        int choice;
        do {
            cout << "Выберите класс для отображения:" << endl;
            cout << "1. Дом (House)" << endl;
            cout << "2. Сотрудник и Отдел (Employee and Department)" << endl;
            cout << "3. Дробь (Fraction)" << endl;
            cout << "4. Имена (Names)" << endl; 
            cout << "0. Выход" << endl;
            cin >> choice;
            switch (choice) {
            case 1:  // Дом
                for (int i = 0; i < numberOfHouses; ++i) {
                    houses[i].print();
                }
                break;

            case 2:  // Сотрудники
                itDepartment.printEmployees();
                break;

            case 3: {  // Дроби
                Fraction result = f1.multiply(f2);
                cout << f1.toString() << " * " << f2.toString() << " = " << result.toString() << endl;
                // Сложная операция
                Fraction f3(1, 3);
                Fraction finalResult = f1.sum(f2).div(f3).minus(5);
                cout << f1.toString() << " + " << f2.toString()
                    << " / " << f3.toString()
                    << " - 5 = " << finalResult.toString() << endl;
                break;
            }

            case 4: { // Имена
                cout << клеопатра.toString() << endl;
                cout << пушкин.toString() << endl;
                cout << маяковский.toString() << endl;
                break;
            }

            case 0:  // Выход
                cout << "Выход из программы" << endl;
                break;
            default:  // Проверка на ввод
                cout << "Такой цифры нет в меню, введите число от 1 до 4" << endl;
            }
            cout << endl;
        } while (choice != 0);  // Цикл будет работать, пока пользователь не введет 0
    }
    catch (const std::invalid_argument& e) {  // Обработка исключений
        cout << e.what() << endl;
    }
    return 0; 
}
