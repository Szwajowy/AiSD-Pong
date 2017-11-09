#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

void gotoxy(short x, short y) {
	COORD coord = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

short mapX = 60;
short mapY = 13;
char sign = '#';
	
void renderGUI() {
	for(int i=0;i<mapX+2;i++) {
		cout << sign;	
	}
	cout << endl;
	for(int i=0;i<mapY;i++) {
		cout << sign;
		for(int j=0;j<mapX;j++) {
			cout << " ";
		}
		cout << sign << endl;		
	}
	for(int i=0;i<mapX+2;i++) {
		cout << sign;	
	}	
	cout << endl;
}

class player {
	private:
	string name;
	short points;
	
	public:
	player() {
		name = "Player";
		points = 0;
	}
	
	player(string name, short points) {
		this->name = name;
		points = points;
	}
	
	void setName(string name) {
		this->name = name;
	}
	
	string getName() {
		return name;
	}
	
	void addPoint() {
		points++;
	}
};

class paddle :
	public player {
	private:
	short side = 0;
	short posY = 1, size = 3;
	char sign = '$';
	
	void render() {
			if (side == 0) {
				for(int i=1;i<mapY+1;i++) {
					gotoxy(1,i);
					cout << " ";	
				}
				for(int i=0;i<size;i++) {
					gotoxy(1,posY+i);
					cout << sign;
				}
			} else if (side == 1) {
				for(int i=1;i<mapY+1;i++) {
					gotoxy(mapX,i);
					cout << " ";	
				}
				for(int i=0;i<size;i++) {
					gotoxy(mapX,posY+i);
					cout << sign;
				}	
			}
	}
		
	public:	
	paddle(string name,short side) {
		setName(name);
		this->side = side;
		posY = mapY/2+1-size/2;
		render();
	}
	
	short getPosY() {
		return posY;
	}
	
	short getSize() {
		return size;
	}
	
	void move(string way) {
		if(way == "up") {
			if(posY > 1) {
				posY--;
				render();
			}
		} else if(way == "down") {
			if(posY < mapY+1-size) {
				posY++;
				render();
			}
		}
	}	

};

class ball {
	private:
	short posX, posY, angle = 45;
	string way = "left";
	bool hit;
	char sign = 'O';
	
	void render() {
		gotoxy(posX,posY);
		cout << sign;
	}
	
	public:
	ball() {
		posX = mapX/2+1;
		posY = mapY/2+1;
		render();
	}
	
	reset() {
		gotoxy(posX,posY);
		cout << " ";
		posX = mapX/2+1;
		posY = mapY/2+1;
		render();
	}
	
	move(paddle* PaddleLeft, paddle* PaddleRight) {
		gotoxy(posX,posY);
		cout << " ";
		hit = false; 
		if(way == "left") {
			if(posX > 2) {
				if (angle == 45) {
					posX--;
					posY--;
					render();
					if (posY == 1 ) {
						angle = 135;	
					} else if (posX == 2) {
						for(int i=0;i<PaddleLeft->getSize();i++){
							if (posY == PaddleLeft->getPosY()+i) {
								hit = true;
							}
						}
						if (hit == true) {
							way = "right";
						} else {
							PaddleLeft->addPoint();
							reset();
						}
					}
				} else if(angle == 90) {
					posX--;
					render();
				} else if(angle == 135) {
					posX--;
					posY++;
					render();
					if (posY == mapY ) {
						angle = 45;	
					} else if (posX == 2) {
						for(int i=0;i<PaddleLeft->getSize();i++){
							if (posY == PaddleLeft->getPosY()+i) {
								hit = true;
							}
						}
						if (hit == true) {
							way = "right";
						} else {
							PaddleRight->addPoint();
							reset();
						}
					}
				}
			}
		} else if(way == "right") {
			if(posX < mapX-1) {
				if (angle == 45) {
					posX++;
					posY--;
					render();
					if (posY == 1 ) {
						angle = 135;	
					} else if (posX == mapX-1) {
						for(int i=0;i<PaddleRight->getSize();i++){
							if (posY == PaddleRight->getPosY()+i) {
								hit = true;
							}
						}
						if (hit == true) {
							way = "left";
						} else {
							PaddleLeft->addPoint();
							reset();
						}
					}
				} else if(angle == 90) {
					posX++;
					render();
				} else if(angle == 135) {
					posX++;
					posY++;
					render();
					if (posY == mapY ) {
						angle = 45;	
					} else if (posX == mapX-1) {
						for(int i=0;i<PaddleRight->getSize();i++){
							if (posY == PaddleRight->getPosY()+i) {
								hit = true;
							}
						}
						if (hit == true) {
							way = "left";
						} else {
							PaddleLeft->addPoint();
							reset();
						}
					}
				}
			}
		}	
	}
};

int main(int argc, char** argv) {
	
	renderGUI();	
	
	paddle* PaddleLeft = new paddle("Player1",0);
	paddle* PaddleRight = new paddle("Player2",1);
	ball* Ball = new ball();
	
	gotoxy(0,mapY+3);
	cout << PaddleLeft->getName() << ": [w] up  [s] down   ";
	cout << PaddleRight->getName() << ": [i] up  [k] down" << endl;

	char ch;
	
	do {
		Ball->move(PaddleLeft, PaddleRight);
		gotoxy(0,mapY+3);
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
	
	gotoxy(0,mapY+3);

	return 0;
}
