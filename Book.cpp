#include "Book.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

CBook::CBook() {}


CBook::CBook(char* cName, char* cIsbn, char* cPrice, char* cAuthor) {
	strncpy_s(m_cName, cName, NUM1);
	strncpy_s(m_cIsbn, cIsbn, NUM1);
	strncpy_s(m_cPrice, cPrice, NUM2);
	strncpy_s(m_cAuthor, cAuthor, NUM2);
}

CBook::~CBook() {}

char* CBook::getName() {
	return m_cName;
}

char* CBook::getIsbn() {
	return m_cIsbn;
}

char* CBook::getPrice() {
	return m_cPrice;
}

char* CBook::getAuthor() {
	return m_cAuthor;
}

void CBook::setName(char* cName) {
	strncpy_s(m_cName, cName, NUM1);
}

void CBook::setIsbn(char* cIsbn) {
	strncpy_s(m_cIsbn, cIsbn, NUM1);
}

void CBook::setPrice(char* cPrice) {
	strncpy_s(m_cPrice, cPrice, NUM2);
}

void CBook::setAuthor(char* cAuthor) {
	strncpy_s(m_cAuthor, cAuthor, NUM2);
}

// write data to file
void CBook::writeData() {
	ofstream ofile;
	ofile.open("book.dat", ios::binary | ios::app);
	try
	{
		ofile.write(m_cName, NUM1);
		ofile.write(m_cIsbn, NUM1);
		ofile.write(m_cPrice, NUM2);
		ofile.write(m_cAuthor, NUM2);
	}
	catch (const std::exception&)
	{
		throw "error occured when writing file";
		ofile.close();
	}
	ofile.close();
}

// read from file
void CBook::getBookFromFile(int iCount) {
	char cName[NUM1];
	char cIsbn[NUM1];
	char cPrice[NUM2];
	char cAuthor[NUM2];
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	try
	{
		// sets the position of the next character to be extracted in the input stream
		// beg:begin;	current:cur;	end:end
		ifile.seekg((long)iCount * (NUM1 * 2 + NUM2 * 2), ios::beg);
		ifile.read(cName, NUM1);
		// returns the position of current character in input stream
		if (ifile.tellg() > 0) strncpy_s(m_cName, cName, NUM1);
		ifile.read(cIsbn, NUM1);
		if (ifile.tellg() > 0) strncpy_s(m_cIsbn, cIsbn, NUM1);
		ifile.read(cPrice, NUM2);
		if (ifile.tellg() > 0) strncpy_s(m_cPrice, cPrice, NUM2);
		ifile.read(cAuthor, NUM2);
		if (ifile.tellg() > 0) strncpy_s(m_cAuthor, cAuthor, NUM2);


	}
	catch (const std::exception&)
	{
		throw "eror occured when reading file";
		ifile.close();
	}
	ifile.close();
}


// delete data
void CBook::deleteData(int iCount) {
	long respos;
	int iDataCount = 0;
	fstream file;
	fstream tmpfile;
	ofstream ofile;
	char cTempBuf[2 * NUM1 + 2 * NUM2];
	file.open("book.dat", ios::binary | ios::in | ios::out);
	tmpfile.open("temp.dat", ios::binary | ios::in | ios::out | ios::trunc);
	// get the length of the inputstream
	file.seekg(0, ios::end);
	respos = file.tellg();
	iDataCount = respos / (2 * NUM1 + 2 * NUM2);
	if (iCount<0 || iCount>iDataCount) {
		throw "input number error";
	}
	else {
		file.seekg((long)iCount * (NUM1 * 2 + NUM2 * 2), ios::beg);
		for (int i = 0; i < (iDataCount - iCount); i++) {
			memset(cTempBuf, 0, 2 * NUM1 + 2 * NUM2);
			file.read(cTempBuf, 2 * NUM1 + 2 * NUM2);
			tmpfile.write(cTempBuf, 2 * NUM1 + 2 * NUM2);
		}
		file.close();
		tmpfile.seekg(0, ios::beg);
		ofile.open("book.dat");
		// set the position where the next character to be inserted into the output stream
		ofile.seekp(((long)iCount - 1) * (2 * NUM1 + 2 * NUM2), ios::beg);
		for (int j = 0; j < (iDataCount - iCount); j++) {
			memset(cTempBuf, 0, 2 * NUM1 + 2 * NUM2);
			tmpfile.read(cTempBuf, 2 * NUM1 + 2 * NUM2);
			ofile.write(cTempBuf, 2 * NUM1 + 2 * NUM2);
		}
	}
	tmpfile.close();
	ofile.close();
	remove("temp.dat");

}





