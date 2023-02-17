#include "TextEditor.h"
using namespace std;


//GLOBAL FUNCTIONS
void gotoRowCol(int rpos, int cpos)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int xpos = cpos, ypos = rpos;
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}



// UTILITY TEXT EDITOR FUNCTIONS
void TextEditor::ControlsMenu(const char* fname)
{
	system("cls");
	char ch;
	ifstream rdr(fname);
	do
	{
		ch = rdr.get();
		cout << ch;
	} while (!rdr.eof());
	cout << "\n\n";
	system("pause");
}
void TextEditor::InputString(char*&S)
{
	delete[]S;
	char ch;
	int size = 0;
	S = new char[size + 1]{};
	do
	{
		ch = _getche();

		if (ch == 13)
		{
			break;
		}
		else if (ch == 8 && size !=0)
		{
			cout << " \b";
			char *NS = new char[size];
			int j = 0;
			for (int i = 0; i < size; j++)
			{
				if (j == size -1)
					continue;

				NS[i] = S[j];
				i++;
			}
			delete[] S;
			S = NS;
			size--;
		}
		else
		{
			InsertAtEnd(S, size, ch);
		}

	} while (true);
}
int TextEditor::getLength(const char* astring)
{
		int c = 0;
		while (astring[c] != '\0')
		{
			c++;
		}
		return c;
}
bool TextEditor::isPunctuation(char c)
{
	if((c >= 32 && c<=47) || (c>=58 && c<=64) || (c>=91 &&  c<=96) || (c>=123 && c<=126) || c == '\0' || c == '\n')
		return true;
	return false;
}
void TextEditor::InsertAtEnd(char*& S, int &size, char ch)
{
	char *NS = new char[size + 2];
	for (int i = 0; i < size; i++)
		NS[i] = S[i];
	NS[size] = ch;
	delete[]S;
	S = NS;
	size++;
	S[size] = '\0';
	NS = nullptr;
}
void TextEditor::InsertAtEnd(int*& S, int& size, int n)
{
	int* NS = new int[size + 1];
	for (int i = 0; i < size; i++)
		NS[i] = S[i];
	NS[size] = n;
	delete[]S;
	S = NS;
	size++;
}
const char* TextEditor::toUpper(const char* A)
{
	int size = TextEditor::getLength(A); // abdef
	char* NS = new char[size+1]{};		// 7 size ki array 
	char ch;
	for (int i = 0; i<size; i++)     
	{
		if (A[i] >= 'a' && A[i] <= 'z')
			NS[i] = A[i] - 32;
		else
			NS[i] = A[i];
	}
	NS[size] = '\0';
	return NS;
}
const char* TextEditor::toLower(const char* A)
{
	int size = TextEditor::getLength(A);
	char* NS = new char[size + 1]{};
	char ch;
	for (int i = 0; i < size; i++)
	{
		if (A[i] >= 'A' && A[i] <= 'Z')
			NS[i] = A[i] + 32;
		else
			NS[i] = A[i];
	}
	NS[size] = '\0';
	return NS;
}
char TextEditor::toUpper(char A)
{
	if (A >= 97 && A <= 122)
		return A - 32;
	else
		return A;
}
char TextEditor::toLower(char A)
{
	if (A >= 65 && A <= 90)
		return A + 32;
	else
		return A;
}
char* TextEditor::concatenateString(const char* A, const char* B)
{
	char* NS{};
	int size = getLength(A) + getLength(B);

	NS = new char[size + 1];
	int i = 0;
	for (i = 0; i < getLength(A); i++)
		NS[i] = A[i];

	for (int j = 0; j <= getLength(B); j++, i++)
		NS[i] = B[j];

	return NS;
}
void TextEditor::eraseRow(int r, int c)
{
	gotoRowCol(r, c);
	for (int i = 0; i < 210; i++)
	{
		cout << " ";
	}
}

const char* TextEditor::encodestring(char* str)
{
	int size{};
	char* temp{};
	for (int i = 0; i < getLength(str); i++)
	{
		InsertAtEnd(temp, size, str[i]);
	}

	for (int i = 0; i < size; i++)
	{
		if (temp[i] != '\n' && temp[i] != '\0')
			temp[i] += 32;
	}

	return temp;
}


//TEXT EDITOR MAIN FUNCTIONS 
TextEditor::TextEditor(string fname)
{
	cc = 0; cr = 0;
	Docs = new Document*;
	Docs[cdoc] = new Document;
	NOD = 1;
	if (Docs[cdoc]->Load(fname))
	{

	}
	else
	{
		removeDocument();
	}
}
TextEditor::TextEditor()
{
	cc = 0; cr = 0;
	Docs = new Document*;
	Docs[cdoc] = new Document;
	Docs[cdoc]->Load();
	NOD = 1;
}
void TextEditor::addDocument()
{
	ofstream create("NewDocument.txt");
	create << 1 << " " << 0 << endl << "Empty Document";
	create.close();
	addDocument("NewDocument.txt");
}
void TextEditor::addDocument(string fname)
{
	Document** newDocs = new Document * [NOD + 1];
	for (int i = 0; i < NOD; i++)
	{
		newDocs[i] = Docs[i];
	}
	newDocs[NOD] = new Document;
	if(newDocs[NOD]->Load(fname))
	{
		delete[]Docs;
		Docs = newDocs;
		newDocs = nullptr;
		NOD++;
		cdoc = NOD - 1;
	}
	
}
void TextEditor::switchDocument()
{
	cdoc++;
	if (cdoc >= NOD)
		cdoc = 0; 
	system("cls");
	gotoRowCol(0, 0);
	Print();
}
void TextEditor::removeDocument()
{
	Document** newDocs = new Document * [NOD - 1];
	int j = 0;
	for (int i = 0; i < NOD; i++)
	{
		if (i != cdoc)
		{
			newDocs[j] = Docs[i];
			j++;
		}
		if (i == cdoc)
		{
			delete[]Docs[i]->Ls;
			Docs[i]->Ls = nullptr;
		}
	}

	delete[]Docs;
	Docs = newDocs;
	newDocs = nullptr;
	NOD--;
}

void TextEditor::EditingCMD()
{
	int d{}, opt{}, * crs{}, * ccs{}, pcount;
	char ch{}, * string1{}, * string2{}, * string3{}; //generically named strings to be used anywhere needed.
	string cmd;
	Print();
	gotoRowCol(0, 0);
	PrintStats();
	while (true)
	{
		if (_kbhit())
		{
			d = _getch();

			//MOVEMENT & DELETE
			if (d == 224)
			{
				d = _getch();
				if (d == 72)
				{
					if (cr > 0)
						cr--;
					if (cc > Docs[cdoc]->Ls[cr].size)
						cc = Docs[cdoc]->Ls[cr].size;
				}
				else if (d == 80)
				{
					if (cr < Docs[cdoc]->NOL - 1)
						cr++;
					if (cc > Docs[cdoc]->Ls[cr].size)
						cc = Docs[cdoc]->Ls[cr].size;
				}
				else if (d == 77)
				{
					if (cc <= Docs[cdoc]->Ls[cr].size)
					{
						cc++;
						if (cc > Docs[cdoc]->Ls[cr].size)
						{
							if (cr == Docs[cdoc]->NOL - 1)
								cc--;
							else
							{
								cr++;
								cc = 0;
							}
						}
					}
				}
				else if (d == 75)
				{
					if (cc >= 0)
					{
						cc--;
						if (cc < 0)
						{
							if (cr == 0)
								cc++;
							else
							{
								cr--;
								cc = Docs[cdoc]->Ls[cr].size;
							}
						}
					}
				}
				else if (d == 83)
				{
					if (cc + 1 < Docs[cdoc]->Ls[cr].size)
					{
						gotoRowCol(cr, 0);
						Docs[cdoc]->Ls[cr].clearLine();
						Docs[cdoc]->Ls[cr].removeAt(cc);
						Docs[cdoc]->saved = false;
						gotoRowCol(cr, 0);
						Docs[cdoc]->Ls[cr].printLine();
					}
				}
				else if (d == 116)
				{
					do
					{
						cc++;
						if (cc >= Docs[cdoc]->Ls[cr].size)
						{
							if (cr >= Docs[cdoc]->NOL - 1)
							{
								cc--;
								break;
							}
							cr++;
							cc = 0;
						}
					} while (!isPunctuation(Docs[cdoc]->Ls[cr].Cs[cc]));
				}
				else if (d == 115)
				{
					do
					{
						cc--;
						if (cc < 0)
						{
							if (cr == 0)
							{
								cc++;
								break;
							}
							cr--;
							cc = Docs[cdoc]->Ls[cr].size;
						}
					} while (!isPunctuation(Docs[cdoc]->Ls[cr].Cs[cc]) && cc > 0);

				}
			}
			//CMDTAKE
			else if (d == 26)
			{
				eraseRow(46, 0);
				gotoRowCol(46, 0);
				cout << "Enter Command('-' to cancel): ";
				cin >> cmd;

				if (cmd != "-")
				{
					//repace first 
					if (cmd == "repf")
					{
						system("cls");
						cout << "Input Search String: ";
						InputString(string1);
						system("cls");
						cout << "Replace With: ";
						InputString(string2);

						Docs[cdoc]->replace(string1, string2, false);
						Print();
						Docs[cdoc]->saved = false;
					}
					//replace all
					else if (cmd == "repa")
					{
						system("cls");
						cout << "Input Search String: ";
						InputString(string1);
						system("cls");
						cout << "Replace With: ";
						InputString(string2);

						Docs[cdoc]->replace(string1, string2, true);
						gotoRowCol(0, 0);
						Print();
						Docs[cdoc]->saved = false;
					}
					//prefix
					else if (cmd == "pref")
					{
						system("cls");
						cout << "Input Word: ";
						InputString(string1);
						system("cls");
						cout << "Prefix: ";
						InputString(string2);
						string3 = concatenateString(string2, string1);

						Docs[cdoc]->replace(string1, string3, true);
						delete[]string3;
						Print();
						Docs[cdoc]->saved = false;
					}
					//postfix
					else if (cmd == "posf")
					{
						system("cls");
						cout << "Input Word: ";
						InputString(string1);
						system("cls");
						cout << "Postfix: ";
						InputString(string2);
						string3 = concatenateString(string1, string2);

						Docs[cdoc]->replace(string1, string3, true);
						delete[]string3;
						Print();
						Docs[cdoc]->saved = false;
					}
					//wordcount
					else if (cmd == "wc")
					{
						system("cls");
						cout << "Word Count: " << Docs[cdoc]->WordCount() << endl;
						cout << "Average Word Length: " << Docs[cdoc]->AvgWordLength() << endl;
						cout << "Special Characters: " << Docs[cdoc]->SpecialCharacterCount() << endl;
						cout << "Sentence Count: " << Docs[cdoc]->SentenceCount() << endl;
						cout << "Paragraph Count: " << Docs[cdoc]->ParagraphCount() << endl;
						system("pause");
						Print();
					}
					//find case insensitive
					else if (cmd == "find")
					{
						system("cls");
						cout << "Input Search String: ";
						InputString(string1);
						Docs[cdoc]->insensitiveFind(string1, crs, ccs, pcount);
						gotoRowCol(0, 0);
						Print();

						cr = crs[0];
						cc = ccs[0];
						gotoRowCol(cr, cc);
						for (int i = 1; i < pcount; i++)
						{
							d = _getch();
							if (d == 14)
							{
								cr = crs[i];
								cc = ccs[i];
								gotoRowCol(cr, cc);
							}
							else
								break;
						}

						delete[]crs;
						delete[]ccs;

					}
					//find case sensitive
					else if (cmd == "findc")
					{
						system("cls");
						cout << "Input Search String: ";
						InputString(string1);
						Docs[cdoc]->sensitiveFind(string1, crs, ccs, pcount);

						gotoRowCol(0, 0);
						Print();

						cr = crs[0];
						cc = ccs[0];
						gotoRowCol(cr, cc);
						for (int i = 0; i < pcount; i++)
						{
							d = _getch();
							if (d == 14)
							{
								cr = crs[i];
								cc = ccs[i];
								gotoRowCol(cr, cc);
							}
							else
								break;
						}


						delete[]crs;
						delete[]ccs;
					}
					//largest word
					else if (cmd == "lword")
					{
						Docs[cdoc]->LargestWord(cr, cc);
					}
					//smallest word
					else if (cmd == "sword")
					{
						Docs[cdoc]->SmallestWord(cr, cc);
					}
					//highest alpha
					else if (cmd == "hword")
					{
						Docs[cdoc]->HighestAlpha(cr, cc);
					}
					//mergeDoc
					else if (cmd == "merge")
					{
						system("cls");
						cout << "Enter Name Of Second Document To Merge: ";
						InputString(string1);
						Docs[cdoc]->mergeDoc(string1);
						gotoRowCol(0, 0);
						system("cls");
						Print();
						Docs[cdoc]->saved = false;
					}
					//toggle password
					else if (cmd == "pass")
					{
						if (Docs[cdoc]->pass == 0)
						{
							system("cls");
							Docs[cdoc]->addPassword();
							Docs[cdoc]->Update();
							Print();
						}
						else if (Docs[cdoc]->pass == 1)
						{
							system("cls");
							do
							{
								cout << "This File is Already Password Protected\n"
									<< "1. Change Password\n"
									<< "2. Remove Password\n"
									<< "3. Cancel\n>";
								opt = _getch();
							} while (opt < 49 && opt >51 );
							
							switch (opt)
							{
							case 49:
								system("cls");
								Docs[cdoc]->changePassword();
								Docs[cdoc]->Update();
								break;
							case 50:
								system("cls");
								Docs[cdoc]->removePassword();
								Docs[cdoc]->Update();
								break;
							case 51:
								break;
							}
							Print();
						}
					}
					//open new doc
					else if (cmd == "open")
					{
						do
						{
							system("cls");
							cout << "1.\t Open New Document\n";
							cout << "2.\t Open Existing Document\n";
							cout << "3.\t Cancel";
							opt = _getch();
						} while (opt < 49 || opt > 51);


						switch (opt)
						{
						case 49:
							addDocument();
							break;
						case 50:
							system("cls");
							cout << "Enter Document Name To Open: ";
							InputString(string1);
							addDocument(string1);
							break;
						case 51:
							break;
						}
						system("cls");
						gotoRowCol(0, 0);
						Print();
					}
					//repace from cursor
					else if (cmd == "repc")
					{
						system("cls");
						cout << "Input Search String: ";
						InputString(string1);
						system("cls");
						cout << "Replace With: ";
						InputString(string2);

						Docs[cdoc]->sensitiveFind(string1, crs, ccs, pcount);
						gotoRowCol(0, 0);
						Print();

						int tcr = cr, tcc = cc;
						for (int i = 0; i < pcount;)
						{
							while (true)
							{
								if (i >= pcount - 1)
									break;
								else if (crs[i] < tcr)
								{
									i++;
								}
								else if (crs[i] == tcr)
								{
									if (ccs[i] < tcc)
										i++;
									else
										break;
								}
								else
									break;
							}

							cr = crs[i];
							cc = ccs[i];
							gotoRowCol(cr, cc);

							d = _getch();
							//next
							if (d == 14)
							{
								if (i < pcount - 1)
									i++;
							}
							//previous
							else if (d == 2)
							{
								if (i > 0)
									i--;
							}
							//replace
							else if (d == 18)
							{
								Docs[cdoc]->Ls[cr].clearLine();
								Docs[cdoc]->replaceSelectively(string1, string2, cr, cc);
								if (i < pcount - 1)
								{
									i++;
									gotoRowCol(cr, 0);
									Docs[cdoc]->Ls[cr].printLine();
								}
								else
								{
									gotoRowCol(cr, 0);
									Docs[cdoc]->Ls[cr].printLine();
									cr = 0;
									cc = 0;
									break;
								}

						}
						//replaceall(previous OR next)
						else if (d == 0)
						{
							d = _getch();
							if (d == 49)
							{
								for (; i < pcount; i++)
								{
									gotoRowCol(crs[i], 0);
									Docs[cdoc]->Ls[crs[i]].clearLine();
									Docs[cdoc]->replaceSelectively(string1, string2, crs[i], ccs[i]);
									if (i != pcount - 1 && crs[i + 1] == crs[i])
									{
										ccs[i + 1] += TextEditor::getLength(string2) - TextEditor::getLength(string1);
									}
									gotoRowCol(crs[i], 0);
									Docs[cdoc]->Ls[crs[i]].printLine();
								}
								cr = crs[pcount - 1];
								cc = ccs[pcount - 1];
								break;
							}
							else if (d == 48)
							{
								for (; i >= 0; i--)
								{
									gotoRowCol(crs[i], 0);
									Docs[cdoc]->Ls[crs[i]].clearLine();
									Docs[cdoc]->replaceSelectively(string1, string2, crs[i], ccs[i]);
									gotoRowCol(crs[i], 0);
									Docs[cdoc]->Ls[crs[i]].printLine();
								}
								cr = crs[0];
								cc = ccs[0];
								break;
							}
						}
						else
							break;
					}

					}
					//save as 
					else if (cmd == "nsave")
					{
						system("cls");
						cout << "\n\nEnter A New Name: ";
						InputString(string1);
						Docs[cdoc]->Update(string1);
						Docs[cdoc]->saved = true;
						system("cls");
						Print();
					}
					//save 
					else if (cmd == "save")
					{
						Docs[cdoc]->Update();
						Docs[cdoc]->saved = true;
					}
					//escape menu
					else if (cmd == "close")
					{
						if (!Docs[cdoc]->saved)
						{
							do
							{
								system("cls");
								cout << "[!] You Have UnDocs[cdoc]->saved Changes\n\n";
								cout << "1.\t Save And Quit\n";
								cout << "2.\t Quit Without Saving\n";
								cout << "3.\t Save As[New Name]\n";
								cout << "4.\t Cancel";
								opt = _getch();
							} while (opt < 49 || opt > 52);

							switch (opt)
							{
							case 49:
								Docs[cdoc]->Update();
								cout << "\n\n[:)] Changes Saved Succesfully\n\n";
								system("pause");

								if (NOD == 1)
								{
									removeDocument();
									return;
								}
								else
								{
									removeDocument();
									switchDocument();
									Print();
								}
								break;

							case 50:
								cout << "\n\n[!]You Quit Without Saving\n\n";
								system("pause");

								if (NOD == 1)
								{
									removeDocument();
									return;
								}
								else
								{
									removeDocument();
									switchDocument();
									Print();
								}
								break;
							case 51:
								cout << "\n\nEnter A New Name: ";
								InputString(string1);
								Docs[cdoc]->Update(string1);

								cout << "\n\n[:)] Changes Saved Succesfully\n\n";
								system("pause");

								if (NOD == 1)
								{
									removeDocument();
									return;
								}
								else
								{
									removeDocument();
									switchDocument();
									Print();
								}
								break;

							case 52:
								gotoRowCol(0, 0);
								Print();
								break;
							}

						}
						else
						{
							system("cls");
							cout << "\n\n[|]Document Closed Successfully\n\n";
							system("pause");
							if (NOD == 1)
							{
								removeDocument();
								return;
							}
							else
							{
								removeDocument();
								switchDocument();
								Print();
							}
						}
					}
					//toggle encoding
					else if (cmd == "encode")
					{
						Docs[cdoc]->toggleEncoding();
						Print();
					}
					//wrong command
					else
					{
						eraseRow(46, 30);
						gotoRowCol(46, 30);
						cout << "Invalid Command";
						_getch();
						eraseRow(46, 30);
					}
					Docs[cdoc]->saved = false;
				}
				eraseRow(46, 0);
			}
			//ENTER
			else if (d == 13)
			{
				Docs[cdoc]->AddLine(cr, cc);
				Docs[cdoc]->saved = false;
				cr++;
				cc = 0;
				system("cls");
				Print();
			}
			//BACKSPACE
			else if (d == 8)
			{
				if (cc - 1 < 0 && cr > 0)
				{
					cc = Docs[cdoc]->Ls[cr - 1].size;
					Docs[cdoc]->RemoveLine(cr);
					Docs[cdoc]->saved = false;
					cr--;
					system("cls");
					Print();
				}
				else if (cc - 1 >= 0)
				{
					gotoRowCol(cr, 0);
					Docs[cdoc]->Ls[cr].clearLine();
					Docs[cdoc]->Ls[cr].removeAt(cc - 1);
					Docs[cdoc]->saved = false;
					gotoRowCol(cr, 0);
					Docs[cdoc]->Ls[cr].printLine();
					cc--;
				}
			}
			//SAVE 
			else if (d == 19)
			{
				Docs[cdoc]->Update();
				Docs[cdoc]->saved = true;
			}
			//CTRL+ALT 
			else if (d == 0)
			{
				d = _getch();
				//SAVE AS
				if (d == 31)
				{
					system("cls");
					cout << "\n\nEnter A New Name: ";
					InputString(string1);
					Docs[cdoc]->Update(string1);
					Docs[cdoc]->saved = true;
					system("cls");
					Print();
				}
				//SWITCH/SHIFT DOCUMENTS
				else if (d == 148)
				{
					switchDocument();
				}
				//CONTROLS MENU
				else if (d == 59)
				{
					ControlsMenu("commands.txt");
					gotoRowCol(0, 0);
					Print();
				}

			}
			//ESCAPE MENU
			else if (d == 27)
			{
				if (!Docs[cdoc]->saved)
				{
					do
					{
						system("cls");
						cout << "[!] You Have Unsaved Changes\n\n";
						cout << "1.\t Save And Quit\n";
						cout << "2.\t Quit Without Saving\n";
						cout << "3.\t Save As[New Name]\n";
						cout << "4.\t Cancel";
						opt = _getch();
					} while (opt < 49 || opt > 52);

					switch (opt)
					{
					case 49:
						Docs[cdoc]->Update();
						cout << "\n\n[:)] Changes Saved Succesfully\n\n";
						system("pause");

						if (NOD == 1)
						{
							removeDocument();
							return;
						}
						else
						{
							removeDocument();
							switchDocument();
							Print();
						}
						break;

					case 50:
						cout << "\n\n[!]You Quit Without Saving\n\n";
						system("pause");

						if (NOD == 1)
						{
							removeDocument();
							return;
						}
						else
						{
							removeDocument();
							switchDocument();
							Print();
						}
						break;
					case 51:
						cout << "\n\nEnter A New Name: ";
						InputString(string1);
						Docs[cdoc]->Update(string1);

						cout << "\n\n[:)] Changes Saved Succesfully\n\n";
						system("pause");

						if (NOD == 1)
						{
							removeDocument();
							return;
						}
						else
						{
							removeDocument();
							switchDocument();
							Print();
						}
						break;

					case 52:
						gotoRowCol(0, 0);
						Print();
						break;
					}

				}
				else
				{
					system("cls");
					cout << "\n\n[|]Document Closed Successfully\n\n";
					system("pause");
					if (NOD == 1)
					{
						removeDocument();
						return;
					}
					else
					{
						removeDocument();
						switchDocument();
						Print();
					}
				}
			}
			//TYPING
			else
			{
				ch = int(d);
				gotoRowCol(cr, 0);
				Docs[cdoc]->Ls[cr].clearLine();
				Docs[cdoc]->Ls[cr].insertAt(cc, ch);
				Docs[cdoc]->saved = false;
				gotoRowCol(cr, 0);
				Docs[cdoc]->Ls[cr].printLine();
				cc++;
			}
			PrintStats();
			gotoRowCol(cr, cc);

		}
	}

	//FREEING ANY MEMORY TO PREVENT ACCIDENTAL LEAKS
	delete[]string1;
	delete[]string2;
	delete[]string3;
	delete[]crs;
	delete[]ccs;
}

void TextEditor::Print()
{
	system("cls");
	gotoRowCol(0, 0);
	Docs[cdoc]->printDocument();
}
void TextEditor::PrintAds()
{
	cout << "cr: " << &cr << " cc: " << &cc;
	Docs[cdoc]->printDocumentAds();
}

void TextEditor::PrintStats()
{
	eraseRow(47, 0);
	gotoRowCol(47, 0);
	cout << "|\"" << Docs[cdoc]->DName << "\""
		<< "|Index: " << cdoc + 1
		<< "|Ln: " << cr + 1
		<< "|Col: " << cc + 1
		<< "|";
}

TextEditor::~TextEditor()
{
	for (int i = 0; i < NOD; i++)
	{
		Docs[i]->DeAllocater();
	}
	delete[]Docs;

}

//LINE FUNCTIONS
Line::Line()
{
	Cs = new char[1];
	size = 0;
}
void Line::insertAt(int ind, char ch)
{
	char* NS = new char[size + 2];
	int j = 0;
	for (int i = 0; i <= size+1; i++)
	{
		if (i == ind)
		{
			NS[i] = ch;
			continue;
		}
		if(size != 0)
			NS[i] = Cs[j];
		j++;
	}
	delete[]Cs;
	Cs = NS;
	size++;
	Cs[size] = '\0';
}
void Line::removeAt(int ind)
{
	char* NS = new char[size];
	int j = 0;
	for (int i = 0; i < size; j++)
	{
		if (j == ind)
			continue;

		NS[i] = Cs[j];
		i++;
	}
	delete[] Cs;
	Cs = NS;
	size--;
}
void Line::printLine()
{
	for (int i = 0; i < size; i++)
	{
		cout << Cs[i];
	}
	cout << endl;
}
void Line::printLineAds()
{
	cout << "size: " << &size << "|" << (void*)&Cs << " ===> ";
	for (int i = 0; i < size; i++)
	{
		cout << (void*)&Cs[i] << " ";
	}
	cout << endl;
}
void Line::clearLine()
{
	for (int i = 0; i < size; i++)
	{
		cout << " ";
	}
}
void Line::copyLine(const Line &L, int si = 0, int ei = -1)
{
	if (ei == -1)
		ei = L.size;

	char* NS = new char[ei - si + 1];

	int j = 0;
	for (int i = si; i < ei; i++)
	{
		NS[j] = L.Cs[i];
		j++;
	}
	delete[] Cs;
	Cs = NS;
	size = ei - si;
	Cs[size] = '\0';
}
void Line::concatenateLine(const Line &L)
{
	char* NS = new char[size + L.size + 1];

	int i = 0;
	for (i = 0; i < this->size; i++)
	{
		NS[i] = this->Cs[i];
	}
	for (int j = 0; j <= L.size; j++, i++)
	{
		NS[i] = L.Cs[j];
	}
	
	delete[]Cs;
	Cs = NS;
	size = this->size + L.size;
}

Line::~Line()
{
	delete[]Cs;
	Cs = nullptr;
	size = 0;
}


//DOCUMENT FUNCTIONS
Document::Document()
{
	Ls = nullptr;
	NOL = 0;
}
void Document::printDocument()
{
	for (int i = 0; i < NOL; i++)
		Ls[i].printLine();
}
void Document::printDocumentAds()
{

	cout << "\nDName:" << &DName << "\nNOL:" << &NOL << " " << &Ls << " ==>\n";
	for (int i = 0; i < NOL; i++)
	{
		cout << "\t\t" << &Ls[i] << " ===> ";
		Ls[i].printLineAds();
	}

}

void Document::AddLine(int li,int ci)
{
	Line* NLs = new Line[NOL + 1]{};
	int i = 0;
	for (i = 0; i < li; i++)
	{
		NLs[i].copyLine(Ls[i]);
	}

	if (ci < Ls[li].size && ci > 0)
	{
		NLs[li].copyLine(Ls[li], 0, ci);
		NLs[li + 1].copyLine(Ls[li], ci , Ls[li].size);
		i++;
	}
	if (ci >= Ls[li].size)
	{
		NLs[li].copyLine(Ls[li], 0, ci);
		NLs[li+1].Cs = nullptr;
		NLs[li+1].size = 0;
		i++;
	}
	if (ci <= 0)
	{
		NLs[li + 1].copyLine(Ls[li]);
		NLs[li].Cs = nullptr;
		NLs[li].size = 0;
		i++;
	}

	for (; i < NOL; i++)
	{
		NLs[i+1].copyLine(Ls[i]);
	}

	delete[] Ls;
	Ls = NLs;
	NOL++;
}
void Document::RemoveLine(int li)
{
	Line* NLs = new Line[NOL - 1];
	int i = 0;
	for (i = 0; i < li; i++)
	{
		NLs[i].copyLine(Ls[i]);
	}
	if (Ls[li].size != 0)
		NLs[li - 1].concatenateLine(Ls[li]);

	for (i = li+1; i < NOL; i++)
	{
		NLs[i-1].copyLine(Ls[i]);
	}

	delete[] Ls;
	Ls = NLs;
	NOL--;

}

void Document::Update()
{
	if (DName == "NewDocument.txt")
	{
		system("cls");
		cout << "Please Enter A Name For the Document: ";
		cin >> DName;
		system("cls");
		gotoRowCol(0, 0);
		printDocument();
	}
	Update(DName);
	
}
void Document::Update(string fname)
{
	ofstream wrt(fname);
	wrt << NOL << " " << pass << " " << encoded;

	if (pass == 1)
	{
		wrt << " ";
		if (encoded == 1)
			wrt << TextEditor::encodestring(password);
		else
			wrt << password;
	}
		
	wrt << endl;

	for (int i = 0; i < NOL; i++)
	{
		if (encoded == 0)
			wrt << Ls[i].Cs << endl;
		else if(encoded == 1)
			wrt << TextEditor::encodestring(Ls[i].Cs) << endl;
	}
	wrt.close();
}

void Document::sensitiveFind(const char* searchstring, int* &ri, int* &ci, int &count)
{
	bool stringfound = false; 
	int searchsize = TextEditor::getLength(searchstring);
	count = 0;
	int rc{}, cc{};
	ri = new int[1]{};
	ci = new int[1]{};
	for (int r = 0; r < NOL; r++)
	{
		for (int c = 0; c < Ls[r].size; c++)
		{
			if (Ls[r].Cs[c] == searchstring[0])
			{
				stringfound = true; 
				int tc = c, tr = r;
				for (int si = 0; si < searchsize; si++, tc++)
				{
					if (Ls[tr].Cs[tc] == '\n' || Ls[tr].Cs[tc] == '\r' || Ls[tr].Cs[tc] == '\0')
					{
						tr++;
						tc = 0;
					}
					if (Ls[tr].Cs[tc] != searchstring[si])
					{
						stringfound = false;
						break;
					}
				}
				if (stringfound)
				{
					TextEditor::InsertAtEnd(ri, rc, r);
					TextEditor::InsertAtEnd(ci, cc, c);
					count = rc;
				}
			}
		}
	}
}
void Document::insensitiveFind(const char* searchstring, int*&ri, int*&ci, int&count)
{
	bool stringfound = false;
	int searchsize = TextEditor::getLength(searchstring);
	count = 0;
	int rc{}, cc{};
	ri = new int[1]{};
	ci = new int[1]{};
	for (int r = 0; r < NOL; r++)
	{
		for (int c = 0; c < Ls[r].size; c++)
		{
			if (TextEditor::toLower(Ls[r].Cs[c]) == TextEditor::toLower(searchstring[0]))
			{
				stringfound = true;
				int tc = c, tr = r;
				for (int si = 0; si < searchsize; si++, tc++)
				{
					if (Ls[tr].Cs[tc] == '\n' || Ls[tr].Cs[tc] == '\r' || Ls[tr].Cs[tc] == '\0')
					{
						tr++;
						tc = 0;
					}
					if (TextEditor::toLower(Ls[tr].Cs[tc]) != TextEditor::toLower(searchstring[si]))
					{
						stringfound = false;
						break;
					}
				}
				if (stringfound)
				{
					TextEditor::InsertAtEnd(ri, rc, r);
					TextEditor::InsertAtEnd(ci, cc, c);
					count = rc;
				}
			}
		}
	}

}
void Document::replace(const char* searchstring, const char* replacestring, const bool all = false)
{
	int searchsize = TextEditor::getLength(searchstring);
	int replacesize = TextEditor::getLength(replacestring);
	int* ri{}, * ci{}, count{};
	sensitiveFind(searchstring, ri, ci, count);
	int replacecount = 1;

	if (all)
		replacecount = count;

	for (int rc = 0; rc < replacecount; rc++)
	{
		replaceSelectively(searchstring, replacestring, ri[rc], ci[rc]);
	}
		
	
}
void Document::replaceSelectively(const char* searchstring, const char* replacestring, int r, int c)
{
	int searchsize = TextEditor::getLength(searchstring);
	int replacesize = TextEditor::getLength(replacestring);

	Line R;
	R.size = Ls[r].size - searchsize + replacesize;
	R.Cs = new char[R.size + 1];

	int i = 0;
	for (i = 0; i < c; i++)
	{
		R.Cs[i] = Ls[r].Cs[i];
	}
	int si = i + searchsize;
	for (int j =0; j < replacesize; j++, i++)
	{
		R.Cs[i] = replacestring[j];
	}
	for(;i<R.size;i++,si++)
	{
		R.Cs[i] = Ls[r].Cs[si];
	}
	delete[]Ls[r].Cs;
	Ls[r].Cs = R.Cs;
	R.Cs = nullptr;
	Ls[r].size = R.size;
	Ls[r].Cs[R.size] = '\0';
}

void Document::addPassword()
{
	system("cls");
	cout << "Enter New Password: ";
	TextEditor::InputString(password);
	pass = 1;
	system("cls");
	cout << "Password Added\n";
	system("pause");
}
bool Document::removePassword()
{
	system("cls");
	cout << "Enter Current Password: ";

	char* pstring{};
	TextEditor::InputString(pstring);

	if (strcmp(pstring,password) == 0)
	{
		delete[]password;
		password = nullptr;
		pass = 0;
		system("cls");
		cout << "Password Removed\n";
		system("pause");
		return true;
	}
	else
	{
		system("cls");
		cout << "Wrong Password\n";
		system("pause");
		return false;
	}
	delete[]pstring;
}
void Document::changePassword()
{
	system("cls");
	bool removed = removePassword();

	if (removed)
		addPassword();
	else
	{
		cout << "Password could not be changed\n";
		system("pause");
	}
}

void Document::toggleEncoding()
{
	system("cls");
	if (encoded == 1)
	{
		encoded = 0;
		cout << "Encoding Disabled\n";
	}
	else
	{
		encoded = 1;
		cout << "Encoding Enabled\n";
	}
	system("pause");
}

int Document::WordCount()
{
	int wordcount{};
	for (int r = 0; r < NOL; r++)
	{
		for (int c = 0; c < Ls[r].size; c++)
		{
			if (Ls[r].Cs[c] == ' ' || Ls[r].Cs[c+1] == '\0' || Ls[r].Cs[c+1] == '\n')
				wordcount++;
		}
	}
	return wordcount;
}
int Document::AvgWordLength()
{
	int words = WordCount();
	int characters = 0;

	for (int r = 0; r < NOL; r++)
	{
		for (int c = 0; c < Ls[r].size; c++)
		{
			if (Ls[r].Cs[c] == ' ' || Ls[r].Cs[c+1] == '\0' || Ls[r].Cs[c+1] == '\n')
			{
				continue;
			}
			characters++;
		}
	}

	return characters / words;

}
int Document::SpecialCharacterCount()
{
	int specialcount{};
	for (int r = 0; r < NOL; r++)
	{
		for (int c = 0; c < Ls[r].size; c++)
		{
			if (TextEditor::isPunctuation(Ls[r].Cs[c]) && Ls[r].Cs[c] != ' ' && Ls[r].Cs[c] != '\0' && Ls[r].Cs[c] != '\n')
				specialcount++;
		}
	}
	return specialcount++;
}
int Document::SentenceCount()
{
	int sentencecount{};
	for (int r = 0; r < NOL; r++)
	{
		for (int c = 0; c < Ls[r].size; c++)
		{
			if (Ls[r].Cs[c] == '.' && (Ls[r].Cs[c + 1] == ' ' || Ls[r].Cs[c + 1] == '\0' || Ls[r].Cs[c + 1] == '\n'))
				sentencecount++;
				
		}
	}
	return sentencecount;
}
int Document::ParagraphCount()
{

	int paracount{};
	if (Ls[0].size != 0)
		paracount++;

	for (int r = 0; r+1 < NOL; r++)
	{
		if (Ls[r].size == 0 && Ls[r + 1].size != 0)
			paracount++;
	}
	return paracount;
}

void Document::LargestWord(int& ri, int& ci)
{
	int max = 0;
	int characters = 0;

	for (int r = 0; r < NOL; r++)
	{
		characters = 0;
		for (int c = 0; c < Ls[r].size; c++)
		{
			if (TextEditor::isPunctuation(Ls[r].Cs[c]))
			{
				if (characters > max)
				{
					max = characters;
					ri = r;
					ci = c - characters + 1;
				}
				characters = 0;
			}
			characters++;
		}
	}
}
void Document::SmallestWord(int& ri, int& ci)
{
	int min = INT_MAX;
	int characters = 0;

	for (int r = 0; r < NOL; r++)
	{
		characters = 0;
		for (int c = 0; c < Ls[r].size; c++)
		{
			if (TextEditor::isPunctuation(Ls[r].Cs[c]) && !TextEditor::isPunctuation(Ls[r].Cs[c+1]))
			{
				if (characters < min)
				{
					min = characters;
					ri = r;
					ci = c - characters + 1;
				}
				characters = 0;
			}
			characters++;
		}
	}
}

int Document::checkSubAlphas(const char*checkstring, int checksize)
{
	int subwords = 0;
	int LettersFound = 0;
	int tc = 0;
	int* checked = new int[1]{};
	int csize = 0;
	bool isChecked = false;
	for (int r = 0; r < NOL; r++)
	{
		for (int c = 0; c <= Ls[r].size; c++)
		{
			if (!TextEditor::isPunctuation(Ls[r].Cs[c]))
			{
				tc++;
				for (int csi = 0; csi < checksize; csi++)
				{
					if (TextEditor::toLower(Ls[r].Cs[c]) == checkstring[csi])
					{
						isChecked = false; 
						for (int i = 0; i < csize; i++)
							if (csi == checked[i])
								isChecked = true;

						if (isChecked)
						{
							continue;
						}
						else
						{
							TextEditor::InsertAtEnd(checked, csize, csi);
							LettersFound++;
							break;
						}
					}
				}
			}
			else
			{
				if (LettersFound == tc)
					subwords++;

				LettersFound = 0;
				tc = 0;

				delete[]checked;
				csize = 0;
				checked = new int[1];
			}
		}
	}
	return subwords;
}
void Document::HighestAlpha(int& ri, int& ci)
{
	char* S{};
	int size{};
	S = new char[size + 1];
	int max = 0;
	int alphacount = 0;
	for (int r = 0; r < NOL; r++)
	{
		for (int c = 0; c <= Ls[r].size; c++)
		{
			if (TextEditor::isPunctuation(Ls[r].Cs[c]))
			{
				alphacount = checkSubAlphas(TextEditor::toLower(S), size);
				if (max < alphacount)
				{
					max = alphacount;
					ri = r;
					ci = c - size;
				}

				delete[]S;
				size = 0;
				S = new char[size + 1];
			}
			else
			{
				TextEditor::InsertAtEnd(S, size, Ls[r].Cs[c]);
			}
		}

	}
}
void Document::mergeDoc(const char* fname)
{
	Document* doctwo = new Document;
	doctwo->Load(fname);

	Document* newdoc = new Document;
	newdoc->NOL = this->NOL + doctwo->NOL;
	newdoc->Ls = new Line[newdoc->NOL]{};

	int i = 0;
	for (;i < this->NOL; i++)
	{
		newdoc->Ls[i].copyLine(this->Ls[i]);
	}
	for (int j = 0; j < doctwo->NOL; j++,i++)
	{
		newdoc->Ls[i].copyLine(doctwo->Ls[j]);
	}
	delete[]Ls;
	NOL = newdoc->NOL;
	Ls = newdoc->Ls;
}


bool Document::Load(string fname)
{
	DName = fname;
	ifstream rdr(fname);
	if (rdr)
	{
		rdr >> NOL >> pass >> encoded;
		rdr.ignore();
		if (pass == 1)
		{
			password = new char{};
			int psize = 0;
			char ch;
			do
			{
				ch = rdr.get();
				if (encoded == 1)
					ch -= 32;
				if (TextEditor::isPunctuation(ch))
					break;
				TextEditor::InsertAtEnd(password, psize, ch);
			} while (true);
			int tries{};
			do
			{
				system("cls");
				cout << "Enter Password: ";
				char* inpass{};
				TextEditor::InputString(inpass);
				if (strcmp(inpass, password) == 0)
					break;
				else
				{
					if (tries >= 5)
					{
						cout << "\nToo Many Attempts.\n";
						system("pause");
						return false;
					}
					else
					{
						cout << "\nError: Wrong Password\n";
						tries++;
						if (tries != 0)
							cout << "Attempts: " << tries << endl;
						system("pause");
					}


				}
				delete[]inpass;
			} while (true);
		}

		Ls = new Line[NOL];
		int li = 0;
		int ci = 0;
		while (true)
		{
			if (!rdr)
				break;
			char ch = rdr.get();
			if (ch == '\n')
			{
				li++;
				ci = 0;
				continue;
			}
			if (ch != -1)
			{
				if (encoded == 1)
					ch -= 32;
				Ls[li].insertAt(ci, ch);
				ci++;
			}
		}
		rdr.close();
	}
	else
	{
		system("cls");
		cout << "Invalid Filename. Could Not Load\n\n";
		system("pause");
		return false;
	}
	
}
void Document::Load()
{
	ofstream create("NewDocument.txt");
	create << 1 << " " << 0 << endl << "Empty Document";
	create.close();
	Load("NewDocument.txt");
}

void Document::DeAllocater()
{
	for (int i = 0; i < NOL; i++)
	{
		delete[]Ls[i].Cs;
	}
	delete[]Ls;
	NOL = 0;
	DName.clear();
	pass = 0;
	delete[] password;
	saved = true;
}

Document::~Document()
{
	DeAllocater();
}
