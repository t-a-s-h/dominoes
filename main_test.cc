#include <gtest/gtest.h>
#include "doublyLinkedList.h"
#include "game.h"

class DominoBoardTest : public ::testing::Test {
};

void makeSampleHand(DominoPlayer &p, int* include = nullptr, int include_len = 0) {
    for (int i = 0; i < include_len; ++i) {
        p.hand[i].top = include[i * 2];
        p.hand[i].bottom = include[i * 2 + 1];
    }
}

TEST(DominoTest, createsHand) {
  DominoBoard board;
  DominoPlayer p;
  int sample[14] = {0,1,1,2,2,3,3,4,4,5,5,6,6,7};
  makeSampleHand(p,sample,7);
  DominoArray& hand = p.hand;
  EXPECT_EQ(p.hand.length,7);
}

TEST(DominoTest, playsSelect) {
  DominoBoard board;
  DominoPlayer p;
  int sample[14] = {0,1,1,2,2,3,3,4,4,5,5,6,6,0};
  makeSampleHand(p,sample,7);
  // hand is on stack
  DominoArray hand = p.hand;
  // must use last domino, because hand is on stack (not heap like in implementation)
  int lastDominoIndex = hand.length;
  p.play(&board,&hand[--lastDominoIndex],true);
  p.play(&board,&hand[--lastDominoIndex],true); 
  p.play(&board,&hand[--lastDominoIndex],true);
  EXPECT_EQ(p.hand.length,4);
}

TEST(DominoHandTest, playsEntireHand) {
  DominoBoard board;
  DominoPlayer p;
  int sample[14] = {0,1,1,2,2,3,3,4,4,5,5,6,6,0};
  makeSampleHand(p,sample,7);
  DominoArray hand = p.hand;
  // must use last domino, because hand is on stack (not heap like in implementation)
  int lastDominoIndex = hand.length;
  p.play(&board,&hand[--lastDominoIndex],true);
  p.play(&board,&hand[--lastDominoIndex],true); 
  p.play(&board,&hand[--lastDominoIndex],true);
  p.play(&board,&hand[--lastDominoIndex],true); 
  p.play(&board,&hand[--lastDominoIndex],true); 
  p.play(&board,&hand[--lastDominoIndex],true);
  p.play(&board,&hand[--lastDominoIndex],true); 
  EXPECT_EQ(p.hand.length,0);
}


// nvm dumb idea
// TEST(DominoHandTest, makesRandomishDominoes) {
//   DominoBoard b;

  
//   DominoPlayer p[4];
//   // int n = 1;
//   // int numItemsOverAvg = 0;
//   // DominoArray hand = p.hand;
//   // srand(time(0));  DominoPlayer p[4];
//   DominoGame g(&b,p,4);
//   int numItems = g.getNumStartDominoes();
//   int numItemsOverAvg = 0;
  
//   // int numItems = hand.length;
//   // basic (bad) test for randomness 
//   g.makeHands(numItems);
//   for (int j = 0; j < 4; ++j) {
//       double variance = 0;
//       DominoArray hand = p[j].hand;
//       cout << p[j];
//       for (int i = 0; i < numItems; ++i) {
//         // cout << g.players[j];
//         variance += ((hand[i].top + hand[i].bottom - numItems + 1) * (hand[i].top + hand[i].bottom - numItems + 1));
//         cout << variance << " ";
//         // if (((hand[i].top + hand[i].bottom - g.getUpToDouble()) * i) >= 0) {
//         //   ++numItemsOverAvg;
//         // }
        
//       }
//       cout << variance / (numItems - 1) << endl;

//   }
//   // EXPECT_LE(numItemsOverAvg, numItems * 10 / 2 + 5);
//   // EXPECT_GE(numItemsOverAvg, numItems * 10 / 2 - 5); 
// }

TEST(DominoTest, createsDomino) {
  Domino d(1,2);
  EXPECT_EQ(d.top,1);
  EXPECT_EQ(d.bottom,2);
}

TEST(DominoBoardTest, makesEmptyList) {
  DominoBoard b;
  EXPECT_EQ(b.length,0);
}

TEST(DominoBoardTest, addsDominoToList) {
  DominoBoard b;
  Domino d(6,5);
  b.addtoFront(&d);
  EXPECT_EQ(b.head->data,&d);
  EXPECT_EQ(b.head->data->top,6);
  EXPECT_EQ(b.head->data->bottom,5);
  EXPECT_EQ(b.length,1);
}

// tests
// throws out of bounds when hand.length out of bounds
// creates valid dominoes (try diff double numbers)
// PlayPosition p; p++ works
// auto makes hands with correct amount of / valid dominoes
// test randomish dominoes
// doesn't ask where to play at end, if only one domino left
// asks where to play if two options

// int main(int argc, char **argv) {
  
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }