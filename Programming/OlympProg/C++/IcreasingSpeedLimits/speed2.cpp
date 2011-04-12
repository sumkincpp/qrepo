#include <iostream>
#include <math.h>
using namespace std;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
const int N=6;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int m_cpy (int* from, int * to, int l) {
    for (int i  = 0; i < l; i++) {
        to[i] = from[i];
        }
    }
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
/*

 l - from what element to start
 r - right border(boundary) of array
 tsz - size of previos temp array (prohibited)
 temp - the array (prohibited)
*/
int process(int* mass1, int l, int r, int tsz = 0, int* temp = 0) {
    int count = 0;

    if ( tsz == 0 || temp == 0) {
        for (int i = 0; i < r; i++) {
            int temp2[N] = { mass1[i] };

            count += process(mass1, i+1, r, 1, temp2);
            }
        return count;
        }

    if (tsz >= 2)   {
        for (int i = 0 ; i < tsz; i++) {
            cout << temp[i] << "; ";
            }
        cout << endl;
        count ++;
        //cout << endl << "          --- " << l << " - " << r << " " << tsz << endl;
        }

    for (int i = l; i < r; i++) {
        if (mass1[i] > temp[tsz-1]) {
            int temp2[N];
            m_cpy(temp, temp2, tsz);
            temp2[tsz] = mass1[i];

            count += process(mass1, i+1, r, tsz+1, temp2);
            }
        }
    return count;
    }

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int main(){
    int mas[N] = {1,4,2,1,0,7};

    cout << process(mas, 0, 6) << " subsequence-s";

    //cout << "fdsfsd";
    return 0;

/*
    int m2[N];
    int m3[N*N][N];

    int p = 0;

    for (int i = 0; i < N; i++) {
        int k = 0;
        m2[k] = mas[i];

        for (int j = i+1 ; j < N; j++) {
            if (mas[j] > m2[k]) {
                m2[k+1] = mas[j];
                k++;

                for (int l = 0 ; l < k+1; l++) {
                    cout << m2[l] << "; ";
                    }
                cout << endl;
                }
            }
        }
    }
    */
    }
