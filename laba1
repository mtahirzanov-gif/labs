#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

class HRDepartment {
private:
    string companyName;
    int employeeCount;
    double monthlyProductionNorm;
    double hourlyRate;
    double incomeTaxRate;

public:
    // Свойства только для записи (write-only)
    void setCompanyName(const string& name) { companyName = name; }
    void setEmployeeCount(int count) { employeeCount = count; }
    void setMonthlyProductionNorm(double norm) { monthlyProductionNorm = norm; }
    void setHourlyRate(double rate) { hourlyRate = rate; }
    void setIncomeTaxRate(double tax) { incomeTaxRate = tax; }

    // Метод для подсчета общей выплаты по подоходному налогу
    double calculateTotalIncomeTax() {
        return monthlyProductionNorm * hourlyRate * employeeCount * (incomeTaxRate / 100.0);
    }
};

// Функция для ввода чисел с проверкой
template<typename T>
T inputNumber(const string& prompt) {
    string input;
    T value;
    
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        try {
            size_t pos;
            if constexpr (is_integral<T>::value) {
                value = stoi(input, &pos);
                // Проверка на переполнение для int
                if (value < 0) {
                    cout << "Ошибка: число не может быть отрицательным!" << endl;
                    continue;
                }
                if (value > 1000000) { // Разумное ограничение
                    cout << "Ошибка: слишком большое значение! Введите число до 1,000,000" << endl;
                    continue;
                }
            } else {
                value = stod(input, &pos);
                // Проверка на отрицательные и очень большие числа для double
                if (value < 0) {
                    cout << "Ошибка: число не может быть отрицательным!" << endl;
                    continue;
                }
                if (value > 1e9) { // Ограничение
                    cout << "Ошибка: слишком большое значение! Введите число до 1,000,000,000" << endl;
                    continue;
                }
            }
            
            if (pos == input.length()) {
                return value;
            }
        } catch (const out_of_range& e) {
            cout << "Ошибка: число слишком большое!" << endl;
        } catch (...) {
            // Обработка исключений
            cout << "Введите корректное число!" << endl;
        }
    }
}

int main() {
    HRDepartment hr;
    
    cout << "Введите данные для департамента\n=== Ввод данных ===\n\n";
    
    string name;
    cout << "Введите имя: ";
    getline(cin, name);
    hr.setCompanyName(name);
    
    hr.setEmployeeCount(inputNumber<int>("Введите количество участников: "));
    hr.setMonthlyProductionNorm(inputNumber<double>("Введите норму времени (часы): "));
    hr.setHourlyRate(inputNumber<double>("Введите зарплату в час: "));
    hr.setIncomeTaxRate(inputNumber<double>("Введите налог (%): "));
    
    // Дополнительная проверка результата
    double result = hr.calculateTotalIncomeTax();
    if (isinf(result)) {
        cout << "Ошибка: результат вычисления слишком большой!" << endl;
        return 1;
    }
    
    cout << "Общая выплата по подоходному налогу:\n";
    cout << fixed << setprecision(2) << result << endl;
    
    return 0;
}
