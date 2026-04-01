#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <iostream>

/// Estou criando esta classe AGORA (fora do projeto)
class BigInt {
  private:
    bool neg;
    int nDig;
    int8_t* d;

  public:
    BigInt();
    BigInt(bool, int);
    ~BigInt();
    BigInt(const BigInt&);
    bool isNeg() {return neg;}
    int size() {return nDig;};
    void clear();

};

#endif
