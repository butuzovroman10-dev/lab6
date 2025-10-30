#include "JordanGaussSolver.h"
#include <iostream>
#include <cassert>

using namespace std;

void testBasicSystem() {
    cout << "Тест 1: Базовая система 3x3" << endl;
    
    vector<vector<double>> matrix = {
        {4, -1, 3, 12},
        {2, 2, -1, 4},
        {1, 1, 1, 6}
    };
    
    auto result = JordanGaussSolver::solve(matrix);
    assert(result.success);
    
    // Проверка с допустимой погрешностью
    double epsilon = 1e-6;
    assert(abs(result.solution[0] - 22.0/15.0) < epsilon);
    assert(abs(result.solution[1] - 28.0/15.0) < epsilon);
    assert(abs(result.solution[2] - 8.0/3.0) < epsilon);
    
    cout << "✅ Тест пройден" << endl;
}

void testValidation() {
    cout << "Тест 2: Проверка валидации матрицы" << endl;
    
    // Некорректная матрица
    vector<vector<double>> invalidMatrix = {
        {1, 2, 3},
        {4, 5}
    };
    
    assert(!JordanGaussSolver::validateMatrix(invalidMatrix));
    cout << "✅ Тест пройден" << endl;
}

int main() {
    cout << "Запуск тестов..." << endl << endl;
    
    testBasicSystem();
    testValidation();
    
    cout << endl << "Все тесты пройдены успешно! 🎉" << endl;
    return 0;
}