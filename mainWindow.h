#pragma once
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <fstream>
#include "Book.h"
using namespace std;

void setScreenGrid();
void setSysCation();
void setSysCation(const char* pText);
void clearScreen();
void showWelcome();
void showRootMenu();
void waitUser();
void mainloop();
int getSelect();
void addBook();
void viewBooks(int iSelPage = 1);
void deleteBook();
long getFileLength(ifstream& ifs);
void waitView(int iCurPage);
