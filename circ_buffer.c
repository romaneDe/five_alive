
#include <stddef.h>
#include <stdio.h>

#define NB_CARTES_TOTAL 75

typedef enum {
    INVALID,
    N1, // number 1
    N2,// number 1
    N21, // number 21
    PASS, // passer
    INVERSION, // inversion
} cardType_t;



typedef struct stack {
    cardType_t valeurs[NB_CARTES_TOTAL];
    int64_t first_index;
    int64_t last_index;
} stack_t;

stack_t pioche;
stack_t main_joueur1;
stack_t main_joueur2;

// take card from top 
cardType_t piocherCarte(stack_t * stack) {
    if (stack->first_index >= stack->last_index) {
	    return INVALID; // the stack is empty
    }

    // remove card at bottom
    stack->first_index ++;

    // return first card

    return stack->valeurs[(stack->first_index - 1) % NB_CARTES_TOTAL];
}

// add card at top
void ajouterCarteAtTop(stack_t * stack, cardType_t card) {

    // add card at bottom
    stack->first_index --;

    // set the new card value
    stack->valeurs[stack->first_index % NB_CARTES_TOTAL] = card;

}


// add card at bottom
void ajouterCarteAtBottom(stack_t * stack, cardType_t card) {

    // set the new card value
    stack->valeurs[stack->last_index % NB_CARTES_TOTAL] = card;

    // add card at bottom
    stack->last_index ++;

}


// put all available cards in a stack
void initialiseStack(stack_t * stack) {

    int valeurs[] = {
        // list of all available cards
        N1, N1, N21, PASS, INVERSION,
        //etc...
    };

    for (int i = 0; i < NB_CARTES_TOTAL; i++) {
        ajouterCarteAtTop(stack, valeurs[i]); // add to pioche
    }
}

// count the number of cards in a stack
int numCardsinPioche(stack_t * stack) {

    return stack->last_index - stack->first_index;
}

void shuffle(cardType_t cards[], int num) {
    // implement your favorite shuffle algorithm
}

void melangerStack(stack_t * stack) {
 

    int num_cards_in_pioche = numCardsinPioche(stack);


   if (num_cards_in_pioche == 0) return; // the stack was empty, nothing to do


    // Temporary store all the values of all cards in the pioche
    // we need to store in an array, because arrays are easy to shuffle  
    cardType_t cards[num_cards_in_pioche];

    // read all values in the pioche
    int64_t i ;
    for(i = stack ->first_index; i < stack->last_index; i++) { // traverse the stack
        cards[i] = stack->valeurs[i]; // save the card type
    }

    // shuffle the array of card types
    shuffle(cards, num_cards_in_pioche);

    // after shuffle, adjust values of all the cards in the pioche
    for(i = stack ->first_index; i < stack->last_index; i++) { // traverse the stack
        stack->valeurs[i] = cards[i]; // save the card type
    }

}


int main(void) {
    
    initialiseStack(&pioche);
    printf("num cards in pioche %d\n", numCardsinPioche(&pioche));

    melangerStack(&pioche);
}


