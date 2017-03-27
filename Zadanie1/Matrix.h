#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>

class Matrix
{

    unsigned int n;
    unsigned int m;
    std::vector < double > tablica;


    public:
        //cstor + dstor
        Matrix();
        Matrix(unsigned int n, unsigned int m);
        Matrix(unsigned int n, unsigned int m, std::vector < double > tablica);
        Matrix(char *plik);
        virtual ~Matrix();

        //Akcesory
        unsigned int getN();
        unsigned int getM();
        double get(unsigned int i,unsigned int j) throw(int);

        //Podstawowe operacje na macierzach
        void change(char* plik) throw(int);
        void change(unsigned int n, unsigned int m, std::vector < double > tablica);
        void setSize(unsigned int n, unsigned int m);
        void set(unsigned int i, unsigned int j, double value) throw(int);
        std::string toString();

        //Zaawansowane operacje na macierzach
        double det();
        Matrix Minor(unsigned int k, unsigned int w) throw(int);
        Matrix Cofactor() throw(int);
        Matrix Transpose();
        Matrix Inverse() throw(int);
        Matrix Diagonal() throw(int);
        bool Diag_0();

        //Operatory
        Matrix operator+(const Matrix& b) throw(int);
        Matrix operator-(const Matrix& b) throw(int);
        Matrix operator*(const Matrix& b) throw(int);
        Matrix operator*(const double& a);
        Matrix operator/(const double& a) throw(int);

        //Mozliwe bledy
        static const int INDEX_OUT_OF_BOUND_EXCEPTION;
        static const int FILE_NOT_FOUND;
        static const int UNEXPECTED_SIZE;
        static const int SINGULAR;
        static const int DIVIDE_BY_ZERO;
};

#endif // MATRIX_H
