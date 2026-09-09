#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <cstdint>
#include <string>

class BigInt {
    private:
        int nDig;
        bool neg;
        int8_t *d;

        BigInt(bool, int);
        void correct();

    public:
        BigInt(); //construtor default
        ~BigInt(); //destrutor
        BigInt(long long int); // conversor long long int --> BigInt
        BigInt(const BigInt&); // construtor por copia (B = A)
        BigInt(BigInt&&) noexcept; // construtor por movimento (B = A + C)
        BigInt(const std::string&);

        BigInt& operator=(const BigInt&); // operador atr. copia
        const BigInt& operator=(BigInt&& B) noexcept; // atribuicao movimento
        //const BigInt& operator=(BigInt&& B) noexcept; // operador atr. movimento
        int operator[](int i) const {return (i >= size() || i < 0? 0: int(d[i]));}

        friend operator std::ostream operator<<(std::ostream&, const BigInt &);

        /// funcoes de consulta (inline)
        bool isNeg() const {return neg;}
        int size() const {return nDig;}
        bool isZero() const {return (nDig == 1 && d[0] == 0? true: false);}

        long long int toInt();

};

#endif
