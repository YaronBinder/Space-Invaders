#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

// defining playground size
constexpr int x = 60;
constexpr int y = (x / 2);

using std::cout;
using std::cin;
using std::endl;


bool Start()
{
	srand((int)time(NULL));
	int i, j, a, life = 5, score = 0, enemy_y = 1;
	int player_x = x / 2, player_y = y - 1, bullet_x = player_x, bullet_y = player_y - 1;
	char plr_key = 'p';
	char player[][5] = { {200,' ',202,' ',188}, {204,205,206,205,185}, {201,' ',203,' ',187} };
	char enemy[][3]{ {191,194,218},{217,193,192} };
	int EnemyRandPos_X = rand() % (x - 4) + 4;
	int SpaceDust_X[] = { rand() % (x - 4) + 2, rand() % (x - 7) + 2, rand() % (x - 11) + 2, rand() % (x - 17) + 2 };
	int SpaceDust_Y[] = { rand() % (y - 15) + 1, rand() % (y - 17) + 1, rand() % (y - 22) + 1, rand() % (y - 25) + 1 };
	bool GameOn = true;
	do {
		for (i = 0; i <= y; i++)
		{
			for (j = 0; j <= x; j++)
			{
				// Drawing walls
				if (!i || !j || j == x || i == y)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					cout << (char)177;
				}

				// Drawing bullet
				else if (bullet_x == j && bullet_y == i && plr_key == ' ')
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
					cout << (char)232;
				}

				// Drawing first row of the player
				else if (player_x == j - 2 && player_y == i)
				{
					cout << "\b\b\b\b";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					for (a = 0; a < 5; a++) cout << player[0][a];
				}

				// Drawing second row of the player
				else if (player_x == j - 2 && player_y == i + 1)
				{
					cout << "\b\b\b\b";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					for (a = 0; a < 5; a++) cout << player[1][a];
				}

				// Drawing third row of the player
				else if (player_x == j - 2 && player_y == i + 2)
				{
					cout << "\b\b\b\b";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					for (a = 0; a < 5; a++) cout << player[2][a];
				}

				// Drawing first row of the enemy
				else if (EnemyRandPos_X == j && enemy_y == i)
				{
					cout << "\b\b";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
					for (a = 0; a < 3; a++) cout << enemy[0][a];
				}

				// Drawing second row of the enemy
				else if (EnemyRandPos_X == j && enemy_y + 1 == i)
				{
					cout << "\b\b";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
					for (a = 0; a < 3; a++) cout << enemy[1][a];
				}

				// Spcae dust
				else if (SpaceDust_X[0] == j && i == SpaceDust_Y[0])
				{
					if(SpaceDust_Y[0] >= y - 2 || SpaceDust_X[0] >= x || SpaceDust_X[0] <= 1)
					{
						SpaceDust_Y[0] = 1;
						SpaceDust_X[0] = rand() % (x - 4) + 2;
						SpaceDust_Y[0] = rand() % (y - 26) + 1;
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << (char)250;
				}

				// Spcae dust 2
				else if (SpaceDust_X[1] == j && i == SpaceDust_Y[1])
				{
					if (SpaceDust_Y[1] >= y - 2 || SpaceDust_X[1] >= x || SpaceDust_X[1] <= 1)
					{
						SpaceDust_Y[1] = 1;
						SpaceDust_X[1] = rand() % (x - 7) + 2;
						SpaceDust_Y[1] = rand() % (y - 27) + 1;
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << (char)250;
				}

				// Spcae dust 3
				else if (SpaceDust_X[2] == j && i == SpaceDust_Y[2])
				{
					if (SpaceDust_Y[2] >= y - 2 || SpaceDust_X[2] >= x || SpaceDust_X[2] <= 1)
					{
						SpaceDust_Y[2] = 1;
						SpaceDust_X[2] = rand() % (x - 11) + 2;
						SpaceDust_Y[2] = rand() % (y - 28) + 1;
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << (char)250;
				}

				// Spcae dust 4
				else if (SpaceDust_X[3] == j && i == SpaceDust_Y[3])
				{
					if (SpaceDust_Y[3] >= y - 2 || SpaceDust_X[3] >= x || SpaceDust_X[3] <= 1)
					{			   	
						SpaceDust_Y[3] = 1;
						SpaceDust_X[3] = rand() % (x - 17) + 2;
						SpaceDust_Y[3] = rand() % (y - 29) + 1;
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << (char)250;
				}
				// Drawing empty space in the matrix
				else cout << " ";
			}

			cout << endl;

			// Bullet and enemy collision
			if ((enemy_y + 2 >= bullet_y && enemy_y <= bullet_y) && (bullet_x + 2 >= EnemyRandPos_X && bullet_x <= EnemyRandPos_X))
			{
				bullet_y = player_y - 1;
				enemy_y = 1;
				score++;
				EnemyRandPos_X = rand() % (x - 4) + 4;
				plr_key = 'p';
			}

			// Bullet and environment collision
			if (bullet_y <= 0)
			{
				bullet_y = player_y - 1;
				plr_key = 'p';
			}

			// Player and enemy or enemy and environment collision
			if (enemy_y + 3 == player_y && (player_x + 4 >= EnemyRandPos_X && player_x <= EnemyRandPos_X + 2)
				|| enemy_y == player_y && (player_x + 4 >= EnemyRandPos_X && player_x <= EnemyRandPos_X + 2)
				|| enemy_y >= y - 1)
			{
				life--;
				EnemyRandPos_X = (rand() % x - 10) + 5;
				enemy_y = 1;
				player_y = player_y + 1;
				plr_key = 'p';
			}
		}

		// Moving the space dust forward
		for (int a = 0; a < 4; a++)
			SpaceDust_Y[a] += 2;
		
		// moving the enemy forward
		enemy_y++;

		// Printing the Life and Score
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "Life left: " << life << endl;
		cout << "Score: " << score << endl;

		// Controls
		if (_kbhit())
			switch (_getch())
			{
				case 'a': plr_key = 'a'; break;
				case 'd': plr_key = 'd'; break;
				case 's': plr_key = 's'; break;
				case 'w': plr_key = 'w'; break;
				case 'p': plr_key = 'p'; break;
				case 'x': plr_key = 'x'; break;
				case ' ': plr_key = ' '; break;
			}
		
		switch (plr_key)
		{
			case 'a': player_x -= 2; bullet_y = player_y - 2; break;
			case 'd': player_x += 2; bullet_y = player_y - 2; break;
			case 's': player_y++; break;
			case 'w': player_y--; break;
			case 'p': player_y = player_y; player_x = player_x; break;
			case 'x': GameOn = false; break;
			case ' ': bullet_y--; bullet_x = player_x; break;
		}

		// Player Position collision
		if (player_x >= x - 3) player_x = x - 3;
		if (player_x <= 3) player_x = 3;
		if (player_y >= y - 1) player_y = y - 1;
		if (player_y <= 3) player_y = 3;

		Sleep(150);
		system("cls");

	} while (life && GameOn);

	if (!GameOn && life)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << "Good game" << endl;
	}
	else if (!life)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "YOU LOSE!!!" << endl;
	}
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Your score is: " << score << endl;
	return GameOn;
}

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Welcome to Space War" << endl;
	cout << "In this game you need to prevent from the enemy spaceship to pass by you" << endl;
	cout << "Every time the enemy spaceship colliding you or passing you, you lose 1 life" << endl;
	cout << "Use the wasd keys to move, space bar to shot, and x to exit" << endl;
	cout << "All of humanity trusts in you" << endl;
	cout << "Goodluck" << endl;
	cout << "Press any key to continue";
	(void)_getch();
	bool GameOn = Start();
	do {
		if (GameOn)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			cout << "Play again? Y/N" << endl;
			if (_getch() == 'Y' || _getch() == 'y') GameOn = Start();
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "Bye bye";
			}
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << "Bye bye";
		}
	} while (GameOn);
}