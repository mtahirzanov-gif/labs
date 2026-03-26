#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

class HRDepartment {
private:
    string companyName;
    int employeeCount;
    double monthlyProductionNorm;      // часы в месяц
    double hourlyRate;                 // ставка за час
    double incomeTaxRate;              // налог в процентах

public:
    // Сеттеры (свойства только для записи)
    void setCompanyName(const string& name) { companyName = name; }
    void setEmployeeCount(int count) { employeeCount = count; }
    void setMonthlyProductionNorm(double norm) { monthlyProductionNorm = norm; }
    void setHourlyRate(double rate) { hourlyRate = rate; }
    void setIncomeTaxRate(double tax) { incomeTaxRate = tax; }

    // Расчёт общей суммы подоходного налога
    double calculateTotalIncomeTax() const {
        return monthlyProductionNorm * hourlyRate * employeeCount * (incomeTaxRate / 100.0);
    }
};

// Шаблонная функция ввода числа с проверкой диапазона
template<typename T>
T inputNumber(const string& prompt, T minValue, T maxValue) {
    string input;
    T value;

    while (true) {
        cout << prompt;
        getline(cin, input);

        // Удаляем лишние пробелы по краям
        size_t start = input.find_first_not_of(" \t");
        size_t end = input.find_last_not_of(" \t");
        if (start == string::npos) {
            cout << "Ошибка: поле не может быть пустым!" << endl;
            continue;
        }
        input = input.substr(start, end - start + 1);

        try {
            size_t pos = 0;
            if constexpr (is_integral<T>::value) {
                value = static_cast<T>(stoi(input, &pos));
            }
            else {
                value = static_cast<T>(stod(input, &pos));
            }

            // Проверка: вся ли строка была распознана как число
            if (pos != input.length()) {
                cout << "Ошибка: введите корректное число без лишних символов!" << endl;
                continue;
            }

            // Проверка диапазона
            if (value < minValue || value > maxValue) {
                cout << "Ошибка: значение должно быть в диапазоне ["
                    << minValue << "; " << maxValue << "]" << endl;
                continue;
            }

            return value;

        }
        catch (const out_of_range&) {
            cout << "Ошибка: число выходит за допустимый диапазон!" << endl;
        }
        catch (const invalid_argument&) {
            cout << "Ошибка: введите корректное число!" << endl;
        }
        catch (...) {
            cout << "Ошибка: непредвиденная ошибка ввода!" << endl;
        }
    }
}

int main() {
    // Корректная работа с русскими символами в консоли Windows
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    HRDepartment hr;

    cout << "=== Ввод данных для расчёта подоходного налога ===" << endl << endl;

    // Ввод названия компании
    string name;
    cout << "Введите название работы: ";
    getline(cin, name);
    hr.setCompanyName(name);

    // Ввод данных с валидацией по диапазонам:

    // 1. Количество работников: 1 – 10 000
    hr.setEmployeeCount(inputNumber<int>(
        "Введите количество работников (1-10000): ", 1, 10000));

    // 2. Время работы в месяц: 12 – 720 часов
    hr.setMonthlyProductionNorm(inputNumber<double>(
        "Введите время работы в месяц, часов (12-720): ", 12.0, 720.0));

    // 3. Ставка в час: 200 – 10 000
    hr.setHourlyRate(inputNumber<double>(
        "Введите ставку в час, руб. (200-10000): ", 200.0, 10000.0));

    // 4. Налог: 2% – 50%
    hr.setIncomeTaxRate(inputNumber<double>(
        "Введите ставку подоходного налога, % (2-50): ", 2.0, 50.0));

    // Расчёт результата
    double result = hr.calculateTotalIncomeTax();

    // Проверка на переполнение
    if (isinf(result) || isnan(result)) {
        cout << "\nОшибка: результат вычисления некорректен!" << endl;
        return 1;
    }

    // Вывод результата
    cout << "\n=== Результат ===" << endl;
    cout << "Компания: " << name << endl;
    cout << "Общая сумма подоходного налога: ";
    cout << fixed << setprecision(2) << result << " руб." << endl;

    // Пауза перед закрытием консоли (для Windows)
    cout << "\nНажмите Enter для выхода...";
    cin.get();

    return 0;
}