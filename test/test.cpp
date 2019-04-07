#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;

struct chromo_typ { int N; int len; };

double Schwefel_Function(int* bits, chromo_typ size)
{
    int N = size.N;
    int len = size.len;
    
    double fsch=418.98291*N;
    for(int j=0; j<N; j++)
    {
        int index = j * len;
        double x_i=0;
        for(int k=0;k<len;k++)
        {
            x_i+=double(*(bits + index + k))*pow(2, len-k-1);
        }
        x_i-=512;
        fsch -= x_i*sin(sqrt(abs(x_i)));
    }
    return fsch;
}


class individual
{
    private:
      chromo_typ gene_size;
      double (*fitnessFN)(int *, chromo_typ);

    public:
      int *bits;
      double fitness;
      individual() : bits(NULL), fitness(0.0f){};
      individual(int N_X, int len, double (*fitnessfn)(int *, chromo_typ))
      {
          gene_size = {N_X, len};
          fitnessFN = fitnessfn;
          bits = new int[N_X * len];
          for (int i = 0; i < N_X; i++)
          {
              int index = i * len;
              for (int j = 0; j < len; j++)
                  *(bits + index + j) = (rand() >= 0.5 * (double)RAND_MAX) ? 1 : 0;
          }
          fitness = fitnessFN(bits, gene_size);
          //print();
        }
        void print(){
            for (int i = 0; i < gene_size.N; i++) 
            {
                int index = i * gene_size.len;
                for (int j = 0; j < gene_size.len; j++)
                    cout << *(bits + index + j);
                cout << endl;
            }
            cout << "----------------" << endl;
            cout << "fitness: " << fitness << endl;
        }
};


int main()
{
    /*vector<individual> population;
    population.resize(5);
    srand(time(NULL));
    for (int i = 0; i < 5;i++)
    {
        individual* chr = new individual(10, 10, Schwefel_Function);
        population[i] = (*chr);
        cout << "pointer: " << chr << endl;
        cout << "pointer: " << &population[i] << endl;
    }
    system("pause");
*/
    
    vector<int> selected(5);
    p:
    for (int i = 0; i < 5;i++)
    {
        selected[i] = rand() % 10;
        for (int j = 0; j < i; j++)
        {
            if(selected[j]==selected[i])
            {
                j = 0;
                selected[i] = rand() % 10;
                cout << "same";
            }
        }
    }
    for(int p : selected){
        cout << p << " ";
    }
    
    system("pause");
    goto p;
    return 0;
}