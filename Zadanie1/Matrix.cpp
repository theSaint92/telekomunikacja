#include "Matrix.h"
#include "sstream"
#include <fstream>
#include <algorithm>

const int Matrix::INDEX_OUT_OF_BOUND_EXCEPTION = 10;
const int Matrix::FILE_NOT_FOUND = 11;
const int Matrix::UNEXPECTED_SIZE = 12;
const int Matrix::SINGULAR = 13;
const int Matrix::DIVIDE_BY_ZERO = 14;

//Konstruktory
Matrix::Matrix()
{
    this->n = 0;
    this->m = 0;
}

Matrix::Matrix(unsigned int n, unsigned int m)
{
    this->n = n;
    this->m = m;
    for (int i=0; i<n*m ; i++)
        this->tablica.push_back(0);
}

Matrix::Matrix(unsigned int n, unsigned int m, std::vector < double > tablica)
{
    this->n = n;
    this->m = m;
    this->tablica = tablica;
}

Matrix::Matrix(char *wybor)
{
    std::fstream plik;
    plik.open(wybor);
    std::string unused;
    double liczba;
    this->n = 0;
    this->m = 0;

    while ( std::getline(plik, unused) )
        n++;

    plik.clear();
    plik.seekg(0, std::ios::beg);

    while (!plik.eof())
    {
        plik >> liczba;
        this->tablica.push_back(liczba);
        m++;
    }
    m = m/n;
}

Matrix::~Matrix()
{
    //Destruktor
}

//Akcesory
unsigned int Matrix::getN()
{
    return this->n;
}

unsigned int Matrix::getM()
{
    return this->m;
}

double Matrix::get(unsigned int i,unsigned int j) throw(int)
{
    if (i<n && j<m){
        return this->tablica[i*m+j];
    } else {
        throw Matrix::INDEX_OUT_OF_BOUND_EXCEPTION;
    }
}

//Podstawowe operacje na macierzach

void Matrix::change(char* wybor) throw(int)
{
    std::fstream plik;
    plik.open(wybor);
    if (plik.good()){
        std::string unused;
        double liczba;

        this->n = 0;
        this->m = 0;
        this->tablica.clear();

        while ( std::getline(plik, unused) )
            n++;

        plik.clear();
        plik.seekg(0, std::ios::beg);

        while (!plik.eof())
        {
            plik >> liczba;
            this->tablica.push_back(liczba);
            m++;
        }
        m = m/n;
    } else {
        throw Matrix::FILE_NOT_FOUND;
    }

}

void Matrix::change(unsigned int n, unsigned int m, std::vector < double > tablica)
{
    this->n = n;
    this->m = m;
    this->tablica = tablica;
}

void Matrix::setSize(unsigned int n, unsigned int m)
{
    Matrix temp(n,m);
    int n_min = std::min(this->n,n);
    int m_min = std::min(this->m,m);

    for (int i=0;i<n_min;i++)
    {
        for (int j=0;j<m_min;j++)
            temp.set(i,j,this->get(i,j));
    }

    // Jak to zrobic latwiej?

    this->n = n;
    this->m = m;
    this->tablica.clear();
    for (int i=0; i<n*m ; i++)
        this->tablica.push_back(0);

    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
            this->set(i,j,temp.get(i,j));
    }
}

void Matrix::set(unsigned int i, unsigned int j, double value) throw(int)
{
    if (i<n && j<m){
        this->tablica[i*m+j]=value;
    } else {
        throw Matrix::INDEX_OUT_OF_BOUND_EXCEPTION;
    }
}

std::string Matrix::toString()
{
    std::stringstream ss;
    for (unsigned int i=0; i<n;i++){
        ss<<"\n";
        for (unsigned int j=0; j<m; j++){
            ss<<this->get(i,j)<<" ; ";
        }
    }
    return ss.str();
}

//Zaawansowane operacje na macierzach
double Matrix::det()
{
    if (this->n==this->m)
    {
        double wynik=0;

        if (this->n==1)
        {
            wynik=  this->tablica[0];
        }

        else if (this->n==2)
        {
            wynik=  this->tablica[0]*this->tablica[3] - \
                    this->tablica[1]*this->tablica[2];
        }

        else if (this->n==3)
        {
            wynik=  this->tablica[0]*this->tablica[4]*this->tablica[8] + \
                    this->tablica[1]*this->tablica[5]*this->tablica[6] + \
                    this->tablica[2]*this->tablica[3]*this->tablica[7] - \
                    this->tablica[6]*this->tablica[4]*this->tablica[2] - \
                    this->tablica[7]*this->tablica[5]*this->tablica[0] - \
                    this->tablica[8]*this->tablica[3]*this->tablica[1];
        }

        //ROZWINIECIE LAPLACE'A - wzgledem pierwszego wiersza
        else
        {
            for (int j = 0; j<this->n; j++)
            {
                Matrix minor;
                minor = this->Minor(0,j);
                if (j%2==0) wynik+=this->get(0,j)*minor.det();
                else wynik+=this->get(0,j)*(-1)*minor.det();
            }
        }

        return wynik;
    }
    else
    {
        throw Matrix::UNEXPECTED_SIZE;
    }
}

Matrix Matrix::Minor(unsigned int k, unsigned int w) throw(int)
{
    if (this->n == this->m)
    {
        Matrix wynik(this->n-1,this->m-1);
        int n = wynik.getN();
        int m = wynik.getM();
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<m;j++)
            {
                if ( i<k && j<w) wynik.set(i,j,this->get(i,j));
                else if (i<k && j>=w) wynik.set(i,j,this->get(i,j+1));
                else if (i>=k && j<w) wynik.set(i,j,this->get(i+1,j));
                else if (i>=k && j>=w) wynik.set(i,j,this->get(i+1,j+1));
            }
        }
        return wynik;
    }

    else
    {
        throw Matrix::UNEXPECTED_SIZE;
    }
}

Matrix Matrix::Cofactor() throw(int)
{
    if (this->n==this->m)
    {
        Matrix wynik(this->n,this->m);
        Matrix minor;
        double temp;

        for (int i=0;i<this->n;i++)
        {
            for (int j=0;j<this->m;j++)
            {
                temp=0;
                minor = this->Minor(i,j);
                if ((i+j)%2 == 0) temp = minor.det();
                else temp = -minor.det();
                wynik.set(i,j,temp);
            }

        }
        return wynik;
    }
    else
    {
        throw Matrix::UNEXPECTED_SIZE;
    }
}

Matrix Matrix::Transpose()
{
    Matrix wynik(this->m,this->n);
    for (int i=0;i<this->m;i++)
    {
        for (int j=0;j<this->n;j++)
        {
            wynik.set(i,j,this->get(j,i));
        }

    }
    return wynik;

}

Matrix Matrix::Inverse() throw(int)
{
    if (this->n==this->m)
    {
        double wyznacznik = this->det();
        if (wyznacznik != 0)
        {
            Matrix wynik;
            wynik = this->Cofactor();
            wynik = wynik.Transpose();
            wynik = wynik*(1/wyznacznik);
            return wynik;
        }
        else
        {
            throw Matrix::SINGULAR;
        }
    }
    else
    {
        throw Matrix::UNEXPECTED_SIZE;
    }
}

Matrix Matrix::Diagonal() throw(int)
{
    if (this->n == this->m)
    {
        Matrix wynik(this->n,this->m);
        for (int i=0;i<this->n;i++)
                wynik.set(i,i,this->get(i,i));
        return wynik;
    }
    else
    {
        throw Matrix::UNEXPECTED_SIZE;
    }
}

bool Matrix::Diag_0()
{
    for (int i=0;i<this->n;i++)
        if (this->get(i,i) == 0) return true;
    else return false;
}

//Operatory
Matrix Matrix::operator +(const Matrix& b) throw(int)
{
    if (this->n==b.n && this->m==b.m)
    {
        Matrix wynik(b.n,b.m);
        for (int i=0;i<b.n;i++)
        {
            for (int j=0;j<b.m;j++)
                wynik.set(i,j,this->get(i,j)+b.tablica[i*m+j]);
        }
        return wynik;
    }
    else
    {
        throw Matrix::UNEXPECTED_SIZE;
    }
}

Matrix Matrix::operator -(const Matrix& b) throw(int)
{
    if (this->n==b.n && this->m==b.m)
    {
        Matrix wynik(b.n,b.m);
        for (int i=0;i<b.n;i++)
        {
            for (int j=0;j<b.m;j++)
                wynik.set(i,j,this->get(i,j)-b.tablica[i*m+j]);
        }
        return wynik;
    }
    else
    {
        throw Matrix::UNEXPECTED_SIZE;
    }
}

Matrix Matrix::operator*(const Matrix& b) throw(int)
{
    if (this->m==b.n)
    {
        unsigned int wynik_n = this->n;
        unsigned int wynik_m = b.m;
        double aktualny;
        Matrix wynik(wynik_n,wynik_m);
        for (int i=0;i<wynik_n;i++)
        {
            for (int j=0;j<wynik_m;j++)
            {
                for (int k=0 ; k<this->m ; k++)
                {
                    aktualny+=this->get(i,k)*b.tablica[k*b.m+j];
                    //std::cout << this->get(i,k) << " " << b.tablica[k*b.m+j] << std::endl;
                }
                //std::cout << std::endl;
                wynik.set(i,j,aktualny);
                aktualny = 0;
            }
        }
        return wynik;
    }
    else
    {
        throw Matrix::UNEXPECTED_SIZE;
    }
}

Matrix Matrix::operator*(const double& a)
{
    Matrix wynik(this->n,this->m);
    for (int i=0;i<this->n;i++)
    {
        for (int j=0;j<this->m;j++)
            wynik.set(i,j,this->get(i,j)*a);
    }
    return wynik;
}

Matrix Matrix::operator/(const double& a) throw(int)
{
    if (a!=0)
    {
        Matrix wynik(this->n,this->m);
        for (int i=0;i<this->n;i++)
        {
            for (int j=0;j<this->m;j++)
                wynik.set(i,j,this->get(i,j)/a);
        }
        return wynik;
    }
    else
    {
        throw Matrix::DIVIDE_BY_ZERO;
    }
}
