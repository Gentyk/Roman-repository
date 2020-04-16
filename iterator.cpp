// ConsoleApplication16.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stdint.h>
#include <vector>
using namespace std;


// круговой итератор по вектору с целочисленными значениями 
class myIterator 
{
public:
	// конструктор
	myIterator(vector<int> inputVector) {
		if (inputVector.empty()) {
			throw string("Error: empty vector");
		}
		this->vector_ = inputVector;
		this->currentIdx = -1;//назначаем -1, чтобы первой итерацией next() выйти на нулевой жлемент
	}

	// деструктор
	~myIterator() {
		this->vector_.clear();
	}

	// выводит следующий элемент (или первый, если мы перешагнули последний)
	int next() {

		this->currentIdx++;
		if (currentIdx == vector_.size()) {
			this->currentIdx = 0;
		}
		return vector_[currentIdx];
	}

	// говорит, на последнем мы элементе, или нет
	bool isFinish() {
		int maxElem = vector_.size() - 1;
		if (currentIdx == maxElem) {
			return true;
		}
		return false;
	}

	// возвращаем все на исходную, чтобы итератор работал с первого жлемента
	void begin() {
		this->currentIdx = - 1;
	}
private:
	vector<int> vector_;
	int currentIdx;

};


//задание номер два: вывод всех элементов итератора
void showIters(myIterator iter) {
	iter.begin();
	string s = "";
	while (!iter.isFinish()) {
		s += to_string(iter.next());
		s += " ";
	}
	cout << "task 2 - all elements: " << s << " \n";
}


int main()
{
	std::vector<int> nums{ 1, 3, 5, 7 };
	int i;
	string s ="";
	cout << "Size of input els: " << nums.size() << " \n";
	myIterator *iter = new myIterator(nums);

	//проверим , что он сможет работает по кругу
	for (i = 1; i <= 8; i++) {
		s += to_string(iter->next());
		s += ", ";
	}
	cout << "two cycles of elements: " << s << " \n"; // увидели, что циклится и не падает

	// задание номер три (объявление итератора - выше) + вызов задания два - ниже
	showIters(*iter);
	return 0;
}
