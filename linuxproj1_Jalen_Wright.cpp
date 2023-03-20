/*==============================================================================
Program: Program 2
Author: Jalen Wright
Class: CS1428.H01
Instructor: Dr. Zong
Date: 9/15/22
Description: Program that controls a quiz show
==============================================================================*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct summ {
    string name;
    int score;
};
int check_files();
void read_questions(string questions[50][6], int SETS);
void read_answers(char answers[50],  int SETS);
void show_questions(string questions[50][6], int SETS, int quesnum, bool second_chance);
char player_try(char answers[50], int SETS);
void play_game(string questions[50][6], char answers[50], int SETS, summ player, bool second_chance);
void sort_score();


int main(/*int argc, char* argv[]*/) {
    srand(time(NULL));
    int SETS = check_files();
    if (SETS == -1) {
        return -1;
    }
    string questions[50][6];
    char answers[50];
    bool second_chance = 0;

    read_questions(questions, SETS);
    read_answers(answers, SETS);
    summ player;
    play_game(questions, answers, SETS, player, second_chance);

}

check_files() {

    int numlines = 0;
    int numlines2 = 0;
    string dump;
    string dump2;
    ifstream fin;
    ifstream fin2;
    fin.open ("answers.txt");
    fin2.open ("questions.txt");

    if (!fin.is_open()) {
      cout << "Could not open the answers file. Terminating program..."<< endl;
      return -1;
    }

    if (!fin2.is_open()) {
      cout << "Could not open the questions file. Terminating program..."<< endl;
      return -1;
    }

    while (!fin.eof()) {
        getline(fin, dump);
        numlines++;
    }

    while (!fin2.eof()) {
        getline(fin2, dump2);
        numlines2++;
    }

    if (numlines != (numlines2 + 1) / 6) {
        cout << "Questions and answers files do not match. Terminating program..." << endl;
        return -1;
    }

    else {
        cout << "Files checked, all is good!" << endl;
        return numlines;
    }
}

void read_questions (string questions[50][6], int SETS) {

    ifstream fin;
    fin.open ("questions.txt");

    while (!fin.eof()) {

        for(int i = 0; i < SETS; i++){

            for(int j = 0; j < 6; j++){

                getline(fin, questions[i][j]);
            }
        }
    }

    cout << "Questions file has been extracted!" << endl;

    fin.close();

}
void read_answers (char answers[50], int SETS) {

    ifstream fin;
    fin.open ("answers.txt");

    while (!fin.eof()) {
        for (int i = 0; i < SETS; i++) {
            fin >> answers[i];
        }
    }

    cout << "Answers file has been extracted!" << endl;

    fin.close();
}

void show_questions(string questions[50][6], int SETS, int quesnum, bool second_chance) {
    string pre[4] = {"A. ", "B. ", "C. ", "D. "};

    cout << "Question " << quesnum + 1 << ". " << questions[quesnum][0] << endl;
    for(int i = 1; i < 5; i++) {
        cout << pre[i - 1] << questions[quesnum][i] << endl;
    }

}

char player_try() {
    char ans;

    cin >> ans;
    return toupper(ans);
}

void play_game(string questions[50][6], char answers[50], int SETS, summ player, bool second_chance) {
    cout << "Enter your name: " << endl;
    getline(cin, player.name);
    int questions_answered[6];
    int comicsans = 0;

    //This for loop handles running the game up to 6 times, accounting for second chances and counting score;
    while (comicsans < 6) {
        ROLL:
        int quesnum = rand() % SETS;
        cout << player.name << ", ";
        START:
        show_questions(questions, SETS, quesnum, second_chance);
        char response = player_try();
        
        for (int j = 0; j < comicsans; j++) {
           if (quesnum == questions_answered[j]) {
                goto ROLL;
           }
        }

        if (response != 'A' && response != 'B' && response != 'C' && response != 'D') {
            cout << "Invalid response, please try again: " << endl;
            goto START;
        }

        else if (response == answers[quesnum]) {
            cout << "Correct! Onto the next question..." << endl;
            if (comicsans == 0) {
                player.score += 10;
            }
            else {
                player.score += (player.score *=  10);
            }
        }

        else { 
            cout << "Incorrect, would you like try again?" << endl;
            char sec;
            cin >> sec;

            if (toupper(sec) == 'Y') {
                switch (response) {
                    case 'A':
                        cout << player.name << ", " << "Question " << quesnum + 1 << ". " << questions[quesnum][0] << endl;
                        cout << "B. " << questions[quesnum][2] << endl;
                        cout << "C. " << questions[quesnum][3] << endl;
                        cout << "D. " << questions[quesnum][4] << endl;
                        break;
                    case 'B':
                        cout << player.name << ", " << "Question " << quesnum + 1 << ". " << questions[quesnum][0] << endl;
                        cout << "A. " << questions[quesnum][1] << endl;
                        cout << "C. " << questions[quesnum][3] << endl;
                        cout << "D. " << questions[quesnum][4] << endl;
                        break;
                    case 'C':
                        cout << player.name << ", " << "Question " << quesnum + 1 << ". " << questions[quesnum][0] << endl;
                        cout << "A. " << questions[quesnum][1] << endl;
                        cout << "B. " << questions[quesnum][2] << endl;
                        cout << "D. " << questions[quesnum][4] << endl;
                        break;
                    case 'D':
                        cout << player.name << ", " << "Question " << quesnum + 1 << ". " << questions[quesnum][0] << endl;
                        cout << "A. " << questions[quesnum][1] << endl;
                        cout << "B. " << questions[quesnum][2] << endl;
                        cout << "C. " << questions[quesnum][3] << endl;
                        break;
                }
                    
                response = player_try();

                if (response == answers[quesnum]) {
                    cout << "Correct! Half points awarded for second try!" << endl;
                    if (comicsans == 0) {
                        player.score += 5;
                    }
                    else {
                        player.score += (player.score *=  5);
                    }
                }

                else {
                    cout << "Incorrect! You failed the second chance, better luck next time..." << endl;
                    goto END;
                }
                
                
            }

            else {
                cout << "Second chance rejected, next question..." << endl;
            }
        }

        quesnum = questions_answered[comicsans];
        comicsans++;
    }

    cout << "Game Complete! Here is your score: " << endl;
    cout << "   " << player.name << "           " << player.score << endl;

    END:
    ofstream fout;
    fout.open("summary.txt", ios::app);
    fout << player.name << "    " << player.score << endl;
    fout.close();
    cout << "Thank you for playing!" << endl;
     
}


void sort_score () {


}