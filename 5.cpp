#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

CONST int mapX = 60;
CONST int mapY = 13;

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

class paddle {
	private:
	short side = 0;
	short posY = 1, paddleSize = 3;
	
	void render() {
		if (posY>0 && posY<mapY-1) {
			if (side == 0) {
				for(int i=1;i<mapY+1;i++) {
					gotoxy(1,i);
					cout << " ";	
				}
				for(int i=0;i<paddleSize;i++) {
					gotoxy(1,posY+i);
					cout << "$";
				}
			} else if (side == 1) {
				for(int i=1;i<mapY+1;i++) {
					gotoxy(mapX,i);
					cout << " ";	
				}
				for(int i=0;i<paddleSize;i++) {
					gotoxy(mapX,posY+i);
					cout << "$";
				}	
			}
		}
	}
		
	public:	
	paddle(short side) {
		this->side = side;
		posY = mapY/2;
		render();
	}
	
	short getPosY() {
		return posY;
	}
	
	void move(string way) {
		if(way == "up") {
			posY--;
			render();
		} else if(way == "down") {
			posY++;
			render();
		}
	}	

};

int main(int argc, char** argv) {
	
	map(mapX,mapY);
	paddle* PaddleLeft = new paddle(0);
	paddle* PaddleRight = new paddle(1);
	
	char ch;
	
	do {
		ch = _getch();
		if(ch == 'w') {
		    PaddleLeft->move("up");
		} else if(ch == 's') {
			PaddleLeft->move("down");
		} else if(ch == 'i') {
			PaddleRight->move("up");
		} else if(ch = 'k') {
			PaddleRight->move("down");
		}
	} while(ch != 'p');
	
	gotoxy(0,30);

	return 0;
}
