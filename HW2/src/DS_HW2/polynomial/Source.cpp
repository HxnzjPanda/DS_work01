#include<iostream> 
#define debug false 
using namespace std;

double START, END;

void runTime(bool start = false) {
	if (debug) {
		if (start) {
			START = clock();
		}
		else {
			END = clock();
			//cout << endl << "程式執行所花費：" << (double)clock() / CLOCKS_PER_SEC << " S";
			cout << endl << "進行運算所花費的時間：" << (double)(END - START) <<" mS" << endl;
		}
	}
}

class Term {
	friend class Polynomial;
	friend ostream& operator<<(ostream& os, Polynomial& poly); //friend輸出多項式 不然會無法存取係數與指數

private:
	float coef;	// 係數
	int exp;	// 指數 
};

class Polynomial {
public:
	friend ostream& operator<<(ostream& os, Polynomial& poly);
	friend Polynomial operator>>(istream & is, Polynomial & poly);

	Polynomial() {
		termArray = new Term[10];
		capacity = 10;
		terms = 0;
	};

	Polynomial Add(Polynomial poly) { //多項式相加 
		Polynomial tempPoly;
		int aPos = 0, bPos = 0;
		while ((aPos < terms) && (bPos < poly.terms)) {
			if (termArray[aPos].exp == poly.termArray[bPos].exp) { //指數相同財相加
				float t = termArray[aPos].coef + poly.termArray[bPos].coef;//係數相加 
				if (t) tempPoly.NewTerm(t, termArray[aPos].exp); //係數不為0才新增項目
				aPos++;
				bPos++;
			}
			else  if (termArray[aPos].exp < poly.termArray[bPos].exp) {
				tempPoly.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
				bPos++;
			}
			else {
				tempPoly.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
				aPos++;
			}
		}

		for (; aPos < terms; aPos++) {
			tempPoly.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
		}
		for (; bPos < poly.terms; bPos++) {
			tempPoly.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
		}
		return tempPoly;
	};

	Polynomial Mult(Polynomial poly) {
		Polynomial tempPoly;
		if (terms == 0 || poly.terms == 0) return tempPoly; //若為0則回傳空多項式
		tempPoly.capacity = terms * poly.terms;    //計算所需空間
		tempPoly.termArray = new Term[tempPoly.capacity]; //配置空間 
		for (int i = 0; i < terms; i++) {
			for (int j = 0; j < poly.terms; j++) {
				int c = termArray[i].coef * poly.termArray[j].coef; //係數相乘 
				int e = termArray[i].exp + poly.termArray[j].exp; //指數相加 
				tempPoly.NewTerm(c, e);
			}
		}
		return tempPoly;
	};

	float Eval(float f) { //帶入f計算多項式的值 
		float result = 0;
		for (int i = 0; i < terms; i++) {
			float temp = 1;
			for (int j = 0; j < termArray[i].exp; j++) {
				temp *= termArray[i].coef;
			}
			result += temp * f;
		}
		return result;
	};

	void NewTerm(float coef, int exp) { //新增項目
		if (terms == capacity) {
			capacity *= 2; //擴充2倍的空間 
			Term* temp = new Term[capacity];
			copy(termArray, termArray + terms, temp);
			delete[] termArray;
			termArray = temp;
		}
		termArray[terms].coef = coef;
		termArray[terms++].exp = exp;
	};

private:
	Term* termArray;
	int capacity; // 有多少空間 
	int terms;  // 非零項 
};

Polynomial operator>>(istream& is, Polynomial& poly) {
	float coef;
	int exp;
	is >> coef >> exp; //依序輸入係數與指數 
	while (coef != 0 || exp != 0) {
		poly.NewTerm(coef, exp); //新增項目 
		is >> coef >> exp;
	}
	return poly;
}

ostream& operator<<(ostream& os, Polynomial& poly) {
	for (int i = 0; i < poly.terms; i++) {
		if (poly.termArray[i].coef > 0) { //判斷正負號 
			if (i != 0) os << "+";
		}
		else {
			os << "-";
		}

		if (poly.termArray[i].exp == 0) { //判斷指數輸出字元
			os << poly.termArray[i].coef;
		}
		else if (poly.termArray[i].exp == 1) {
			os << poly.termArray[i].coef << "x";
		}
		else {
			os << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
		}
	}
	return os;
}

int main() {
	class Polynomial poly1, poly2, poly3;
	float f; //計算用 
	int coef, exp; //輸入的指數與係數 

	cout << "請輸入係數和指數，輸入0 0結束：\n";
	cin >> coef >> exp;
	while (coef != 0 || exp != 0) {
		poly1.NewTerm(coef, exp);
		cin >> coef >> exp;
	}
	runTime(true);
	cout << poly1 << endl << endl;
	runTime();

	cout << "請輸入一個數字(輸入0略過)：\n";
	cin >> f;
	runTime(true);
	if (f != 0)
		cout << "poly1(" << f << ") = " << poly1.Eval(f) << endl;
	runTime();
	cout << endl;



	cout << "請輸入係數和指數，輸入0 0結束：\n";
	cin >> coef >> exp;
	while (coef != 0 || exp != 0) {
		poly2.NewTerm(coef, exp);
		cin >> coef >> exp;
	}
	runTime(true);
	cout << poly2 << endl << endl;
	runTime();

	cout << "請輸入一個數字(輸入0略過)：\n";
	cin >> f;
	runTime(true);
	if (f != 0)
		cout << "poly2(" << f << ") = " << poly2.Eval(f) << endl;
	runTime();
	cout << endl;

	cout << "poly1 + poly2 = ";
	runTime(true);
	poly3 = poly1.Add(poly2);
	cout << poly3 << endl;
	runTime();

	cout << "poly1 * poly2 = ";
	runTime(true);
	poly3 = poly1.Mult(poly2);
	cout << poly3 << endl;
	runTime();

	return 0;
}