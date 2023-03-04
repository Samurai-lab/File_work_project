#include<stdio.h>
#include<string>
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>

int countToAdd = 0;
using namespace std;

struct Student
{
	string surname, name, otchestvo;
	string date;
	string homeAdress;
	string raiting;
};

ostream& operator << (ostream& os, Student& student) {

	os << "Surname: " + student.surname << endl
		<< "Name: " + student.name << endl
		<< "Otchestvo: " + student.otchestvo << endl
		<< "Date of bithday: " + student.date << endl
		<< "Home Adress: " + student.homeAdress << endl
		<< "Raiting: " + student.raiting << endl
		<< endl;

	return os;
}

istream& operator >> (istream& is, Student& student) {

	is >> student.surname
		>> student.name
		>> student.otchestvo
		>> student.date
		>> student.homeAdress
		>> student.raiting;

	return is;
}

Student createStudent(int numberOfStudent) {

	Student student;

	cout << "Student number " << numberOfStudent << endl;

	cout << "Write surname: ";
	cin >> student.surname;

	cout << "Write name: ";
	cin >> student.name;

	cout << "Write otchestvo: ";
	cin >> student.otchestvo;

	cout << "Write date of bithday: ";
	cin >> student.date;

	cout << "Write home adress: ";
	cin >> student.homeAdress;

	cout << "Write raiting: ";
	cin >> student.raiting;
	cout << endl;
	
	return student;
}

Student* createStudentsList(Student* students, int count) {
	for (int i = 0; i < count; i++) {
		students[i] = createStudent(i + 1);
	}
	return students;
}

void displayStudentsList(Student* students, int count) {
	cout << "___________________________" << endl;
		for (int i = 0; i < count; i++) {
			cout << students[i] << endl;
		}
	cout << "___________________________" << endl;
	return;
}

void fileOutHelper(string fileName, string line_file_text) {
	ofstream file_out;
	file_out.open(fileName, std::ios::trunc | std::ios::binary); //открыть и обрезать

	file_out.write(line_file_text.c_str(), line_file_text.size());
	file_out.clear();
}

string deleteElementHelper(string fileName, int deleteObjNum) {
	ifstream file_in;
	file_in.open(fileName);
	string line; //для хранения строк
	string line_file_text; //для хранения текста файла
	int countHelper = 0;

	while (getline(file_in, line))
	{

		if (countHelper < deleteObjNum - 7 || countHelper >= deleteObjNum)
		{
			line_file_text.insert(line_file_text.size(), line); /*дабавить строку*/
			/*добавить перенос на слудующую строку*/
			line_file_text.insert(line_file_text.size(), "\r\n");

		}
		countHelper++;
	}

	file_in.close();
	return line_file_text;
}

void deleteElement(string fileName, int deleteObjNum) {
	deleteObjNum *= 7;
	string line_file_text = deleteElementHelper(fileName, deleteObjNum);
	fileOutHelper(fileName, line_file_text);

	cin.get();
	return;
}

void deleteElement(string fileName) {
	
	cout << "Введите номер элемента для удаления:" << endl;
	int deleteObjNum = 0;
	cin >> deleteObjNum;
	deleteObjNum *= 7;

	string line_file_text = deleteElementHelper(fileName, deleteObjNum);

	fileOutHelper(fileName, line_file_text);

	cin.get();
return;
}

void insertElementBetwOth(string fileName, string fNameForSave) {
	fstream fsS;
	ofstream file_out;
	ifstream file_in;
	ifstream file_inS;
	
	fsS.open(fNameForSave, fstream::in | fstream::out | fstream::app);
	file_in.open(fileName);
	file_inS.open(fNameForSave);

	string line, line_file_text, lineS, line_file_textS;
	Student* studentS = new Student[1];
	int countHelper = 1;
	int countHelperS = 1;

	cout << "Введите фамилию студента, перед которым вы хотите добавить нового:" << endl;
	string surname = "";
	cin >> surname;

	while (getline(file_in, line))
	{
		countHelper++;
		if (line == "Surname: " + surname) {
			countHelper -= 1;
			break;
		}
	}
	cout << countHelper;
	studentS[0] = createStudent(1);

	file_in.close();
	fsS << studentS[0];
	file_in.open(fileName);

	while (getline(file_in, line))
	{
		if (countHelperS == countHelper) {
			while (getline(file_inS, lineS))
			{
				line_file_text.insert(line_file_text.size(), lineS);
				line_file_text.insert(line_file_text.size(), "\r\n");
			}
		}
		line_file_text.insert(line_file_text.size(), line);
		line_file_text.insert(line_file_text.size(), "\r\n");
		countHelperS++;
	}

	file_in.close();
	fileOutHelper(fileName, line_file_text);
	file_inS.close();
	fsS.close();
	remove(fNameForSave.c_str());
	delete[] studentS;
	cin.get();
}

int main()
{
	//setlocale(LC_ALL, "Rus");
	setlocale(LC_ALL, "Russian_Russia.1251"); //для платформы win разрешение вывода русского языка в консоль
	system("chcp 1251>nul");
	bool appExit = false;
	string fileName = "testFile.txt";

	while (!appExit) {
		cout << "What do you want to do: \n"
			<< "\n1 - Working with binary files"
			<< "\n2 - working with text files"
			<< "\n3 - Exit" << endl;

		int ansvere;
		cin >> ansvere;
		switch (ansvere) {
		case 1: {
			break;
		}
		case 2: {
			fstream fs;
			fs.open(fileName, fstream::in | fstream::out | fstream::app);
			if (!fs)
			{
				cerr << "Ошибка, невозможно открыть файл : testFile.txt" << endl;
				return (EXIT_FAILURE);
			}

			cout << "How many student you want to create: ";
			int count;
			cin >> count;
			Student* students = new Student[count];
			int* dublStudNum = new int[count];

			while (!appExit) {
				cout << "What do you want to do: \n"
					<< "\n1 - Create list of students"
					<< "\n2 - Show student list"
					<< "\n3 - Save this list of students in file"
					<< "\n4 - Add student and save in file"
					<< "\n5 - Show information in a file"
					<< "\n6 - Delete element in file"
					<< "\n7 - Delete elements with equivalents lines"
					<< "\n8 - Add element before object"
					<< "\n9 - Exit" << endl;

				int ansvere;
				cin >> ansvere;
				system("cls");
				switch (ansvere) {
				case 1: {
					if (count == 0) {
						cout << "How many student you want to create: ";
						cin >> count;
						students = new Student[count];
					}
					createStudentsList(students, count);
					cin.get();
					break;
				}
				case 2: {
					displayStudentsList(students, count);
					cin.get();
					break;
				}
				case 3: {
					for (int i = 0; i < count; i++) {
						fs << students[i];
					}
					cin.get();
					break;
				}
				case 4: {
					Student* student = new Student[1];
					createStudentsList(student, 1);
					fs << student[0];
					delete[] student;
					cin.get();
					break;
				}
				case 5: {
					ifstream file_in;
					file_in.open(fileName);
					string line;

					while (getline(file_in, line))
					{
						cout << line << endl;
					}
					file_in.close();
					break;
				}
				case 6: {
					deleteElement(fileName);
					cin.get();
					break;
				}
				case 7: {
					ifstream file_in;
					file_in.open(fileName);
					int arrHelper = 0;
					int countHelper = 1;
					string line;

					cout << "Enter the date of birth of the student by which the search for a duplicate and further deletion of elements will be:" << endl;
					string dateBithday = "";

					cin >> dateBithday;
					dateBithday = "Date of bithday: " + dateBithday;

					while (getline(file_in, line)) {
						
						if (dateBithday == line) {
							dublStudNum[arrHelper] = ((countHelper / 7) + 1);
							arrHelper++;
						}
						countHelper++;
					}

					for (int i = arrHelper; i > 0; i--) {
						deleteElement(fileName, dublStudNum[i - 1]);
					}
					break;
				}
				case 8: {
					string fNameForSave = "timesFile.txt";
					insertElementBetwOth(fileName, fNameForSave);
					break;
				}
				case 9: appExit = true; break;
				default: cout << "Неверная команда. Повторите попытку!";
				}
			}

			delete[] students;
			delete[] dublStudNum;
			fs.close();
			break;
		}
		case 3:  appExit = true; break;
		default: cout << "Неверная команда. Повторите попытку!";
		}
	}
	return (EXIT_SUCCESS);
}