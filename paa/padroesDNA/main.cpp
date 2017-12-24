#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;



int main()
{
    string DNA;
    cin >> DNA;
    int t = DNA.length();

    int mut[t+1];
    int matrizLen[t+1][t+1];
    int mutLen[t+1][t+1];
    int best = 0;
    int bestT = 0;
    int nMut, pos;
    int cordX, cordY;
    for(int w = 0; w < t+1; w++) {
        mut[w] = 0;
    }

    cin >> nMut;
    for(int q = 0; q < nMut; q ++) {
        cin >> pos;
        mut[pos] = 1;

    }
   // for(int p = 0; p < t+1; p++) {
     //   for(int z = 0; z < t+1; z++) {
       //     matrizLen[p][z] = 0;
         //   mutLen[p][z] = 0;
        //}
    //}
    int i;
    for(int cls = 1; cls < t+1; cls++) {
        i=1;
        for(int j = cls; j < t+1; j++) {

            if(i == j) {
                matrizLen[i][j] = 1;
                mutLen[i][j] = mut[i];
            }
            else if(i == j-1 && DNA[i-1] == DNA[j-1]) {
                matrizLen[i][j] = 2;
                mutLen[i][j] = mut[i]+mut[j];
            }

            else if(i <= j-1 && DNA[i-1] != DNA[j-1]) {

                    if(mutLen[i+1][j] > mutLen[i][j-1]) {
                        matrizLen[i][j] = matrizLen[i+1][j];
                        mutLen[i][j] = mutLen[i+1][j];
                    }
                    else if(mutLen[i+1][j] == mutLen[i][j-1] && matrizLen[i+1][j] >= matrizLen[i][j-1]) {
                        matrizLen[i][j] = matrizLen[i+1][j];
                        mutLen[i][j] = mutLen[i+1][j];
                    }
                    else {
                        matrizLen[i][j] = matrizLen[i][j-1];
                        mutLen[i][j] = mutLen[i][j-1];
                    }

            }

            else if(i < j-1 && DNA[i-1] == DNA[j-1]) {

                    if(mutLen[i+1][j] > mutLen[i][j-1]) {
                       cordX = i+1;
                       cordY = j;
                    }
                    else if(mutLen[i+1][j] == mutLen[i][j-1] && matrizLen[i+1][j] >= matrizLen[i][j-1]) {
                        cordX = i+1;
                        cordY = j;
                    }
                    else {
                        cordX = i;
                        cordY = j-1;
                    }


                     if(mutLen[cordX][cordY] > (mutLen[i+1][j-1]+mut[i]+mut[j])) {
                        mutLen[i][j] = mutLen[cordX][cordY];
                        matrizLen[i][j] = matrizLen[cordX][cordY];
                    }
                    else if(mutLen[cordX][cordY] == (mutLen[i+1][j-1]+mut[i]+mut[j]) && matrizLen[cordX][cordY] >= (matrizLen[i+1][j-1])+2) {
                        mutLen[i][j] = mutLen[cordX][cordY];
                        matrizLen[i][j] = matrizLen[cordX][cordY];
                    }
                    else {
                        mutLen[i][j] = mutLen[i+1][j-1] + mut[i] + mut[j];
                        matrizLen[i][j] = matrizLen[i+1][j-1] + 2;
                    }
            }

          //  cout << matrizLen[i][j] << " " ;
            //cout << "best: " << best << endl;
              if(mutLen[i][j] > best || (mutLen[i][j] == best && matrizLen[i][j] >= bestT)) {
                best = mutLen[i][j];
                bestT = matrizLen[i][j];
                //cordX = i;
                //cordY = j;
             }

             i++;
        }
      //  cout << endl;
    }

    cout << bestT << endl;
   // cout << best << endl;

    return 0;
}
