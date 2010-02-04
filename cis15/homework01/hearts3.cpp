// Frank Bardelli
// Advanced C++ Programming (Section WQ6)
// Assignment 1 Part 1
// September 3, 2009
//---------- SOURCE CODE BEGINS HERE ----------
// include C and C++ headers
#include <stdlib.h>
//#include <time.h>
#include <sys/time.h>
#include <iostream>
using namespace std;
// define constants for suits
enum {DIAMONDS,CLUBS,HEARTS,SPADES};

//avoid "magic numbers" in program
const int CARDS_IN_SUIT   = 13;
const int NUMBER_OF_SUITS = 4;
const int CARDS_IN_DECK   = CARDS_IN_SUIT * NUMBER_OF_SUITS;
const int CARDS_IN_HAND   = 13;

// define constants for face characters, such that:
// 0 is 2, 1 is 3, ... , 8 is ten (T), 9 is jack (J),
// 10 is queen (Q), 11 is king (K), 12 is ace (A)
//                    0123456789012
const string FACES = "23456789TJQKA";
// define constants to describe faces
const string SUITS[NUMBER_OF_SUITS] = {"Diamonds","Clubs","Hearts","Spades"};



/**        
 * HELPER FUNCTIONS 
*/

/**
 * partialShuffle(int cards[],int number_to_shuffle)
 * randomize only as many elements as we need
 * This requires exactly numcards calls to rand()
 * and 2*numcard total iterations as we need to loop again to assign
 * cards from the sorted deck. For medium to large values of numcards 
 * this method will usually outperform picking at random.
*/

void partialShuffle(int cards[],int number_to_shuffle){
 //avoid array out of bounds error
 if(number_to_shuffle > CARDS_IN_DECK){ 
   cout << "number_to_shuffle: " << number_to_shuffle
        << " is larger than the number of cards in this deck: "
        << CARDS_IN_DECK << endl;
   exit(1);
 }
 struct timeval time; 
 gettimeofday(&time, 0);

 long int n = time.tv_usec * getpid(); 
 srand(n);
 
 for (int i = 0; i < number_to_shuffle; i++) {
    int tempCard = cards[i];
    int randomCardIndex = rand() % CARDS_IN_DECK;
    cards[i] =  cards[randomCardIndex];
    cards[randomCardIndex] = tempCard;
  }
}

/**
 * getFaceValue(int card)
 * returns suit of card supplied 
 * as a value in the suits enumeration
 */
int getSuit(int card){
  return(card / CARDS_IN_SUIT);
}

/**
 * getFaceValue(int card)
 * returns value of the card supplied 
 * relative to other cards in the same suit
 */
int getFaceValue(int card){
  return card % CARDS_IN_SUIT;
}

/**
 * getFace(int card)
 * returns a character representing 
 * face value of the card supplied
 */
char getFace(int card){
  char face = FACES[getFaceValue(card)];
  return face;
}

/**
 * isQueenOfSpades(int suit,char face)
 * returns true if the card supplied is the queen of spades
 */
bool isQueenOfSpades (int suit,char face){
  return (suit == SPADES && face == 'Q');
}
/**
 * isQueenOfSpades(int card)
 * overload isQueenOfSpades(int suit,char face) to parse the card
 * returns true if the card supplied is the queen of spades
 */
bool isQueenOfSpades (int card){
  int  suit = getSuit(card);
  char face = getFace(card);
  return isQueenOfSpades(suit,face);
}

/**
 * dealHand()
 * this function emulates dealing "numcards" from a deck.
 * it stores the cards in the "cards" array.
 * it ensures that there are no duplicates in the "cards" array.
 */
void dealHand( int numcards, int cards[] ) {
  int deck[CARDS_IN_DECK]; //unsorted deck 
  int newcard; // value of new card
  for ( int i=0; i< CARDS_IN_DECK; i++ ) { // initialize deck
    deck[i] = i;
  }

  partialShuffle(deck,CARDS_IN_HAND);
  for ( int i=0; i< numcards; i++ ) { // pick "numcards" unique cards
    cards[i] = deck[i]; // select the unpicked card
  }
} // end of dealHand()


/**        
 * ASSIGNMENT FUNCTIONS 
*/

/**
 * showCard()
 * this function displays the face character and suit name of the
 * "card" argument. for example, if "card" is 0, then this function
 * will output "2 of diamonds".
 */
void showCard( int card ) {
  string suit = SUITS[getSuit(card)];
  char face = getFace(card);
  cout << face << " of " << suit << endl;
} // end of showCard()


/**
 * showHand()
 * this function displays the face character and suit name of each entry in the
 * "cards" array. "numcards" is the number of entries in this array.
 * HINT: call the function "showCard()", which you have defined above,
 * to display the face character and suit name of individual entries.
 */
void showHand( int numcards, int cards[] ) {
  for ( int i=0; i< numcards; i++ ) {
    showCard(cards[i]); 
  }
} // end of showHand()


/**
 * countPoints()
 * this function will count and return the number of points in the hand
 * represented by the "cards" argument. "numcards" is the number of entries in
 * this array.
 * points are allocated as follows: the queen of spades (value 49) is worth -26
 * points. all hearts are worth 1 point. cards of all other suits are worth 0.
 */
int countPoints( int numcards, int cards[] ) {
  int points = 0;
  for ( int i=0; i< numcards; i++ ) {
    int  suit = getSuit(cards[i]);
    char face = getFace(cards[i]);
    if (suit == HEARTS){
      ++points;
    }else if ( isQueenOfSpades(suit,face) ){
      points -= 26;
    }
  }
  return points;
} // end of countPoints()


/**
 * change3cards()
 * This function will select 3 entries in the "cards" argument that should be
 * changed. "numcards" is the number of entries in this array. The "change"
 * argument is an array of size 3.
 * First, the function should look for the queen of spades (value=49) in the
 * "cards" array. If it finds it, then it should put its value in the "change"
 * array, and replace its entry in the "cards" array with -1.
 * Second, the function should find the 2 or 3 largest values in the "cards"
 * array, place these values in the "change" array and place -1 in each entry in
 * the "cards" array that is selected.
 * Note that we say "2 or 3 values" above because if the queen of spades is
 * found, then you only need to find the 2 largest values; otherwise you need to
 * find the 3 largest values.
 */
void change3cards( int numcards, int cards[], int change[] ) {
  int indexOfHighestCards[3] = {-1,-1,-1};
  int valueOfHighestCards[3] = {-1,-1,-1};
  int indexOfQueenofSpades = -1;
  for ( int i=0; i< numcards; i++ ) {
    int  suit     = getSuit(cards[i]);
    int faceValue = getFaceValue(cards[i]);
    if (isQueenOfSpades(cards[i])){
      indexOfQueenofSpades = i;
      continue;
    }
    // Maintain array of 3 highest cards
    // This is a bit of bookkeeping
    // For larger capacity of changed cards a qsort
    // of the hand would be a better way to go
    if ( faceValue > valueOfHighestCards[0]){
       valueOfHighestCards[2] = valueOfHighestCards[1];
       indexOfHighestCards[2] = indexOfHighestCards[1];
       valueOfHighestCards[1] = valueOfHighestCards[0];
       indexOfHighestCards[1] = indexOfHighestCards[0];
       valueOfHighestCards[0] = faceValue;
       indexOfHighestCards[0] = i;
    }else if(faceValue > valueOfHighestCards[1]){
       valueOfHighestCards[2] = valueOfHighestCards[1];
       indexOfHighestCards[2] = indexOfHighestCards[1];
       valueOfHighestCards[1] = faceValue;
       indexOfHighestCards[1] = i;
    }else if(faceValue > valueOfHighestCards[2]){
       valueOfHighestCards[2] = faceValue;
       indexOfHighestCards[2] = i;
    }
  }
  if (indexOfQueenofSpades >= 0){
    indexOfHighestCards[2] = indexOfQueenofSpades;
  }
  for ( int i=0; i< 3; i++ ) {
     change[i] = cards[indexOfHighestCards[i]];
     cards[indexOfHighestCards[i]] = -1;
  }
} // end of change3cards()


/**
 * main()
 * This is the main function of the program. Inside, you should write code to:
 * 1. declare an array of 13 integers that will store an array of cards that
 *    represents your "hand" in the game
 * 2. call the function dealHand() to initialize your array ("hand")
 * 3. call the function showHand() to display the contents of your hand
 * 4. call countPoints() to calculate the point value of the cards in your hand,
 *    and then display that value
 * 5. call change3cards() to select 3 cards to change from your hand,
 *    and then display those 3 cards
 */
int main() {
  int hand[CARDS_IN_HAND];
  int change[3];
  dealHand(CARDS_IN_HAND,hand);
  showHand(CARDS_IN_HAND,hand);
  cout << "Total score is: " << countPoints(CARDS_IN_HAND,hand) << endl;
  change3cards(CARDS_IN_HAND,hand,change);
  cout << "removing these cards\n";
  for ( int i=0; i< 3; i++ ) {
     showCard(change[i]);
  }
  return 0;
} // end of main()

