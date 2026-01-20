#ifndef GAME_HH
#define GAME_HH

#include "doublyLinkedList.h"
#include <iostream>
#include <string>

using namespace std;

enum PlayPosition { none, front, back, both };

struct Domino {
    public:
    int top;
    int bottom;
    bool sideways;
    friend ostream& operator<<(ostream& os, const Domino&);

    Domino(int t = 0, int b = 0):
        top{t},
        bottom{b},
        sideways{false}{}

        void swap(Domino& d) {
            std::swap(*this,d);
        }

        void flip() {
            int tmp = this->top;
            this->top = this->bottom;
            this->bottom = tmp;
        }

        void rotateCCW() {
            this->sideways = true;
        }

        void rotateCW() {
            this->flip();
            this->sideways = true;
        }
};

struct DominoBoard : public DoublyLinkedList<Domino> {
    void clear();
        friend std::ostream& operator<<(std::ostream& os, const DominoBoard& b) {
        if (!b.length) return os;
        for (auto it = b.head; it->prev == nullptr; ++it) {
            os << *b.head->data;
        }
        return os;
      }
};

struct DominoArray {
    int length;
    Domino* dArray;
    Domino& operator[](int);
    DominoArray(int length) {
        this->length = length;  
        dArray = new Domino[length];
    }   
};

struct DominoPlayer {
    int index;
    string name;
    int lastPlayerIndex;
    // const int numStartDominoes;
    DominoArray hand;
    bool autoPlay(DominoBoard*);
    int countPips();
    // DominoBoard* board;
    bool play(DominoBoard*, Domino*, bool);
    void printMove(PlayPosition, Domino*);
    void pass();
    PlayPosition findPlayPosition (DominoBoard*, Domino*, bool);
    friend ostream& operator<<(ostream& os, DominoPlayer& p);

    DominoPlayer(const int numStartDominoes = 7):
        // board{board},
        lastPlayerIndex{0},
        // numStartDominoes{this->numStartDominoes},
        hand{DominoArray(numStartDominoes)}{}
    };

class DominoGame {

    int dominoSetLength = 0;
    int upToDouble = 6;
    const int minNumPlayers = 2;
    friend ostream& operator<<(ostream& os, const DominoGame&);
    const int numStartDominoes;

    public:
    int gameWinner;
    int isTie;
    DominoBoard* board;
    int lastPlayerIndex;
    int numPassesInRow;
    int numPlayers;
    DominoPlayer* players;
    Domino* dominoSet;

    void makeHands();
    void autoPlayGame();
    void findWinner();
    void regularGame();
    void autoPlayRounds();
    void playFirstDomino();
    Domino* createDominoes(int);
    int getUpToDouble() {
        return upToDouble;
    }

    int getNumStartDominoes() {
        return 7;
    }

    DominoGame(DominoBoard* board, DominoPlayer* players, int numPlayers):
        numStartDominoes{7},
        gameWinner{0},
        isTie{false},
        board{board},
        lastPlayerIndex{0},
        numPassesInRow{0},
        numPlayers{numPlayers},
        players{players},
        dominoSet{createDominoes(upToDouble)}{}
};

struct DominoRound {
    DominoBoard* board;
    int nextPlayerIndex;
    int numPlayers;
    int gameNum;
    DominoPlayer* players;
    int* score;
    int roundIndex = 0;
    const int numGamesInSet = 7;
    void autoPlayRounds(int);
    // DominoGame* games;
    int numPassesInRow;
    void regularPlayRounds(int);

    DominoRound(int numPlayers, DominoBoard* board):
        board{board},
        numPlayers{numPlayers},
        gameNum{0},
        players{new DominoPlayer[numPlayers]},
        score{new int[numPlayers]()}{
        cin.ignore();
        for (int i = 0; i < numPlayers; ++i) {
            // players[i].board = board;
            players[i].index = i;
            string s;
            cout << "player " + to_string(i+1) << "'s name: ";
            getline(cin,s);
            players[i].name = s;
        }
    }
};


#endif