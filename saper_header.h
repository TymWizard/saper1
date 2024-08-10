#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

//saper ma 8x8 pol i 10 min

class Engine {
protected:
	int tiles[10][10];	//ile ma sasiadow bomb, dodatkowo 9=bomba!
	int vis[10][10];	//0 - zakryte, 1-odkryte 2-oflagowane

protected:
	void set_bombs(); //ustaw wszystkei bomby i pozostale pola na 0 zeby sie nie zbugowalo
	void set_tiles(); //ustaw pola ktore nie sa bombami
	void set_game(); //wywolaj set_bombs i set_game i ustaw wszystkie vis na 0
public: Engine(); //konstruktor wywoluje set_game
public: void print_tiles(); //pomocnicze print_tiles
protected: virtual bool is_won() = 0; //sprawdza czy juz wygrano
		   virtual bool has_lost(int n, int k) = 0; //sprawdza czy w pole o podanych koordynatach...
						//...jest widoczne i zarazem jest bomba, jezeli tak to zwraca 1 czyli przegrana

private:
	//virtual void flag(int n, int k);
	//virtual void show(int n, int k);

	Engine(const Engine& b);
	Engine& operator = (const Engine& b);
	
};


class GameRun : public Engine{
protected:
	bool is_lost = false;
	virtual bool is_won();
	virtual bool has_lost(int n, int k);
	void flag(int n, int k);
	void show(int n, int k);
	void reset_game();


private:
	GameRun(const GameRun& b);
	GameRun& operator = (const GameRun& b);

public: GameRun();

};


class GameTxt : public GameRun {
private:
	
	GameTxt(const GameTxt& b);
	GameTxt& operator = (const GameTxt& b);

	void print_board();
	void user_input();
public:
	GameTxt();
	void run_game();
};