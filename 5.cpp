#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

CONST int mapX = 60;
CONST int mapY = 13;

int paddleY1 =mapY/2;
int paddleY2 =mapY/2;

void gotoxy(short x, short y) {
	COORD coord = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void map(int x,int y) {
	for(int i=0;i<x+2;i++) {
		cout << "#";	
	}
	cout << endl;
	for(int i=0;i<y;i++) {
		cout << "#";
		for(int j=0;j<x;j++) {
			cout << " ";
		}
		cout << "#" << endl;		
	}
	for(int i=0;i<x+2;i++) {
		cout << "#";	
	}	
	cout << endl;
}

void paddle(bool side, int y) {
	if (y>0 && y<mapY-1) {
		if (side == 0) {
			for(int i=y-3;i<y+4;i++) {
				gotoxy(1,i+1);
				cout << " ";
			}
			for(int i=y-1;i<y+2;i++) {
				gotoxy(1,i+1);
				cout << "$";
			}
		} else if (side == 1) {
			for(int i=y-1;i<y+2;i++) {
				gotoxy(mapX-1,i+1);
				cout << "$" << endl;
			}	
		}
	}
}

int main(int argc, char** argv) {
	
	map(mapX,mapY);
	paddle(0,paddleY1);
	paddle(1,paddleY2);
	
	char ch;
	
	do {
		ch = _getch();
		if(ch == 'w') {
		    paddleY1=paddleY1-1;
			paddle(0,paddleY1);
		} else if(ch == 's') {
			paddleY1 = paddleY1 + 1;
			paddle(0,paddleY1+1);
		}
	} while(1);
	
	gotoxy(0,30);

	return 0;
}
