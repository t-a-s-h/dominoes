#include <iostream>
#include "game.h"
#include "doublyLinkedList.h"

using namespace std;

int main(){
    int numPlayers;
    cout << "How many players will be in this game? (2-4)" << endl;
    cin >> numPlayers;
    if (numPlayers > 4 || numPlayers < 1) {
      cout << "too bad" << endl;
      return 0;
    }
    DominoBoard* b = new DominoBoard;
    DominoRound* r = new DominoRound(numPlayers,b);
    // cout << r.game.dominoSetLength;
    r->regularPlayRounds(numPlayers);
}