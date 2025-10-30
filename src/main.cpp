#include "JordanGaussSolver.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

class ReportGenerator {
public:
    static void generateCSV(const JordanGaussSolver::SolutionResult& result, 
                           const vector<vector<double>>& originalMatrix) {
        ofstream file("jordan_gauss_results.csv");
        
        file << "Step,Matrix,Operation,Solution\n";
        
        // Заголовок с системой уравнений
        file << "0,\"Система уравнений:\",\"\",\"\"\n";
        file << "1,\"4x - y + 3z = 12\",\"\",\"\"\n";
        file << "2,\"2x + 2y - z = 4\",\"\",\"\"\n";
        file << "3,\"x + y + z = 6\",\"\",\"\"\n";
        file << "4,\"\",\"\",\"\"\n";
        
        // Шаги решения
        int step = 0;
        for (size_t i = 0; i < result.steps.size(); i++) {
            string operation = getOperationDescription(i, result.steps.size());
            string solution = getSolutionString(result.steps[i]);
            
            file << step + 5 << ",\"" << matrixToString(result.steps[i]) << "\",\""
                 << operation << "\",\"" << solution << "\"\n";
            step++;
        }
        
        // Финальное решение
        file << step + 5 << ",\"\",\"Финальное решение:\",\"\"\n";
        file << step + 6 << ",\"x = " << result.solution[0] << "\",\"\",\"\"\n";
        file << step + 7 << ",\"y = " << result.solution[1] << "\",\"\",\"\"\n";
        file << step + 8 << ",\"z = " << result.solution[2] << "\",\"\",\"\"\n";
        
        file.close();
        cout << "✅ CSV отчет сохранен в jordan_gauss_results.csv" << endl;
    }
    
    static void generateHTML(const JordanGaussSolver::SolutionResult& result,
                            const vector<vector<double>>& originalMatrix) {
        ofstream file("jordan_gauss_report.html");
        
        file << R"(<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Решение СЛАУ методом Жордана-Гаусса</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            padding: 20px;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
            background: white;
            border-radius: 15px;
            box-shadow: 0 20px 40px rgba(0,0,0,0.1);
            overflow: hidden;
        }
        
        .header {
            background: linear-gradient(135deg, #2c3e50, #34495e);
            color: white;
            padding: 30px;
            text-align: center;
        }
        
        .header h1 {
            font-size: 2.5em;
            margin-bottom: 10px;
        }
        
        .header .subtitle {
            font-size: 1.2em;
            opacity: 0.9;
        }
        
        .content {
            padding: 30px;
        }
        
        .section {
            margin-bottom: 40px;
            background: #f8f9fa;
            padding: 25px;
            border-radius: 10px;
            border-left: 5px solid #3498db;
        }
        
        .section-title {
            color: #2c3e50;
            margin-bottom: 20px;
            font-size: 1.5em;
            display: flex;
            align-items: center;
            gap: 10px;
        }
        
        .section-title i {
            color: #3498db;
        }
        
        .system-equations {
            display: grid;
            gap: 10px;
            font-size: 1.2em;
            font-family: 'Courier New', monospace;
        }
        
        .equation {
            padding: 10px 15px;
            background: white;
            border-radius: 5px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
        }
        
        .steps-container {
            display: grid;
            gap: 15px;
        }
        
        .step {
            background: white;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 3px 10px rgba(0,0,0,0.1);
            border: 1px solid #e9ecef;
        }
        
        .step-header {
            display: flex;
            justify-content: between;
            align-items: center;
            margin-bottom: 15px;
            padding-bottom: 10px;
            border-bottom: 2px solid #3498db;
        }
        
        .step-number {
            background: #3498db;
            color: white;
            padding: 5px 15px;
            border-radius: 20px;
            font-weight: bold;
        }
        
        .step-operation {
            color: #e74c3c;
            font-weight: bold;
            font-size: 1.1em;
        }
        
        .matrix {
            font-family: 'Courier New', monospace;
            background: #f8f9fa;
            padding: 15px;
            border-radius: 5px;
            margin: 10px 0;
        }
        
        .matrix-row {
            display: flex;
            justify-content: center;
            gap: 20px;
            margin: 5px 0;
        }
        
        .matrix-element {
            padding: 5px 10px;
            min-width: 60px;
            text-align: center;
        }
        
        .solution {
            background: linear-gradient(135deg, #27ae60, #2ecc71);
            color: white;
            padding: 25px;
            border-radius: 10px;
            text-align: center;
        }
        
        .solution-values {
            display: flex;
            justify-content: center;
            gap: 30px;
            margin-top: 15px;
            flex-wrap: wrap;
        }
        
        .solution-value {
            background: rgba(255,255,255,0.2);
            padding: 15px 25px;
            border-radius: 8px;
            font-size: 1.3em;
            font-weight: bold;
        }
        
        .fraction-solution {
            margin-top: 20px;
            padding: 15px;
            background: rgba(255,255,255,0.1);
            border-radius: 5px;
        }
        
        .check-results {
            display: grid;
            gap: 10px;
            margin-top: 15px;
        }
        
        .check-equation {
            display: flex;
            justify-content: space-between;
            padding: 8px 15px;
            background: rgba(255,255,255,0.9);
            border-radius: 5px;
            color: #2c3e50;
        }
        
        @media (max-width: 768px) {
            .container {
                margin: 10px;
            }
            
            .header h1 {
                font-size: 2em;
            }
            
            .solution-values {
                flex-direction: column;
                gap: 10px;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>🧮 Решение СЛАУ</h1>
            <div class="subtitle">Метод Жордана-Гаусса</div>
        </div>
        
        <div class="content">
            <div class="section">
                <div class="section-title">
                    <span>📋 Исходная система</span>
                </div>
                <div class="system-equations">
                    <div class="equation">4x - y + 3z = 12</div>
                    <div class="equation">2x + 2y - z = 4</div>
                    <div class="equation">x + y + z = 6</div>
                </div>
            </div>
            
            <div class="section">
                <div class="section-title">
                    <span>🔄 Процесс решения</span>
                </div>
                <div class="steps-container">
        )";
        
        // Генерация шагов решения
        for (size_t i = 0; i < result.steps.size(); i++) {
            file << generateStepHTML(i, result.steps[i], result.steps.size());
        }
        
        file << R"(
                </div>
            </div>
            
            <div class="section">
                <div class="section-title">
                    <span>✅ Результат</span>
                </div>
                <div class="solution">
                    <h3>Решение системы</h3>
                    <div class="solution-values">
        )";
        
        // Вывод решения
        char var = 'x';
        for (size_t i = 0; i < result.solution.size(); i++) {
            file << "<div class=\"solution-value\">" << var << " = " 
                 << fixed << setprecision(6) << result.solution[i] << "</div>";
            var++;
        }
        
        file << R"(
                    </div>
                    <div class="fraction-solution">
                        <div>Точное решение в дробях:</div>
                        <div>x = 22/15, y = 28/15, z = 8/3</div>
                    </div>
                </div>
            </div>
            
            <div class="section">
                <div class="section-title">
                    <span>🔍 Проверка решения</span>
                </div>
                <div class="check-results">
        )";
        
        // Проверка решения
        auto residuals = JordanGaussSolver::checkSolution(originalMatrix, result.solution);
        vector<string> equations = {
            "4x - y + 3z = 12",
            "2x + 2y - z = 4", 
            "x + y + z = 6"
        };
        
        for (size_t i = 0; i < residuals.size(); i++) {
            file << "<div class=\"check-equation\">"
                 << "<span>" << equations[i] << "</span>"
                 << "<span>Невязка: " << scientific << setprecision(2) << residuals[i] << "</span>"
                 << "</div>";
        }
        
        file << R"(
                </div>
            </div>
        </div>
    </div>
    
    <script>
        // Анимация появления шагов
        document.addEventListener('DOMContentLoaded', function() {
            const steps = document.querySelectorAll('.step');
            steps.forEach((step, index) => {
                setTimeout(() => {
                    step.style.opacity = '1';
                    step.style.transform = 'translateY(0)';
                }, index * 200);
            });
            
            // Изначальные стили для анимации
            steps.forEach(step => {
                step.style.opacity = '0';
                step.style.transform = 'translateY(20px)';
                step.style.transition = 'all 0.5s ease';
            });
        });
    </script>
</body>
</html>)";
        
        file.close();
        cout << "✅ HTML отчет сохранен в jordan_gauss_report.html" << endl;
    }
    
private:
    static string matrixToString(const vector<vector<double>>& matrix) {
        stringstream ss;
        ss << "[";
        for (size_t i = 0; i < matrix.size(); i++) {
            ss << "[";
            for (size_t j = 0; j < matrix[i].size(); j++) {
                ss << fixed << setprecision(6) << matrix[i][j];
                if (j < matrix[i].size() - 1) ss << ", ";
            }
            ss << "]";
            if (i < matrix.size() - 1) ss << ", ";
        }
        ss << "]";
        return ss.str();
    }
    
    static string getOperationDescription(int stepIndex, size_t totalSteps) {
        vector<string> operations = {
            "Начальная матрица",
            "Перестановка строк 1 и 3",
            "R2 = R2 - 2×R1, R3 = R3 - 4×R1", 
            "Перестановка строк 2 и 3",
            "Нормализация строки 2",
            "Исключение x из строки 1",
            "Нормализация строки 3",
            "Исключение x,y из остальных строк"
        };
        
        if (stepIndex < operations.size()) {
            return operations[stepIndex];
        }
        return "Шаг преобразования";
    }
    
    static string getSolutionString(const vector<vector<double>>& matrix) {
        int n = matrix.size();
        stringstream ss;
        ss << "[";
        for (int i = 0; i < n; i++) {
            ss << matrix[i][n];
            if (i < n - 1) ss << ", ";
        }
        ss << "]";
        return ss.str();
    }
    
    static string generateStepHTML(int stepIndex, const vector<vector<double>>& matrix, size_t totalSteps) {
        stringstream ss;
        ss << "<div class=\"step\">\n";
        ss << "    <div class=\"step-header\">\n";
        ss << "        <div class=\"step-number\">Шаг " << (stepIndex + 1) << "</div>\n";
        ss << "        <div class=\"step-operation\">" << getOperationDescription(stepIndex, totalSteps) << "</div>\n";
        ss << "    </div>\n";
        ss << "    <div class=\"matrix\">\n";
        
        for (const auto& row : matrix) {
            ss << "        <div class=\"matrix-row\">\n";
            ss << "            <div class=\"matrix-element\">|</div>\n";
            for (size_t j = 0; j < row.size() - 1; j++) {
                ss << "            <div class=\"matrix-element\">" << fixed << setprecision(3) << row[j] << "</div>\n";
            }
            ss << "            <div class=\"matrix-element\">|</div>\n";
            ss << "            <div class=\"matrix-element\">" << fixed << setprecision(3) << row.back() << "</div>\n";
            ss << "            <div class=\"matrix-element\">|</div>\n";
            ss << "        </div>\n";
        }
        
        ss << "    </div>\n";
        ss << "</div>\n";
        return ss.str();
    }
};

void printSystemInfo() {
    cout << "==========================================" << endl;
    cout << " Лабораторная работа №6" << endl;
    cout << " Решение СЛАУ методом Жордана-Гаусса" << endl;
    cout << "==========================================" << endl;
    cout << endl;
    
    cout << "Система уравнений:" << endl;
    cout << "4x - y + 3z = 12" << endl;
    cout << "2x + 2y - z = 4" << endl;
    cout << "x + y + z = 6" << endl;
    cout << endl;
}

int main() {
    printSystemInfo();
    
    // Расширенная матрица системы
    vector<vector<double>> matrix = {
        {4, -1, 3, 12},
        {2, 2, -1, 4},
        {1, 1, 1, 6}
    };
    
    cout << "Расширенная матрица системы:" << endl;
    JordanGaussSolver::printMatrix(matrix);
    cout << endl;
    
    // Решение системы
    auto result = JordanGaussSolver::solve(matrix);
    
    if (result.success) {
        cout << "✅ Система успешно решена!" << endl << endl;
        
        // Генерация отчетов
        ReportGenerator::generateCSV(result, matrix);
        ReportGenerator::generateHTML(result, matrix);
        
        // Вывод решения в консоль
        JordanGaussSolver::printSolution(result.solution);
        
        cout << endl << "📊 Отчеты успешно сгенерированы:" << endl;
        cout << "   • jordan_gauss_results.csv - таблица с шагами решения" << endl;
        cout << "   • jordan_gauss_report.html - визуальный отчет" << endl;
        
    } else {
        cout << "❌ Ошибка при решении системы: " << result.error_message << endl;
        return 1;
    }
    
    return 0;
}