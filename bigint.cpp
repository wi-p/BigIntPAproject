#include "bigint.h"
#include <cmath>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
/* ACRESCENTAR */
/*
PAREI EM:
 // Faz o BigInt manter o sinal e passar a ter size()+1 digitos,
      // avancando todos para uma posicao mais significativa aa frente.
      //B.nDig = B.size() + 1;
*/


using namespace std;

/// Construtor default.
/// Inicializa com um inteiro de 1 digito, valor 0 (zero).
/// NAO PODE SER MODIFICADO
BigInt::BigInt()
  : neg(false)
  , nDig(1)
  , d(new int8_t[1]{0})
{}

/// Destrutor
BigInt::~BigInt() { // destrutor
    delete[] d;
}

/// Construtor especifico PRIVADO que recebe o sinal e a quantidade de digitos
BigInt::BigInt(bool IsNeg, int size):
	neg(IsNeg),
	nDig( size >= 1? size:1),
	d(new int8_t[nDig]{0}) // cria array com nDig valores inteiros (todos 0)
{}

/// Construtor por copia.
/// Delega ao construtor especifico privado.
/// NAO PODE SER MODIFICADO.
BigInt::BigInt(const BigInt& B)
  : BigInt(B.isNeg(), B.size())
{
  // Copia os digitos
  for (int i=0; i<size(); ++i) d[i] = B.d[i];
}

/// Atribuicao por copia
const BigInt& BigInt::operator=(const BigInt& B) {
  // se os valores passados forem iguais, trata-se do mesmo
  // objeto, entao so retornar ele mesmo e nao precisa copiar
  if (this == &B) return *this;

  if (this->nDig != B.nDig) { // verifica se tem mesmo tamanho
    delete[] d;

    neg = B.isNeg();
    nDig = B.nDig;

    this->d = new int8_t[nDig]; // aloca memoria
  }

  for (int i = 0; i < nDig; ++i) d[i] = B.d[i]; // copia elementos

  return *this; // retorna objeto (desreferenciado)

}

/// Construtor por movimento
BigInt::BigInt(BigInt&& B) noexcept:
	neg(B.neg),
	nDig(B.nDig),
	d(B.d)
{
	B.nDig = 0;
	B.d = nullptr;
}

/// Atribuicao por movimento
const BigInt& BigInt::operator=(BigInt&& B) noexcept {
    if (this == &B) return *this;

    delete[] d; // libera o espaco anterior

    // copia os elementos para o referido BigInt
    this->neg = B.neg;
    this->nDig = B.nDig;
    this->d = B.d;

    // limpa o BigInt temporario
    B.nDig = 0;
    B.d = nullptr;

    return *this;
}

/// Funcoes de consulta


/// Construtor especifico a partir de inteiro longo.
/// Tambem conversor de long long int para BigInt.
/// NAO PODE SER MODIFICADO NAS PARTES JAH IMPLEMENTADAS.
/// PODE (E PRECISA) RECEBER ACRESCIMOS, APENAS
/// NAS PARTES INDICADAS POR /* ACRESCENTAR */
BigInt::BigInt(long long int N):
    BigInt(
		(N < 0? true: false), // sinal do BigInt
		(N == 0? 1: 1 + int(log10(fabs(N))))  // numero de digitos
	)
{
  // Calcula os digitos, usando divisao inteira por 10
  for (int i=0; i<size(); ++i)
  {
    d[i] = abs(N%10); // Modulo do resto da divisao
    N /= 10;          // Divisao inteira
  }
}

/// Conversor de BigInt para long long int
/* ACRESCENTAR */
long long int BigInt::toInt() {
	int val = 0;

	for (int i = size() -1; i >= 0; --i) {
		val = 10 * val + d[i];

		if (val < 0) {
			std::cerr << "Erro, numero muito grande";
			return 0;
		}
	}

	if (isNeg()) val = - val;

	return val;
}

/// ******************
/// * FIM DA PARTE 1 *
/// ******************

/// Funcao privada que corrige o numero, caso haja inconsistencias
void BigInt::correct() {
    int newSize = size();

    while (newSize > 1 && d[newSize - 1] == 0) newSize -= 1;

    if (newSize != size()) nDig = newSize;

    if (isZero()) neg = false;
}

/// Construtor especifico a partir de string.
/// Nao eh conversor de string para BigInt.
/// Delega ao construtor default.
/// NAO PODE SER MODIFICADO NAS PARTES JAH IMPLEMENTADAS.
/// PODE (E PRECISA) RECEBER ACRESCIMOS, APENAS
/// NAS PARTES INDICADAS POR /* ACRESCENTAR */
BigInt::BigInt(const string& S)
  : BigInt() // Valor inicial zero
{
  // Se string vazia, emite erro e permanece com valor inicial zero
  if (S.empty())
  {
    cerr << "empty string cannot create a BigInt\n";
    return;
  }

  // Posicao onde comecam os digitos, inicialmente zero
  size_t ini=0;
  // Leva em conta o sinal
  bool IsNeg = false;

  if (S[0]=='+' || S[0]=='-')
  {
    // Se nao tem nenhum digito alem do sinal, emite erro e permanece com valor inicial
    if (S.size()==1)
    {
      cerr << "sign-only string cannot create a BigInt\n";
      return;
    }
    IsNeg = (S[0]=='-');
    ++ini;
  }

  // Faz ter sinal (IsNeg) e numero de digitos (tamanho da string - ini) corretos
    *this = BigInt(IsNeg, S.size() - ini);

  // Calculo dos digitos do BigInt
  for (int i=0; i<size(); ++i)
  {
    const char& c = S[S.size()-1-i]; // Referencia (apelido) para facilitar a notacao
    if (!isdigit(c))
    {
      *this = BigInt(); // = 0
      cerr << "string with invalid character cannot create a BigInt\n";
      return;
    }
    d[i] = static_cast<int8_t>(c-'0');
  }
  // Corrige eventuais numeros fora da especificacao
  correct();
}

/// ******************
/// * FIM DA PARTE 2 *
/// ******************

/// Insercao (impressao)
ostream& operator<<(ostream &O, const BigInt &B) {
    if (B.isNeg()) O << '-';

    for (int i = B.size() - 1; i >= 0 ; --i) {
        //O << isdigit(B[i])? B[i]: '#';
        O << (B[i] >= 0 && B[i] <= 9? B[i]: '#');
    }

    return O;
}

/// Extracao (digitacao).
/// NAO PODE SER MODIFICADO NAS PARTES JAH IMPLEMENTADAS.
/// PODE (E PRECISA) RECEBER ACRESCIMOS NAS PARTES INDICADAS POR /* ACRESCENTAR */
istream& operator>>(istream& I, BigInt& B)
{
  // Valor inicial zero
  B = BigInt(); // = 0

  // Testa a stream de entrada e descarta eventuais separadores iniciais.
  // Em caso de erro, encerra a digitacao.
  istream::sentry s(I);
  if (!s) return I;

  // Inspeciona o primeiro caractere que serah lido
  char c = I.peek();

  // Testa se o primeiro caractere eh um sinal.
  // Se for, consome (elimina do buffer), processa e inspeciona o proximo caractere.
  if (c=='+' || c=='-')
  {
    // Consome da stream
    I.get(c);  // Valor de "c" permanece o mesmo...
    // Atribui o sinal
    B.neg = (c=='-');
    // Obtem o proximo caractere
    c = I.peek();
  }

  // Numero de digitos que foram digitados
  int numDigitos = 0;

  // Testa se eh um caractere valido: digitos 0 a 9
  while (isdigit(c))
  {
    // Consome da stream
    I.get(c);  // Valor de "c" permanece o mesmo...
    ++numDigitos;

    if (numDigitos>1)
    {
      // Faz o BigInt manter o sinal e passar a ter size()+1 digitos,
      // avancando todos para uma posicao mais significativa aa frente.

      BigInt prov = BigInt(B.isNeg(), B.size() + 1);

      for (int i = 0; i < B.size(); ++i) prov.d[i + 1] = B[i];

      B = prov;
    }

    // Acrescenta o novo digito como sendo o primeiro (o menos significativo)
    B.d[0] = static_cast<int8_t>(c-'0');

    // Inspeciona o proximo caractere que vai ser lido
    c = I.peek();
  }

  // Assinala erro na stream se nenhum digito foi lido
  if (numDigitos==0) I.setstate(ios::failbit);

  // Corrige eventuais erros na digitacao
  B.correct();

  // Encerra a digitacao
  return I;
}

/// ******************
/// * FIM DA PARTE 3 *
/// ******************

/// Teste de igualdade
bool operator==(const BigInt &B1, const BigInt &B2) {
    if ((B1.isNeg() != B2.isNeg()) || (B1.size() != B2.size())) return false;

    for (int i = 0; i < B1.size(); ++i) {
        if (B1[i] != B2[i]) return false;
    }

    return true;
}

bool operator!=(const BigInt &B1, const BigInt &B2) {
 return !(B1 == B2);
}

/// Menor que
/* ACRESCENTAR */
bool operator<(const BigInt &A, const BigInt &B) {
    // testa sinais diferentes
    if (A.isNeg() != B.isNeg()) return A.isNeg();

    //testa tamanhos diferentes
    if (A.size() != B.size()) {
        if (!A.isNeg()) return (A.size() < B.size());// positivo/nulo
        else return (A.size() > B.size());//negativo
    }

    // mesmo numero de digitos
    for (int i = A.size() - 1; i >= 0; --i) {
        if (A.d[i] != B.d[i]) {
            if (!A.isNeg()) return (A.d[i] < B.d[i]); // positivo/nulo
            else return (A.d[i] > B.d[i]); // negativo
        }
    }

    return false;
}

/// Maior que

bool operator>(const BigInt &A, const BigInt &B) {
    return (B < A);
}

/// Operador Mior ou igual
bool operator>=(const BigInt &B1, const BigInt &B2) {
    return !(B1 < B2);
}


/// Operador Menor ou igual
bool operator<=(const BigInt &B1, const BigInt &B2) {
    return !(B2 < B1);
}


/// ******************
/// * FIM DA PARTE 4 *
/// ******************

/// Funcao privada que incrementa os digitos (o modulo) do numero
/* ACRESCENTAR */
void BigInt::increment() {
    int k = 0;

    while (k < size()) {
        if (d[k] < 9) {
            d[k] = d[k] + 1;
            return;
        }

        d[k] = 0;
        k = k + 1;
    }

    *this = BigInt(isNeg(), size() + 1); // Aumenta o tamanho
    this->d[size() -1 ] = 1; // faz o digito mais sig ser 1
}

/// Funcao privada que decrementa os digitos (o modulo) do numero
void BigInt::decrement() {
    if (isZero()) {
        *this = -1; // faz ser -1

        return;
    }

    int k = 0;
    while (k < size()) {
        if (d[k] > 0) {
            d[k] = d[k] - 1;
            break; // sai do laco
        }
        d[k] = 9;
        k = k + 1;
    }

    correct();
}

/// Operador de incremento pre-fixado
/// NAO PODE SER MODIFICADO
BigInt& BigInt::operator++()
{
  if (!isNeg()) increment();
  else decrement();
  return *this;
}

/// Operador de decremento pre-fixado
/// NAO PODE SER MODIFICADO
BigInt& BigInt::operator--()
{
  if (isNeg()) increment();
  else decrement();
  return *this;
}

/// Operador de incremento pos-fixado
BigInt BigInt::operator++(int) {
    BigInt prev = *this; // guarda o valor anterior

    ++(*this); // incrementa

    return prev;
}

/// Operador de decremento pos-fixado
BigInt BigInt::operator--(int) {
    BigInt prev = *this; // guarda o valor anterior para retornar depois

    --(*this); // decrementa

    return prev;
}

/// ******************
/// * FIM DA PARTE 5 *
/// ******************

/// Modulo (abs)
BigInt abs(const BigInt &B) {
    BigInt prov = B;
    prov.neg = false;

    return prov;
}

/// Negativo (unario)
BigInt BigInt::operator-() const {
    if (size() == 1 && this->d[0] == 0) return BigInt();

    BigInt prov = *this;

    prov.neg = !prov.neg;

    return prov;
}

/// Soma
BigInt operator+(const BigInt &A, const BigInt &B) {
   if (A.isZero()) return B;
   if (B.isZero()) return A;
   if (A.isNeg() != B.isNeg()) return (A - (-B));

   BigInt C(A.isNeg(), 1 + max(A.size(), B.size()));
   int carry = 0;

   for (int i = 0; i <= C.size() - 1; ++i) {
    C.d[i] = A[i] + B[i] + carry;

    if (C.d[i] > 9) {
        C.d[i] = C.d[i] - 10;
        carry = 1;
    } else carry = 0;
   }

   C.correct();

   return C;
}

/// Subtracao
BigInt operator-(const BigInt &A, const BigInt &B) {
    if (A.isZero()) return (-B);
    if (B.isZero()) return A;
    if (A.isNeg() != B.isNeg()) return (A + (-B));
    if (abs(A) < abs(B)) return (-(B-A));

    BigInt C(A.isNeg(), A.size());
    int borrow = 0;

    for (int i = 0; i <= C.size() - 1; ++i) {
        C.d[i] = A[i] - B[i] - borrow;

        if (C.d[i] < 0) {
            C.d[i] = C.d[i] + 10;
            borrow = 1;
        } else borrow = 0;
    }

    C.correct();

    return C;
}


/// ******************
/// * FIM DA PARTE 6 *
/// ******************

/// Multiplicacao
BigInt operator*(const BigInt &A, const BigInt &B) {
    if (A.isZero() || B.isZero()) return BigInt();

    BigInt C( (A.isNeg() != B.isNeg()? true: false), A.size() + B.size());

    for (int i = 0; i <= A.size() - 1; ++i) {
        if (A.d[i] != 0) {
            for (int j = 0; j <= B.size() - 1; ++j) {
                if (B.d[j] != 0) {
                    int k = i + j;

                    C.d[k] = C.d[k] + (A.d[i] * B.d[j]);

                    while(C.d[k] > 9) {
                        int carry = C.d[k]/ 10;
                        C.d[k] = C.d[k] % 10;
                        ++k;
                        C.d[k] = C.d[k] + carry;
                    }
                }
            }
        }
    }

    C.correct();

    return C;
}

/// Fatorial
BigInt BigInt::operator!() {
    if(this->isNeg()) {
        cerr << "Erro, numero nao pode ser negativo\n";
        return BigInt();
    }
    BigInt C(1);

    for (int N = 2; N <= *this; ++N) C = C * N;

    return C;
}


/// ******************
/// * FIM DA PARTE 7 *
/// ******************

/// Deslocamento aa esquerda
BigInt BigInt::operator<<(int N) const {
    if (N <= 0 || this->isZero()) return *this;

    BigInt C(this->isNeg(), this->size() + N);

    for (int i = N; i <= C.size() - 1; ++i) {
        C.d[i] = this->d[i - N];
    }

    return C;
}

/// Deslocamento aa direita
BigInt BigInt::operator>>(int N) const {
    if (N <= 0 || this->isZero()) return *this;
    if (N >= this->size()) return BigInt();

    BigInt C(this->isNeg(), this->size() - N);

    for (int i = 0; i <= C.size() - 1; ++i) C.d[i] = this->d[i + N];

    return C;
}

/// Divisao de *this por D.
/// Armazena o resultado (quociente) em Q e o resto da divisao em R.
void BigInt::division(const BigInt &D, BigInt &Q, BigInt &R) const{
    if (this->isZero() || D.isZero()) {
        if (D.isZero()) cerr << "Erro de divisao por zero\n";

        Q = BigInt();
        R = BigInt();

        return;
    }

    BigInt absD = abs(D);

    if (abs(*this) < absD) {
        Q = BigInt();
        R = *this;

        return;
    }

    Q = BigInt((this->isNeg() != D.isNeg()), this->size() - D.size() + 1);
    R = abs(*this >> (this->size() - D.size()));

    for (int i = Q.size() - 1; i >= 0; --i) {
        int div = 0;

        while (R >= absD) {
            R = R - absD;
            div = div + 1;
        }

        Q.d[i] = div;

        if (i > 0) {
            R = R << 1;
            R.d[0] = this->d[i - 1];
        }
    }

    Q.correct();

    if (!(R.isZero())) R.neg = this->isNeg();
}

/// Quociente da divisao inteira
BigInt operator/(const BigInt &A, const BigInt &D) {
    BigInt Q, R;

    A.division(D, Q, R);

    return Q;
}

/// Resto da divisao inteira
BigInt operator%(const BigInt &A, const BigInt &D) {
    BigInt Q, R;

    A.division(D, Q, R);

    return R;
}

/// ******************
/// * FIM DA PARTE 8 *
/// ******************
