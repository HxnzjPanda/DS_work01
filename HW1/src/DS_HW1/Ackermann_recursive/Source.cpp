#include <iostream>
#include <cstdlib>
using namespace std;
int A(int m, int n) {
    if (m == 0) {//條件判斷
        return n + 1;
    }
    else if (n == 0) {//條件判斷  
        return A(m - 1, 1);
    }
    else//條件判斷
        return A(m - 1, A(m, n - 1));
}
int main() {
    int m, n;
    while (cin >> m >> n) {
        cout << A(m, n) << endl;
    }
}