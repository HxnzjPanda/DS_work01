#include <iostream>
#include <cstdlib>
using namespace std;
template <class T>
class ChainNode {
public:
	T data; //���
	ChainNode* link; //�U�@�Ӫ���}
	ChainNode() {} //�غc�l�A���򳣨S��
	ChainNode(const T& data)//�غc�l,����� �S�U�@�Ӫ���}
	{
		this->data = data;
	}
	ChainNode(const T& data, ChainNode* link) //�غc�l,����� ���U�@�Ӫ���}
	{
		this->data = data;
		this->link = link;
	}
};
template <class T>
class CircularListWithHeader { //���t�Y�������쵲��C
public:
	CircularListWithHeader()
	{
		last = new ChainNode<T>(); last->link = last; //�غc�l��l�@�ӧt�Y�������쵲��C
	}
	void InsertBack(const T& e); //�Ω󴡤J�s�� x ��
	bool isEmpty() //�Ω�P�_�O�_���Ū������쵲��C
	{
		return last == last->link;
	}
		ChainNode<T>*begin() const //���ѲĤ@�Ӹ�ƪ���}
	{
		return (last->link)->link;
	}
	ChainNode<T>* first() const //�����Y����}
	{
		return last->link;
	}
	class Iterator { //���N���Ω����ڭ̧�n���X�C�Ӹ��
	public:
		Iterator(ChainNode<T>* startNode = 0) //�غc�l�Ω�s���N���{�b��}
		{
			current = startNode;
		}
		T& operator*()const //�i�s���{�b��}�����
		{
			return current->data;
		}
		T* operator->()const //��K�����s�� Term �� Coef �� Exp
		{
			return &current->data;
		}
		Iterator& operator++() //���쵲��C�๳�Ʀr+1 �@�˫e���U�@�Ӧ�},�^�ǤU�@�Ӧ�}
		{
			current = current->link;
			return *this;
		}
		Iterator& operator++(int) //���쵲��C�๳�Ʀr+1 �@�˫e���U�@�Ӧ�},�^�ǲ{�b��}
		{
			Iterator old = *this;
			current = current->link;
			return old;
		}
		bool operator!=(const Iterator right) //�P�_���O�s��ۦP��}
		{
			return current != right.current;
		}
		bool operator==(const Iterator right) //�P�_�O�s��ۦP��}
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
	if (last) //�p�G���ӴN���@�ӥH�W(�t)�����
	{
		last = last->link = new ChainNode<T>(e, last->link);
	}
	else //�p�G�S�����
	{
		last->link = last = new ChainNode<T>(e);
	}
}
struct Term //�Ω��ܨC�Ӷ���ƪ����c
{
	float coef;
	int exp;
	Term Set(float c, int e) { coef = c; exp = e; return *this; }
};
class Polynomial { //�Ω�N��h���������O
public:
	Polynomial()
	{
		CircularListWithHeader<Term>::Iterator set = poly.first();
		set->exp = -1; //�]�w������C���Y�����謰-1�A�H��K�ڭ̪��D�ڭ̨��X�@�M
	}
	Polynomial(const Polynomial& a); //Copy Constructor �ƻs�غc�l
	~Polynomial();
	void NewTerm(float c, int e) //�Ω�[�J�s����
	{
		Term temp;
		if (c != 0)
			poly.InsertBack(temp.Set(c, e));
	}
	Polynomial& operator+(const Polynomial& b); //�h��������ۥ[�B��l�h��
	Polynomial& operator*(const Polynomial& b); //�h��������ۭ��B��l�h��
	Polynomial& operator-(const Polynomial& b); //�h��������۴�B��l�h��
	const Polynomial& operator=(const Polynomial& b);//�h�������󵥩�B��l�h��
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
	float b = 0;//��J���Y��
	int c = 0, flag = 0;//��J�����Ʀ����U�@���O�_�� 0 ���X��
		while (1)//�@���j��N���J�@�Ӷ�
		{
			char n = ' ';
			//��J�ɲ��L^�Ÿ��ΧP�_�O�����F?
			a >> b;
			if (flag)//�P�_�W�@���j��̫�Ū�i���O���O�t��,�O�h�o���Y�Ƭ��t
			{
				b *= -1;
				flag = 0;//�ܦ^�w�]
			}
			a.get(n);//5x^2 �� x ��m�A�p������h������ 0 �����J����
			if (n == '\n')
			{
				B.NewTerm(b, 0);
				break;
			}
			a.get(n); //5x^2 ��^��m�A�p������� + �� - ���h������ 1 ����A�M�ᴫ��h�����A + �� - ���h��ܤU�@���O���٭t
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
			a >> c; //�o�@�������Ʀ���
				a.get(n); //5x^2 ���̫��m�A�p������h�����A - ���h��ܤU�@���O�t�~���J
				B.NewTerm(b, c);
			if (n == '-') //�P�_ 5x^2 ���̫��m�A�p������h�����A - ���h��ܤU�@���O�t�~���J
				flag = 1;
			else if (n == '\n')
			{
				break;
			}
		}
	return a;
}
Polynomial::~Polynomial() //�h�����Ѻc�l
{
	poly.~CircularListWithHeader();
}
Polynomial::Polynomial(const Polynomial& a)
{
	CircularListWithHeader<Term>::Iterator ai = a.poly.begin();
	CircularListWithHeader<Term>::Iterator set = poly.first();
	set->exp = -1; //�Y�]��-1 ���ѬO�_��ܶ]���@���F
	Term temp;
	while (ai->exp != -1) //�]�L������
	{
		poly.InsertBack(temp.Set(ai->coef, ai->exp)); //��J�h���� A ���C�@��
		ai++;
	}
}
const Polynomial& Polynomial::operator=(const Polynomial& b)//��������
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
		if (ai->exp == bi->exp) //�ⶵ������ۦP�A�Y�Ƭۥ[
		{
			if (ai->exp == -1) return c; //�פ����A��ܨ�̬ҥH�]���[�`���A�i�^��
			int sum = ai->coef + bi->coef;
			if (sum)c.poly.InsertBack(temp.Set(sum, ai->exp));
			ai++;
			bi++;
		}
		else if (ai->exp < bi->exp) //B ������������j�AB ��J C �h������
		{
			c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
			bi++;
		}
		else //A ������������j�AA ��J C �h������
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
	while (ai->exp != -1) //�~�j��]�Ҧ� A ��{����
	{
		bi = b.poly.begin();
		Polynomial d;
		while (bi->exp != -1) //���j��]�Ҧ� B ��{����
		{
			d.poly.InsertBack(temp.Set(ai->coef * bi->coef, ai->exp + bi->exp)); //�C���� A�h�������@�����H B �h�������Ҧ����[�`
				bi++;
		}
		c = c + d;
		ai++;
	}
	return c;
}
Polynomial& Polynomial::operator-(const Polynomial& b) //�����[�k�@�˥u�t�b�O��k
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
			c.poly.InsertBack(temp.Set(-bi->coef, bi->exp)); //�ѩ�O�Q�Ū����A�B A �h�����S���ۦP���誺, �ҥH���W - 1
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
float Polynomial::Evaluate(float x) //�h�����N�J�\��
{
		float sum = 0;
	CircularListWithHeader<Term>::Iterator ai = poly.begin();
	while (ai->exp != -1)
	{
		sum += ai->coef * pow(x, ai->exp); //���X�C�Ӷ��N�J�M���`�M
		ai++;
	}
	return sum;
}
int main()
{
	Polynomial a, b;
	cout << "��J A �h����:";
	cin >> a;
	cout << "��J B �h����:";
	cin >> b;
	Polynomial c(a);
	cout << "��X C(Copy Constructor A �h����)�h����:";
	cout << c << endl;
	cout << "��X A+B �h����:";
	c = a + b;
	cout << c << endl;
	cout << "��X A*B �h����:";
	c = a * b;
	cout << c << endl;
	cout << "��X A-B �h����:";
	c = a - b;
	cout << c << endl;
	int n;
	cout << "��J�n�N�J A �h�������Ʀr:";
	cin >> n;
	cout << "��X A(n)�h����:";
	cout << a.Evaluate(n) << endl;
}
