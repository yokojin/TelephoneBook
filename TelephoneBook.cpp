// TelephoneBook.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <limits>
using namespace std;
class PhoneBook {
private:
	char* name{ 0 };
	char lastName[50]{ 0 };	                     //в чём лучше хранить
	char HomePhone[50]{ 0 };
	char MobilePhone[50]{ 0 };
	char inforMation[50]{ 0 };
public:
	PhoneBook() : PhoneBook("", "", "", "", "") {}
	PhoneBook(const char* name1) : PhoneBook(name1, "", "", "", "") {}
	PhoneBook(const char* name1, const char* lastName2, const char* HomePhone3, const char* MobilePhone4, const char* inforMation5) {
		creatName(name1);
		strcpy_s(lastName, 50, lastName2);
		strcpy_s(HomePhone, 50, HomePhone3);
		strcpy_s(MobilePhone, 50, MobilePhone4);
		strcpy_s(inforMation, 50, inforMation5);
	}
	void creatName(const char* subscriBerName) {
		int nameLength = strlen(subscriBerName);
		name = new char[nameLength + 1];
		for (int i = 0; i <= nameLength; i++) {
			name[i] = subscriBerName[i];
		}
	}
	void setName(const char* subscriBerName) {
		delete[]name;
		creatName(subscriBerName);
	}
	const char* getName()
	{
		return name;
	}
	void setlastName(const char* subscriBerName) {
		strcpy_s(lastName, 50, subscriBerName);
	}
	const char* getlastName() {
		return lastName;
	}
	void setHomePhone(const char* hHomePhone) {
		strcpy_s(HomePhone, 50, hHomePhone);
	}
	const char* getHomePhone() {
		return HomePhone;
	}
	void setMobilePhone(const char* MobMobilePhone) {
		strcpy_s(MobilePhone, 50, MobMobilePhone);
	}
	const char* getMobilePhone() {
		return MobilePhone;
	}
	void setinforMation(const char* inforMation5) {
		strcpy_s(inforMation, 50, inforMation5);
	}
	const char* getinforMation() {
		return inforMation;
	}
	void setAbonent() {
		//ввод данных в объект
		cout << "\tinput name: ";
		char name1[50];
		cin.ignore();
		cin.getline(name1, 50);
		setName(name1);
		//==========================================//separator		
		cout << "\tinput lastName: ";
		char lastName[50];
		cin.getline(lastName, 50);
		setlastName(lastName);
		//==========================================//separator	        
		cout << "\tinput HomePhone: ";
		char homePhone[50];
		cin.getline(homePhone, 50);
		setHomePhone(homePhone);
		//==========================================//separator	  
		cout << "\tinput Mobile phone: ";
		char mobilphone[50];
		cin.getline(mobilphone, 50);
		setMobilePhone(mobilphone);
		//==========================================//separator	  
		cout << "\tInput information: ";
		char inf[50];
		cin.getline(inf, 50);
		setinforMation(inf);
	}
	void Show() {
		cout << getName() << endl;
		cout << getlastName() << endl;
		cout << getHomePhone() << endl;
		cout << getMobilePhone() << endl;
		cout << getinforMation() << endl;
	}
	bool search(const char* Name, const char* name) {
		if (strcmp(Name, name) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
//Функция должна принять объект и записать его в динамический массив и вернуть указатель на новый массив 
PhoneBook* dynamicArrayPhoneBook(PhoneBook*& arr, PhoneBook abonent, int& sizeArray) {
	PhoneBook* newArr = new PhoneBook[sizeArray + 1];
	for (int i = 0; i < sizeArray; i++) {
		newArr[i] = arr[i];
	}
	cout << sizeArray;
	newArr[sizeArray++] = abonent;
	arr = newArr;
	return arr;
}
//Запись массива в файл
void RecordToFile(PhoneBook*& subscriBer, int& sizeArray) {
	string path = "Phonebook.txt";
	ofstream fout;
	fout.open(path);
	if (!fout.is_open())
	{
		cout << "Error open file!" << endl;
	}
	else {
		for (int i = 0; i < sizeArray; i++) {

			fout << subscriBer[i].getName() << ";";
			fout << subscriBer[i].getlastName() << ";";
			fout << subscriBer[i].getHomePhone() << ";";
			fout << subscriBer[i].getMobilePhone() << ";";
			fout << subscriBer[i].getinforMation() << ";" << "\n";
		}
	}
	fout.close();
}
PhoneBook* parcer(string dataFile, PhoneBook*& subscriBer, int& sizeArray) {
	//dataFile содержимое файла
	 // итератор
	//перевод string  в char*
	char* str = new char[dataFile.length() + 1];
	strcpy(str, dataFile.c_str());
	//cout << str;// проверка перевода в указатель на char
	int nPosType = 0;
	char* tempData = (char*)"";
	PhoneBook abonent;
	//Перебираем содержимое файла 
	for (int i = 0; (int)strlen(str) > i; i++) {
		//Если не новая строка
		if (str[i] != '\n') {
			//Если сепаратор
			if (str[i] == ';') {
				//Проверяем позиуию итератора
				switch (nPosType)
				{
				case 0: abonent.setName(tempData);
				case 1: abonent.setlastName(tempData);
				case 2: abonent.setHomePhone(tempData);
				case 3: abonent.setMobilePhone(tempData);
				case 4: abonent.setinforMation(tempData);
				default:
					break;
				}
				//Очистка переменной
				tempData = (char*)"";
				//Увелич итератор
				nPosType++;
			}
			else {
				size_t len = strlen(tempData);
				char* ret = new char[len + 2];
				strcpy_s(ret, len + 2, tempData);
				ret[len] = str[i];
				ret[len + 1] = '\0';
				tempData = ret;
			}
		}
		else {
			////увеличиваем счётчик размера массива
			//sizeArray++;
			//dynamicArrayPhoneBook(subscriBer, abonent, sizeArray); //Добавление объекта в конец массива
			//tempData = (char*)""; //чистим переменную
			//nPosType = 0;
		}
	}
	//Перенес сюда - мы же одну строку только обрабатываем 
	//sizeArray++; - это не нужно	
	dynamicArrayPhoneBook(subscriBer, abonent, sizeArray);
	return subscriBer;
	//Добавление объекта в конец массива
   //tempData = (char*)""; -это тоже
   //nPosType = 0; 
	//возвращаем указатель на новый массив
}
PhoneBook* LoadToFile(PhoneBook*& subscriBer, int& sizeArray) {
	string path = "Phonebook.txt";
	ifstream fin;
	fin.open(path, ifstream::out);
	if (!fin.is_open()) {
		cout << "Error open file" << endl;
	}
	else
	{
		cout << "Open file!" << endl;
		string dataFile;
		while (!fin.eof()) {
			dataFile = "";
			getline(fin, dataFile);
			if (dataFile != "") {
				parcer(dataFile, subscriBer, sizeArray);
				dataFile = "";
			}
		}
	}
	fin.close();
	return subscriBer;
}
//Функция добавления объекта в динамический массив объектов (вернуть указатель на новый динамический массив);
//Запись массива в файл
//Чтение массива объектов из файла
//Вывод всего массива на экран 
//Поиск объекта
//Редактирование объекта
//Сортировка массива
//Сортировка объекта (возможно)
void Show(PhoneBook*& arr, int& sizeArray) {
	if (sizeArray != 0) {
		for (int i = 0; i < sizeArray; i++) {
			cout << "------------ Card -----------" << endl;
			cout << "1.First name: " << arr[i].getName() << endl;
			cout << "2.Second name: " << arr[i].getlastName() << endl;
			cout << "3.Home number: " << arr[i].getHomePhone() << endl;
			cout << "4.Mobile Number: " << arr[i].getMobilePhone() << endl;
			cout << "5.Information: " << arr[i].getinforMation() << endl;
		}
	}
	else {
		cout << "here is clear" << endl;
	}
}
void searchSub(PhoneBook*& subscriBer, int& sizeArray) {
	char findContact[50];
	cin.ignore();
	cout << "Input search name: ";
	cin.getline(findContact, 50); // ввод искомого имени в объекте
	bool bFind = false;
	int nPosition = -1;
	for (int i = 0; i < sizeArray; i++) { // проходим по контактам	
		if (subscriBer[i].search(findContact, subscriBer[i].getName())) {   // передача контакта в функцию (искомого значения и значение имени контакта)
			nPosition = i;
			bFind = true;
			if (nPosition != -1) {
				cout << "------------ Card -----------" << endl;
				cout << "1.First name: " << subscriBer[nPosition].getName() << endl;
				cout << "2.Second name: " << subscriBer[nPosition].getlastName() << endl;
				cout << "3.Home number: " << subscriBer[nPosition].getHomePhone() << endl;
				cout << "4.Mobile Number: " << subscriBer[nPosition].getMobilePhone() << endl;
				cout << "5.Information: " << subscriBer[nPosition].getinforMation() << endl;
			}
		}
	}
}
int main()
{
	PhoneBook abon; // Объект класса
	int sizeArray = 0; //количество объектов класса
	PhoneBook* subscriBer = new PhoneBook[sizeArray]; //динамический массив объектов класса с размером 0;
	int z = 0;
	LoadToFile(subscriBer, sizeArray);                                    // Открытие файла
	//Show(subscriBer, sizeArray);
	cout << "\tPhone BOOK" << endl;
	cout << "\t1. Add abonent" << endl;
	cout << "\t2. Show Array" << endl;
	cout << "\t3. Search subscriber" << endl;
	while (true) {
		cin >> z;
		switch (z) {
		case 1: {
			abon.setAbonent(); // Установить данные для абонента
			dynamicArrayPhoneBook(subscriBer, abon, sizeArray);//Добавить данные в динамический массив объектов
			//Show(subscriBer, sizeArray); // показать значение для массива объектов(абонентов)
			RecordToFile(subscriBer, sizeArray); //запись добавленного абонента в файл 
			break;
		}
		case 2: {
			Show(subscriBer, sizeArray);// вывод всех абонентов на экран
			break;
		}
		case 3: {
			searchSub(subscriBer, sizeArray);  // ищет только целое слово
			break;
		}
		}
	}

	delete[]subscriBer;
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
