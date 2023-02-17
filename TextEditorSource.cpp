#include <iostream>
#include <conio.h>
#include "TextEditor.h"
using namespace std;

int main()
{
	char* customDoc{};
	int opt;
	bool newdoc = false;
	
	while (true)
	{
		do
		{
			system("cls");
			cout << "1.\t New Document\n"
				<< "2.\t Open Existing\n"
				<< "3.\t Exit Editor";
			opt = _getch();
		} while (opt != 49 && opt != 50 && opt != 51);

		switch (opt)
		{
		case 49:
			newdoc = true;
			break;
		case 50:
			newdoc = false;
			system("cls");
			cout << "Enter Name Of Document: ";
			TextEditor::InputString(customDoc);
			break;
		case 51:
			return 0;
		}
		system("cls");
		if (newdoc)
		{
			TextEditor TE;
			TE.EditingCMD();
		}
		else
		{
			TextEditor TE(customDoc);
			TE.EditingCMD();
		}
	}

	
}