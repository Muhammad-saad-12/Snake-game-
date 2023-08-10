#include <iostream>
#include <conio.h>
#include <vector> //Dynamic memory Allocation
#include <graphics.h>
#include <direct.h> // libs
#include <stdio.h>
#include <stdlib.h> //random number generation
#include <time.h>
#include <fstream>
#include <iomanip>
using namespace std;

void line()
{
	cout << setw(100)<<"*************************************************" << endl;
}
// Private password function ----------------------------------------------------------------------.
string hestric_pass()
{
	string pass = "";
	char ch;
	cout << "Enter pass\n";
	ch = _getch();
	while (ch != 13)
	{ // character 13 is enter
		pass.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	return pass;
}


class login     // LOGIN & Registration SYSTEM .
{		
	private:	   // Login Class
	int i = 0; //
	string name, n, pass, p;

public:
	void reg()
	{ // Registration Function.
		cout << "Enter UserName:";
		cin >> name;
		pass = hestric_pass(); // (*) password.
		ofstream file;		  // created a file
		file.open("log.txt"); // opened a file.
		file << name << endl
			 << pass << endl; // stored data in file.
		file.close();		  // closed the file.
	}

	bool log()
	{ // Login Function.
		cout << "Enter UserName:";
		cin >> name;
		pass = hestric_pass();  // (*) password.
		ifstream infile;         //Opened a file.
		infile.open("log.txt"); // open previous file for reading
		getline(infile, n);		//coying data from file to variable
		getline(infile, p);		////coying data from file to variable
		if (n == name && p == pass)
		{
			return true;
		}
		else
		{
			return false;
		}
		infile.close();//close the file.
	}

	void search(string nem)
	{ // Search if forget login data.
		int count = 0;
		ifstream infile;
		infile.open("log.txt");
		while (infile >> name >> pass)
		{
			if (nem == name)
			{
				count = 1;
			}
			else
			{
				cout << "Try again" << endl;
			}
		}
		if (count == 1)
		{
			cout << "Entered user name is valid" << endl;
			cout << "Here is your password:" << pass << endl;
		}
		infile.close();
	}
};

void menu()  // Login & registration Menu.
{
	cout << endl
		 << "To Run this Program you have to first loggin................." << endl;
	cout << "press 1 to register" << endl;
	cout << "press 2 to login" << endl;
	cout << "Press 3 if you forgot your password" << endl;
	cout << "Press 4 if you want to exit" << endl;
}


void Game_instructions() // snake game instructions.
{
	cout << "use the W Key Word for up." << endl;
	cout << "use the d Key Word for right." << endl;
	cout << "use the s Key Word for down." << endl;
	cout << "use the a Key Word for feft." << endl
		 << endl;
	cout << "Press C Key Word to Pause the game" << endl;
	cout << "Press P Key Word to continue the game" << endl;
}

int Snake_menu()
{ // Snake Game menu
	int s_choice;
	line();
	cout <<setw(106)<<"Welcome to Slithering Fun: The Easy Snake Adventure Game " << endl
		 << endl;
	line();
	cout << endl
		 << endl;
	line();
	cout <<setw(80)<<"GAME MENU" << endl;
	line();
	cout <<setw(80)<<"1.PLAY GAME" << endl;
	cout <<setw(80)<<"2.SCORE CARD" << endl;
	cout <<setw(80)<<"3.INSTRUCTIONS"<<endl;
	cout <<setw(80)<<"4.CLOSE GAME" << endl
		 << endl;
	cout << "Enter your choice" << endl;
	cin >> s_choice;
	return s_choice;
}

int lenght = 2;
int lenghtmax = 2; // controls snake's lenght

int x1 = 30;
int y1 = 170; // snake's location

char direc = '-'; // point
char last = '-';  // direction//point

bool playing = true; // if you are alive

int fruitx;
int fruity;
bool eaten = false; // fruit position

vector<int> snakex;
vector<int> snakey; // where your tail needs to go

int i = 1;
int imax = 0; // some basic for() things

char score[50];
int score1; // your score

void fruit();
void graphic();
void move();
void start();
void update(); // all voids

int main()
{
//Login page---------------------------------------------=Login page----------------------------------
login:
	int c, s_cho; 
	login p1; //Object Variable.
	while (true)
	{
		system("CLS");
		menu();  //Calling login page menu
		cin >> c; //Taking choice.
		if (c == 1)
		{
			system("CLS");
			cout << endl
				 << "Enter the input for registration................." << endl;
			p1.reg();
			main();// again to Login page menu.
		}

		if (c == 2)
		{
			system("CLS");
			ifstream infile("log.txt");//opened a file
			if (infile.is_open()) 
			{
				cout << endl
					 << "Enter the input for Login......................." << endl;
				bool res;
				res = p1.log();
				if (!res)
				{
					cout << "Try Again" << endl;
					system("PAUSE");
					main();
				}
				else
				{
					cout << endl
						 << "Congratulations you have been successfully logged in" << endl;
					system("PAUSE");
				}
				break;
			}
			else
			{
				cout << "You have first register to login" << endl;
				system("PAUSE");
				main();
			}
		}

		if (c == 3)
		{
			string na;
			system("CLS");
			cout << "Search your password by entering your name:";
			cin >> na;
			p1.search(na);
			system("PAUSE");
			main();
		}

		if (c == 4)
		{
			system("PAUSE");
			exit(0);
		}

		else
		{
			cout << "Invalid number" << endl;
			system("PAUSE");
			main();
		}
	}
// -----------------------------------------snake game Page----------------------------------------
snake:
Snake:
	system("CLS");
	s_cho = Snake_menu();
	switch (s_cho)
	{
	case 1:
		start();

		while (playing == true)
		{
			update();

			if (x1 >= 340 || x1 < 0 || y1 >= 340 || y1 < 10) // check if you are inside the map
			{
				playing = false; // you die :P
			}

			if (lenghtmax > 3 || direc != '-' && direc != 'w' && direc != 'a' && direc != 's' && direc != 'd' && direc != 'W' && direc != 'A' && direc != 'S' && direc != 'D')
			{
				for (lenght = lenghtmax; lenght >= 0; lenght--)
				{
					if (x1 == snakex[i] && y1 == snakey[i])
					{
						playing = false; // check if you head hits your tail
					}

					i--;
				}

				i = imax;
			}
		}

		if (playing == false)
		{
			char b;
			cleardevice();
			outtextxy(70, 170, "YOU LOST, YOUR ");
			outtextxy(188, 170, score);
			outtextxy(70, 170, "Press b to goo back");
			cin >> b;
			if (b == 'b')
			{
				goto Snake;
			}
			getch();
			getch();
		}
		break;

	case 2:
		break;
	case 3:
		char word;
		Game_instructions();
		cout << "Press (y) to go back";
		cin >> word;
		if (word == 'y' || word == 'Y')
		{
			goto snake;
		}
		break;
	case 4:
		goto login;
		break;
	}
}
// snake game Functions-----------------------------------------------------------------------------------------
void start() // execute at the start of the game
{
	sprintf(score, "SCORE : %d ", score1);

	srand(time(NULL));
	initwindow(350, 354, "SnakeGame");

	setcolor(WHITE);
	setfillstyle(SOLID_FILL, BLACK);
	rectangle(0, 0, 340, 10);
	floodfill(5, 5, BLACK);

	setcolor(LIGHTBLUE);
	outtextxy(10, 0, score);

	fruitx = rand() % 34;
	fruity = rand() % 34;
	fruity = fruity * 10;
	fruitx = fruitx * 10;

	if (fruity == 0)
	{
		fruity = fruity + 10;
	}

	setcolor(YELLOW);
	setfillstyle(SOLID_FILL, BLACK);
	rectangle(fruitx, fruity, fruitx + 10, fruity + 10);
	floodfill(fruitx + 5, fruity + 5, RED);
}

void update() // execute every frame
{
	sprintf(score, "SCORE : %d ", score1);

	delay(150);

	snakex.push_back(x1);
	snakey.push_back(y1); // makes your tail know the way to your head

	fruit();

	move();

	graphic();
}

void move() // all move related things
{
	if (kbhit())
	{
		direc = getch();
	}

	if (direc == 'w' && last == 's' || direc == 'W' && last == 'S')
	{
		direc = last;
	}

	if (direc == 'a' && last == 'd' || direc == 'A' && last == 'D')
	{
		direc = last;
	}

	if (direc == 's' && last == 'w' || direc == 'S' && last == 'W')
	{
		direc = last;
	}

	if (direc == 'd' && last == 'a' || direc == 'D' && last == 'A')
	{
		direc = last;
	}

	last = direc;

	if (direc == 's' || direc == 'S')
	{
		y1 = y1 + 10;
	}

	if (direc == 'a' || direc == 'A')
	{
		x1 = x1 - 10;
	}

	if (direc == 'w' || direc == 'W')
	{
		y1 = y1 - 10;
	}

	if (direc == 'd' || direc == 'D')
	{
		x1 = x1 + 10;
	}
}

void graphic() // the graphic
{
	cleardevice();

	setcolor(CYAN);
	setfillstyle(SOLID_FILL, CYAN);
	rectangle(0, 0, 350, 10); // green line
	floodfill(5, 5, CYAN);

	setcolor(BLUE);
	outtextxy(10, 0, score); // score

	setcolor(LIGHTGREEN);
	setfillstyle(SOLID_FILL, RED);
	rectangle(fruitx, fruity, fruitx + 10, fruity + 10); // fruit
	floodfill(fruitx + 5, fruity + 5, LIGHTGREEN);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	rectangle(x1, y1, x1 + 10, y1 + 10); // head
	floodfill(x1 + 5, y1 + 5, WHITE);

	for (int lenght = lenghtmax; lenght > 0; lenght--)
	{
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		rectangle(snakex[i], snakey[i], snakex[i] + 10, snakey[i] + 10); // tail
		floodfill(snakex[i] + 5, snakey[i] + 5, WHITE);
		i--;
	}

	imax++;
	i = imax;
}

void fruit() // fruit things
{
	if (x1 == fruitx && y1 == fruity)
	{
		eaten = true;
	}

	if (eaten == true)
	{
		eaten = false;
		lenghtmax++;
		score1++;
		lenght = lenghtmax;
		fruitx = rand() % 34;
		fruity = rand() % 34;
		fruity = fruity * 10;
		fruitx = fruitx * 10; // random location

		for (lenght = lenghtmax; lenght >= 0; lenght--)
		{
			if (fruitx == snakex[i] && fruity == snakey[i])
			{
				fruitx = rand() % 34;
				fruity = rand() % 34;
				fruity = fruity * 10;
				fruitx = fruitx * 10; // don't spawn the fruit on the snake
			}

			i--;
		}

		if (fruity == 0)
		{
			fruity = 10;
		}

		i = imax;

		setcolor(RED);
		setfillstyle(SOLID_FILL, RED);
		rectangle(fruitx, fruity, fruitx + 10, fruity + 10); // makes fruit
		floodfill(fruitx + 5, fruitx + 5, RED);
	}
}