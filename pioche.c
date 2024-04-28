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




typedef struct card {
    cardType_t type;
    struct card * next; // pointer to next card in the list
} card_t;



typedef struct jeu {
    card_t cards[NB_CARTES_TOTAL];
    card_t * pioche; // first card, at the top of the stack (pioche)
    card_t * reserve; // cards that are NOT in the pioche (par example dans la main d'un joueur)
} jeu_t;

jeu_t mon_jeu; // statically allocated



// take a card at the top of the stack and return its value
card_t *piocherCarte(jeu_t * jeu) {
    if (jeu->pioche == NULL) {
        return NULL; // pioche is empty
    }
    // take first card
    card_t * top_card = jeu->pioche;

    // remove the card at the top
    jeu->pioche = jeu->pioche->next;

    // clean the next pointer
    top_card->next = NULL;

    // return first card value
    return top_card;
}

// Ajoute une carte au dessus de la pioche
void ajouterALaPioche(jeu_t *jeu, card_t *card) {
    card->next = jeu->pioche;
    jeu->pioche = card;
}

// Ajoute une carte au dessus de la reserve
void ajouterALaReserve(jeu_t *jeu, card_t *card) {
    card->next = jeu->reserve;
    jeu->reserve = card;
}



// take a card from the reserve
card_t * take_from_reserve(jeu_t * jeu) {
    if (jeu->reserve == NULL) return NULL; // reserve is empty
    card_t *top_card = jeu->reserve;
    jeu->reserve = jeu->reserve->next; // remove the card from the reserve
    top_card->next = NULL; // clean the pointer
    return top_card;
}

void initialiseJeu(jeu_t * jeu) {

    int valeurs[] = {
        // list of all available cards
        N1, N1, N21, PASS, INVERSION,
        //etc...
    };


    for (int i = 0; i < NB_CARTES_TOTAL; i++) {
        jeu->cards[i].type = valeurs[i]; // initialize card type
        jeu->cards[i].next = NULL; // clear pointer
        ajouterALaPioche(jeu, jeu->cards + i); // add to reserve
    }
}

// count the number of cards in the pioche
int numCardsinPioche(jeu_t * jeu) {
    int num = 0;
    card_t * card = jeu->pioche;
    while (card) { // traverse the chain, until we find the last card
        num ++;
        card = card->next;
    }
    return num;
}

void shuffle(cardType_t cards[], int num) {
    // implement your favorite shuffle algorithm
}

void melangerPioche(jeu_t * jeu) {
    card_t * card = jeu->pioche;
    if (card == NULL) return; // the pioche was empty

    // Temporary store all the values of all cards in the pioche
    // we need to store in an array, because arrays are easy to shuffle  
    int num_cards_in_pioche = numCardsinPioche(jeu);

    cardType_t cards[num_cards_in_pioche];

    int i = 0;

    // read all values in the pioche
    card = jeu->pioche;
    while (card) { // traverse the chain, until we find the last card
        cards[i] = card->type; // save the card type
        card = card->next;
    }

    // shuffle the array of card types
    shuffle(cards, num_cards_in_pioche);

    // after shuffle, adjust values of all the cards in the pioche
    card = jeu->pioche;
    while (card) { // traverse the chain, until we find the last card
        card->type = cards[i]; // save the card type
        card = card->next;
    }

}


int main(void) {
    
    initialiseJeu(&mon_jeu);
    printf("num cards in pioche %d\n", numCardsinPioche(&mon_jeu));
}