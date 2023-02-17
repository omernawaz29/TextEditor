#pragma once
#include <string>
#include<conio.h>
#include<iostream>
#include<windows.h>
#include <fstream>
using namespace std;

void gotoRowCol(int rpos, int cpos);


class Line
{
	friend class TextEditor;
	friend class Document;
	char* Cs;
	int size;
public:
	Line();
	void insertAt(int, char);
	void removeAt(int);

	void clearLine();
	void printLine();
	void printLineAds();
	void copyLine(const Line&, int , int);
	void concatenateLine(const Line&);
	~Line();
};

class Document
{
	friend class TextEditor;
	Line* Ls;
	int NOL;
	string DName;
	int pass = 0;
	int encoded = 0;
	char* password{};
	bool saved = true;
public:
	Document();

	bool Load(string);
	void Load();

	void printDocument();
	void printDocumentAds();

	void AddLine(int,int);
	void RemoveLine(int);

	void Update();
	void Update(string);

	void insensitiveFind(const char*, int*&, int*&, int&);
	void sensitiveFind(const char*,int*&, int*&, int&);
	void replace(const char*,const char*,const bool);
	void replaceSelectively(const char* searchstring, const char* replacestring, int r, int c);

	int WordCount();
	int AvgWordLength();
	int SpecialCharacterCount();
	int SentenceCount();
	int ParagraphCount();

	void LargestWord(int&, int&);
	void SmallestWord(int&, int&);
	void HighestAlpha(int&, int&);
	int checkSubAlphas(const char*, int);

	void mergeDoc(const char*);
	void addPassword();
	bool removePassword();
	void changePassword();

	void toggleEncoding();

	
	void DeAllocater();
	~Document();
};

class TextEditor
{
	int cr = 0 , cc = 0;
	Document** Docs;
	int NOD = 1;
	int cdoc = 0;
public:
	//UTILITY FUNCTIONS 
	static void ControlsMenu(const char*);
	static void InputString(char*&);
	static int getLength(const char*);
	static bool isPunctuation(char c);
	static void InsertAtEnd(char*&, int&, char);
	static void InsertAtEnd(int*&, int&, int);
	static const char* toUpper(const char*);
	static const char* toLower(const char*);
	static char toUpper(char A);
	static char toLower(char A);
	static char* concatenateString(const char*, const char*);
	static void eraseRow(int, int);
	static const char* encodestring(char*);
	

	//MAIN FUNCTIONS 
	TextEditor(string fname);
	TextEditor();
	void addDocument();
	void addDocument(string);
	void switchDocument();
	void removeDocument();
	void Editing();
	void EditingCMD();
	void Print();
	void PrintAds();
	void PrintStats();


	~TextEditor();

};

