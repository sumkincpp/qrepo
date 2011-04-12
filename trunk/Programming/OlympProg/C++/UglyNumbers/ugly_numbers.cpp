#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

#define prI(a) printf("[%d]", a);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
/*
(int)pow иногда не срабатывает ??
floor (pow) ->
ceil (pow)
*/
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int at(int num, int lev){
    return ((int)(num/pow(10, lev)))%10;
    }
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
bool ugly (int num) {
    return (num % 2 == 0 || num % 3 == 0 ||
            num % 5 == 0 || num % 7 == 0);
    }
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int proceed (int* mass, int digits) {
    int places = digits-1;
//    cout << places << endl;
    int K = (int)pow(2, places);
    int count = 0;

    for (int k = 0; k < K; k++) {
        int digit = mass[0];
        int res = digit;

        for (int i = 1; i < digits; i++) {
            digit = mass[i];
            if ((k % (int)pow(2, i)) < pow(2, i-1)) {
                res += digit;
                }
            else {
                res -= digit;
                }
            }
        cout << " {" << res << "} \n";
        count += ugly(res);
        }
    return count;
    }
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int gD(int num) {
    return (int)log10(num) + 1;
    }
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int printAr (int* mass, int sz) {
    cout << "------ \n";

    for (int i = 0; i < sz; i++)
        cout << mass[i] << endl;

    cout << "------ \n";
    }
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int proceed2 (int num) {
    int digits = gD(num);
    int K = (int)pow(2, digits - 1);
    int* mass = new int[digits];

    int count = 0;

    for (int k = 0; k < K; k++) {
        int sz = 1;
        mass[0] = at(num, 0);

        for (int i = 1; i < digits; i++) {
            if ((k % (int)pow(2, i)) < pow(2, i-1)) {
                mass[sz-1] += at(num, i)*floor(pow(10, gD(mass[sz-1]))); // склеивание
//                mass[sz-1] += at(num, i)*((int)pow(10, gD(mass[sz-1]))); // склеивание

                // Правильно было бы (int)pow(10, 2), но не работает?
                }
            else {
                mass[sz] = at(num, i); //несклеивание
                sz++;
                }
            }
        count += proceed(mass, sz);
        printAr(mass, sz);
        }

    delete[] mass;

    return count;
    }
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int main() {
    int num = 135;

//    cout << pow(10, gD(22));

    cout << proceed2(num);

    //prI(proceed(mass, 3));



    return 0;
    }
