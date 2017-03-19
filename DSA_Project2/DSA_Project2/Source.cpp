#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <conio.h>

#define _CRTDBG_MAP_ALLOC
#include<cstdlib>
#include<crtdbg.h>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>      

#include "HTable.h"
#include "BST.h"

using namespace std;

unsigned int bucks = 521;
class DTSTimer
{
	unsigned int startTime;
public:
	DTSTimer()
	{
		reset();
	}

	void reset()
	{
		startTime = clock();
	}

	unsigned int getElapsedTime()
	{
		return (clock() - startTime);
	}

	static void delay(const unsigned int milli)
	{
		unsigned int st = clock();
		while (clock() - st < milli) {}
	}

};
unsigned int Hfunc(const string& word)
{
	unsigned int index = 0;
	for (unsigned int i = 0; i < word.length(); i++)
	{
		index = 7*index + word[i];
	}
	index = index % bucks;
	return index;
}
HTable<string> Load(string file, unsigned int b)
{
	
	 HTable<string> Dict(b, Hfunc);

	string word;
	ifstream open;
	open.open(file);
	if (open.is_open())
	{
		while (open.good())
		{
			open >> word;
			open.ignore(INT_MAX, '\n');
			if (word.find('\'') == word.npos)
			{
				if (word.length() > 2 && word.length() < 7)
				{
					Dict.insert(word);
				}
			}
		}
	}
		open.close();
	return Dict;
}
string Scramble(string w)
{
	bool check = true;
		string scrambled = w;
		int r = rand() % 6;
		if (r == 0)
		{
			scrambled[0] = w[5];
			scrambled[1] = w[4];
			scrambled[2] = w[3];
			scrambled[3] = w[2];
			scrambled[4] = w[1];
			scrambled[5] = w[0];
		}
		else if (r == 1)
		{
			scrambled[0] = w[5];
			scrambled[2] = w[4];
			scrambled[4] = w[3];
			scrambled[1] = w[2];
			scrambled[3] = w[1];
			scrambled[5] = w[0];
		}
		else if (r == 2)
		{
			scrambled[5] = w[5];
			scrambled[3] = w[4];
			scrambled[1] = w[3];
			scrambled[4] = w[2];
			scrambled[2] = w[1];
			scrambled[0] = w[0];
		}
		else if (r == 3)
		{
			scrambled[3] = w[5];
			scrambled[5] = w[4];
			scrambled[1] = w[3];
			scrambled[2] = w[2];
			scrambled[0] = w[1];
			scrambled[4] = w[0];
		}
		else if (r == 4)
		{
			scrambled[2] = w[5];
			scrambled[5] = w[4];
			scrambled[4] = w[3];
			scrambled[3] = w[2];
			scrambled[0] = w[1];
			scrambled[1] = w[0];
		}
		else if (r == 4)
		{
			scrambled[2] = w[5];
			scrambled[5] = w[4];
			scrambled[4] = w[3];
			scrambled[3] = w[2];
			scrambled[0] = w[1];
			scrambled[1] = w[0];
		}
		else if (r == 5)
		{
			scrambled[1] = w[5];
			scrambled[5] = w[4];
			scrambled[0] = w[3];
			scrambled[4] = w[2];
			scrambled[3] = w[1];
			scrambled[2] = w[0];
		}
		
	return scrambled;
}
bool GameOver(string name, int score)
{
	int sc1 = 0;
	int sc2 = 0;
	int sc3 = 0;
	int sc4 = 0;
	int sc5 = 0;
	string n1 = "N/A";
	string n2 = "N/A";
	string n3 = "N/A";
	string n4 = "N/A";
	string n5 = "N/A";

	ifstream open;
	open.open("TopScore.text");
	if (open.is_open())
	{
		open >> n1 >> sc1;
		open.ignore(INT_MAX, '\n');
		open >> n2 >> sc2;
		open.ignore(INT_MAX, '\n');
		open >> n3 >> sc3;
		open.ignore(INT_MAX, '\n');
		open >> n4 >> sc4;
		open.ignore(INT_MAX, '\n');
		open >> n5 >> sc5;
		open.ignore(INT_MAX, '\n');

		open.close();
	}

	fstream save;
	save.open("TopScore.text", ios_base::out | ios_base::trunc);
	if (save.is_open())
	{
		if (score > sc1)
		{
			n5 = n4;
			sc5 = sc4;
			n4 = n3;
			sc4 = sc3;
			n3 = n2;
			sc3 = sc2;
			n2 = n1;
			sc2 = sc1;
			n1 = name;
			sc1 = score;
		}
		else if (score > sc2)
		{
			n5 = n4;
			sc5 = sc4;
			n4 = n3;
			sc4 = sc3;
			n3 = n2;
			sc3 = sc2;
			n2 = name;
			sc2 = score;
		}
		else if (score > sc3)
		{
			n5 = n4;
			sc5 = sc4;
			n4 = n3;
			sc4 = sc3;
			n3 = name;
			sc3 = score;
		}
		else if (score > sc4)
		{
			n5 = n4;
			sc5 = sc4;
			n4 = name;
			sc4 = score;
		}
		else if (score > sc5)
		{
			n5 = name;
			sc5 = score;
		}
		save << n1 << '\t' << sc1 << '\n';
		save << n2 << '\t' << sc2 << '\n';
		save << n3 << '\t' << sc3 << '\n';
		save << n4 << '\t' << sc4 << '\n';
		save << n5 << '\t' << sc5 << '\n';

		save.close();
	}
	system("cls");
	cout << "\n\n\n\n" << "\t\t\t" << "HIGH SCORE" << "\n\n\n\n";
	cout << "\t\t\t 1. " << n1 << " " << sc1 << "\n";
	cout << "\t\t\t 2. " << n2 << " " << sc2 << "\n";
	cout << "\t\t\t 3. " << n3 << " " << sc3 << "\n";
	cout << "\t\t\t 4. " << n4 << " " << sc4 << "\n";
	cout << "\t\t\t 5. " << n5 << " " << sc5 << "\n";
	cout << "\t\t\t Play Again? (SpaceBar/ESC)";
	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			return false;
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			return true;
		}
	}
}
void Game(HTable<string> Ht, unsigned int b)
{
	int score = 0;
	bool LevelUp = false;
	bool run = true;
	while (run)
	{
		string word = Ht.GetWord(b);
		string scrambled = Scramble(word);
		DTSTimer bob;
		string userInput;
		BST<string> WordCollection;

		while (bob.getElapsedTime() < 60000)
		{

			// 1 - get user input
			if (_kbhit())
			{
				char ch = _getch();

				if (-32 == ch)
					_getch();

				// did the user press a-z?
				else if (isalpha(ch))
				{
					userInput += tolower(ch);
				}
			}

			// 2 - act on it
			if (GetAsyncKeyState(VK_RETURN))
			{
				if (userInput.length() > 2 && userInput.length() < 7)
				{
					if (userInput.length() == 6)
					{
						bool sub0, sub1, sub2, sub3, sub4, sub5;
						sub0 = false;
						sub1 = false;
						sub2 = false;
						sub3 = false;
						sub4 = false;
						sub5 = false;
						int check = 0;
						for (int i = 0; i < 6; i++)
						{
							if (userInput[i] == scrambled[0] && sub0 != true)
							{
								sub0 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[1] && sub1 != true)
							{
								sub1 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[2] && sub2 != true)
							{
								sub2 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[3] && sub3 != true)
							{
								sub3 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[4] && sub4 != true)
							{
								sub4 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[5] && sub5 != true)
							{
								sub5 = true;
								check = check + 1;
							}
						}
						if (check == 6)
						{
							int valid = Ht.find(userInput);
							if (valid != -1)
							{
								if (WordCollection.find(userInput) == false)
								{
									WordCollection.insert(userInput);
									score = score + 719;
									LevelUp = true;
								}
							}
						}
					}
					else if (userInput.length() == 5)
					{
						bool sub0, sub1, sub2, sub3, sub4, sub5;
						sub0 = false;
						sub1 = false;
						sub2 = false;
						sub3 = false;
						sub4 = false;
						sub5 = false;
						int check = 0;
						for (int i = 0; i < 5; i++)
						{
							if (userInput[i] == scrambled[0] && sub0 != true)
							{
								sub0 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[1] && sub1 != true)
							{
								sub1 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[2] && sub2 != true)
							{
								sub2 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[3] && sub3 != true)
							{
								sub3 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[4] && sub4 != true)
							{
								sub4 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[5] && sub5 != true)
							{
								sub5 = true;
								check = check + 1;
							}
						}
						if (check == 5)
						{
							int valid = Ht.find(userInput);
							if (valid != -1)
							{
								if (WordCollection.find(userInput) == false)
								{
									WordCollection.insert(userInput);
									score = score + 119;
								}
							}
						}
					}
					else if (userInput.length() == 4)
					{
						bool sub0, sub1, sub2, sub3, sub4, sub5;
						sub0 = false;
						sub1 = false;
						sub2 = false;
						sub3 = false;
						sub4 = false;
						sub5 = false;
						int check = 0;
						for (int i = 0; i < 4; i++)
						{
							if (userInput[i] == scrambled[0] && sub0 != true)
							{
								sub0 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[1] && sub1 != true)
							{
								sub1 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[2] && sub2 != true)
							{
								sub2 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[3] && sub3 != true)
							{
								sub3 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[4] && sub4 != true)
							{
								sub4 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[5] && sub5 != true)
							{
								sub5 = true;
								check = check + 1;
							}
						}
						if (check == 4)
						{
							int valid = Ht.find(userInput);
							if (valid != -1)
							{
								if (WordCollection.find(userInput) == false)
								{
									WordCollection.insert(userInput);
									score = score + 23;
								}
							}
						}

					}
					else if (userInput.length() == 3)
					{
						bool sub0, sub1, sub2, sub3, sub4, sub5;
						sub0 = false;
						sub1 = false;
						sub2 = false;
						sub3 = false;
						sub4 = false;
						sub5 = false;
						int check = 0;
						for (int i = 0; i < 3; i++)
						{
							if (userInput[i] == scrambled[0] && sub0 != true)
							{
								sub0 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[1] && sub1 != true)
							{
								sub1 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[2] && sub2 != true)
							{
								sub2 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[3] && sub3 != true)
							{
								sub3 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[4] && sub4 != true)
							{
								sub4 = true;
								check = check + 1;
							}
							else if (userInput[i] == scrambled[5] && sub5 != true)
							{
								sub5 = true;
								check = check + 1;
							}
						}
						if (check == 3)
						{
							int valid = Ht.find(userInput);
							if (valid != -1)
							{
								if (WordCollection.find(userInput) == false)
								{
									WordCollection.insert(userInput);
									score = score + 5;
								}
							}
						}

					}
				}
				userInput.clear();
			}
			if (GetAsyncKeyState(VK_BACK))
			{
				if (!userInput.empty())
					userInput.erase(userInput.end() - 1, userInput.end());
			}

			LockWindowUpdate(GetConsoleWindow());
			// 3 - draw the screen
			system("cls");
			cout << "Time: " << 60 - bob.getElapsedTime() / 1000 << "\t\t\t\t\t\t\t    " << "Score: " << score;
			cout << "\n\n\n\n\n\n" << "\t\t\t\t    " << scrambled << "\n\n\n";
			cout << "Words inputed: ";
			WordCollection.printInOrder();
			cout << "\n\t\t\t\t" << userInput << '\n';
			LockWindowUpdate(NULL);
			bob.delay(100);
		}
		if (LevelUp == true)
		{
			system("cls");
			cout << "\n\n\n\n\n\n\n\n" << "\t\t" << "Congratulations, you found a six letter word!" << "\n";
			cout << "\t\t\t" << "Your current score is: " << score << "\n";
			cout << "\t\t" << "Press Enter to proceed to the next level!";
			while (true)
			{
				if (GetAsyncKeyState(VK_RETURN))
				{
					LevelUp = false;
					break;
				}
			}
		}
		else if (LevelUp == false)
		{
			char temp[32];
			string name;
			system("cls");
			cout << "\n\n\n\n\n\n\n\n" << "\t\t\t" << "Game Over!" << "\n";
			cout << "\t\t\t" << "The six letter word is: " << word << "\n";
			cout << "\t\t\t" << "Your  score is: " << score << "\n";
			cout << "\t\t\t" << "Please enter your name: ";
			cin.getline(temp, 32);
			name = temp;
			if (GameOver(name, score) == true)
			{
				run = false;
			}
			else
			{
				score = 0;
			}
		}
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);

	
	HTable<string> Dictionary = Load("engldict.txt", bucks);
	Dictionary.printSomeStuff();
	Game(Dictionary, bucks);
	Dictionary.clear();
	return 0;
}