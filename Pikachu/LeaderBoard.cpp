#include "LeaderBoard.h"
#include <iostream>
#include <conio.h>
using namespace std;

//sort the leaderboard
void sortLeaderBoard(Player list[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (list[i].point < list[j].point) {
                swap(list[i], list[j]);
            }
        }
    }
}



//print the leaderboard on the console
void showLeaderBoard(char& c, Player list[], int totalAccounts, int& pos) {
    //choose the mode leaderboard 
    goToXY(45, 15);
    cout << "Which mode you want to see? (N/H): ";
    cin >> c;
    string filename;
    if (c == 'n' || c == 'N') {
        filename = "Normal.txt";
    }
    else if (c == 'h' || c == 'H') {
        filename = "Hard.txt";
    }
    else {
        system("cls");
        return;
    }
    system("cls");

	cout << R"(
					    __     ______ ___     ____   ______ ____   ____   ____   ___     ____   ____
					   / /    / ____//   |   / __ \ / ____// __ \ / __ ) / __ \ /   |   / __ \ / __ \
					  / /    / __/  / /| |  / / / // __/  / /_/ // __  |/ / / // /| |  / /_/ // / / /
					 / /___ / /___ / ___ | / /_/ // /___ / _, _// /_/ // /_/ // ___ | / _, _// /_/ /
					/_____//_____//_/  |_|/_____//_____//_/ |_|/_____/ \____//_/  |_|/_/ |_|/_____/)";

	DrawBox(40, 10, 80, 19);
	goToXY(41, 14);
	for (int i = 1; i <= 78; i++)
	{
		cout << char(196);
	}
	for (int i = 1; i <= 17; i++)
	{
		goToXY(50, 10 + i);
		cout << char(179);
	}
	for (int i = 1; i <= 17; i++)
	{
		goToXY(108, 10 + i);
		cout << char(179);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	goToXY(43, 12);
	cout << "Rank";
	goToXY(56, 12);
	cout << "Username";
	goToXY(111, 12);
	cout << "Score";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 0, j = 0; i < totalAccounts && i <= 4; i++, j += 3)
	{
		gotoXY(45, 10 + 5 + j);
		cout << i + 1;
		gotoXY(54, 10 + 5 + j);
		cout << list[i].name;
		gotoXY(113, 10 + 5 + j);
		cout << list[i].point;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	_getch();
	system("cls");
}

//update the leaderboard with a new player entry
void writeLeaderBoard(Player p, string filename) {
    //open the file
    ifstream fin(filename);
    //if the file is opened
    if (fin) {
        Player* list = new Player[11];
        int no_player = 0;
        string s;

        //get all infor of the old file
        while (getline(fin, s, ' ')) {
            list[no_player].name = s;
            fin >> list[no_player].point;
            fin.ignore();
            no_player++;
        }

        //update the new entry
        bool found = false;
        //if the player already have account then update the point
        for (int i = 0; i < no_player; i++) {
            if (p.name == list[i].name) {
                found = true;
                if (p.point > list[i].point) {
                    list[i].point = p.point;
                    break;
                }
            }
        }
        //if the player is new and the leaderboard is not full, add new player into the leaderboard
        if (found == false && no_player < 10) {
            list[no_player].name = p.name;
            list[no_player].point = p.point;
            no_player++;
            //if the leaderboard is full, add new player into the board and sort the board, after that take 10 highest score 
        }
        else if (found == false && no_player >= 10) {
            sortLeaderBoard(list, no_player);
            if (list[no_player - 1].point < p.point) {
                list[no_player - 1].name = p.name;
                list[no_player - 1].point = p.point;
            }
        }

        sortLeaderBoard(list, no_player);


        fin.close();

        //write the new information into the file
        ofstream fout(filename);

        for (int i = 0; i < no_player; i++) {
            fout << list[i].name << " " << list[i].point << endl;
        }

        fout.close();

        delete[]list;
    }
    else {
        //handle the new leaderboard with no information
        ofstream fout(filename);
        fout << p.name << " " << p.point << endl;
        fout.close();
    }
}






