#include<iostream>  //������ C++
#include<time.h>    //������ srand
#include<Windows.h>
#include<fstream>   //������ � ������� 
#include<cstdlib>
#include<conio.h>   //��������� ������� _getch

using namespace std;

char input = 0;
enum Fillers { ROCK = 35, PLAYER = 164, TELEPORT = 169 };
enum Directions { LEFT = 97, RIGHT = 100, UP = 119, DOWN = 115, QUIT = 113 };
char map[10][30];
bool mapUnlocks[10][30] = {false};
int wormX = 1;
int wormY = 4;
int playerX = 1;
int playerY;

void LevelGenerate() 
{
	//���������� �������
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 30; j++) 
		{
			map[i][j] = ROCK;
		}
	}

	//�������� �����
	while (true) 
	{
		//�������� "�����"
		map[4][1] = ' ';
		//��������
		int moveTo = rand() % 3; // 0 - �����, 1 - ������, 2 - ����
		if (moveTo == 0) 
		{
			if (map[wormY - 1][wormX] == ROCK) 
			{
				if (wormY != 1) 
				{
					wormY--;
					map[wormY][wormX] = ' ';
				}
			}
		}
		if (moveTo == 1)
		{
			if (map[wormY][wormX+1] == ROCK)
			{
				wormX++;
				map[wormY][wormX] = ' ';
			}
		}
		if (moveTo == 2)
		{
			if (map[wormY+1][wormX] == ROCK)
			{
				if (wormY != 8) 
				{
					wormY++;
					map[wormY][wormX] = ' ';
				}
			}
		}
		//��������� ����
		int randWay = rand() % 5;
		if (randWay == 4) 
		{
			for (int i = wormY; i < 10 - wormY; i++) 
			{
				map[i][wormX] = ' ';
			}
			map[0][wormX] = ROCK;
			map[9][wormX] = ROCK;
		}

		//���� �� �����
		bool isCompleted = false;
		for (int i = 0; i < 10; i++) 
		{
			if (map[i][29] == ' ') 
			{
				isCompleted = true;
				break;
			}
		}
		if (isCompleted) 
		{
			ofstream saveFile("LevelExample.txt");
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 30; j++)
				{
					saveFile << map[i][j];
				}
				saveFile << endl;
			}
			saveFile.close();
			break;
		}

	}

	//�������� ������
	for (int i = 0; i < 10; i++)
	{
		if (map[i][1] == ' ')
		{
			map[i][1] = PLAYER;
			playerY = i;
			break;
		}
	}
}

void UpdateScreen() 
{
	//������� ������
	system("cls");
	cout << "q - �����\n";
	//������������� �����
	mapUnlocks[playerY][playerX] = true;
	mapUnlocks[playerY][playerX+1] = true;
	mapUnlocks[playerY+1][playerX] = true;
	mapUnlocks[playerY+1][playerX + 1] = true;
	mapUnlocks[playerY][playerX - 1] = true;
	mapUnlocks[playerY - 1][playerX] = true;
	mapUnlocks[playerY - 1][playerX - 1] = true;
	//����� �� �����
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 30; j++) 
		{
			if (mapUnlocks[i][j]) cout << map[i][j];
			else cout << '?';
		}
		cout << endl;
	}
}

void StartGame() 
{
	while (input != QUIT)
	{
		input = _getch();
		//������
		if (input == RIGHT)
		{
			if (map[playerY][playerX + 1] == ' ')
			{
				map[playerY][playerX] = ' ';
				playerX++;
				map[playerY][playerX] = PLAYER;
				UpdateScreen();
			}
		}
		//�����
		if (input == LEFT)
		{
			if (map[playerY][playerX - 1] == ' ')
			{
				map[playerY][playerX] = ' ';
				playerX--;
				map[playerY][playerX] = PLAYER;
				UpdateScreen();
			}
		}
		//�����
		if (input == UP)
		{
			if (map[playerY - 1][playerX] == ' ')
			{
				map[playerY][playerX] = ' ';
				playerY--;
				map[playerY][playerX] = PLAYER;
				UpdateScreen();
			}
		}
		//����
		if (input == DOWN)
		{
			if (map[playerY + 1][playerX] == ' ')
			{
				map[playerY][playerX] = ' ';
				playerY++;
				map[playerY][playerX] = PLAYER;
				UpdateScreen();
			}
		}
		//������ �� ����� ��������
		if (playerX == 29) break;
	}
}

void LoadLevel(string levelName)
{
	ifstream file(levelName + ".txt");
	if (!file)
	{
		LevelGenerate();
		UpdateScreen();
		StartGame();
		cout << "���� �� ��� ������, ������ ��������� �������";
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				file >> map[i][j];
			}
		}
		//�������� ������
		for (int i = 0; i < 10; i++)
		{
			if (map[i][1] == ' ')
			{
				map[i][1] = PLAYER;
				playerY = i;
				break;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				mapUnlocks[i][j] = true;
			}
		}
		UpdateScreen();
		StartGame();
	}
}

int main() 
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	while (input != QUIT) 
	{
		cout << "1. ������\n";
		cout << "2. ���������\n";
		cout << "3. �����\n";
		input = _getch();
		if (input == '1')
		{
			LevelGenerate(); //�������� ������
			UpdateScreen(); //���������� ������
			StartGame();
		}
		else if (input == '2') 
		{
			system("cls");
			string levelName = "";
			cout << "������� �������� ������: ";
			cin >> levelName;
			LoadLevel(levelName);
		}
		else if (input == '3') break;
	}

	system("pause");
	return 0;
}