#include "JordanGaussSolver.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

bool JordanGaussSolver::validateMatrix(const vector<vector<double>>& matrix) {
    if (matrix.empty()) return false;
    
    size_t n = matrix.size();
    size_t expectedCols = n + 1;
    
    for (const auto& row : matrix) {
        if (row.size() != expectedCols) {
            return false;
        }
    }
    
    return true;
}

int JordanGaussSolver::findPivotRow(const vector<vector<double>>& matrix, int col) {
    int n = matrix.size();
    int maxRow = col;
    double maxVal = abs(matrix[col][col]);
    
    for (int i = col + 1; i < n; i++) {
        if (abs(matrix[i][col]) > maxVal) {
            maxVal = abs(matrix[i][col]);
            maxRow = i;
        }
    }
    
    return maxRow;
}

void JordanGaussSolver::swapRows(vector<vector<double>>& matrix, int row1, int row2) {
    if (row1 != row2) {
        swap(matrix[row1], matrix[row2]);
    }
}

void JordanGaussSolver::normalizeRow(vector<vector<double>>& matrix, int row) {
    int n = matrix.size();
    double pivot = matrix[row][row];
    
    for (int j = row; j <= n; j++) {
        matrix[row][j] /= pivot;
    }
}

void JordanGaussSolver::eliminateVariable(vector<vector<double>>& matrix, int pivotRow) {
    int n = matrix.size();
    
    for (int i = 0; i < n; i++) {
        if (i != pivotRow) {
            double factor = matrix[i][pivotRow];
            for (int j = pivotRow; j <= n; j++) {
                matrix[i][j] -= factor * matrix[pivotRow][j];
            }
        }
    }
}

bool JordanGaussSolver::isZero(double value, double epsilon) {
    return abs(value) < epsilon;
}

JordanGaussSolver::SolutionResult JordanGaussSolver::solve(
    const vector<vector<double>>& matrix) {
    
    SolutionResult result;
    
    if (!validateMatrix(matrix)) {
        result.success = false;
        result.error_message = "Некорректная матрица системы";
        return result;
    }
    
    vector<vector<double>> workingMatrix = matrix;
    int n = matrix.size();
    
    result.steps.push_back(workingMatrix);
    
    try {
        for (int k = 0; k < n; k++) {
            // Поиск главного элемента
            int pivotRow = findPivotRow(workingMatrix, k);
            if (pivotRow != k) {
                swapRows(workingMatrix, k, pivotRow);
                result.steps.push_back(workingMatrix);
            }
            
            // Проверка на вырожденность
            if (isZero(workingMatrix[k][k])) {
                throw runtime_error("Система вырождена или не имеет единственного решения");
            }
            
            // Нормализация
            normalizeRow(workingMatrix, k);
            result.steps.push_back(workingMatrix);
            
            // Исключение
            eliminateVariable(workingMatrix, k);
            result.steps.push_back(workingMatrix);
        }
        
        // Извлечение решения
        result.solution.resize(n);
        for (int i = 0; i < n; i++) {
            result.solution[i] = workingMatrix[i][n];
        }
        
        result.success = true;
        
    } catch (const exception& e) {
        result.success = false;
        result.error_message = e.what();
    }
    
    return result;
}

vector<double> JordanGaussSolver::checkSolution(
    const vector<vector<double>>& originalMatrix,
    const vector<double>& solution) {
    
    int n = originalMatrix.size();
    vector<double> residuals(n, 0.0);
    
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += originalMatrix[i][j] * solution[j];
        }
        residuals[i] = sum - originalMatrix[i][n];
    }
    
    return residuals;
}

void JordanGaussSolver::printMatrix(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        cout << "| ";
        for (int j = 0; j < n; j++) {
            cout << setw(10) << fixed << setprecision(6) << matrix[i][j] << " ";
        }
        cout << "| " << setw(10) << fixed << setprecision(6) << matrix[i][n] << " |" << endl;
    }
}

void JordanGaussSolver::printSolution(const vector<double>& solution) {
    cout << "Решение системы:" << endl;
    char variable = 'x';
    for (size_t i = 0; i < solution.size(); i++) {
        cout << variable << " = " << fixed << setprecision(6) << solution[i] << endl;
        variable++;
    }
}