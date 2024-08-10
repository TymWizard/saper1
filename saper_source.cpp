#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "saper_header.h"


using namespace std;


Engine::Engine() { set_game(); }

void Engine::set_bombs() {
	srand(time(0));
	vector<pair<int, int>> position_coordinates;

	for (int i = 0; i < 10; i++) {		//ustaw wszedzie zera na poczatek,
		for (int j = 0; j < 10; j++) {	//zeby sie nie zbugowalo
			tiles[i][j] = 0;
		}
	}
	
	for (int i = 1; i < 9; i++) { //ustaw koordynaty w pary
		for (int j = 1; j < 9; j++) {
			position_coordinates.push_back({ i,j });
		}
	}

	random_shuffle(position_coordinates.begin(), position_coordinates.end());

	for (int k = 0; k < 10; k++) {
		int i = position_coordinates[k].first;
		int j= position_coordinates[k].second;
		tiles[i][j] = 9;
	}
}


void Engine::set_tiles() {
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (tiles[i][j] == 9) continue;
			
			int count = 0;
			if (tiles[i - 1][j+1] == 9) count += 1; //lewy gorny rog i dalej wokol wskazowek zegara
			if (tiles[i][j+1] == 9) count += 1;
			if (tiles[i+1][j + 1] == 9) count += 1;
			if (tiles[i+1][j] == 9) count += 1;
			if (tiles[i+1][j-1] == 9) count += 1;
			if (tiles[i][j - 1] == 9) count += 1;
			if (tiles[i-1][j -1] == 9) count += 1;
			if (tiles[i-1][j] == 9) count += 1;

			tiles[i][j] = count;
		}
	}
}


void Engine::set_game() {
	set_bombs();
	set_tiles();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			vis[i][j] = 0;
		}
	}
}

//pomocnicza metoda print_tiles
void Engine::print_tiles() {
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			cout << tiles[i][j] << " ";
		}
		cout << endl;
	}
}






GameRun::GameRun()   /* { set_game(); }*/  :Engine() {}

void GameRun::flag(int n, int k) {
	if ((n > 0) && (n < 9) && (k > 0) && (k < 9)) {
		vis[n][k] = 2; //uzytkownik na swoim widoku ma ponumerowane 1-8
	}
}

void GameRun::show(int n, int k) {
	if ((n > 0) && (n < 9) && (k > 0) && (k < 9)) {
		vis[n][k] = 1; //uzytkownik na swoim widoku ma ponumerowane 1-8
		//if (tiles[n][k] == 9) { Sleep(3000);  set_game(); } //jezeli uzytkownik przegral  czekaj 3 sekundy i zresetuj gre
	}
}

bool GameRun::is_won() {
	int n_good_tiles=0; //55 gg
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (tiles[i][j] == 9) continue;
			if (vis[i][j] == 1) n_good_tiles += 1;
		}
	}
	return (n_good_tiles == 54); // if (n_good_tiles == 55) return 1; 	//else return 0;
}

bool GameRun::has_lost(int n,int k) {
	return ((vis[n][k] == 1) && (tiles[n][k] == 9));
}

void GameRun::reset_game() {
	is_lost = 0;
	set_game();
}






//GameTxt::GameTxt() : GameRun() {} //konstruktor gametxt z lista inicjalizacyjna wywoluje konstruktor GameRun, ...
								//...ktory sam wywoluje konstruktor Engine

void GameTxt::print_board(){
	system("color a");
	cout << "\t\t\t\t\t            1 2 3 4 5 6 7 8\n" << endl;
	for (int i = 1; i < 9; i++) {
		cout << "\t\t\t\t\t\t"<<i << "   ";
		for (int j = 1; j < 9; j++) {

			if (vis[i][j] == 0) cout << "x ";
			else if (vis[i][j] == 2) cout <<"F ";
			else if (vis[i][j] == 1) {
				if (tiles[i][j] == 9) cout << "B ";
				else cout << tiles[i][j] << " ";
			}
	
		}
		cout << endl;
	}
}

void GameTxt::user_input() {
	int x,y;
	char action;
	cout << "\nPodaj koordynaty pola (x,y) oraz akcje, ktora chcesz wykonac\n('l' by odkryc pole, 'p' by oflagowac pole) oddzielone spacja: ";
	cin >> x >> y >> action;
	if (action == 'l') show(y, x);       //odwrocone
	else if (action == 'p') flag(y, x);	 //odwrocone

	if (has_lost(y, x)) {
		flag(y, x);
		is_lost = true; //odwrocone x y
	}
}

void GameTxt::run_game() {
	while (true) {
		print_board();
		user_input();
		if (is_lost) {
			cout << "\nPrzegrales! " << endl;
			Sleep(7000);
			system("cls");
			reset_game();
			continue;
		} //jezeli is_lost wtedy czekaj 7 sekund i resetuj gre
		if (is_won()) {
			cout << "\nWygrales! \n";
			Sleep(60000);
			exit(1);
		} //jezeli wygrano to czekaj minute i wylacz sapera
		//--------------------
		/*cout << "\nWygrales! \n";
		Sleep(60000);
		exit(1);*/
		//-------------------
		system("cls");
	}
}

GameTxt::GameTxt()  {
	run_game();
} 



