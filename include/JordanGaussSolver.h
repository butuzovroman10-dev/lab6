#ifndef JORDAN_GAUSS_SOLVER_H
#define JORDAN_GAUSS_SOLVER_H

#include <vector>
#include <stdexcept>
#include <string>

class JordanGaussSolver {
public:
    struct SolutionResult {
        std::vector<double> solution;
        std::vector<std::vector<std::vector<double>>> steps;
        bool success;
        std::string error_message;
    };
    
    static SolutionResult solve(const std::vector<std::vector<double>>& matrix);
    static bool validateMatrix(const std::vector<std::vector<double>>& matrix);
    static std::vector<double> checkSolution(
        const std::vector<std::vector<double>>& originalMatrix,
        const std::vector<double>& solution);
    
    // Утилиты для вывода
    static void printMatrix(const std::vector<std::vector<double>>& matrix);
    static void printSolution(const std::vector<double>& solution);
    
private:
    static int findPivotRow(const std::vector<std::vector<double>>& matrix, int col);
    static void swapRows(std::vector<std::vector<double>>& matrix, int row1, int row2);
    static void normalizeRow(std::vector<std::vector<double>>& matrix, int row);
    static void eliminateVariable(std::vector<std::vector<double>>& matrix, int pivotRow);
    static bool isZero(double value, double epsilon = 1e-10);
};

#endif