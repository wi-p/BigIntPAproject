#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <iostream>

/// Estou criando esta classe AGORA (fora do projeto)
class BigInt {
  private:
  	BigInt(bool, int);
    bool neg;
    int nDig;
    int8_t* d;

  public:
    BigInt();
    ~BigInt();
    BigInt(const BigInt& bi);
    bool isNeg() const {return neg;}
    int size() const {return nDig;};
    void clear();
};

#endif
