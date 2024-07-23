#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
int main() {
    int m, n;
    while (cin >> m >> n) {
        int num = 0;
        switch(m) {
            case 0:
                num = n + 1;
                cout << num << endl;
                break;
            case 1:
                num = n + 2;
                cout << num << endl;
                break;
            case 2:
                num = 2*(n+3)-3;
                cout << num << endl;
                break;
            case 3:
                num = pow(2,(n+3))-3;
                cout << num << endl;
                break;
            case 4:
                if (n == 0) {
                    num = 13;
                    cout << num << endl;
                }
                else if (n == 1) {
                    num = 65533;
                    cout << num << endl;
                }
                else
                    cout << "n太大" << endl;
                break;
            case 5:
                if (n == 0) {
                    num = 65533;
                    cout << num << endl;
                }
                else
                    cout << "n太大" << endl;

                break;
        }
        
    }
}
