
#include <stddef.h>
#include <stdio.h>

#define NB_CARTES_TOTAL 75

typedef enum {
    INVALID = -1,
    N0, // number 0
    N1, // number 1
    N2,// number 1
    N21, // number 21
    PASS, // passer
    INVERSION, // inversion
    // etc...
} cardType_t;

int valeurs[NB_CARTES_TOTAL] = {
    // list of all available cards
    N0, N1, N2, N21, PASS, INVERSION,
    //etc...
};

// Rule for stack is that first_index must always be <= last_index
typedef struct stack {
    cardType_t valeurs[NB_CARTES_TOTAL];
    int first_index;
    int last_index;
} stack_t;


stack_t pioche;
stack_t main_joueur1;
stack_t main_joueur2;


// set a card into a stack
void setCard(stack_t * stack, int index, cardType_t card) {
    // adjust the index not to overflow the array
    index = index % NB_CARTES_TOTAL;
    if (index < 0) index += NB_CARTES_TOTAL;
    // set the card
    stack->valeurs[index] = card;
}


// get a card from a stack
cardType_t getCard(stack_t * stack, int index) {
    // adjust the index not to overflow the array
    index = index % NB_CARTES_TOTAL;
    if (index < 0) index += NB_CARTES_TOTAL;
    // return the card value
    return stack->valeurs[index];
}


// take card from top
// return INVALID is stack is empty
cardType_t piocherCarte(stack_t * stack) {
    if (stack->first_index >= stack->last_index) {
	    return INVALID; // the stack is empty
    }
    // remove card at bottom
    stack->first_index ++;
    // return first card
    return getCard(stack, stack->first_index - 1);
}


// add card at top of a stack
void ajouterCarteAtTop(stack_t * stack, cardType_t card) {
    // add card at bottom
    stack->first_index --;
    // set the new card value
    setCard(stack, stack->first_index, card );
}


// add card at bottom of a stack
void ajouterCarteAtBottom(stack_t * stack, cardType_t card) {
    // set the new card value
    setCard(stack, stack->last_index, card );
    // add card at bottom
    stack->last_index ++;
}


// put all available cards in a stack
void initialiseStack(stack_t * stack) {
    for (int i = 0; i < NB_CARTES_TOTAL; i++) {
        ajouterCarteAtTop(stack, valeurs[i]); // add to pioche
    }
}


// count the number of cards in a stack
int numCardsinPioche(stack_t * stack) {
    return stack->last_index - stack->first_index;
}


// shuffle an array of integer
void shuffle(int cards[], int num) {
    // implement your favorite shuffle algorithm
}

// Shuffle cards in a stack
void melangerStack(stack_t * stack) {
    int num_cards_in_pioche = numCardsinPioche(stack);
    if (num_cards_in_pioche == 0) return; // the stack was empty, nothing to do

    // Allocate temporary array to store all the values of all cards in the stack
    // We want to store in a separate array of integers, because arrays are easy to shuffle  
    int cards[num_cards_in_pioche];

    // get all values from the stack
    for(int i = 0; i < num_cards_in_pioche; i++) { // traverse the stack
        cards[i] = (int)piocherCarte(stack);
    }

    // shuffle the array of card types
    shuffle(cards, num_cards_in_pioche);

    // after shuffle, put back all the cards into the stack
    for(int i = 0; i < num_cards_in_pioche; i++) { // traverse the stack
        ajouterCarteAtTop(stack, (cardType_t)cards[i]);
    }
}


void print_stack(stack_t * stack) {
    for(int i = stack ->first_index; i < stack->last_index; i++) { // traverse the stack
        printf("  card %d : %u\n", i, getCard(stack, i));
    }
}


int main(void) {
    initialiseStack(&pioche);
    melangerStack(&pioche);
    printf("initialized: num cards in pioche %d\n", numCardsinPioche(&pioche));

    // print_stack(&pioche);

    // distribute cards to players
    int num_card_per_player = 5;
    for (int i = 0; i < num_card_per_player; i++) {
        // pioche and distribute to player 1
        cardType_t card = piocherCarte(&pioche);
        if (card != INVALID)
            ajouterCarteAtTop(&main_joueur1, card);
        // pioche and distribute to player 2
        card = piocherCarte(&pioche);
        if (card != INVALID)
            ajouterCarteAtTop(&main_joueur2, card);
    }

    printf("distributed:\n");
    printf("    num cards in main_joueur1 %d\n", numCardsinPioche(&main_joueur1));
    printf("    num cards in main_joueur2 %d\n", numCardsinPioche(&main_joueur2));
    printf("    num cards in pioche %d\n", numCardsinPioche(&pioche));
}


