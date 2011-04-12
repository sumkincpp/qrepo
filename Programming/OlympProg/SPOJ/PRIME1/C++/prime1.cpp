#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

//#define DEBUG

int modulo(int a, int b, int c){
    long long x = 1, y = a;

    while(b > 0){
        if(b % 2 == 1)
            x = (x * y) % c;
        y = (y * y) % c;
        b /= 2;
        }
    return x % c;
    }

typedef long long mlong;
mlong mulmod(mlong a, mlong b, mlong c){
    mlong x = 0, y = a % c;
    while(b > 0){
        if(b % 2 == 1) x = (x + y) % c;
        y = (y * 2) % c;
        b /= 2;
        }
    return x % c;
    }

const int MRIterations = 7;
bool IsMRPrime(long long p, int N){
    if(p < 2 || (p != 2 && p % 2 == 0)) return false;

    long long s = p - 1;

    while(s % 2 == 0) s /= 2;

    for(int i = 0; i < N;i++){
        long long a = rand() % (p - 1) + 1, temp = s;
        long long mod = modulo(a, temp, p);

        while(temp != p - 1 && mod != 1 && mod != p - 1){
            mod = mulmod(mod, mod, p);
            temp *= 2;
            }
        if(mod != p - 1 && temp % 2 == 0) return false;
        }
    return true;
    }

int main() {
    #ifdef DEBUG
    int StartSeconds = time(0);
    std::fstream in("in.txt", std::ios_base::in);
    std::fstream out("out.txt", std::ios_base::out);
    #else
    std::istream& in(std::cin);
    std::ostream& out(std::cout);
    #endif

    int Cases = 0;

    in >> Cases;

    long long N = 0, M = 0;

    while(Cases-- > 0) {
        in >> N >> M;
        for (long long i = N; i <= M; i++) {
            if (IsMRPrime(i, MRIterations)) {
                out << i << std::endl;
                }
            }
//        if (Cases >= 1)
        out << std::endl;
        }
    #ifdef DEBUG
    int StopSeconds = time(0);
    out << StopSeconds - StartSeconds;

    in.close();
    out.close();
    #endif

    return 0;
    }
