#include<iostream>
#include<stdio.h>
#include<time.h>
using namespace std;

typedef void(*func)(int*, int*, char[][3]);

bool OnlyFullDiagonal(char Field[][3]) {
	if ((Field[0][0] == 'X' && Field[0][1] == ' ' && Field[0][2] == ' ' && 
		 Field[1][0] == ' ' && Field[1][1] == 'O' && Field[1][2] == ' ' &&
		 Field[2][0] == ' ' && Field[2][1] == ' ' && Field[2][2] == 'X') ||
		(Field[0][0] == ' ' && Field[0][1] == ' ' && Field[0][2] == 'X' &&
		 Field[1][0] == ' ' && Field[1][1] == 'O' && Field[1][2] == ' ' &&
		 Field[2][0] == 'X' && Field[2][1] == ' ' && Field[2][2] == ' ')) {
		return true;
	}
	else return false;
}

bool OneFieldPlayed(char Field[][3]) {
	int anzSpace = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (Field[i][j] == ' ') {
				anzSpace++;
			}
		}
	}
	if (anzSpace == 8) {
		return true;
	}
	else { return false; }
}

bool OppInCornerNotDiagonal(char Field[][3]) {
	if ((Field[2][0] == 'X' && Field[0][2] == ' ') || (Field[2][0] == ' ' && Field[0][2] == 'X')) {
		return true;
	}
	else return false;
}

bool OppInMiddleSpot(char Field[][3]) {
	if ((Field[1][0] == 'X' && Field[0][1] == ' ' && Field[1][2] == ' ' && Field[2][1] == ' ') || 
		(Field[1][0] == ' ' && Field[0][1] == 'X' && Field[1][2] == ' ' && Field[2][1] == ' ') || 
		(Field[1][0] == ' ' && Field[0][1] == ' ' && Field[1][2] == 'X' && Field[2][1] == ' ') || 
		(Field[1][0] == ' ' && Field[0][1] == ' ' && Field[1][2] == ' ' && Field[2][1] == 'X')) {
		return true;
	}
	else return false;
}

bool OppInCornerDiagonal(char Field[][3]) {
	if (Field[2][2] == 'X') {
		return true;
	}
	else return false;
}

bool comStarted(char Field[][3]) {
	int anzX = 0;
	int anzO = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (Field[i][j] == 'X') {
				anzX++;
			}
			else if (Field[i][j] == 'O') {
				anzO++;
			}
		}
	}
	if (anzO >= anzX) {
		return true;
	}
	else { 
		return false;
	}
}

bool checkEmpty(char Field[][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (Field[i][j] != ' ') {
				return false;
			}
		}
	}
	return true;
}

bool checkForTwo(int* row, int* column, char Field[][3], char sign) {
	int a, b, c, help;
	a = 0;
	b = 1;
	c = 2;
	//check Rows
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (Field[i][a] == Field[i][b] && Field[i][a] == sign && Field[i][c] == ' ') {
				*row = i+1;
				*column = c+1;
				return true;
			}
			help = a;
			a = b;
			b = c;
			c = help;
		}
	}
	//check Columns
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (Field[a][i] == Field[b][i] && Field[a][i] == sign && Field[c][i] == ' ') {
				*row = c+1;
				*column = i+1;
				return true;
			}
			help = a;
			a = b;
			b = c;
			c = help;
		}
	}
	//check Diagonals
		for (int j = 0; j < 3; j++) {
			if (Field[a][a] == Field[b][b] && Field[a][a] == sign && Field[c][c] == ' ') {
				*row = c+1;
				*column = c+1;
				return true;
			}
			help = a;
			a = b;
			b = c;
			c = help;
		}
		for (int j = 0; j < 3; j++) {
			if (Field[a][2-a] == Field[b][2-b] && Field[a][2-a] == sign && Field[c][2-c] == ' ') {
				*row = c + 1;
				*column = (2-c) + 1;
				return true;
			}
			help = a;
			a = b;
			b = c;
			c = help;
		}
	
	return false;
}

bool checkDraw(char Field[][3]) {
	for(int i=0; i<3;i++) {
		for (int j = 0; j < 3; j++) {
			if (Field[i][j]==' ') {
				return false; //Wenn irgendwo Space dann kein Draw
			}
		}
	}
	return true; //Wenn nirgends Space dann voll -> Draw
}

bool checkEnd(char Field[][3]) {
	if (Field[0][0] == Field[0][1] && Field[0][0] == Field[0][2] && Field[0][0] != ' ' ||
		Field[1][0] == Field[1][1] && Field[1][0] == Field[1][2] && Field[1][0] != ' ' ||
		Field[2][0] == Field[2][1] && Field[2][0] == Field[2][2] && Field[2][0] != ' ' ||
		Field[0][0] == Field[1][0] && Field[0][0] == Field[2][0] && Field[0][0] != ' ' ||
		Field[0][1] == Field[1][1] && Field[0][1] == Field[2][1] && Field[0][1] != ' ' ||
		Field[0][2] == Field[1][2] && Field[0][2] == Field[2][2] && Field[0][2] != ' ' ||
		Field[0][0] == Field[1][1] && Field[0][0] == Field[2][2] && Field[0][0] != ' ' ||
		Field[0][2] == Field[1][1] && Field[0][2] == Field[2][0] && Field[0][2] != ' ') {
		return true;
	}
	else return false;
}

void comFields(int* row, int* column, char Field[][3]) {
	if (checkForTwo(row, column, Field, 'O')) {
		return;
	}
	if (checkForTwo(row, column, Field, 'X')) {
		return;
	}
	if (checkEmpty(Field)) {
		*row = 1;
		*column = 1;
		return;
	}
	if (comStarted(Field)) {
		if (OppInCornerNotDiagonal(Field) && Field[2][2] == ' ') {
			*row = 3;
			*column = 3;
			return;
		}
		if (OppInMiddleSpot(Field) && Field[1][1] == 'O') {
			if (Field[1][0] == 'X') {
				*row = 1;
				*column = 2;
				return;
			}
			else {
				*row = 2;
				*column = 1;
				return;
			}
		}
		if (OppInMiddleSpot(Field) && Field[1][1] == ' ') {
			*row = 2;
			*column = 2;
			return;
		}
		if (OppInCornerDiagonal(Field)&&Field[2][0]=='O') {
			*row = 1;
			*column = 3;
			return;
		}
		if (OppInCornerDiagonal(Field) && Field[2][0] == ' ') {
			*row = 3;
			*column = 1;
			return;
		}
	}
	else {//Player hat angefangen
		if (OneFieldPlayed(Field) && Field[1][1] == ' ') {
			*row = 2;
			*column = 2;
			return;
		}
		if (OnlyFullDiagonal(Field)) {
			*row = 2;
			*column = 1;
			return;
		}
	}

	srand(time(NULL));
	while (true) {
		*row = rand() % 3 + 1;
		*column = rand() % 3 + 1;
		if (Field[*row - 1][*column - 1] == ' ') {
			return;
		}
	}
	
}

void playerFields(int* row, int* column, char Field[][3]) {
	srand(time(NULL));
	while (true) {
		cout << "Wo willst du dein Zeichen setzen?\n Zeile: ";
		cin >> *row;
		cout << "Spalte: ";
		cin >> *column;
		cout << "Es wurde Zeile " << *row << " und Spalte " << *column << " eingegeben.\n";
		if (*row < 1 || *row>3 || *column < 0 || *column>3) {
			cout << "Ungueltige Eingabe! Bitte erneut versuchen.\n";
			continue;
		}
		if (Field[*row - 1][*column - 1] == ' ') {
			return;
		}
		else {
			cout << "Da war schon ein Zeichen. Waehlen Sie bitte ein leeres Kaestchen.\n";
		}
	}
}

void printCurrentField(char Field[][3]) {
	system("cls");
	cout << "      1       2        3\n";
	cout << "  -------------------------\n";
	cout << "  |       |       |       |\n";
	cout << "1 |   "<<Field[0][0]<<"   |   "<<Field[0][1]<<"   |   "<<Field[0][2]<<"   |\n";
	cout << "  |       |       |       |\n";
	cout << "  -------------------------\n";
	cout << "  |       |       |       |\n";
	cout << "2 |   " << Field[1][0] << "   |   " << Field[1][1] << "   |   " << Field[1][2] << "   |\n";
	cout << "  |       |       |       |\n";
	cout << "  -------------------------\n";
	cout << "  |       |       |       |\n";
	cout << "3 |   " << Field[2][0] << "   |   " << Field[2][1] << "   |   " << Field[2][2] << "   |\n";
	cout << "  |       |       |       |\n";
	cout << "  -------------------------\n";
}

int whoStarts() {
	char input;
	cout << "Moechten Sie anfangen, der Computer oder soll gelost werden?\n";
	while (1) {
		cout << "C - Computer\nM - Mensch\nZ - Zufall\nEingabe:";
		cin >> input;
		if (input == 'C' || input == 'c') {
			cout << "Der Computer beginnt!\n";
			return -1;//Computer beginnt entspricht -1
		}
		else if (input == 'M' || input == 'm') {
			cout << "Sie beginnen!\n";
			return 1;//Mensch beginnt entspricht 1
		}
		else if (input == 'Z' || input == 'z') {
			cout << "Es wird gelost...\n";
			srand(time(NULL));
			int beginner = rand() % 2;
			if (beginner) {
				cout << "Sie beginnen!\n";
				return 1;
			}
			else {
				cout << "Der Computer beginnt!\n";
				return -1;
			}
		}
		else {
			cout << "Ungueltige Eingabe! Erneut versuchen:\n";
		}
	}

}

void Play(func PlayerOne, func PlayerTwo, int Beginner) {
	int currentPlayer = Beginner;
	char Field[3][3] = { {' ',' ',' '},{' ',' ',' '} ,{' ',' ',' '} };
	printCurrentField(Field);

	while (true) {
		int row, column;

		if (currentPlayer == 1) {
			//Spieler ist dran
			cout << "Spieler 1 ist dran: X\n";
			PlayerOne(&row, &column, Field);
			Field[row - 1][column - 1] = 'X';
			printCurrentField(Field);
			if (checkEnd(Field)) {
				//Sieg Spieler
				cout << "Herzlichen Glueckwunsch!\nSpieler 1 hat gewonnen!\n";
				return;
			}
			currentPlayer *= -1;
		}
		else if (currentPlayer == -1) {
			cout << "Spieler 2 ist dran: O\n";
			PlayerTwo(&row, &column, Field);
			Field[row - 1][column - 1] = 'O';
			printCurrentField(Field);
			if (checkEnd(Field)) {
				//Sieg Spieler
				cout << "Herzlichen Glueckwunsch!\nSpieler 2 hat gewonnen!\n";
				return;
			}
			currentPlayer *= -1;
		}

		if (checkDraw(Field)) {
			//Unentschieden
			cout << "Unentschieden! Keiner hat gewonnen.\n";
			return;
		}

	}

}

void GameMode() {
	char input;
	cout << "Moechten Sie gegen den Computer spielen oder gegen einen anderen Menschen?\n";
	while (1) {
		cout << "C - Computer\nM - Mensch\nEingabe:";
		cin >> input;
		if (input == 'C' || input == 'c') {
			Play(&playerFields, &comFields, whoStarts());
			return;
		}
		else if (input == 'M' || input == 'm') {
			cout << "Spiel gegen Menschen wird gestartet!\n";
			Play(&playerFields, &playerFields, 1);
			return;
		}
		else {
			cout << "Ungueltige Eingabe! Erneut versuchen:\n";
		}
	}
}

void RunMenu() {
	char input;
	cout << "Willkommen bei TicTacToe!\n";
	while (1) {
		cout << "S - Starten\nE - Beenden\nEingabe:";
		cin >> input;
		if (input == 'E' || input == 'e') {
			return;
		}
		else if (input == 'S' || input == 's') {
			GameMode();
		}
		else {
			cout << "Ungueltige Eingabe! Erneut versuchen:\n";
		}
	}
}

int main() {
RunMenu();

	return 0;
}