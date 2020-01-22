// ConsoleApplication16.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>

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

	//  деструктор - но не вижу смысла чистить - потому убрал. Закомментил на случай, если препод запросит
	// ~Student(){};

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
		int curr_i = (int)hight / 2;
		int curr_dir = 1;
		int curr_step = rand() % max_step + 1;
		int next_i;
		int j = 0;
		cardio.clear();
		cardio.assign(hight * width + hight, '-');
		for (int i = 0; i < hight; i++)
		{
			cardio[i * (width + 1) + width] = '\n';
		}
		while (j < width)
		{
			next_i = curr_i + curr_dir * curr_step;
			if (next_i >= hight || next_i < 0)
			{
				curr_dir *= -1;
				curr_step = rand() % max_step + 1;
				continue;
			}
			cardio[next_i * (width + 1) + j] = '*';
			curr_i = next_i;
			j++;
		}
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
		info += " - Кадиограмма: \n" + cardio + "\n";
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

	string cardio;

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
	// введем имя группы
	string group_name, first_name, second_name;
	cout << "Group name:" << endl;
	cin >> group_name;

	// выделили динамически память на группу студентов
	int N, r;
	cout << "Number of students:" << endl;
	cin >> N;
	// особенности с работом маллока для классов написаны здесь https://web-answers.ru/c/ispolzovanie-malloc-realloc-dlja-massiva-klassov.html
	// резервирует память для хранения инфы о студенах, но не инициализирует память - требуется конструктов
	Student *StudentGroup = (Student*)malloc(N*sizeof(Student));
	if (StudentGroup == NULL) exit(1);

	// заполняем
	for (int i = 0; i < N; i++) {
		cout << "student " << i << endl;
		cout << "First Name:" << endl;
		cin >> first_name;
		cout << "Second Name:" << endl;
		cin >> second_name;
		cout << endl;
		new (StudentGroup + i) Student(first_name, second_name, group_name); // а вот и конструктор
		
		// далее -то, что поставили врачи, но влом заполнять. так или иначе, можно переделать на cin, но поступим методом военкомата)))
		StudentGroup[i].oculist_checkup("good");
		StudentGroup[i].neurologist_checkup("good");
		StudentGroup[i].surgeon_checkup("good");
		StudentGroup[i].therapist_checkup("good");
	}

	// теперь формируем отчет и юзаем перегруженный плюсик
	OfficialReport report1 = OfficialReport("Info about all students");
	for (int i = 0; i < N; i++) {
		report1 = report1 + StudentGroup[i].get_all_info();
	}

	ofstream fout("Official report.txt"); 
	fout << report1.report;
	fout.close();
	/* тут  сказано  https://web-answers.ru/c/ispolzovanie-malloc-realloc-dlja-massiva-klassov.html, что надо деструктором пройтись. если рии надо, то сделай это так
	но наш диструктор нифига не делает - значит и не надо
	for (int i = 0; i < N; i++)
		StudentGroup[i].~Student();
	*/
	free(StudentGroup);

	return 0;
}
