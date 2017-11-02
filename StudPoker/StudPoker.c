/*==============================================================================
|
|   Source code: StudPoker.c
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
|      Language: C
|      Compile/Run:
|			make build
|			./StudPoker n m
|
|			Where n and m are the cards per hands and players respectively;
|			n must be an integer value between 1-13 and m must be an integer
|			value between 1-7. Their product cannot exceed 52.
|
|			if make build fails try: gcc StudPoker.c Cards.c -o StudPoker
|			./StudPoker n m
|
|			Assure the header file required (StudPokerHeader.h) is located
|			in the same directory as StudPoker.c and Cards.c
|
|  +----------------------------------------------------------------------------
|
|   Description: This program simulates the process of generating a deck of 52
|				 cards, shuffling the deck, and dealing the shuffled deck to
|				 a set of players. In addition each player is assigned a 
|				 poker rank based on their hand and a winner(s) is determined.
|         Input: Two integers in the range of 1-13, 1-7 respectively.
|				 Their product cannot exceed 52.
|        Output: The original deck of cards in order, the shuffled deck,
|				 the hands of each player after the cards have been dealt, the
|				 result of the game along with its winners, and test cases for
|				 the ranking system.
|       Process: Construction of a deck using the appropriate data structures,
|				 shuffling of the deck using randomized algorithms, distribution
|				 of the cards to the players in the game aka dealing, sorting
|				 each hand in ascending order, assigning poker ranks to each
|				 hand, testing the poker ranking system.
|    Required Features Not Included: N/A
|    Known Bugs: N\A
|
|*============================================================================*/

#include <stdio.h>
#include <stdlib.h> // needed to use atoi function

/* constants */
#define EXIT_FAILURE 1
#define PLAYERS_INDEX 2
#define CARDS_PER_PLAYER 5
#define MAX_PLAYERS 7
#define SUIT_SIZE 4
#define RANK_SIZE 13
#define RANK_INDEX 1
#define POKER_RANKINGS 9
#define NEWLINE "\n"
#define DIVIDER "\n--------------------------------------------------\n\n"
#define ORIGINAL_DECK_TITLE "Original deck:\n\n"
#define SHUFFLED_DECK_TITLE "Shuffled deck:\n\n"
#define HANDS_TITLE "Hands:\n\n"
#define SORTED_HANDS_TITLE "Sorted hands:\n\n"
#define HANDS_POKER_RANKINGS_TITLE "Hands' poker rankings:\n\n"
#define POKER_RANKINGS_TEST_TITLE "Poker rankings test:\n\n"
#define WINNER_LABEL "<--- WINNER!"

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

/*------------------------------------------------------------------------------
|  function: main()
|
|  Purpose: Entry point of program execution
|  @param argc - the number of command-line arguments
|  @param argv - array of strings representing the command-line arguments
|  @return 0 - flag indicating program executed successfully
------------------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	validateInput(argc, argv);
	const int CARDS_PER_HAND = CARDS_PER_PLAYER;
	const int PLAYERS = atoi(argv[PLAYERS_INDEX]);
	Card deck[SUIT_SIZE][RANK_SIZE];
	createDeck(deck);
	printf(NEWLINE);
	printf(ORIGINAL_DECK_TITLE);
	displayDeck(deck);
	time_t t;
	srand((unsigned) time(&t));
	shuffleDeck(deck);
	printf(DIVIDER);
	printf(SHUFFLED_DECK_TITLE);
	displayDeck(deck);
	Hand hands[MAX_PLAYERS];
	dealHands(deck, hands, CARDS_PER_HAND, PLAYERS);
	printf(DIVIDER);
	printf(HANDS_TITLE);
	displayHands(hands, CARDS_PER_HAND, PLAYERS);
	sortHands(hands, CARDS_PER_HAND, PLAYERS);
	printf(DIVIDER);
	printf(SORTED_HANDS_TITLE);
	displayHands(hands, CARDS_PER_HAND, PLAYERS);
	assignPokerRanks(hands, PLAYERS);
	printf(DIVIDER);
	printf(HANDS_POKER_RANKINGS_TITLE);
	displayPokerRanks(hands, PLAYERS);
	Hand presetHands[POKER_RANKINGS];
	populatePresetHands(presetHands);
	printf(DIVIDER);
	printf(POKER_RANKINGS_TEST_TITLE);
	testPresetHandsPokerRank(presetHands);
	printf(NEWLINE);
	return EXIT_SUCCESS;
} // end main function
