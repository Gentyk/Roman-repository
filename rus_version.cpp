// ConsoleApplication16.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "windows.h"

using namespace std;

class Student
{
public:
	// конструктор
	Student(string first_name, string second_name, string group_name)
	{
		this->first_name = first_name;
		this->second_name = second_name;
		this->group_name = group_name;
		if (!check_init())
		{
			throw string("Error: all fields should be filled");
		}
	}

	//  деструктор  - зачищаем динамические ресурсы
	~Student() {
		delete cardio;
	};

	void oculist_checkup(string diagnosis_in)
	{
		oculist_diagnosis = diagnosis_in;
	}
	void neurologist_checkup(string diagnosis_in)
	{
		neurologist_diagnosis = diagnosis_in;
	}
	void surgeon_checkup(string diagnosis_in)
	{
		surgeon_diagnosis = diagnosis_in;
	}
	void therapist_checkup(string diagnosis_in)
	{
		therapist_diagnosis = diagnosis_in;
	}
	void cardio_checkup(int hight = 20, int width = 200, int max_step = 3)
	{
		// in this method we can change cardio
	}
	string get_all_info()
	{
		string info;
		info += " - Имя: " + first_name + "\n";
		info += " - Фамилия: " + second_name + "\n";
		info += " - Группа: " + group_name + "\n";
		info += " - Диагноз окулиста: \n" + oculist_diagnosis + "\n";
		info += " - Диагноз невролога: \n" + neurologist_diagnosis + "\n";
		info += " - Диагноз хирурга: \n" + surgeon_diagnosis + "\n";
		info += " - Диагноз терапевта: \n" + therapist_diagnosis + "\n";
		return info;
	}

private:
	string first_name;
	string second_name;
	string group_name;

	string oculist_diagnosis;
	string neurologist_diagnosis;
	string surgeon_diagnosis;
	string therapist_diagnosis;

	int *cardio = new int; // пусть кардиограмма это как график через  промежутки времени. т.е. набор чисел
						   // Операция new создает объект заданного типа, выделяет ему память и возвращает указатель правильного типа на данный участок памяти. - другими словами, нам это еще потом очищать


	int check_init()
	{
		if (!first_name.length() || !second_name.length() || !group_name.length())
		{
			return 0;
		}
		return 1;
	}
};

// список в ученое управление
class OfficialReport
{
public:
	OfficialReport(string info)
	{
		report = info;
	}

	// перегруженный унарный оператор: пусть мы хотим, чтобы каждая новая запись добавляллась после черты и это делалось после знака +
	OfficialReport operator+(string new_info)
	{
		return this->report + "\n----------------------------------\n" + new_info;
	}

	string report;
};

int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);
	// введем имя группы
	string group_name, first_name, second_name, verdict;
	char z[250];
	cout << "Имя группы:" << endl;
	cin >> group_name;
	//group_name = z;
	//cin >> group_name;

	// выделили динамически память на группу студентов
	int N, r;
	cout << "Количество студентов:" << endl;
	cin >> N;
	// особенности с работом маллока для классов написаны здесь https://web-answers.ru/c/ispolzovanie-malloc-realloc-dlja-massiva-klassov.html
	// резервирует память для хранения инфы о студенах, но не инициализирует память - требуется конструктов
	Student *StudentGroup = (Student*)malloc(N * sizeof(Student));
	if (StudentGroup == NULL) exit(1);

	// заполняем
	for (int i = 0; i < N; i++) {
		cout << "Студент " << i << endl;
		cout << "Имя:" << endl;
		cin >> first_name;
		cout << "Фамилия:" << endl;
		cin >> second_name;
		cout << endl;
		new (StudentGroup + i) Student(first_name, second_name, group_name); // а вот и конструктор
																			 // далее -то, что поставили врачи, но влом заполнять. так или иначе, можно переделать на cin, но поступим методом военкомата)))
		cout << "Вердикт окулиста: " << endl;
		cin >> verdict;
		StudentGroup[i].oculist_checkup(verdict);
		cout << "Вердикт нейролога: " << endl;
		cin >> verdict;
		StudentGroup[i].neurologist_checkup(verdict);
		cout << "Вердикт хирурга: " << endl;
		cin >> verdict;
		StudentGroup[i].surgeon_checkup(verdict);
		cout << "Вердикт терапевта: " << endl;
		cin >> verdict;
		StudentGroup[i].therapist_checkup(verdict);
	}

	// теперь формируем отчет и юзаем перегруженный плюсик
	OfficialReport report1 = OfficialReport("IИнформация о студентах");
	for (int i = 0; i < N; i++) {
		report1 = report1 + StudentGroup[i].get_all_info();
	}

	ofstream fout("Official report.txt");
	fout << report1.report;
	fout.close();
	// тут  сказано  https://web-answers.ru/c/ispolzovanie-malloc-realloc-dlja-massiva-klassov.html, что надо деструктором пройтись
	for (int i = 0; i < N; i++)
		StudentGroup[i].~Student();
	free(StudentGroup);

	return 0;
}
