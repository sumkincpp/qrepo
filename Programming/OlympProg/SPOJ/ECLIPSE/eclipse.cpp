#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MY_DEBUG

//using namespace std;
using std::cout;

struct Point {
    long long x, y, z;
    };

struct Planet : Point {
    long long R;

    friend std::ostream& operator << (std::ostream& os, Planet& p) {
        os << "(" << p.x << "," << p.y << "," << p.z << "," << p.R << ")" << std::endl;
        }
    friend std::istream& operator >> (std::istream& is, Planet& p) {
        is >> p.x >> p.y >> p.z >> p.R;
        }
    };

long long distance(Point& p1, Point& p2) {
    long double l = pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2);
    long long res = (long long)sqrt(l);
    cout << l << "   " <<  res << std::endl;
    return res; //(sqrt(l));
//    return sqrt(l);
    }
/*
long long d(long long x0, long long y0, long long z0, long long x1, long long y1, long long z1, long long l, long long m, long long n) {
    long long dx = x0 - x1;
    long long dy = y0 - y1;
    long long dz = z0 - z1;

    return sqrt(pow(dy*n-dz*m, 2)+pow(dz*l-dx*n, 2)+pow(dx*m-dy*l, 2))/sqrt(l*l + n*n + m*m);
    }
*/
struct Line : Point {
    long long l, m, n;

    Point getPoint(long long a) {
        long long t = a / sqrt(l*l + n*n + m*m);
        Point p2 = {x + t*l, y + t*m, z + t*n};
        return p2;
        }
    };

int main() {
    #ifdef MY_DEBUG
    int StartSeconds = time(0);
    std::fstream in("in.txt", std::ios_base::in);
    std::fstream out("out.txt", std::ios_base::out);
    #else
    std::istream& in(cin);
    std::ostream& out(cout);
    #endif

    while(!in.eof()) {
        Planet Sun;
        in >> Sun;
        if (Sun.x < 0) break;

        Planet FPl;
        in >> FPl;

        Planet SPl;
        in >> SPl;

        out << Sun << FPl;

        long a = distance(Sun, FPl);

        std::cout <<  Sun.x << "dfds";

        long long tgl = (Sun.R - FPl.R) / a;
        long long tgb = (Sun.R + FPl.R) / a;

//        Line l = {{Sun.x, Sun.y, Sun.z}, FPl.x - Sun.x, FPl.y - Sun.y, FPl.z - Sun.z};

        long long x = Sun.R / tgb;

 //       Point p = l.getPoint(x);


        }
    #ifdef MY_DEBUG
    int StopSeconds = time(0);
    out << StopSeconds - StartSeconds << " Seconds";

    in.close();
    out.close();
    #endif

    return 10;
    }
