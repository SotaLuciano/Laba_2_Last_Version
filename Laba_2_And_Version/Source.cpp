#include "Header.h"

void Print(fstream & Text)
{
	Text.seekg(0, ios::beg);
	char n[Max_Len];
	while (!Text.eof())
	{
		Text >> n;
		cout << n << endl;
	}
	Text.flush();
}

void push(char* info, Stek *& Stringns)	//Add new element  of stack
{
	Stek *tmp = new Stek;
	char * buff = _strdup(info);
	tmp->text = buff;
	tmp->next = Stringns;
	Stringns = tmp;
}

void pop(Stek *& Stringns)				//Extract element of stack
{
	if (Stringns == NULL)
	{
		printf("Stek is empty");
		return;
	}
	Stek *tmp = Stringns;
	Stringns = tmp->next;
	cout << tmp->text << endl;// cout
							  //	delete tmp->text; ERROR
	tmp->text = NULL;
	delete tmp;					// deleting element of stack
	return;
}

int LoadFileToStek(Stek *& Strings, string name, string road)
{

	fstream file(road + name);

	const int MAX_SIZE = 10;

	char *buffer = new char[MAX_SIZE];

	char *arr = new char[MAX_SIZE];

	int n = MAX_SIZE;

	int count = 0;

	bool isFirst = true;

	char k1;

	while (file.get(k1))
	{
		/*if (file.eof())
		break;*/

		file.seekg(-1, ios::cur);

		file.getline(buffer, MAX_SIZE, '\n');

		if (isFirst)
		{
			strcpy(arr, buffer);

		}

		char k;

		file.clear();

		file.seekg(-1, ios::cur);

		file.get(k);
		if (!file.get(k1))
		{
			k = '\n';
		}
		file.seekg(-1, ios::cur);
		if (k == '\n' || !file.good() || k == '\n')
		{

			if (isFirst)
			{
				strcpy(arr, buffer);
			}
			else
			{
				strcat(arr, buffer);
			}



			strcat(arr, "\n");


			push(arr, Strings);

			count++;

			isFirst = true;

			delete[] arr;

			n = MAX_SIZE;

			arr = new char[n];

		}
		else
		{
			char *b = _strdup(arr);

			n = n * 2;

			delete[] arr;

			arr = new char[n];

			strcpy(arr, b);

			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				strcat(arr, buffer);
			}

		}

	}

	file.close();
	return count;
}

void Renumber(Stek *&Strings, int count)
{
	Stek *p = Strings;

	int i = count;

	while (p != NULL)
	{
		char *a = new char[(strlen(p->text) + 2 + (int)log10(i))];

		sprintf(a, "%d: %s", i, p->text);

		delete p->text;

		p->text = a;

		p = p->next;

		--i;
	}

	count = 0;
}

void Purge(Stek *& Strings)// Purge all stack
{
	while (Strings != NULL)
	{
		pop(Strings);//extracting top element
	}
	delete Strings;
}

void LinePrint(void)
{
	for (int i = 0; i < 160; i++)
		cout << '*';
}

void ListofFiles(void)
{
	WIN32_FIND_DATAA FindFileData; // function for searching files

	HANDLE hSearch;

	cout << "\t\t\t\t\tStart searching" << endl;

	LinePrint();

	cout << "\t\t\t\t\tRESULTS:" << endl;

	//Searching files

	hSearch = FindFirstFileA(("d:\\Visual Studio C++ Projects\\Laba_2\\Laba_2\\*.txt"), &FindFileData); // Way to directory

	if (hSearch == INVALID_HANDLE_VALUE)
	{
		printf("Invalid File Handle. GetLastError reports %d\n", GetLastError());
	}
	else
	{
		do
		{
			printf("%s\n", FindFileData.cFileName);			// Print files
		} while (FindNextFileA(hSearch, &FindFileData));	//Search next file
		FindClose(hSearch);
	}
}