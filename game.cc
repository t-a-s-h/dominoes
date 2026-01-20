#include <iostream>
#include "game.h"
#include "doublyLinkedList.h"

using namespace std;

const int MAX_PIPS = 63;  // max amout of pips in hand

ostream& operator<<(ostream& os, const Domino& d) {
    os << "Domino: " << d.top << " " << d.bottom;
    os << (d.sideways ? " sideways" : "");
    return os;
}

ostream& operator<<(ostream& os, DominoPlayer& p) {
    os << "Hand for " << p.name << "." << endl;
    for (int i = 0; i < p.hand.length; ++i) {
        os << i << ": " << p.hand[i] << endl;
    }
    return os;
}

void DominoBoard::clear() {
  head = nullptr;
  tail = nullptr;
  length = 0;
}

ostream& operator<<(ostream& os, const DominoGame& g) {
    os << "Domino set:" << endl;
    for (int i = 0; i < g.dominoSetLength; ++i) {
        os << g.dominoSet[i] << endl;
    }

    for (int i = 0; i < g.numPlayers; ++i) {
        DominoPlayer& p = g.players[i];
        os << p << endl;
    }
    return os;
}

Domino& DominoArray::operator[](int i) {
    if (i >= length) throw invalid_argument("array index out of bounds");
    else {
        return dArray[i];
    }
}

Domino* DominoGame::createDominoes(int upToDouble) {
    dominoSetLength = (upToDouble + 2) * (upToDouble + 1) / 2;
    Domino* dominoesList = new Domino[dominoSetLength];
    int rowLength = upToDouble + 1;
    int prevLength = 0;
        for (int i = 0; i <= upToDouble; ++i) {
            for (int j = i; j <= upToDouble; ++j) {
                Domino* d = new Domino(i,j);
                dominoesList[prevLength + j] = *d;
            }
        prevLength += --rowLength;
        }
    return dominoesList;
};

PlayPosition& operator++ (PlayPosition& p) {
  (p == none) ? p =  back : p = both;
  return p;
}

DominoBoard* board = new DominoBoard;

void DominoGame::makeHands() {
    srand(time(0));
    for (int i = 0; i < numPlayers; ++i) {
        players[i].hand.length = numStartDominoes;
        for (int j = numStartDominoes - 1; j >= 0; --j) {
            int randomNum = rand() % dominoSetLength;
            players[i].hand[j] = dominoSet[randomNum];
            dominoSetLength--;
            swap(dominoSet[randomNum],dominoSet[dominoSetLength]);
        }
    }
}

void DominoPlayer::printMove(PlayPosition p, Domino* move){
    switch (p) {
    case front:
        cout << name << " played " << *move << endl;
        break;
    case back:
        cout << name << " played " << *move << endl;
        break;
    default:
        cout << name << " passed " << endl;
        break;
    }
}

PlayPosition DominoPlayer::findPlayPosition(DominoBoard* board, Domino* domino, bool autoPlay = false) {
    if (board->length == 0) return front;
    PlayPosition p = none;
    if (domino->top == board->head->data->top || domino->bottom == board->head->data->top) {
        p = front;
    }
    if ((domino->top == board->tail->data->bottom || domino->bottom == board->tail->data->bottom) && board->head->data->top != board->tail->data->bottom) {
        hand.length == 1 || autoPlay ? p = front : ++p;
    }
    if (p == both) {
      int selection;
      cout << "What end would you like to play?" << endl;
      cout << "0: play at the front (on the end with " << board->head->data->top << ")" << endl;
      cout << "1: play at the back (on the end with " << board->tail->data->bottom <<  ")" << endl;
      cin >> selection;
      switch(selection) {
          case 0: p = front; break;
          case 1: p = back; break;
          default: p = front;
      }
    }
    return p;
}

bool DominoPlayer::play(DominoBoard* board, Domino* domino, bool autoPlay = false) {
    PlayPosition playPosn = findPlayPosition(board, domino, autoPlay);
    if (playPosn == none) return false;
    if  (playPosn == front) {
        if (domino->top == domino->bottom) domino->rotateCCW();
        else if (board->length && domino->top == board->head->data->top) domino->flip();
        domino->swap(hand[hand.length - 1]);
        board->addtoFront(&hand[hand.length - 1]);
        printMove(front,&hand[hand.length - 1]);
    }
    else if (playPosn == back) {
        if (domino->top == domino->bottom) domino->rotateCCW();
        else if (domino->bottom == board->tail->data->bottom) domino->flip();
        domino->swap(hand[hand.length - 1]);
        board->addtoBack(&hand[hand.length - 1]);
        printMove(back,&hand[hand.length - 1]);
    }
    --hand.length;
    // delete domino;
    return true;
}

void DominoPlayer::pass() {
  printMove(none,nullptr);
}

bool DominoPlayer::autoPlay(DominoBoard* board) {
    for (int i = 0; i < hand.length; ++i) {
        Domino* domino = &hand[i];
        if (play(board,domino,true)) {
            return true;
        }
    }
    pass();
    return false;
}

int DominoPlayer::countPips() {
    int pipCount = 0;
    for (int i = 0; i < hand.length; ++i) {
        pipCount += hand[i].top + hand[i].bottom;
    }
    return pipCount;
}

void DominoGame::playFirstDomino() {
    int firstPlayerIndex = -1;
    int firstPlayIndex = -1;
    int highestPip = -1;
    for (int i = 0; i < numPlayers; ++i) {
        for (int j = 0; j < players[i].hand.length; ++j) {
            if (players[i].hand[j].top != players[i].hand[j].bottom) continue;
            if (players[i].hand[j].top > highestPip) {
                highestPip = players[i].hand[j].top;
                firstPlayIndex = j;
                firstPlayerIndex = i;
            }
        } 
    }
    if (firstPlayIndex == -1) {
        int highestPipSum = -1;
        for (int i = 0; i < numPlayers; ++i) {
            for (int j = 0; j < players[i].hand.length; ++j) {
                if (players[i].hand[j].top + players[i].hand[j].bottom > highestPipSum) {
                    highestPipSum = players[i].hand[j].top + players[i].hand[j].bottom;
                    firstPlayIndex = j;
                    firstPlayerIndex = i;
                }
            } 
        }
    }
    lastPlayerIndex = firstPlayerIndex;
    Domino* firstDomino = &players[firstPlayerIndex].hand[firstPlayIndex];
    players[firstPlayerIndex].play(board,firstDomino);
}

void DominoGame::findWinner() {
    cout << "Game Over:" << endl;
    int minPips = MAX_PIPS;
    int winnerIndex = 0;
    if (players[lastPlayerIndex].hand.length <= 0) {
        winnerIndex = lastPlayerIndex;
    } else {
        cout << players[lastPlayerIndex].name << " has blocked the game." << endl;
        for (int i = 0; i < numPlayers; ++i) {
            int numPips = players[i].countPips();
            cout << players[i].name << ": " << numPips << " pips." << endl;
            if (numPips < minPips) {
                minPips = numPips;
                winnerIndex = i;
                isTie = false;
            }
            else if (numPips == minPips) {
                isTie = true;
            }
        }
    }
    if (isTie) {
        isTie = true;
        cout << "There is a tie. This round will not count." << endl;
    } else {
        gameWinner = winnerIndex;
        cout << players[winnerIndex].name << " has won the game!" << endl;
    }
}

void DominoGame::autoPlayGame() {
    bool gameOver = false;
    srand(time(0));
    makeHands();
    srand(time(0));
    playFirstDomino();
    while (!gameOver) {
        cout << "Current Board:" << endl;
        cout << "  top board: " << (board->head->data->top) << endl << "  bottom board: " << (board->tail->data->bottom) << endl;
        lastPlayerIndex = (lastPlayerIndex + 1) % numPlayers;
        DominoPlayer& player = players[lastPlayerIndex];
        numPassesInRow = player.autoPlay(board) ?  0 : numPassesInRow + 1;
        gameOver = player.hand.length == 0 || numPassesInRow >= numPlayers;
    }
    findWinner();
}

void DominoRound::autoPlayRounds(int numPlayers) {
    for (int i = 0; i < numGamesInSet; ++i) {
        board->clear();
        DominoGame* game = new DominoGame(board, players, numPlayers);
        game->autoPlayGame();
        ++score[game->gameWinner];
        delete game;
    }
    int overallWinnerIndex = 0;
    int winningScore = 0;
    for (int i = 0; i < numPlayers; ++i) {
        cout << players[i].name << "'s' score: " << score[i] << endl;
        if (score[i] > winningScore) {
            winningScore = score[i];
            overallWinnerIndex = i;
        }
    }
    cout << players[overallWinnerIndex].name << " has won the tournament winning " << winningScore << " games" << endl;
}

void DominoGame::regularGame() {
    bool gameOver = false;
    srand(time(0));
    makeHands();
    srand(time(0));
    playFirstDomino();
    while (!gameOver) {
        lastPlayerIndex = (lastPlayerIndex + 1) % numPlayers;
        DominoPlayer& player = players[lastPlayerIndex];
        cout << endl << player.name << "'s turn." << endl;
        cout << "Top of board: " << (board->head->data->top) << ", bottom of board: " << (board->tail->data->bottom) << endl;
        cout << player << player.hand.length << ": Pass" << endl << endl;
        int dominoIndex;
        bool successfulPlay = false;
        while(!successfulPlay) {
            cout << "Please select a valid domino to play." << endl;
            cin >> dominoIndex;
            if (dominoIndex < player.hand.length) {
                successfulPlay = player.play(board,&player.hand[dominoIndex]);
                if (successfulPlay) {
                  numPassesInRow = 0;
                  break;
                }
                cout << "That was not a valid play." << endl;
                continue;
            }
            player.pass();
            ++numPassesInRow;
            successfulPlay = true;
        }
        gameOver = player.hand.length == 0 || numPassesInRow >= numPlayers;
    }
    findWinner();
}

void DominoRound::regularPlayRounds(int numPlayers) {
    for (int i = 0; i < numGamesInSet; ++i) {
        board->clear();
        DominoGame* game = new DominoGame(board, players, numPlayers);
        cout << "There are " << numGamesInSet - i << " games left in the set." << endl << "Would you like to play game " << i+1 << "?" <<endl;
      cout << "0: No" << endl << "1: Yes" << endl;
        int playAgain;
        cin >> playAgain;
        if (!playAgain) break;
        game->regularGame();
        if (game->isTie) {
            --i;
            delete game;
            continue;
        }
        ++score[game->gameWinner];
        delete game;
    }
    int overallWinnerIndex = 0;
    int winningScore = 0;
    for (int i = 0; i < numPlayers; ++i) {
        cout << players[i].name << "'s score: " << score[i] << endl;
        if (score[i] > winningScore) {
            winningScore = score[i];
            overallWinnerIndex = i;
        }
    }
    cout << players[overallWinnerIndex].name << " has won the tournament winning " << winningScore << " games" << endl;
}