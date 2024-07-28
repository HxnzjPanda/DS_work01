#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;
void P(string S,int m,int n,int i)
{
	if (i == 0)//判斷i是否等於0
	{
		cout << "{ }"<<endl;//輸出{ }
		i += 1;//++
		P(S, m, n, i);//進入函式
	}
	else
	{
		cout << "{　";//輸出{ 
		for (int j = 0; j < n; j++)//進入for迴圈
		{
			if (i & (1 << j))//以二進制判斷是否為子集合
				cout << S[j] << " ";//輸出數值
		}
		cout << "}"<<endl;//輸出}
		i += 1;//i++
		if (i != m)//判斷是否呼叫函式
			P(S, m, n, i);
		else//函式結束
			cout << "end" << endl;
	}
}
int main(void) {
	string S;//設定變數
	cin >> S;//輸入字串
	int n = S.length(),m=pow(2,n),i=0;//設定變數n和m，n為字串長度，m為子集合的數目
	cout << "m(子集合的數目)=" << m << endl << "n(字串長度)=" << n << endl;//輸入m和n數值
	P(S,m,n,i);//進入函式
	system("pause");
	return 0;
}
