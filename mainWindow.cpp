#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <fstream>
#include "Book.h"
//#include "mainWindow.h"
using namespace std;

#define CMD_COLS 80
#define CMD_ROWS 25

void mainloop();
void viewBooks(int iSelPage);
void addBook();


void setScreenGrid() {
	char sysSetBuf[80];
	sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_ROWS);
	system(sysSetBuf);
}

void setSysCation() {
	system("title sample");
}

void setSysCation(const char* pText) {
	char sysSetBuf[80];
	sprintf(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}

void clearScreen() {
	system("cls");
}

void showWelcome() {
	for (int i = 0; i < 7; i++) {
		cout << endl;
	}
	cout << setw(40);
	cout << "*****************************************************************************" << endl;
	cout << setw(40);
	cout << "图书管理系统" << endl;
	cout << setw(40);
	cout << "*****************************************************************************" << endl;
}

void showRootMenu() {
	cout << setw(38);
	cout << "请选择功能" << endl;
	cout << setw(38);
	cout << "1 添加新书" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 浏览全部" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 删除图书" << endl;
}

void waitUser() {
	cout << "c:继续添加；		q:退出" << endl;
	char input = ' ';
	while (input == ' ') {
		cin >> input;
	}
	if (input == 'c') addBook();
	if (input == 'q') system("exit");
}


int getSelect() {
	//char buf[256];
	//cgets(buf);
	int input = ' ';
	while (input == ' ') {
		cin >> input;
	}
	return input;
}

long getFileLength(ifstream& ifs) {
	long tmppos;
	long respos;
	tmppos = ifs.tellg();
	ifs.seekg(0, ios::end);
	respos = ifs.tellg();
	ifs.seekg(tmppos, ios::beg);
	return respos;
}

void waitView(int iCurPage) {
	char input = ' ';
	while (input == ' ') {
		cin >> input;
	}
	if (input == 'q') system("exit");
	else if (input == 'm') mainloop();
	else if (input == 'n') viewBooks(iCurPage);
}

// add new book module
void addBook() {
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	cout << "输入书名" << endl;
	cin >> inName;
	cout << "输入ISBN" << endl;
	cin >> inIsbn;
	cout << "输入价钱" << endl;
	cin >> inPrice;
	cout << "输入作者" << endl;
	cin >> inAuthor;

	CBook book(inName, inIsbn, inPrice, inAuthor);
	book.writeData();
	cout << "add book finished" << endl;
	waitUser();
}
// view books module
void viewBooks(int iSelPage = 1) {
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	bool bIndex = false;
	int iFileLength;
	iCurPage = iSelPage;
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	iFileLength = getFileLength(ifile);
	iDataCount = iFileLength / (2 * NUM1 + 2 * NUM2);
	if (iDataCount >= 1) bIndex = true;
	iPage = iDataCount / 20 + 1;
	clearScreen();
	cout << "共有记录" << iDataCount << ",";
	cout << "共有页数" << iPage << ",";
	cout << "当前页数" << iCurPage << " ";
	cout << "n 显示下一页，m 返回上一页" << endl;
	cout << setw(5) << "Index";
	cout << setw(22) << "Name" << setw(22) << "ISBN";
	cout << setw(15) << "Price" << setw(15) << "Author";
	cout << endl;
	try
	{
		ifile.seekg((iCurPage - 1) * 20 * (2 * NUM1 + 2 * NUM2));
		if (!ifile.fail()) {
			for (int i = 1; i < 21; i++) {
				memset(inName, 0, 128);
				memset(inIsbn, 0, 128);
				memset(inPrice, 0, 50);
				memset(inAuthor, 0, 50);
				if (bIndex) cout << setw(3) << (iCurPage - 1) * 20 + i;
				ifile.read(inName, NUM1);
				cout << setw(24) << inName;
				ifile.read(inIsbn, NUM1);
				cout << setw(24) << inIsbn;
				ifile.read(inPrice, NUM2);
				cout << setw(12) << inPrice;
				ifile.read(inAuthor, NUM2);
				cout << setw(12) << inAuthor;
				cout << endl;
				if (ifile.tellg() < 0) bIndex = false;
				else bIndex = true;

			}
		}
	}
	catch (const std::exception&)
	{
		cout << "throw file reading exception" << endl;
		throw "file error occured";
		ifile.close();
	}
	if (iCurPage < iPage) {
		iCurPage = iCurPage + 1;
		waitView(iCurPage);
	}
	else waitView(iCurPage);
	ifile.close();
}

// delete data module
void deleteBook() {
	int iDelCount;
	cout << "Please input delete index" << endl;
	cin >> iDelCount;
	CBook tmpbook;
	tmpbook.deleteData(iDelCount);
	cout << "delete finish" << endl;
	waitUser();
}

// main loop
void mainloop() {
	showWelcome();
	while (1) {
		clearScreen();
		showWelcome();
		showRootMenu();
		switch (getSelect())
		{
		case 1:
			clearScreen();
			addBook();
			break;

		case 2:
			clearScreen();
			viewBooks();
			break;

		case 3:
			clearScreen();
			deleteBook();
			break;
		}
	}
}