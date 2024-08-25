#include <iostream>
#include <cstdlib>
using namespace std;
template <class T>
class ChainNode {
public:
	T data; //資料
	ChainNode* link; //下一個的位址
	ChainNode() {} //建構子，什麼都沒有
	ChainNode(const T& data)//建構子,有資料 沒下一個的位址
	{
		this->data = data;
	}
	ChainNode(const T& data, ChainNode* link) //建構子,有資料 有下一個的位址
	{
		this->data = data;
		this->link = link;
	}
};
template <class T>
class CircularListWithHeader { //有含頭的環形鏈結串列
public:
	CircularListWithHeader()
	{
		last = new ChainNode<T>(); last->link = last; //建構子初始一個含頭的環形鏈結串列
	}
	void InsertBack(const T& e); //用於插入新的 x 項
	bool isEmpty() //用於判斷是否為空的環形鏈結串列
	{
		return last == last->link;
	}
		ChainNode<T>*begin() const //提供第一個資料的位址
	{
		return (last->link)->link;
	}
	ChainNode<T>* first() const //提供頭的位址
	{
		return last->link;
	}
	class Iterator { //迭代器用於幫我們更好走訪每個資料
	public:
		Iterator(ChainNode<T>* startNode = 0) //建構子用於存迭代器現在位址
		{
			current = startNode;
		}
		T& operator*()const //可存取現在位址的資料
		{
			return current->data;
		}
		T* operator->()const //方便直接存取 Term 的 Coef 跟 Exp
		{
			return &current->data;
		}
		Iterator& operator++() //讓鏈結串列能像數字+1 一樣前往下一個位址,回傳下一個位址
		{
			current = current->link;
			return *this;
		}
		Iterator& operator++(int) //讓鏈結串列能像數字+1 一樣前往下一個位址,回傳現在位址
		{
			Iterator old = *this;
			current = current->link;
			return old;
		}
		bool operator!=(const Iterator right) //判斷不是存到相同位址
		{
			return current != right.current;
		}
		bool operator==(const Iterator right) //判斷是存到相同位址
		{
			return current == right.current;
		}
	private:
		ChainNode<T>* current;
	};
private:
	ChainNode<T>* last;
};
template <class T>
void CircularListWithHeader<T>::InsertBack(const T& e)
{
	if (last) //如果本來就有一個以上(含)的資料
	{
		last = last->link = new ChainNode<T>(e, last->link);
	}
	else //如果沒有資料
	{
		last->link = last = new ChainNode<T>(e);
	}
}
struct Term //用於表示每個項資料的結構
{
	float coef;
	int exp;
	Term Set(float c, int e) { coef = c; exp = e; return *this; }
};
class Polynomial { //用於代表多項式的類別
public:
	Polynomial()
	{
		CircularListWithHeader<Term>::Iterator set = poly.first();
		set->exp = -1; //設定環狀串列的頭的次方為-1，以方便我們知道我們走訪一遍
	}
	Polynomial(const Polynomial& a); //Copy Constructor 複製建構子
	~Polynomial();
	void NewTerm(float c, int e) //用於加入新的項
	{
		Term temp;
		if (c != 0)
			poly.InsertBack(temp.Set(c, e));
	}
	Polynomial& operator+(const Polynomial& b); //多項式物件相加運算子多載
	Polynomial& operator*(const Polynomial& b); //多項式物件相乘運算子多載
	Polynomial& operator-(const Polynomial& b); //多項式物件相減運算子多載
	const Polynomial& operator=(const Polynomial& b);//多項式物件等於運算子多載
	float Evaluate(float x);
	friend ostream& operator<<(ostream& a, Polynomial& b);
	friend istream& operator>>(istream& a, Polynomial& B);
private:
	CircularListWithHeader<Term> poly;
};
ostream& operator<<(ostream& a, Polynomial& b)
{
	CircularListWithHeader<Term>::Iterator bi = b.poly.begin();
	while (bi->exp != -1)
	{
		if (bi->coef > 0 && bi != b.poly.begin())
			a << "+";
		if (!(bi->coef == 1 && bi->exp > 0))
			a << bi->coef;
		if (bi->exp == 1)
			a << "x";
		else if (bi->exp != 0)
			a << "x^" << bi->exp;
		bi++;
	}
	return a;
}
istream& operator>>(istream& a, Polynomial& B)
{
	float b = 0;//輸入的係數
	int c = 0, flag = 0;//輸入的指數次方跟下一項是否為 0 的旗標
		while (1)//一次迴圈代表輸入一個項
		{
			char n = ' ';
			//輸入時略過^符號或判斷是結束了?
			a >> b;
			if (flag)//判斷上一次迴圈最後讀進的是不是負號,是則這次係數為負
			{
				b *= -1;
				flag = 0;//變回預設
			}
			a.get(n);//5x^2 的 x 位置，如為換行則此項為 0 次方輸入結束
			if (n == '\n')
			{
				B.NewTerm(b, 0);
				break;
			}
			a.get(n); //5x^2 的^位置，如為換行或 + 或 - 號則此項為 1 次方，然後換行則結束， + 或 - 號則表示下一項是正還負
				if (n == '\n')
				{
					B.NewTerm(b, 1);
					break;
				}
				else if (n == '+' || n == '-')
				{
					B.NewTerm(b, 1);
					if (n == '-')
						flag = 1;
					continue;
				}
			a >> c; //這一項的指數次方
				a.get(n); //5x^2 的最後位置，如為換行則結束， - 號則表示下一項是負繼續輸入
				B.NewTerm(b, c);
			if (n == '-') //判斷 5x^2 的最後位置，如為換行則結束， - 號則表示下一項是負繼續輸入
				flag = 1;
			else if (n == '\n')
			{
				break;
			}
		}
	return a;
}
Polynomial::~Polynomial() //多項式解構子
{
	poly.~CircularListWithHeader();
}
Polynomial::Polynomial(const Polynomial& a)
{
	CircularListWithHeader<Term>::Iterator ai = a.poly.begin();
	CircularListWithHeader<Term>::Iterator set = poly.first();
	set->exp = -1; //頭設為-1 辨識是否表示跑完一輪了
	Term temp;
	while (ai->exp != -1) //跑過全部項
	{
		poly.InsertBack(temp.Set(ai->coef, ai->exp)); //放入多項式 A 的每一項
		ai++;
	}
}
const Polynomial& Polynomial::operator=(const Polynomial& b)//直接等於
{
	poly = b.poly;
	return *this;
}
Polynomial& Polynomial::operator+(const Polynomial& b)
{
	Term temp;
	CircularListWithHeader<Term>::Iterator ai = poly.begin(),
		bi = b.poly.begin();
		Polynomial c;
	while (1)
	{
		if (ai->exp == bi->exp) //兩項的次方相同，係數相加
		{
			if (ai->exp == -1) return c; //終止條件，表示兩者皆以跑完加總完，可回傳
			int sum = ai->coef + bi->coef;
			if (sum)c.poly.InsertBack(temp.Set(sum, ai->exp));
			ai++;
			bi++;
		}
		else if (ai->exp < bi->exp) //B 的項的次方較大，B 放入 C 多項式內
		{
			c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
			bi++;
		}
		else //A 的項的次方較大，A 放入 C 多項式內
		{
			c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
			ai++;
		}
	}
	return c;
}
Polynomial& Polynomial::operator*(const Polynomial& b)
{
	Term temp;
	CircularListWithHeader<Term>::Iterator ai = poly.begin(),
		bi = b.poly.begin();
	Polynomial c;
	while (ai->exp != -1) //外迴圈跑所有 A 方程式項
	{
		bi = b.poly.begin();
		Polynomial d;
		while (bi->exp != -1) //內迴圈跑所有 B 方程式項
		{
			d.poly.InsertBack(temp.Set(ai->coef * bi->coef, ai->exp + bi->exp)); //每次抓 A多項式的一項乘以 B 多項式的所有項加總
				bi++;
		}
		c = c + d;
		ai++;
	}
	return c;
}
Polynomial& Polynomial::operator-(const Polynomial& b) //整體跟加法一樣只差在是減法
{
	Term temp;
	CircularListWithHeader<Term>::Iterator ai = poly.begin(),
		bi = b.poly.begin();
	Polynomial c;
	while (1)
	{
		if (ai->exp == bi->exp)
		{
			if (ai->exp == -1) return c;
			int sum = ai->coef - bi->coef;
			if (sum)c.poly.InsertBack(temp.Set(sum, ai->exp));
			ai++;
			bi++;
		}
		else if (ai->exp < bi->exp)
		{
			c.poly.InsertBack(temp.Set(-bi->coef, bi->exp)); //由於是被剪的項，且 A 多項式沒有相同次方的, 所以乘上 - 1
				bi++;
		}
		else
		{
			c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
			ai++;
		}
	}
	return c;
}
float Polynomial::Evaluate(float x) //多項式代入功能
{
		float sum = 0;
	CircularListWithHeader<Term>::Iterator ai = poly.begin();
	while (ai->exp != -1)
	{
		sum += ai->coef * pow(x, ai->exp); //走訪每個項代入然後總和
		ai++;
	}
	return sum;
}
int main()
{
	Polynomial a, b;
	cout << "輸入 A 多項式:";
	cin >> a;
	cout << "輸入 B 多項式:";
	cin >> b;
	Polynomial c(a);
	cout << "輸出 C(Copy Constructor A 多項式)多項式:";
	cout << c << endl;
	cout << "輸出 A+B 多項式:";
	c = a + b;
	cout << c << endl;
	cout << "輸出 A*B 多項式:";
	c = a * b;
	cout << c << endl;
	cout << "輸出 A-B 多項式:";
	c = a - b;
	cout << c << endl;
	int n;
	cout << "輸入要代入 A 多項式的數字:";
	cin >> n;
	cout << "輸出 A(n)多項式:";
	cout << a.Evaluate(n) << endl;
}
