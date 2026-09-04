

class BigInt {
    private:
        int nDig;
        bool neg;
        int8_t *d;

        BigInt()

    public:
        BigInt(); //construtor default
        ~BigInt(); //destrutor
        BigInt(bool, int);
        BigInt(const BigInt&); // construtor por copia (B = A)
        BigInt(BigInt&&) noexcept; // construtor por movimento (B = A + C)

        BigInt& operator=(const BigInt&); // operador atr. copia
        BigInt& operator=(BigInt&&); // operador atr. movimento
        int operator[](int i) const return {i >= size() || i < 0? 0: int(d[i])};

        /// funcoes de consulta (inline)
        bool isNeg() return this->neg;
        int size() return this->nDig;
        bool isZero() return (nDig == 1 && d[0] == 0? true: false);



}
