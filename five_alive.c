


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_CARTES 77
#define NB_CARTES_PAR_JOUEUR 10

typedef struct {
    int jour;
    int mois;
    int annee;
} t_naissance;

typedef struct {
    char prenom[20];
    t_naissance naissance;
    int vie;

} t_joueur;

typedef struct {
     int valeurs[NB_CARTES];
} JeuDeCartes;

// Prototypes de fonctions
JeuDeCartes initialiserJeuDeCartes();
void melanger(int tab[], int n);
void distribuerCartesInitiales(const JeuDeCartes *jeu, int *mains[], int nombreJoueurs);
void afficherDistributionCartes(int nombreJoueurs, int *mains[]);
void remplirJoueur(t_joueur *joueur, int nombre);
void demanderNombreJoueurs(int *nombre);
int LePlusAge(t_joueur *joueur, int nombre);

int main() {
    int nb;
    srand(time(NULL));
    demanderNombreJoueurs(&nb);
    t_joueur joueur[nb];
    printf("\nInformations du joueur :\n");
    remplirJoueur(joueur, nb);

    int indexPlusAge = LePlusAge(joueur, nb);

    printf("\nLe joueur le plus age est :\n");
    printf("%s\n A vous de commencer\n", joueur[indexPlusAge].prenom);

    JeuDeCartes jeu = initialiserJeuDeCartes();
    int valeurs[NB_CARTES];
    for (int i = 0; i <nb; i++) {
        melanger(jeu.valeurs,NB_CARTES);
    }

    // Déclaration et initialisation de la variable mains
    int *mains[nb];
    distribuerCartesInitiales(&jeu, mains, nb);

    // Affichage de cartes
    afficherDistributionCartes(nb, mains);

    return 0;
}

void demanderNombreJoueurs(int *nombre) {
    do {
        printf("Combien de joueurs souhaitez-vous ajouter (entre 2 et 6) ? ");
        scanf("%d", nombre);
    } while (*nombre < 2 || *nombre > 6);
}

void remplirJoueur(t_joueur *joueur, int nombre) {
    for (int i = 0; i < nombre; i++) {
        printf("Joueur %d :\n", i + 1);
        printf("Entrez votre prenom : ");
        scanf("%s", joueur[i].prenom);

        printf("Entrez votre jour de naissance: ");
        scanf("%d", &joueur[i].naissance.jour);

        printf("Entrez votre mois de naissance: ");
        scanf("%d", &joueur[i].naissance.mois);

        printf("Entrez votre annee de naissance: ");
        scanf("%d", &joueur[i].naissance.annee);
    }
}

int LePlusAge(t_joueur *joueur, int nombre) {
    int indexPlusAge = 0;

    for (int i = 1; i < nombre; i++) {
        if (joueur[i].naissance.annee < joueur[indexPlusAge].naissance.annee ||
            (joueur[i].naissance.annee == joueur[indexPlusAge].naissance.annee &&
             joueur[i].naissance.mois < joueur[indexPlusAge].naissance.mois) ||
            (joueur[i].naissance.annee == joueur[indexPlusAge].naissance.annee &&
             joueur[i].naissance.mois == joueur[indexPlusAge].naissance.mois &&
             joueur[i].naissance.jour < joueur[indexPlusAge].naissance.jour)) {
            indexPlusAge = i;
        }
    }

    return indexPlusAge;
}

JeuDeCartes initialiserJeuDeCartes() {
    JeuDeCartes jeu;

    // Définition des valeurs des cartes
    int valeurs[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
        4, 4, 4, 5, 5, 5, 5, 6, 6, 7, 0, 0, 0, 10, 10, 21, 21, 21, 21, 21, 1, 1, 2, 2, -1, 14, 14, 14, 14, 14, 14,15,15, 15, 15, 16, 17, 17,
    };
    for (int i = 0; i < NB_CARTES; i++) {
        jeu.valeurs[i] = valeurs[i];
    }
    return jeu;
}

void melanger(int tab[], int n) {
    srand(time(NULL));
    int i,j, temp;

    for(i=0;i<n;i++)
    {
        j=rand()%n;
        temp=tab[i];
        tab[i]=tab[j];
        tab[j]=temp;

    }
}


void distribuerCartesInitiales(const JeuDeCartes *jeu, int *mains[], int nombreJoueurs) {
    int index_carte = 0; // Index de la carte dans le jeu de cartes

    // Initialiser tous les pointeurs de mains à NULL
    for (int j = 0; j < nombreJoueurs; j++) {
        mains[j] = NULL;
    }

    for (int i = 0; i < NB_CARTES_PAR_JOUEUR; i++) {
        for (int j = 0; j < nombreJoueurs; j++) {
            // Allouer de la mémoire pour la main du joueur si ce n'est pas déjà fait
            if (mains[j] == NULL) {
                mains[j] = malloc(NB_CARTES_PAR_JOUEUR * sizeof(int));
            }
            // Distribuer la carte actuelle au joueur j
            mains[j][i] = jeu->valeurs[index_carte++];
            // Si l'index de carte dépasse la taille du jeu, revenir au début
            if (index_carte >= NB_CARTES) {
                index_carte = 0;
            }
        }
    }
}

void afficherDistributionCartes(int nombreJoueurs, int *mains[]) {
    printf("Distribution des cartes :\n");
    for (int j = 0; j < nombreJoueurs; j++) {
        printf("Main du joueur %d :\n", j + 1);
        for (int i = 0; i < NB_CARTES_PAR_JOUEUR; i++) {
            printf("%d\n", mains[j][i]); // Utiliser %d pour afficher un entier
        }
        printf("\n");
    }
}


Mettre à jour la pioche et les mains des joueurs??
typedef struct {
	int cartes[NB_CARTES_TOTAL];
	int taille;
} t_pioche;

t_pioche initialiserPioche() {
    t_pioche pioche;
    pioche.taille = NB_CARTES_TOTAL;
   
    for (int i = 0; i < NB_CARTES_TOTAL; i++) {
        pioche.cartes[i] = i
}
    return pioche;
}



int carteDisponible(t_pioche *pioche, int carte) {
    for (int i = 0; i < pioche->taille; i++) 
{
        if (pioche->cartes[i] == carte) {
            return true;
        }
    }
    return false;
}

void retirerCarte(t_pioche *pioche, int carte) {
    for (int i = 0; i < pioche->taille; i++) 
{
        if (pioche->cartes[i] == carte) {
            pioche->cartes[i] = pioche->cartes[pioche->taille - 1];
            pioche->taille--; 
            return;
        }
    }
}

void distribuerCartesInitiales(JeuDeCartes *jeu, int *mains[], int nombreJoueurs, t_pioche *pioche) {
    *pioche = initialiserPioche();

    for (int i = 0; i < NB_CARTES_PAR_JOUEUR; i++) {
        for (int j = 0; j < nombreJoueurs; j++) {
            if (mains[j] == NULL) {
                mains[j] = malloc(NB_CARTES_PAR_JOUEUR * sizeof(int));
            }

            int carte = piocherCarte(pioche);
            mains[j][i] = carte;
     	retirerCarte(pioche, carte);
        }
    }
}

