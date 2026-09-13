#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <cstdint>
#include <string>
#include <iostream>

class BigInt {
    private:
        // Atributos
        int nDig;
        bool neg;
        int8_t *d;

        // construtores
        BigInt(bool, int);


        // funcoes
        void correct();
        void increment();
        void decrement();

    public:
        BigInt(); //construtor default
        ~BigInt(); //destrutor
        BigInt(long long int); // conversor long long int --> BigInt
        BigInt(const BigInt&); // construtor por copia (B = A)
        BigInt(BigInt&&) noexcept; // construtor por movimento (B = A + C)
        explicit BigInt(const std::string&);

        const BigInt& operator=(const BigInt&); // operador atr. copia
        const BigInt& operator=(BigInt&& B) noexcept; // atribuicao movimento
        //const BigInt& operator=(BigInt&& B) noexcept; // operador atr. movimento
        int operator[](int i) const {return (i >= size() || i < 0? 0: int(d[i]));}

        // Lista de operadores
        friend std::ostream &operator<<(std::ostream&, const BigInt &);
        friend std::istream &operator>>(std::istream& I, BigInt& B);
        friend bool operator==(const BigInt &, const BigInt &);
        friend bool operator!=(const BigInt &, const BigInt &);
        friend bool operator<(const BigInt &, const BigInt &);
        friend bool operator>(const BigInt &, const BigInt &);
        friend bool operator>=(const BigInt &, const BigInt &);
        friend bool operator<=(const BigInt &, const BigInt &);
        BigInt &operator++(); // operador de pre incremento
        BigInt &operator--(); // operador de pre decremento
        BigInt operator++(int); // operador pos incremento
        BigInt operator--(int); // operador pos decremento
        BigInt operator!(); // operador fatorial
        BigInt operator<<(int) const; // operador deslocamento esquerda
        BigInt operator>>(int) const; // oper. deslocamento direita

        const BigInt &operator+() const {return *this;};
        BigInt operator-() const;


        /// funcoes de consulta (inline)
        bool isNeg() const {return neg;}
        int size() const {return nDig;}
        bool isZero() const {return (nDig == 1 && d[0] == 0? true: false);}

        long long int toInt();
        void division(const BigInt &, BigInt &, BigInt &) const;

        /// Funcoes classicas
        friend BigInt abs(const BigInt &);
        friend BigInt operator+(const BigInt &, const BigInt &);
        friend BigInt operator-(const BigInt &, const BigInt &);
        friend BigInt operator*(const BigInt &, const BigInt &);
        friend BigInt operator/(const BigInt &, const BigInt &);
        friend BigInt operator%(const BigInt &, const BigInt &);

};

#endif
