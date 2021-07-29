#pragma once
#define NUM1 128
#define NUM2 50
class CBook {
public:
	CBook();
	CBook(char* cName, char* cIsbn, char* cPrice, char* cAuthor);
	~CBook();

public:
	char* getName();
	char* getIsbn();
	char* getPrice();
	char* getAuthor();

	void setName(char* cName);
	void setIsbn(char* cIsbn);
	void setPrice(char* cPrice);
	void setAuthor(char* cAuthor);

	void writeData();
	void deleteData(int iCount);
	void getBookFromFile(int iCount);

protected:
	char m_cName[NUM1];
	char m_cIsbn[NUM1];
	char m_cPrice[NUM2];
	char m_cAuthor[NUM2];
};
