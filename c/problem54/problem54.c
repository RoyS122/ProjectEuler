#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFFER_SIZE 5

// --- DynArray pour stocker les cartes
typedef struct {
    unsigned int *array;
    unsigned int length;
} DynArray;

// --- Carte
typedef struct {
    unsigned int value;
    unsigned int suit;
} Card;

// --- Main
typedef struct {
    DynArray *cards;          // tableau dynamique de valeurs et suits
    unsigned int totalvalue;  // somme des valeurs (facultatif)
    unsigned int rank;        // rank calculé (facultatif)
} Hand;

// --- Structure pour score d’une main
typedef struct {
    unsigned int rank;       // 1..10
    unsigned int mainValue;  // valeur principale de la combinaison
    unsigned int kickers[5]; // kickers triés décroissant
} HandScore;

// --- Fonctions
Card parseCard(char valueChar, char suitChar) {
    Card card;
    switch (valueChar) {
        case '2'...'9': card.value = valueChar - '0'; break;
        case 'T': card.value = 10; break;
        case 'J': card.value = 11; break;
        case 'Q': card.value = 12; break;
        case 'K': card.value = 13; break;
        case 'A': card.value = 14; break;
        default: card.value = 0;
    }
    switch (suitChar) {
        case 'H': card.suit = 0; break;
        case 'D': card.suit = 1; break;
        case 'C': card.suit = 2; break;
        case 'S': card.suit = 3; break;
        default: card.suit = 0;
    }
    return card;
}

// --- Ajouter une carte dans une main
void addCard(Hand *hand, Card card) {
    if (!hand->cards) {
        hand->cards = malloc(sizeof(DynArray));
        hand->cards->array = malloc(BUFFER_SIZE * 2 * sizeof(unsigned int));
        hand->cards->length = 0;
    }
    DynArray *da = hand->cards;
    da->array[da->length++] = card.value;
    da->array[da->length++] = card.suit;
    hand->totalvalue += card.value;
}

// --- Libération mémoire
void freeHand(Hand *h) {
    if (h->cards) {
        free(h->cards->array);
        free(h->cards);
        h->cards = NULL;
    }
    h->totalvalue = 0;
    h->rank = 0;
}

// --- Évaluer la main
HandScore evaluate(Hand hand) {
    HandScore score = {0,0,{0,0,0,0,0}};
    if (!hand.cards || hand.cards->length != 10) return score;

    unsigned int values[5], suits[5];
    for (int i=0;i<5;i++){
        values[i] = hand.cards->array[i*2];
        suits[i]  = hand.cards->array[i*2+1];
    }

    // Tri décroissant
    for (int i=0;i<5;i++)
        for (int j=i+1;j<5;j++)
            if (values[i]<values[j]){
                unsigned int tmp=values[i]; values[i]=values[j]; values[j]=tmp;
            }

    // Comptage occurrences
    unsigned int counts[15]={0};
    for (int i=0;i<5;i++) counts[values[i]]++;

    bool flush = (suits[0]==suits[1] && suits[1]==suits[2] && suits[2]==suits[3] && suits[3]==suits[4]);
    bool straight = true;
    for (int i=0;i<4;i++)
        if (values[i]!=values[i+1]+1){ straight=false; break; }

    unsigned int four=0, three=0, pairs[2]={0};
    int pairCount=0;
    for (int v=14;v>=2;v--){
        if (counts[v]==4) four=v;
        if (counts[v]==3) three=v;
        if (counts[v]==2 && pairCount<2) pairs[pairCount++]=v;
    }

    // Déterminer rank et mainValue
    if (straight && flush && values[0]==14){ score.rank=10; score.mainValue=14; }
    else if (straight && flush){ score.rank=9; score.mainValue=values[0]; }
    else if (four){ score.rank=8; score.mainValue=four; }
    else if (three && pairCount==1){ score.rank=7; score.mainValue=three; }
    else if (flush){ score.rank=6; score.mainValue=values[0]; }
    else if (straight){ score.rank=5; score.mainValue=values[0]; }
    else if (three){ score.rank=4; score.mainValue=three; }
    else if (pairCount==2){ score.rank=3; score.mainValue=(pairs[0]>pairs[1]?pairs[0]:pairs[1]); }
    else if (pairCount==1){ score.rank=2; score.mainValue=pairs[0]; }
    else { score.rank=1; score.mainValue=values[0]; }

    // Remplir kickers
    int k=0;
    if (score.rank==8 || score.rank==4 || score.rank==2){
        for (int i=0;i<5;i++)
            if (values[i]!=score.mainValue)
                score.kickers[k++]=values[i];
    } else if (score.rank==7){ // Full House
        score.kickers[0]=pairs[0];
    } else if (score.rank==3){ // Two Pairs
        for (int i=0;i<5;i++)
            if (values[i]!=pairs[0] && values[i]!=pairs[1])
                score.kickers[0]=values[i];
    } else {
        for (int i=0;i<5;i++) score.kickers[i]=values[i];
    }

    return score;
}

// --- Comparer deux mains
unsigned int compareHands(Hand h1, Hand h2){
    HandScore s1 = evaluate(h1);
    HandScore s2 = evaluate(h2);

    if (s1.rank>s2.rank) return 1;
    if (s2.rank>s1.rank) return 2;

    if (s1.mainValue>s2.mainValue) return 1;
    if (s2.mainValue>s1.mainValue) return 2;

    for (int i=0;i<5;i++){
        if (s1.kickers[i]>s2.kickers[i]) return 1;
        if (s2.kickers[i]>s1.kickers[i]) return 2;
    }

    return 0;
}

// --- Lire le fichier et compter les victoires
void readHands(const char *file, unsigned int *p1, unsigned int *p2){
    FILE *f = fopen(file,"r");
    if(!f){ perror("fopen"); exit(1); }

    int c;
    unsigned int cardCount=0;
    Hand h1={NULL,0,0}, h2={NULL,0,0};
    *p1 = *p2 = 0;

    while ((c=fgetc(f))!=EOF){
        if (isalpha(c) || isdigit(c)){
            char value=c;
            char suit=fgetc(f);
            Card card = parseCard(value,suit);

            if (cardCount<5) addCard(&h1,card);
            else addCard(&h2,card);

            cardCount++;
            if (cardCount==10){
                unsigned int winner = compareHands(h1,h2);
                if (winner==1) (*p1)++; else if (winner==2) (*p2)++;
                freeHand(&h1);
                freeHand(&h2);
                cardCount=0;
                while((c=fgetc(f))!='\n' && c!=EOF); // passer à la ligne suivante
            }
        }
    }
    fclose(f);
}

void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}

int main(){
    unsigned int p1,p2;
    readHands("../data/0054_poker.txt",&p1,&p2); // chemin vers ton fichier

    printf("Player 1 wins: %u\nPlayer 2 wins: %u\n",p1,p2);
    wait();
    return 0;
}
