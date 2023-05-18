#include<iostream>
#include<iomanip>//for manipulating output
#include<cstdlib>
#include<ctime>
#include<fstream>//for file handling
#include<windows.h>
#include<string>
using namespace std;
void Display();//displays main menu
void exit();//used to exit the game 
void record();//writing records on the file
void viewRecord();//viewing records from file
void player1Turn();
void player2Turn();
void score1Check();
void score2Check();
void instructions();// how to play
void mainBoards();//making two boards with 25 random values
void playGame();//whole game functioning
void winnerCheck();//scores are compared to declare winner
const int ROW = 5, COL = 5;//global declarations 
int firstCard[ROW][COL], secondCard[ROW][COL], toss, choice1, choice2, score1, score2, temp, gameId, count1 = 0, count2 = 0, numberOfturns1 = 0, numberOfturns2 = 0, arr1[25] = { 0 }, arr2[25] = { 0 };
string name1, name2;
bool flag = false;
void mainBoards()
{
	srand(time(0));//for differnt random numbers every time
	system("color CF");//colors of the cards
	while (count1 < 25)
	{
		flag = false;
		temp = (rand() % 25) + 1;
		for (int i = 0; i < 25 && flag == false; i++)
		{
			if (temp == arr1[i])
			{
				flag = true;										//getting a 1D array and storing 25 random and non repeating values in it
			}
		}
		if (!flag)
		{
			arr1[count1] = temp;
			count1++;
		}
	}
	int k = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL && k < 25; j++)
		{
			firstCard[i][j] = arr1[k];							//putting values of first 1D in firstcard
			k++;
		}
	}
	while (count2 < 25)
	{
		flag = false;
		temp = (rand() % 25) + 1;
		for (int i = 0; i < 25 && flag == false; i++)
		{
			if (temp == arr2[i])
			{
				flag = true;										//getting a second 1D array and storing 25 random and non repeating values in it
			}
		}
		if (!flag)
		{
			arr2[count2] = temp;
			count2++;
		}
	}
	int f = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL && f < 25; j++)
		{
			secondCard[i][j] = arr2[f];										//putting values of second 1D array in secondcard
			f++;
		}
	}
}
void playGame()
{
	mainBoards();
	system("cls");
	srand(time(0));
	gameId = 1 + rand() % 10000001;
	toss = rand() % 2;
	if (toss == 1)
	{
		player1Turn();
	}
	else
	{
		player2Turn();
	}
}
void player1Turn()
{
	while (numberOfturns1 < 12)
	{
		cout << "Game Id : " << gameId << endl << endl;
		for (int i = 0; i < ROW; i++)
		{
			cout << "\t\t";
			for (int j = 0; j < COL; j++)
			{
				cout << "\t" << "|" << setw(2) << firstCard[i][j] << "|";
				cout << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << name1 << " please choose your number : " << endl;				//getting choice of player 1
		cin >> choice1;
		while (cin.fail())														//exception handling
		{
			cin.clear();
			cin.ignore();
			cout << "Bad entry . Enter a NUMBER: ";
			cin >> choice1;
		}
		if (choice1 > 0 && choice1 < 26)
		{
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					if (firstCard[i][j] == choice1)
					{
						firstCard[i][j] = 0;								//replacing choice of first player in both cards
					}
					if (secondCard[i][j] == choice1)
					{
						secondCard[i][j] = 0;
					}
				}
			}
		}
		else
		{
			do
			{
				cout << "Enter correct choice : " << endl;
				cin >> choice1;
				while (cin.fail())											//exception handling
				{
					cin.clear();
					cin.ignore();
					cout << "Bad entry.  Enter a NUMBER: ";
					cin >> choice1;
				}
			} while (choice1 > 25 || choice1 < 0);
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					if (firstCard[i][j] == choice1)
					{
						firstCard[i][j] = 0;								//replacing choice of first player in both cards
					}
					if (secondCard[i][j] == choice1)
					{
						secondCard[i][j] = 0;
					}

				}
			}
		}
		numberOfturns1++;
		score1Check();
		if (!(score1 >= 5))
		{
			system("cls");
			player2Turn();
		}
		else
		{
			numberOfturns1 = 0;
			numberOfturns2 = 0;
			winnerCheck();
		}
	}
}
void score1Check()
{
	score1 = 0;
	int count;
	for (int i = 0; i < ROW; i++)
	{
		count = 0;
		for (int j = 0; j < COL; j++)
		{
			if ((firstCard[i][j] != 0))
			{
				break;
			}
			else															//checking rows of firstcard
			{
				count++;
				if (count == 5)
				{
					score1++;
				}
			}
		}
	}
	for (int i = 0; i < ROW; i++)
	{
		count = 0;
		for (int j = 0; j < COL; j++)
		{
			if ((firstCard[j][i] != 0))
			{
				break;
			}
			else															//checking colums of first card
			{
				count++;
				if (count == 5)
				{
					score1++;
				}
			}
		}
	}
	if (firstCard[0][0] == 0 && firstCard[1][1] == 0 && firstCard[2][2] == 0 && firstCard[3][3] == 0 && firstCard[4][4] == 0)			//checkings diagonal of firstcard
	{
		score1++;
	}
	if (firstCard[0][4] == 0 && firstCard[1][3] == 0 && firstCard[2][2] == 0 && firstCard[3][1] == 0 && firstCard[4][0] == 0)
	{
		score1++;
	}

}
void player2Turn()
{
	while (numberOfturns2 < 12)
	{
		cout << "Game Id : " << gameId << endl << endl;
		for (int i = 0; i < ROW; i++)
		{
			cout << "\t\t";
			for (int j = 0; j < COL; j++)
			{
				cout << "\t" << "|" << setw(2) << secondCard[i][j] << "|";
				cout << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << name2 << " please choose your number : " << endl;
		cin >> choice2;															//getting choice of player 2
		while (cin.fail())															//exception handling
		{
			cin.clear();
			cin.ignore();
			cout << "Bad entry.  Enter a NUMBER: ";
			cin >> choice2;
		}
		if (choice2 > 0 && choice2 < 26 && choice2 != choice1)
		{
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					if (firstCard[i][j] == choice2)
					{
						firstCard[i][j] = 0;
					}															//replacing choice of first player in both cards
					if (secondCard[i][j] == choice2)
					{
						secondCard[i][j] = 0;
					}
				}
			}
		}
		else
		{
			do
			{
				cout << "Enter correct choice : " << endl;
				cin >> choice2;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Bad entry.  Enter a NUMBER: ";
					cin >> choice2;
				}

			} while (choice2 > 25 || choice2 < 0 || choice2 == choice1);
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					if (firstCard[i][j] == choice2)
					{
						firstCard[i][j] = 0;
					}
					if (secondCard[i][j] == choice2)
					{
						secondCard[i][j] = 0;
					}
				}
			}
		}
		numberOfturns2++;
		score2Check();
		if (!(score2 >= 5))
		{
			system("cls");
			player1Turn();
		}
		else
		{
			numberOfturns2 = 0;
			numberOfturns1 = 0;
			winnerCheck();
		}
	}
}
void score2Check()
{
	score2 = 0;
	int count;
	for (int i = 0; i < ROW; i++)
	{
		count = 0;
		for (int j = 0; j < COL; j++)
		{
			if ((secondCard[i][j] != 0))
			{
				break;
			}																	//checking rows of secondcard
			else
			{
				count++;
				if (count == 5)
				{
					score2++;
				}
			}
		}
	}
	for (int i = 0; i < ROW; i++)
	{
		count = 0;
		for (int j = 0; j < COL; j++)
		{
			if ((secondCard[j][i] != 0))
			{
				break;
			}
			else
			{																							//checking colums of first card
				count++;
				if (count == 5)
				{
					score2++;
				}
			}
		}
	}
	if (secondCard[0][0] == 0 && secondCard[1][1] == 0 && secondCard[2][2] == 0 && secondCard[3][3] == 0 && secondCard[4][4] == 0)		//checking diagonals of secondcard
	{
		score2++;
	}
	if (secondCard[0][4] == 0 && secondCard[1][3] == 0 && secondCard[2][2] == 0 && secondCard[3][1] == 0 && secondCard[4][0] == 0)
	{
		score2++;
	}
}
void winnerCheck()
{
	if (score1 > score2)
	{
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "_______________________________________________" << name1 << " Congrats you won the game" << "_________________________________________________" << endl;
		system("pause");
		system("cls");
	}
	else if (score2 > score1)
	{
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "________________________________________________" << name2 << " Congrats you won the game" << "________________________________________________" << endl;
		system("pause");
		system("cls");

	}
	record();					//moving to record function
}
void exit()					//for exiting out of the game
{
	cout << "\t\t\t\t\t\t You Have Exited The Game" << endl;
	cout << "\t\t\t\t\t\t Your Game Has Ended." << endl;
	exit(0);
}
void instructions()					//how to play
{
	cout << "___________________________________________________________________________________________________" << endl;
	cout << "1) You will be assigned a matrix of 5X5 with random values insreted and you have to input a number." << endl;
	cout << "2) If the number exists in the matrix then that number will be replaced by zero." << endl;
	cout << "3) The first player to make 5 rows,columns or a diagonal of zeros would win the game." << endl;
	cout << "4) The game would end only by Exit" << endl;
	cout << "___________________________________________________________________________________________________" << endl;
	system("pause");
	system("cls");
	Display();
}
void Display()						//main menu
{
	while (true)
	{
		system("color F0");
		cout << "----------------------------------------------------------------------------------------------------------------------- " << endl;
		cout << "\t\t\t\t\t\t WELCOME TO BINGO!" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------ " << endl;
		char ch;
		cout << "\t\t\t\t\t\t" << "Enter 1 to Play Game " << endl;
		cout << "\t\t\t\t\t\t" << "Enter 2 to View Record" << endl;
		cout << "\t\t\t\t\t\t" << "Enter 3 For How To Play?" << endl;
		cout << "\t\t\t\t\t\t" << "Enter 4 to Exit" << endl;
		cout << "\t\t\t\t\t\t";
		cin >> ch;
		cout << "------------------------------------------------------------------------------------------------------------------------ " << endl;
		switch (ch)
		{
		case '1':
			cout << "Enter name of first player : " << endl;
			cin >> name1;
			cout << "Enter name of second player : " << endl;
			cin >> name2;
			playGame();
			break;
		case '2':
			viewRecord();
			break;
		case '3':
			instructions();
			break;
		case '4':
			exit();
		default:
			cout << "Wrong Input" << endl;
			cout << "Select the option again!!" << endl;
			break;
		}
	}
}
void record()					//for storing scores and game ID in a file named record.txt
{
	ofstream fout;
	fout.open("record.txt", ios::app);
	if (!fout.is_open())
	{
		cout << "Error " << endl;
		system("pause");
		return;
	}
	fout << endl;
	fout << "Game ID : " << gameId << endl;
	fout << name1 << "'s Score : ";
	fout << score1 << endl;
	fout << name2 << "'s Score : ";
	fout << score2;
	cout << endl;
	cout << endl;
	fout.close();
	Display();
}
void viewRecord()								//for getting the previous record from record.txt file
{
	char ch;
	ifstream fin;
	fin.open("record.txt");
	if (!fin.is_open())
	{
		cout << "File Not Found";
		system("pause");
		return;
	}
	cout << endl;
	do
	{
		fin.get(ch);
		if (!fin.eof())
		{
			cout << ch;
		}
	} while (!fin.eof());
	cout << endl;
	fin.close();
	system("pause");
	system("cls");
}
int main()
{
	system("color 60");//colors of main menu
	Display();
	system("pause");
	return 0;
}
