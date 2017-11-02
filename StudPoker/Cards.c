/*==============================================================================
|
|   Source code: Cards.c
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

#include <stdio.h>
#include <stdlib.h> // needed for exit function
#include "StudPokerHeader.h" // contains all the constants and prototypes needed


  /*------------------------------------------------------------------------------
  |  function: validateInput(argc, argv)
  |
  |  Purpose: Validates the input of the program by calling other functions that
  |			validate each requirement of the input validation. If at any point
  |			the input invalidation fails an appropriate error message is printed
  |			and the program exits.
  |  @param argc - the number of command-line arguments
  |  @param	argv - array of strings representing the command-line arguments
  ------------------------------------------------------------------------------*/
void validateInput(int argc, char* argv[]) {
	validateArgumentCount(argc);
	validateArgumentTypes(argv);
	validateArgumentRange(argv);
} // end validateInput function


  /*------------------------------------------------------------------------------
  |  function: validateArgumentCount(argc)
  |
  |  Purpose: Validates the user entered the correct number of command-line args
  |  @param argc - the number of command-line arguments
  ------------------------------------------------------------------------------*/
void validateArgumentCount(int argc) {
	if (argc != TOTAL_COMMAND_LINE_ARGS) {
		printf("Error. Two command-line arguments required.\n");
		exit(EXIT_FAILURE);
	} // end if
} // end validateArgumentCount function


  /*------------------------------------------------------------------------------
  |  function: validateArgumentTypes(argv)
  |
  |  Purpose: Validates the two command-line to be are integers
  |  @param	argv - array of strings representing the command-line arguments
  ------------------------------------------------------------------------------*/
void validateArgumentTypes(char* argv[]) {
	validateStringAsInteger(argv[CARDS_PER_HAND_INDEX]);
	validateStringAsInteger(argv[PLAYERS_INDEX]);
} // end validateArgumentTypes function


  /*------------------------------------------------------------------------------
  |  function: validateStringAsInteger(string)
  |
  |  Purpose: Takes a string and validates that every char in it is of a value 0-9
  |  @param string - the string to validate
  ------------------------------------------------------------------------------*/
void validateStringAsInteger(char* string) {
	const char NULL_CHAR = '\0';
	int index;
	for (index = 0; string[index] != NULL_CHAR; index++) {
		if (isdigit(string[index]) == FALSE) {
			printf("Error. Arguments must be positive integers.\n");
			exit(EXIT_FAILURE);
		} // end if
	} // end for
} // end validateStringAsInteger function


  /*------------------------------------------------------------------------------
  |  function: validateArgumentRange(argv)
  |
  |  Purpose: Validates that each of the command-line arguments is in the range
  |			permitted. Validates that the multiplication of the two command-line
  |			arguments does not exceed the amount of cards available. Does this
  |			by first converting each string to its integer representation.
  |  @param	argv - array of strings representing the command-line arguments
  ------------------------------------------------------------------------------*/
void validateArgumentRange(char* argv[]) {
	int cardsPerHand = atoi(argv[CARDS_PER_HAND_INDEX]);
	int players = atoi(argv[PLAYERS_INDEX]);
	if (cardsPerHand < MIN_CARDS_PER_HAND || cardsPerHand > MAX_CARDS_PER_HAND) {
		printf("Error. Cards per hand must be between %d-%d.\n",
			MIN_CARDS_PER_HAND, MAX_CARDS_PER_HAND);
		exit(EXIT_FAILURE);
	} // end if
	if (players < MIN_PLAYERS || players > MAX_PLAYERS) {
		printf("Error. There must be between %d-%d players.\n", MIN_PLAYERS,
			MAX_PLAYERS);
		exit(EXIT_FAILURE);
	} // end if
	int cardsRequired = cardsPerHand * players;
	if (cardsRequired > TOTAL_CARDS) {
		printf("Error. Not enough cards for this game.\n");
		exit(EXIT_FAILURE);
	} // end if
} // end validateArgumentRange function


  /*------------------------------------------------------------------------------
  |  function: createDeck(deck)
  |
  |  Purpose: Initializes the deck to the default values. The deck is made up of
  |			  rows and columns of Card objects.
  |  @param deck - 2D Card array used to represent the deck of cards
  ------------------------------------------------------------------------------*/
void createDeck(Card deck[SUIT_SIZE][RANK_SIZE]) {
	int row;
	int col;
	for (row = 0; row < SUIT_SIZE; row++) {
		for (col = 0; col < RANK_SIZE; col++) {
			deck[row][col].suit = row;
			deck[row][col].rank = col;
		} // end for
	} // end for
} // end createDeck function


  /*------------------------------------------------------------------------------
  |  function: displayDeck(deck)
  |
  |  Purpose: Displays the deck to the console. Does this by iterating through
  |			each Card and mapping the values in the suit and rank members
  |			to the constant strings arrays representing the suits and ranks.
  |  @param deck - 2D Card array used to represent the deck of cards
  ------------------------------------------------------------------------------*/
void displayDeck(Card deck[SUIT_SIZE][RANK_SIZE]) {
	int row;
	int col;
	for (row = 0; row < SUIT_SIZE; row++) {
		for (col = 0; col < RANK_SIZE; col++) {
			printf("%s%s  ", SUIT_NAMES[deck[row][col].suit],
				RANK_NAMES[deck[row][col].rank]);
		} // end for
		printf(NEWLINE);
	} // end for
} // end displayDeck function


  /*------------------------------------------------------------------------------
  |  function: shuffleDeck(deck)
  |
  |  Purpose: Shuffles the deck using an algorithm that imitates Java's
  |			Collections.shuffle() method. Does this by traversing the deck and
  |			for each cell it generates a random row and a random column, swaps
  |			the contents of the current cell with the contents of the cell in
  |			that random row/column combination.
  |			Time complexity: O(n * m) where n and m are the number of rows and
  |							 columns of the array respectively.
  |			Source of algorithm:
  |			https://docs.oracle.com/javase/6/docs/api/java/util/
  |			Collections.html#shuffle(java.util.List)
  |  @param deck - 2D Card array used to represent the deck of cards
  ------------------------------------------------------------------------------*/
void shuffleDeck(Card deck[SUIT_SIZE][RANK_SIZE]) {
	int row;
	int col;
	int randomRow;
	int randomCol;
	int suit;
	int rank;
	for (row = 0; row < SUIT_SIZE; row++) {
		for (col = 0; col < RANK_SIZE; col++) {
			randomRow = rand() % SUIT_SIZE;
			randomCol = rand() % RANK_SIZE;
			suit = deck[randomRow][randomCol].suit;
			rank = deck[randomRow][randomCol].rank;
			deck[randomRow][randomCol].suit = deck[row][col].suit;
			deck[randomRow][randomCol].rank = deck[row][col].rank;
			deck[row][col].suit = suit;
			deck[row][col].rank = rank;
		} // end for
	} // end for
} // end shuffleDeck function


  /*------------------------------------------------------------------------------
  |  function: dealHands(deck, hands, cardsPerHand, players)
  |
  |  Purpose: Takes the deck 2D array, copies it to a 1D array and then uses that
  |			1D array to distribute the cards into 1D Hand array used to
  |			represent the hands. Deals the cards one by one to each player until
  |			each player has the cardsPerHand amount specified by the user.
  |  @param	deck - 2D Card array used to represent the deck of cards
  |  @param	hands - 1D Hand array used to represent the hands that will be dealt
  |  @param	cardsPerHand - the number of card each player receives
  |  @param	players - the number of players participating in the game
  ------------------------------------------------------------------------------*/
void dealHands(Card deck[SUIT_SIZE][RANK_SIZE], Hand hands[MAX_PLAYERS],
	int cardsPerHand, int players) {
	int index = 0;
	Card linearDeck[TOTAL_CARDS];
	int row;
	int col;
	for (row = 0; row < SUIT_SIZE; row++) {
		for (col = 0; col < RANK_SIZE; col++, index++) {
			linearDeck[index].suit = deck[row][col].suit;
			linearDeck[index].rank = deck[row][col].rank;
		} // end for
	} // end for
	int cardsPerHandIndex;
	int playersIndex;
	index = 0;
	for (cardsPerHandIndex = 0; cardsPerHandIndex < cardsPerHand;
		cardsPerHandIndex++) {
		for (playersIndex = 0; playersIndex < players;
			playersIndex++, index++) {
			hands[playersIndex].hand[cardsPerHandIndex].suit = linearDeck[index].suit;
			hands[playersIndex].hand[cardsPerHandIndex].rank = linearDeck[index].rank;
		} // end for
	} // end for
} // end dealHands function


  /*------------------------------------------------------------------------------
  |  function: displayHands(hands, cardsPerHand, players)
  |
  |  Purpose: Displays the hands to the console. Does this by iterating through
  |			each Card and mapping the values in the suit and rank members of each
  |			to the constant string arrays representing the suits and ranks.
  |  @param hands - 1D Hand array used to represent the hands
  |  @param cardsPerHand - the number of card each player receives
  |  @param players - the number of players participating in the game
  ------------------------------------------------------------------------------*/
void displayHands(Hand hands[MAX_PLAYERS], int cardsPerHand, int players) {
	const int OFF_BY_ONE = 1;
	int playersIndex;
	int cardsPerHandIndex;
	for (playersIndex = 0; playersIndex < players; playersIndex++) {
		printf("%s %d:  ", "Player", playersIndex + OFF_BY_ONE);
		for (cardsPerHandIndex = 0; cardsPerHandIndex < cardsPerHand;
			cardsPerHandIndex++) {
			printf("%s%s  ", SUIT_NAMES[hands[playersIndex].hand[cardsPerHandIndex].suit],
				RANK_NAMES[hands[playersIndex].hand[cardsPerHandIndex].rank]);
		} // end for
		printf(NEWLINE);
	} // end for
} // end displayHands function


  /*------------------------------------------------------------------------------
  |  function: sortHands(hands, cardsPerHand, players)
  |
  |  Purpose: Sorts each hand of cards by rank in ascending order.
  |			Uses the bubble sort algorithm. Source of algorithm:
  |			https://en.wikipedia.org/wiki/Bubble_sort
  |			Time complexity: O(n^2)
  |  @param hands - 1D Hand array used to represent the hands
  |  @param cardsPerHand - the number of card each player receives
  |  @param players - the number of players participating in the game
  ------------------------------------------------------------------------------*/
void sortHands(Hand hands[MAX_PLAYERS], int cardsPerHand, int players) {
	const int PREV = -1;
	const int NEXT = 1;
	int player;
	for (player = 0; player < players; player++) {
		int i; // index of outer loop
		int j; // index of inner loop
		for (i = 0; i < cardsPerHand + PREV; i++) {
			for (j = 0; j < cardsPerHand - i + PREV; j++) {
				if (hands[player].hand[j].rank > hands[player].hand[j + NEXT].rank) {
					Card tempCard = hands[player].hand[j];
					hands[player].hand[j] = hands[player].hand[j + NEXT];
					hands[player].hand[j + NEXT] = tempCard;
				} // end if
			} // end for
		} // end for
	} // end for
} // end sortHands function


  /*------------------------------------------------------------------------------
  |  function: isHighCard(hand)
  |
  |  Purpose: Any hand that does not qualify under the other categories
  |			automatically is a "High Card".
  |  @param hand - Hand struct type that contains the array of Cards
  |  @return flag determining if the hand is a "High Card"
  ------------------------------------------------------------------------------*/
int isHighCard(Hand hand) {
	return TRUE;
} // end isHighCard function


  /*------------------------------------------------------------------------------
  |  function: isOnePair(hand)
  |
  |  Purpose: Determines if a certain hand of cards is a "One Pair" by examining
  |			two cards of a matching rank, and three unrelated side cards. This
  |			can either occur at indices 0-1, 1-2, 2-3, 3-4, or 4-5 inclusive.
  |  @param hand - Hand struct type that contains the array of Cards
  |  @return flag determining if the hand is a "One Pair"
  ------------------------------------------------------------------------------*/
int isOnePair(Hand hand) {
	int card1Rank = hand.hand[FIRST_CARD].rank;
	int card2Rank = hand.hand[SECOND_CARD].rank;
	int card3Rank = hand.hand[THIRD_CARD].rank;
	int card4Rank = hand.hand[FOURTH_CARD].rank;
	int card5Rank = hand.hand[FIFTH_CARD].rank;
	if (card1Rank == card2Rank && card2Rank != card3Rank && card3Rank
		!= card4Rank && card4Rank != card5Rank) {
		return TRUE;
	} // end if
	if (card2Rank == card3Rank && card3Rank != card4Rank && card4Rank
		!= card5Rank && card2Rank != card1Rank) {
		return TRUE;
	} // end if
	if (card3Rank == card4Rank && card4Rank != card5Rank && card1Rank
		!= card2Rank && card2Rank != card3Rank) {
		return TRUE;
	} // end if
	if (card4Rank == card5Rank && card4Rank != card3Rank && card3Rank
		!= card2Rank && card2Rank != card1Rank) {
		return TRUE;
	} // end if
	return FALSE;
} // end isOnePair function


  /*------------------------------------------------------------------------------
  |  function: isTwoPairs(hand)
  |
  |  Purpose: Determines if a certain hand of cards is a "Two Pairs" by
  |			examining if ther are two cards of a matching rank, another two cards
  |			of a different matching rank, and one side card. This can either occur
  |			at indices 0-1, 2-3 or 2-3, 3-4 inclusive.
  |  @param hand - Hand struct type that contains the array of Cards
  |  @return flag determining if the hand is a "Two Pairs"
  ------------------------------------------------------------------------------*/
int isTwoPairs(Hand hand) {
	int card1Rank = hand.hand[FIRST_CARD].rank;
	int card2Rank = hand.hand[SECOND_CARD].rank;
	int card3Rank = hand.hand[THIRD_CARD].rank;
	int card4Rank = hand.hand[FOURTH_CARD].rank;
	int card5Rank = hand.hand[FIFTH_CARD].rank;
	if (card1Rank == card2Rank && card3Rank == card4Rank && card2Rank
		!= card5Rank && card4Rank != card5Rank) {
		return TRUE;
	} // end if
	if (card2Rank == card3Rank && card4Rank == card5Rank && card3Rank
		!= card1Rank && card5Rank != card1Rank) {
		return TRUE;
	} // end if
	if (card1Rank == card2Rank && card4Rank == card5Rank && card3Rank
		!= card2Rank && card3Rank != card4Rank) {
		return TRUE;
	} // end if
	return FALSE;
} // end isTwoPairs function


  /*------------------------------------------------------------------------------
  |  function: isThreeOfAKind(hand)
  |
  |  Purpose: Determines if a certain hand of cards is a "Three of a Kind" by
  |			examining if there are three cards of the same rank and two
  |			unrelated side cards. This can either occur in indices 0-2, 1-3,
  |			or 2-4 inclusive.
  |  @param hand - Hand struct type that contains the array of Cards
  |  @return flag determining if the hand is a "Three of a Kind"
  ------------------------------------------------------------------------------*/
int isThreeOfAKind(Hand hand) {
	int card1Rank = hand.hand[FIRST_CARD].rank;
	int card2Rank = hand.hand[SECOND_CARD].rank;
	int card3Rank = hand.hand[THIRD_CARD].rank;
	int card4Rank = hand.hand[FOURTH_CARD].rank;
	int card5Rank = hand.hand[FIFTH_CARD].rank;
	if (card1Rank == card2Rank && card2Rank == card3Rank &&
		card3Rank != card4Rank && card4Rank != card5Rank) {
		return TRUE;
	} // end if
	if (card2Rank == card3Rank && card3Rank == card4Rank &&
		card2Rank != card1Rank && card4Rank != card5Rank) {
		return TRUE;
	} // end if
	if (card3Rank == card4Rank && card4Rank == card5Rank &&
		card3Rank != card2Rank && card2Rank != card1Rank) {
		return TRUE;
	} // end if
	return FALSE;
} // end isThreeOfAKind function


  /*------------------------------------------------------------------------------
  |  function: isStraight(hand)
  |
  |  Purpose: Determines if a certain hand of cards is a "Straight" by examining
  |			if there are five cards in sequence. This occurs when each card's
  |			rank is one higher than its previous starting at card 2. Since the
  |			ace can be either the lowest or highest rank we need to check for
  |			the special case that is the highest with a preceding T, J, Q, K.
  |  @param hand - Hand struct type that contains the array of Cards
  |  @return flag determining if the hand is a "Straight"
  ------------------------------------------------------------------------------*/
int isStraight(Hand hand) {
	const int NEXT = 1;
	int card1Rank = hand.hand[FIRST_CARD].rank;
	int card2Rank = hand.hand[SECOND_CARD].rank;
	int card3Rank = hand.hand[THIRD_CARD].rank;
	int card4Rank = hand.hand[FOURTH_CARD].rank;
	int card5Rank = hand.hand[FIFTH_CARD].rank;
	if (card2Rank == card1Rank + NEXT && card3Rank == card2Rank + NEXT &&
		card4Rank == card3Rank + NEXT && card5Rank == card4Rank + NEXT) {
		return TRUE;
	} // end if
	if (card1Rank == _A && card2Rank == _T && card3Rank == _J &&
		card4Rank == _Q && card5Rank == _K) {
		return TRUE;
	} // end if
	return FALSE;
} // end isStraight function


  /*------------------------------------------------------------------------------
  |  function: isFlush(hand)
  |
  |  Purpose: Determines if a certain hand of cards is a "Flush" by examining if
  |			every card is of the same suit.
  |  @param hand - Hand struct type that contains the array of Cards
  |  @return flag determining if the hand is a "Flush"
  ------------------------------------------------------------------------------*/
int isFlush(Hand hand) {
	const int FIRST_CARD = 0;
	int suitOfFirstCard = hand.hand[FIRST_CARD].suit;
	int i;
	for (i = 1; i < CARDS_PER_PLAYER; i++) {
		if (hand.hand[i].suit != suitOfFirstCard) {
			return FALSE;
		} // end if
	} // end for
	return TRUE;
} // end isFlush function


  /*------------------------------------------------------------------------------
  |  function: isFullHouse(hand)
  |
  |  Purpose: Determines if a certain hand of cards is a "Full House" by
  |			examining if there are three cards of rank a and two cards of rank b
  |			where a and b are distinct. This can either	occur in indices 0-2, 3-4
  |			or 0-1, 2-4 inclusive.
  |  @param hand - Hand struct type that contains the array of Cards
  |  @return flag determining if the hand is a "Full House"
  ------------------------------------------------------------------------------*/
int isFullHouse(Hand hand) {
	int card1Rank = hand.hand[FIRST_CARD].rank;
	int card2Rank = hand.hand[SECOND_CARD].rank;
	int card3Rank = hand.hand[THIRD_CARD].rank;
	int card4Rank = hand.hand[FOURTH_CARD].rank;
	int card5Rank = hand.hand[FIFTH_CARD].rank;
	if ((card1Rank == card2Rank && card2Rank == card3Rank) &&
		(card4Rank == card5Rank)) {
		return TRUE;
	} // end if
	if ((card1Rank == card2Rank) && (card3Rank == card4Rank &&
		card4Rank == card5Rank)) {
		return TRUE;
	} // end if
	return FALSE;
} // end isFullHouse function


  /*------------------------------------------------------------------------------
  |  function: isFourOfAKind(hand)
  |
  |  Purpose: Determines if a certain hand of cards is a "Four of a Kind" by
  |			examining if there are four cards of the same rank. This can either
  |			occur in indices 0-3 or 1-4 inclusive.
  |  @param hand - Hand struct type that contains the array of Cards
  |  @return flag determining if the hand is a "Four of a Kind"
  ------------------------------------------------------------------------------*/
int isFourOfAKind(Hand hand) {
	int card1Rank = hand.hand[FIRST_CARD].rank;
	int card2Rank = hand.hand[SECOND_CARD].rank;
	int card3Rank = hand.hand[THIRD_CARD].rank;
	int card4Rank = hand.hand[FOURTH_CARD].rank;
	int card5Rank = hand.hand[FIFTH_CARD].rank;
	if ((card1Rank == card2Rank && card2Rank == card3Rank && card3Rank ==
		card4Rank && card4Rank != card5Rank) || (card2Rank == card3Rank &&
			card3Rank == card4Rank && card4Rank == card5Rank && card2Rank
			!= card1Rank)) {
		return TRUE;
	} // end if
	return FALSE;
} // end isFourOfAKind function


  /*------------------------------------------------------------------------------
  |  function: isStraightFlush(hand)
  |
  |  Purpose: Determines if a certain hand of cards is a "Straight Flush" by
  |			passing the hand to the isFlush and isStraight functions. If they
  |			both return true this means this hand is a Straight Flush.
  |  @param hand - Hand struct type that contains the array of Cards
  |  @return flag determining if the hand is a "Straight Flush"
  ------------------------------------------------------------------------------*/
int isStraightFlush(Hand hand) {
	return isFlush(hand) && isStraight(hand);
} // end isStraightFlush function


  /*------------------------------------------------------------------------------
  |  function: assignPokerRanks(hands, players)
  |
  |  Purpose: Iterates through each hand in the hands array and calls the
  |			classifyHand function passing the hand as an argument.
  |  @param hands - 1D Hand array used to represent the hands
  |  @param players - the number of players participating in the game
  ------------------------------------------------------------------------------*/
void assignPokerRanks(Hand hands[MAX_PLAYERS], int players) {
	int i;
	for (i = 0; i < players; i++) {
		classifyHand(&hands[i]);
	} // end for
} // end assignPokerRank function


  /*------------------------------------------------------------------------------
  |  function: classifyHand(handPtr)
  |
  |  Purpose: Determines and stores the poker ranking of the hand that is passed
  |			by testing it on the different poker ranking functions. Each hand
  |			can only be assigned one rank so the function returns once the hand
  |			is matched to a ranking.
  |  @param handPtr - pointer to Hand struct type that contains the array of Cards
  ------------------------------------------------------------------------------*/
void classifyHand(Hand* handPtr) {
	if (isStraightFlush(*handPtr)) {
		(*handPtr).pokerRank = STRAIGHT_FLUSH;
		return;
	} // end if
	if (isFourOfAKind(*handPtr)) {
		(*handPtr).pokerRank = FOUR_OF_A_KIND;
		return;
	} // end if
	if (isFullHouse(*handPtr)) {
		(*handPtr).pokerRank = FULL_HOUSE;
		return;
	} // end if
	if (isFlush(*handPtr)) {
		(*handPtr).pokerRank = FLUSH;
		return;
	} // end if
	if (isStraight(*handPtr)) {
		(*handPtr).pokerRank = STRAIGHT;
		return;
	} // end if
	if (isThreeOfAKind(*handPtr)) {
		(*handPtr).pokerRank = THREE_OF_A_KIND;
		return;
	} // end if
	if (isTwoPairs(*handPtr)) {
		(*handPtr).pokerRank = TWO_PAIRS;
		return;
	} // end if
	if (isOnePair(*handPtr)) {
		(*handPtr).pokerRank = ONE_PAIR;
		return;
	} // end if
	if (isHighCard(*handPtr)) {
		(*handPtr).pokerRank = HIGH_CARD;
		return;
	} // end if
} // end classifyHand function


  /*------------------------------------------------------------------------------
  |  function: displayPokerRanks(hands, players)
  |
  |  Purpose: Prints the poker rank of each hand along with the winner status if
  |			applicable. Players and their poker rank are printed on a field of
  |			16 spaces to accomodate the largest poker rank "Three of a Kind"
  |			and properly align the winner labels.
  |  @param hands - 1D Hand array used to represent the hands
  |  @param players - the number of players participating in the game
  ------------------------------------------------------------------------------*/
void displayPokerRanks(Hand hands[MAX_PLAYERS], int players) {
	int pokerRankOfWinners = determinePokerRankOfWinners(hands, players);
	const int OFF_BY_ONE = 1;
	int i;
	for (i = 0; i < players; i++) {
		printf("Player %d:  %-16s", i + OFF_BY_ONE,
			POKER_RANK_NAMES[hands[i].pokerRank]);
		if (hands[i].pokerRank == pokerRankOfWinners) {
			printf(WINNER_LABEL);
		} // end if
		printf(NEWLINE);
	} // end for
} // end displayPokerRanks function


  /*------------------------------------------------------------------------------
  |  function: determinePokerRankOfWinners(hands, players)
  |
  |  Purpose: Determines what is the poker rank of the hands that have won the
  |			game by iterating through the hands and finding the max poker rank.
  |  @param hands - 1D Hand array used to represent the hands
  |  @param players - the number of players participating in the game
  |  @return - the poker rank of the hands that won
  ------------------------------------------------------------------------------*/
int determinePokerRankOfWinners(Hand hands[MAX_PLAYERS], int players) {
	int i;
	int pokerRankOfWinners = 0;
	for (i = 0; i < players; i++) {
		if (hands[i].pokerRank > pokerRankOfWinners) {
			pokerRankOfWinners = hands[i].pokerRank;
		} // end if
	} // end for
	return pokerRankOfWinners;
} // end determinePokerRankOfWinners function


  /*------------------------------------------------------------------------------
  |  function: populatePresetHands(presetHands)
  |
  |  Purpose: Populates a set of hands that each represent an example of each
  |			poker ranking so we can use it for further testing.
  |  @param presetHands - 1D Hand array used to represent the preset hands
  ------------------------------------------------------------------------------*/
void populatePresetHands(Hand presetHands[POKER_RANKINGS]) {
	Hand handHighCard = {{{DIAMONDS, _3}, {HEARTS, _6}, {CLUBS, _T},
		{SPADES, _J}, {HEARTS, _K}}};
	Hand handOnePair = {{{HEARTS, _A}, {CLUBS, _A}, {DIAMONDS, _2},
		{HEARTS, _6}, {SPADES, _8}}};
	Hand handTwoPair = {{{SPADES, _6}, {CLUBS, _6}, {DIAMONDS, _T},
		{CLUBS, _T}, {DIAMONDS, _K}}};
	Hand handThreeOfAKind = {{{CLUBS, _5}, {DIAMONDS, _8}, {CLUBS, _J},
		{HEARTS, _J}, {DIAMONDS, _J}}};
	Hand handStraight = {{{DIAMONDS, _2}, {CLUBS, _3}, {SPADES, _4},
		{HEARTS, _5}, {SPADES, _6}}};
	Hand handFlush = {{{CLUBS, _3}, {CLUBS, _4}, {CLUBS, _6},
		{CLUBS, _8}, {CLUBS, _Q}}};
	Hand handFullHouse = {{{HEARTS, _T}, {CLUBS, _T}, {HEARTS, _K},
		{CLUBS, _K}, {SPADES, _K}}};
	Hand handFourOfAKind = {{{HEARTS, _A}, {CLUBS, _A}, {SPADES, _A},
		{DIAMONDS, _A}, {CLUBS, _8}}};
	Hand handStraightFlush = {{{CLUBS, _5}, {CLUBS, _6}, {CLUBS, _7},
		{CLUBS, _8}, {CLUBS, _9}}};
	presetHands[HIGH_CARD] = handHighCard;
	presetHands[ONE_PAIR] = handOnePair;
	presetHands[TWO_PAIRS] = handTwoPair;
	presetHands[THREE_OF_A_KIND] = handThreeOfAKind;
	presetHands[STRAIGHT] = handStraight;
	presetHands[FLUSH] = handFlush;
	presetHands[FULL_HOUSE] = handFullHouse;
	presetHands[FOUR_OF_A_KIND] = handFourOfAKind;
	presetHands[STRAIGHT_FLUSH] = handStraightFlush;
} // end populatePresetHands function


  /*------------------------------------------------------------------------------
  |  function: testPresetHandsPokerRank(presetHands)
  |
  |  Purpose: Tests each hand of preset cards to validate the poker ranking system
  |			and then displays the results to the console.
  |  @param presetHands - 1D Hand array used to represent the preset hands
  ------------------------------------------------------------------------------*/
void testPresetHandsPokerRank(Hand presetHands[POKER_RANKINGS]) {
	int i;
	for (i = 0; i < POKER_RANKINGS; i++) {
		classifyHand(&presetHands[i]);
	} // end for
	int cardsPerHandIndex;
	for (i = 0; i < POKER_RANKINGS; i++) {
		printf("Hand: ");
		for (cardsPerHandIndex = 0; cardsPerHandIndex < CARDS_PER_PLAYER;
			cardsPerHandIndex++) {
			printf("%s%s  ", SUIT_NAMES[presetHands[i].hand[cardsPerHandIndex].suit],
				RANK_NAMES[presetHands[i].hand[cardsPerHandIndex].rank]);
		} // end for
		printf("classifies as \"%s\"", POKER_RANK_NAMES[presetHands[i].pokerRank]);
		printf(NEWLINE);
	} // end for
} // end testPresetHandsPokerRank function