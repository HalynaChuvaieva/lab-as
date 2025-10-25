#pragma once // Захист від повторного включення файлу

#include <iostream>
#include <string>
#include <stdexcept> // Для обробки помилок (напр., неправильні розміри)

// Об'єктно-орієнтована реалізація класу для роботи з матрицями в стилі T**
// Цей клас об'єднує дані (матрицю) та операції над ними в одне ціле,
// що робить код безпечнішим і зручнішим у використанні.
class Matrix {
private:
    int rows_, cols_;
    double** data_;

public:

    // Конструктор: створює матрицю розміром rows x cols
    // Автоматично виділяє пам'ять і заповнює її нулями.
    Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
        if (rows <= 0 || cols <= 0) {
            throw std::invalid_argument("Matrix dimensions must be positive.");
        }
        // Виділення пам'яті для масиву вказівників (рядків)
        data_ = new double*[rows_];
        // Виділення пам'яті для кожного рядка та ініціалізація нулями
        for (int i = 0; i < rows_; ++i) {
            data_[i] = new double[cols_](); 
        }
    }

    Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
        data_ = new double* [rows_];
        for (int i = 0; i < rows_; ++i) {
            data_[i] = new double[cols_];
            for (int j = 0; j < cols_; ++j)
                data_[i][j] = other.data_[i][j];
        }
    }

    // ✅ Оператор присвоєння (deep copy)
    Matrix& operator=(const Matrix& other) {
        if (this == &other)
            return *this;

        // звільняємо стару пам’ять
        for (int i = 0; i < rows_; ++i)
            delete[] data_[i];
        delete[] data_;

        rows_ = other.rows_;
        cols_ = other.cols_;

        data_ = new double* [rows_];
        for (int i = 0; i < rows_; ++i) {
            data_[i] = new double[cols_];
            for (int j = 0; j < cols_; ++j)
                data_[i][j] = other.data_[i][j];
        }

        return *this;
    }

    // Деструктор: автоматично звільняє всю виділену пам'ять,
    // коли об'єкт матриці знищується. Це запобігає витокам пам'яті.
    ~Matrix() {
        for (int i = 0; i < rows_; ++i) {
            delete[] data_[i]; // Звільняємо кожен рядок
        }
        delete[] data_; // Звільняємо масив вказівників
    }

    // --- Методи доступу ---

    int getRows() const {
        return rows_;
    }

    int getCols() const {
        return cols_;
    }

    double** Matrix::getData() const {
        return data_;  // 
    }

    double& operator()(int r, int c) {
        if (r < 0 || r >= rows_ || c < 0 || c >= cols_) {
            throw std::out_of_range("Matrix subscript out of bounds.");
        }
        return data_[r][c];
    }
    
    // Константна версія для об'єктів, які не можна змінювати
    const double& operator()(int r, int c) const {
        if (r < 0 || r >= rows_ || c < 0 || c >= cols_) {
            throw std::out_of_range("Matrix subscript out of bounds.");
        }
        return data_[r][c];
    }
    
    // --- Операції над матрицями 

    // Метод для додавання матриць. Повертає нову матрицю-результат.
    Matrix add(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition.");
        }
        
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result(i, j) = this->data_[i][j] + other.data_[i][j];
            }
        }
        return result;
    }

    // Метод для віднімання матриць. Повертає нову матрицю-результат.
    Matrix subtract(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
        }

        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result(i, j) = this->data_[i][j] - other.data_[i][j];
            }
        }
        return result;
    }

    // --- Ввід / вивід ---

    // Метод для заповнення матриці з консолі
    void input(const std::string& name) {
        std::cout << "Enter elements for matrix " << name << " (" << rows_ << "x" << cols_ << "):\n";
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cin >> data_[i][j];
            }
        }
    }

    // Метод для друку матриці в консоль
    void print(const std::string& name) const {
        std::cout << "Matrix " << name << ":\n";
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cout << data_[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};