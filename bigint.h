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
  	// funcoes construtoras
    BigInt();
    ~BigInt();
    BigInt(const BigInt& bi);
    BigInt(long long int);
    
    //funcoes de get/set
    bool isNeg() const {return neg;}
    void setNeg(bool value) {neg = 	value;}
    int size() const {return nDig;};
    bool isZero() const {return (nDig == 1 && d[0] == 0 ? true : false);};
    void clear();
    int getIndex(int i) const {return d[i];}
    
    // operadores
    int operator[](int i) const {return (i >= this -> size() || i < 0 ? 0 : int(this->getIndex(i)));}
    
};

#endif
