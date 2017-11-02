/*==============================================================================
|
|   Source code: StudPokerHeader.h
|        Author: Nicolas Queijo
|    Student ID: 5152398
|    Assignment: Program #4 Simulates a game of stud poker
|        Course: COP 4338 - Programming III
|       Section: U03
|    Instructor: William Feild
|      Due Date: Oct 31, 2017, by the end of class
|
|	I hereby certify that this collective work is my own
|	and none of it is the work of any other person or entity.
|	______________________________________ [Signature]
|
|*============================================================================*/

/* constants */
#define EXIT_FAILURE 1
#define TOTAL_COMMAND_LINE_ARGS 3
#define CARDS_PER_HAND_INDEX 1
#define PLAYERS_INDEX 2
#define TRUE 1
#define FALSE 0
#define CARDS_PER_PLAYER 5
#define MIN_CARDS_PER_HAND 1
#define MAX_CARDS_PER_HAND 13
#define MIN_PLAYERS 1
#define MAX_PLAYERS 7
#define SUIT_SIZE 4
#define RANK_SIZE 13
#define TOTAL_CARDS 52
#define SUIT_INDEX 0
#define RANK_INDEX 1
#define POKER_RANKINGS 9
#define CLUBS_ICON "\xe2\x99\xa3"
#define DIAMONDS_ICON "\xe2\x99\xa6"
#define HEARTS_ICON "\xe2\x99\xa5"
#define SPADES_ICON "\xe2\x99\xa0"
#define NEWLINE "\n"
#define HANDS_TITLE "Hands:\n\n"
#define WINNER_LABEL "<--- WINNER!"

/* enumerated types */
enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };
enum Rank { _A, _2, _3, _4, _5, _6, _7, _8, _9, _T, _J, _Q, _K };
enum CardOrder { FIRST_CARD, SECOND_CARD, THIRD_CARD, FOURTH_CARD, FIFTH_CARD };
enum PokerRank { HIGH_CARD, ONE_PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT,
	FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH };

/* card value labels */
const char* SUIT_NAMES[] = {CLUBS_ICON, DIAMONDS_ICON, HEARTS_ICON, SPADES_ICON};
//const char* SUIT_NAMES[] = {"C", "D", "H", "S"};
const char* RANK_NAMES[] = {"A", "2", "3", "4", "5", "6", "7",
	"8", "9", "T", "J", "Q", "K"};
const char* POKER_RANK_NAMES[] = {"High Card", "One Pair", "Two Pairs",
	"Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind",
	"Straight Flush"};

/* card structure definition */
struct card {
	int suit;
	int rank;
}; // end struct card
typedef struct card Card;

/* hand structure definition */
struct hand {
	Card hand[CARDS_PER_PLAYER];
	int pokerRank;
}; // end struct hand
typedef struct hand Hand;

/* function prototypes */
void validateInput(int, char*[]);
void validateArgumentCount(int);
void validateArgumentTypes(char*[]);
void validateStringAsInteger(char*);
void validateArgumentRange(char*[]);
void createDeck(Card[SUIT_SIZE][RANK_SIZE]);
void displayDeck(Card[SUIT_SIZE][RANK_SIZE]);
void shuffleDeck(Card[SUIT_SIZE][RANK_SIZE]);
void dealHands(Card[SUIT_SIZE][RANK_SIZE], Hand[MAX_PLAYERS], int, int);
void displayHands(Hand[MAX_PLAYERS], int, int);
void sortHands(Hand[MAX_PLAYERS], int, int);
int isHighCard(Hand);
int isOnePair(Hand);
int isTwoPairs(Hand);
int isThreeOfAKind(Hand);
int isStraight(Hand);
int isFlush(Hand);
int isFullHouse(Hand);
int isFourOfAKind(Hand);
int isStraightFlush(Hand);
void assignPokerRanks(Hand[MAX_PLAYERS], int);
void classifyHand(Hand*);
void displayPokerRanks(Hand[MAX_PLAYERS], int);
int determinePokerRankOfWinners(Hand[MAX_PLAYERS], int);
void populatePresetHands(Hand [POKER_RANKINGS]);
void testPresetHandsPokerRank(Hand[POKER_RANKINGS]);