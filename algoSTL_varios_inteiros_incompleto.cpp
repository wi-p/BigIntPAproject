#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std;

/// Funcao para retornar se o parametro eh primo ou nao
bool eh_primo(int N)
{
  // Utiliza o modulo do numero, caso seja negativo
  N = abs(N);
  // 0 e 1 nao sao primos
  if (N <= 1) return false;
  // 2 e 3 sao primos
  if (N <= 3) return true;
  // Numeros pares nao sao primos
  if (N%2 == 0) return false;
  // N impar e N<9 (5 e 7) eh primo
  if (N<9) return true;
  // Para numeros impares com raiz quadrada >= que 3 (ou seja, >= 9)
  // testa se eh divisivel por todos os numeros impares ateh a raiz quadrada do valor.
  // Retorna false se for divisivel por qualquer desses numeros.
  const int raiz = sqrt(N);
  for (int i=3; i<=raiz; i+=2) if (N%i == 0) return false;
  // Eh primo
  return true;
}

/// Programa para utilizar varios algoritmos STL em um conteiner de inteiros

int main()
{
  vector<int> VI(1000);
  vector<int>::iterator iter;
  int N,N1,N2;

  // Semente aleatoria para o gerador de valores aleatorios
  srand (time(NULL));

  // Geracao dos numeros aleatorios: usa funcao rand()
  //falta_fazer();
  for (int i = 0; i < int(VI.size()); ++i) {
  	VI.at(i) = rand() % 100; // numeros gerados entre 0 e 100
  }
  
  for_each(VI.begin(), VI.end(), [](int x) {cout << x << ' '; });
  cout << "\n";

  // Procura por um valor especifico: N1
  cout << "Digite o valor que deve ser procurado no conteiner: ";
  cin >> N1;

  //falta_fazer();
  iter = find(VI.begin(), VI.end(), N1);
  
  if (iter==VI.end())
  {
    cout << "Nao existe nenhum numero " << N1 << " no conteiner\n";
  }
  else
  {
    cout << "O numero " << *iter << " existe no conteiner\n";
  }
  
  //Procura e imprime o primeiro numero dentro de uma faixa: N1 a N2
  
  cout << "Digite o valor inferior da faixa que deve ser procurada no conteiner: ";
  cin >> N1;
  cout << "Digite o valor superior da faixa que deve ser procurada no conteiner: ";
  cin >> N2;
  
  iter = find_if( VI.begin(), VI.end(), [N1, N2](int v) { return (N1 < v && v < N2);} ); // N1 e N2 devem ser dentro do colchetes
  if (iter==VI.end())
  {
    cout << "Nao existe nenhum numero na faixa [" << N1 << ',' << N2 << "] no conteiner\n";
  }
  else
  {
    cout << "O primeiro numero na faixa [" << N1 << ',' << N2 << "] no conteiner eh " << *iter << endl;
  }
  
  // Imprime o total de numeros dentro de uma faixa: N1 a N2
  //falta_fazer();
  N = count_if(VI.begin(), VI.end(), [N1, N2](int v) { return (N1 < v && v < N2);});
  cout << "Existem " << N << " numeros na faixa [" << N1 << ',' << N2 << "] no conteiner\n";
  /*
  // 

  

  // Procura e imprime todos os numeros dentro de uma faixa: N1 a N2
  cout << "Todos os numeros na faixa [" << N1 << ',' << N2 << "] no conteiner sao:";
  falta_fazer();
  cout << endl;

  // Procura e imprime o menor numero do conteiner
  // Lembrar que o conteiner nao estah ordenado
  falta_fazer();
  if (iter==VI.end())
  {
    cout << "O conteiner nao contem nenhum numero!\n";
  }
  else
  {
    cout << "O menor numero do conteiner eh " << *iter << endl;
  }

  // Ordena o conteiner em ordem crescente, usando <
  falta_fazer();

  // Remove os elementos repetidos
  falta_fazer();

  // Imprime o numero de inteiros no conteiner apos remocao
  cout << "O tamanho do conteiner eh " << VI.size() << endl;

  // Imprime o maior numero do conteiner
  // Lembrar que o conteiner estah ordenado
  cout << "O maior numero do conteiner eh " << falta_fazer() << endl;

  // Procura e imprime o primeiro numero que seja primo
  falta_fazer();
  if (iter==VI.end())
  {
    cout << "Nao existe nenhum numero primo no conteiner\n";
  }
  else
  {
    cout << "O primeiro numero primo do conteiner eh " << *iter << endl;
  }

  // Procura e imprime todos os numeros primos
  cout << "Todos os numeros primos no conteiner sao:";
  falta_fazer();
  cout << endl;
*/
  return 0;
}

