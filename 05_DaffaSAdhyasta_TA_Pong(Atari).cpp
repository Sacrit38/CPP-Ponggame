//Daffa Salmanaufal Adhyasta
//X RPL A
/*===============
  |
       PONG
                | 
  ===============*/
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
using namespace std;

//Variables
//Screen
#define SCRHEIGHT 25
#define SCRWIDTH 75

//Skoring
int Skorlimit;
int Skor[2] = {0, 0};

//Bola
int Bolposx;
int Bolposy;
int Boldir = 1;

//Player
#define PYRLENGTH 4
char Pyr1a, Pyr1b, Pyr2a, Pyr2b;
int Pyrpos1 = 1, Pyrpos2 = 1;
float Delay = 100;

//Prototipe
void Titlemenu();
void Pregame();
void Game();
void setcsr(int,int);

//Definisi fungsi
int main()
{
	char Jawaban;
	//Urutan scene:
	do
	{
		Titlemenu();
		Pregame();
		Game();
		//Menentukan pemenang
		system("cls");
		if(Skor[0] == Skorlimit)
		{
			cout<<"Player 1 menang!\n";
		}
		if(Skor[1] == Skorlimit)
		{
			cout<<"Player 2 menang!\n";
		}
		//then replay to titlemenu:
		cout<<"Main lagi?(Y/N)";
		cin>>Jawaban;
		if(Jawaban != 'Y' && Jawaban != 'y')
		{
			break;
		}
	}while(1);
}

void Titlemenu()
{
	//Border-making
	for(int i = 0; i <= SCRHEIGHT; i+= SCRHEIGHT)
	{
		setcsr(0, i);
		for(int j = 0; j <= SCRWIDTH; j++)
		{
			cout<<"=";
		}
	}
	for(int i = 1; i < SCRHEIGHT; i++)
	{
		setcsr(0, i);
		cout<<"|";
		setcsr(SCRWIDTH, i);
		cout<<"|";
	}
	//Title
	for(int h = -8; h<=2; h++)
	{
		setcsr(SCRWIDTH/2-13, SCRHEIGHT/2 + h);
		switch(h)
		{
			case -8:cout<<"==========================="; break;
			case -7:cout<<"PPPP   OOOO   NN  N   GGGGG"; break;
			case -6:cout<<"P  PP OO  OO  NN  N  GG    "; break;
			case -5:cout<<"P  PP OO  OO  N N N  GG    "; break;
			case -4:cout<<"PPPP  OO  OO  N N N  GG GGG"; break;
			case -3:cout<<"PP    OO  OO  N N N  GG  GG"; break;
			case -2:cout<<"PP    OO  OO  N  NN  GG  GG"; break;
			case -1:cout<<"PP     OOOO   N  NN   GGGG "; break;
			case  0:cout<<"==========================="; break;
			//Start
			case 2:
				cout<<"---Press Enter to Start---";
				char Anykey[1];
				scanf("%[^\n]", Anykey); 
				break;
		}
	}
	
}

void Pregame()
{
	system("cls");
	cout<<"Konfigurasi kontrol\n";

	cout<<"Player 1:\n";
	cout<<"Tombol 1 (Naik): ";
	cin>>Pyr1a;
	cout<<"Tombol 2 (Turun): ";
	cin>>Pyr1b;
	
	cout<<"Player 2:\n";
	cout<<"Tombol 1 (Naik): ";
	cin>>Pyr2a;
	cout<<"Tombol 2 (Turun): ";
	cin>>Pyr2b;
	
	cout<<endl<<"Bermain sampai skor: ";
	cin>>Skorlimit;
	
}

//Permainan
//Prototipe
void Input();
void Ball();
void Scoring(int);

//Definisi
void Game()
{
	//Arena
	system("cls");
	for(int i = 0; i <= SCRHEIGHT; i+= SCRHEIGHT)
	{
		setcsr(0, i);
		for(int j = 0; j <= SCRWIDTH; j++)
		{
			cout<<"=";
		}
	}
	// Menggambar skor awal:
	Scoring(0);
	//Proses permainan:
	do
	{
		Input();
		Ball();
	}while(Skor[0] != Skorlimit && Skor[1] != Skorlimit);
}

void Input()
{
	if(kbhit())
	{
		char key = getch();
		
		if(key == Pyr1a && Pyrpos1 > 1)
		{
			Pyrpos1--;
			setcsr(0, Pyrpos1 + PYRLENGTH);
			cout<<" ";
		}
		else
		if(key == Pyr1b && Pyrpos1 + PYRLENGTH < SCRHEIGHT)
		{
			Pyrpos1++;
			setcsr(0, Pyrpos1 - 1);
			cout<<" ";
		}
		else
		if(key == Pyr2a && Pyrpos2 > 1)
		{
			Pyrpos2--;
			setcsr(SCRWIDTH, Pyrpos2 + PYRLENGTH);
			cout<<" ";
		}
		else
		if(key == Pyr2b && Pyrpos2 + PYRLENGTH < SCRHEIGHT)
		{
			Pyrpos2++;
			setcsr(SCRWIDTH, Pyrpos2 - 1);
			cout<<" ";
		}
	}
	for(int i = 0; i < PYRLENGTH; i++)
	{
		setcsr(0, Pyrpos1 + i);
		cout<<"|";
		setcsr(SCRWIDTH, Pyrpos2 + i);
		cout<<"|";
	}
}

void Ball()
{
	//Gerakan bola
	//Menghapus bola
	setcsr(Bolposx, Bolposy);
	cout<<" ";
	//Mengarahkan bola
	switch(Boldir)
	{
		/*
		1 kiri-atas
		2 kanan-atas
		3 kiri-bawah
		4 kanan-bawah
		*/
		case 1:
			Bolposy--;
			Bolposx--;
			break;
		case 2:
			Bolposy--;
			Bolposx++;
			break;
		case 3:
			Bolposy++;
			Bolposx--;
			break;
		case 4:
			Bolposy++;
			Bolposx++;
			break;
	}
	//Menggambar bola
	setcsr(Bolposx, Bolposy);
	cout<<"O";
	
	//Merubah arah bola
	if(Bolposy == 1)
	{
		Boldir += 2;
		Delay--;
	}
	else
	if(Bolposy == SCRHEIGHT - 1)
	{
		Boldir -= 2;
		Delay--;
	}
	//Tertangkap player
	if(Bolposx == 1)
	{
		if(Bolposy >= Pyrpos1 && Bolposy < (Pyrpos1 + PYRLENGTH))
		{
			Boldir += 1;
			Delay--;
		}
		else
		{
			Scoring(2);
		}
	}
	if(Bolposx == SCRWIDTH - 1)
	{
		if(Bolposy >= Pyrpos2 && Bolposy < (Pyrpos2 + PYRLENGTH))
		{
			Boldir -= 1;
			Delay--;
		}
		else
		{
			Scoring(1);
		}
	}
	Sleep(Delay);
}

void Scoring(int Pyr)
{
	//Penambahan skor
	Pyr ? Skor[Pyr - 1]++ : 0;
	//Penampilan skor
	setcsr(SCRWIDTH / 2 - 2 , SCRHEIGHT + 1);
	cout<<"|"<<Skor[0]<<"|"<<Skor[1]<<"|";
	setcsr(SCRWIDTH / 2 - 2 , SCRHEIGHT + 2);
	cout<<"\\___/";
	//Bola balik ke tengah 
	setcsr(Bolposx, Bolposy);
	cout<<" ";
	Bolposx = SCRWIDTH/2;
	Bolposy = SCRHEIGHT/2;
	Ball();
	Delay = 100;
	Sleep(1000);
}

void setcsr(int x, int y)
{
	HANDLE handle;
	COORD coord;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}
