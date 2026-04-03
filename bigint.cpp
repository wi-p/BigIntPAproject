#include <iostream>
#include <cstdint>
#include "bigint.h"

using namespace std;

/// Construtor default.
/// Inicializa com um inteiro de 1 digito, valor 0 (zero).
/// NAO PODE SER MODIFICADO
BigInt::BigInt()
  : neg(false)
  , nDig(1)
  , d(new int8_t[nDig]{0})
{}

/// Destrutor COM METODO CLEAR
/* ACRESCENTAR */

BigInt::~BigInt() {clear();}

void BigInt::clear() {
    delete[] d;
}

/// Construtor especifico PRIVADO que recebe o sinal e a quantidade de digitos
BigInt::BigInt(bool uneg, int unDig) : neg(uneg), nDig(unDig >= 1 ? unDig : 1), d(new int8_t[nDig]{0}) {
	
}

int main(void) {
	
	BigInt bi(false, 2);
	
    return 0;
}

/// Construtor por copia.
/// Delega ao construtor especifico privado.
/// NAO PODE SER MODIFICADO.
BigInt::BigInt(const BigInt& B) : BigInt(B.isNeg(), B.size())
{
  // Copia os digitos
  for (int i=0; i<size(); ++i) d[i] = B.d[i];
}


/*


/// Atribuicao por copia
/// ACRESCENTAR

/// Construtor por movimento
/// ACRESCENTAR

/// Atribuicao por movimento
/// ACRESCENTAR

/// Construtor especifico a partir de inteiro longo.
/// Tambem conversor de long long int para BigInt.
/// NAO PODE SER MODIFICADO NAS PARTES JAH IMPLEMENTADAS.
/// PODE (E PRECISA) RECEBER ACRESCIMOS, APENAS
/// NAS PARTES INDICADAS POR  ACRESCENTAR
BigInt::BigInt(long long int N)
  /// ACRESCENTAR
{
  /// Calcula os digitos, usando divisao inteira por 10
  for (int i=0; i<size(); ++i)
  {
    d[i] = abs(N%10); /// Modulo do resto da divisao
    N /= 10;          /// Divisao inteira
  }
}

/// Conversor de BigInt para long long int
/// ACRESCENTAR

/// ******************
/// * FIM DA PARTE 1 *
/// ******************

/// Funcao privada que corrige o numero, caso haja inconsistencias
/// ACRESCENTAR

/// Construtor especifico a partir de string.
/// Nao eh conversor de string para BigInt.
/// Delega ao construtor default.
/// NAO PODE SER MODIFICADO NAS PARTES JAH IMPLEMENTADAS.
/// PODE (E PRECISA) RECEBER ACRESCIMOS, APENAS
/// NAS PARTES INDICADAS POR  ACRESCENTAR
BigInt::BigInt(const string& S)
  : BigInt() /// Valor inicial zero
{
  /// Se string vazia, emite erro e permanece com valor inicial zero
  if (S.empty())
  {
    cerr << "empty string cannot create a BigInt\n";
    return;
  }

  /// Posicao onde comecam os digitos, inicialmente zero
  size_t ini=0;
  /// Leva em conta o sinal
  bool IsNeg = false;

  if (S[0]=='+' || S[0]=='-')
  {
    /// Se nao tem nenhum digito alem do sinal, emite erro e permanece com valor inicial
    if (S.size()==1)
    {
      cerr << "sign-only string cannot create a BigInt\n";
      return;
    }
    IsNeg = (S[0]=='-');
    ++ini;
  }

  /// Faz ter sinal (IsNeg) e numero de digitos (tamanho da string - ini) corretos
  /// ACRESCENTAR

  /// Calculo dos digitos do BigInt
  for (int i=0; i<size(); ++i)
  {
    char c = S[S.size()-1-i];
    if (!isdigit(c))
    {
      *this = BigInt(); /// = 0
      cerr << "string with invalid character cannot create a BigInt\n";
      return;
    }
    d[i] = static_cast<int8_t>(c-'0');
  }
  /// Corrige eventuais numeros fora da especificacao
  correct();
}

/// ******************
/// * FIM DA PARTE 2 *
/// ******************

/// Insercao (impressao)
/// ACRESCENTAR

/// Extracao (digitacao).
/// NAO PODE SER MODIFICADO NAS PARTES JAH IMPLEMENTADAS.
/// PODE (E PRECISA) RECEBER ACRESCIMOS, APENAS
/// NAS PARTES INDICADAS POR  ACRESCENTAR
std::istream& operator>>(istream& I, BigInt& B)
{
  /// Valor inicial zero
  B = BigInt(); /// = 0

  /// Testa a stream de entrada e descarta eventuais separadores iniciais.
  /// Em caso de erro, encerra a digitacao.
  istream::sentry s(I);
  is (!s) return I;

  /// Caractere lido da stream
  int c;

  /// Inspeciona o primeiro caractere que serah lido
  c = I.peek();

  /// Testa se o primeiro caractere eh um sinal.
  /// Se for, consome (elimina do buffer), processa e inspeciona o proximo caractere.
  if (c=='+' || c=='-')
  {
    /// Consome
    c = I.get();
    /// Atribui o sinal
    B.neg = (c=='-');
    /// Obtem o proximo caractere
    c = I.peek();
  }

  /// Numero de digitos que foram digitados
  int numDigitos = 0;

  /// Testa se eh um caractere valido: digitos 0 a 9
  while (isdigit(c))
  {
    /// Consome do buffer
    c = I.get();
    ++numDigitos;

    if (numDigitos>1)
    {
      /// Faz o BigInt manter o sinal e passar a ter size()+1 digitos,
      /// avancando todos para uma posicao mais significativa aa frente.
      /// ACRESCENTAR
    }

    /// Acrescenta o novo digito como sendo o primeiro (o menos significativo)
    B.d[0] = static_cast<int8_t>(c-'0');

    /// Inspeciona o proximo caractere que vai ser lido
    c = I.peek();
  }

  /// Assinala erro na stream se nenhum digito foi lido
  if (numDigitos==0) I.setstate(ios::failbit);

  /// Corrige eventuais erros na digitacao
  B.correct();

  /// Encerra a digitacao
  return I;
}

/// ******************
/// * FIM DA PARTE 3 *
/// ******************

/// Teste de igualdade
///* ACRESCENTAR

/// Menor que
///* ACRESCENTAR

/// ******************
/// * FIM DA PARTE 4 *
/// ******************

/// Funcao privada que incrementa os digitos (o modulo) do numero
///* ACRESCENTAR

/// Funcao privada que decrementa os digitos (o modulo) do numero
///* ACRESCENTAR

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
///* ACRESCENTAR

/// Operador de decremento pos-fixado
///* ACRESCENTAR

/// ******************
/// * FIM DA PARTE 5 *
/// ******************

/// Modulo (abs)
///* ACRESCENTAR

/// Negativo (unario)
///* ACRESCENTAR

/// Soma
///* ACRESCENTAR

/// ******************
/// * FIM DA PARTE 6 *
/// ******************

/// Multiplicacao
///* ACRESCENTAR

/// Fatorial
///* ACRESCENTAR

/// ******************
/// * FIM DA PARTE 7 *
/// ******************

/// Deslocamento aa esquerda
///* ACRESCENTAR

/// Deslocamento ah direita
///* ACRESCENTAR

/// Divisao de *this por D.
/// Armazena o resultado (quociente) em Q e o resto da divisao em R.
///* ACRESCENTAR

/// Quociente da divisao inteira
///* ACRESCENTAR

/// Resto da divisao inteira
///* ACRESCENTAR

/// ******************
/// * FIM DA PARTE 8 *
/// ******************

*/

