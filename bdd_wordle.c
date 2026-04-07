#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_WORDS 10000
#define WORD_LENGTH 6  // 5 lettres + '\0'

char words[MAX_WORDS][WORD_LENGTH];
int word_count = 0;

void charger_mots() {
    FILE *file = fopen("ressource/bdd_wordle.txt", "r");
    
    if (file == NULL) {
        printf("Erreur ouverture fichier\n");
        exit(1);
    }

    char ligne[100];

    while (fgets(ligne, sizeof(ligne), file)) {
        
        ligne[ strcspn(ligne, "\n") ] = 0;

        
        if (strlen(ligne) == 5) {
            strcpy(words[word_count], ligne);
            word_count++;
        }
    }

    fclose(file);
}


char* choisir_mot() {
    srand(time(NULL));
    int index = rand() % word_count;
    return words[index];
}

int est_valide(char *mot) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(words[i], mot) == 0) {
            return 1;
        }
    }
    return 0;
}

void comparer(char *secret, char *proposition) {
    for (int i = 0; i < 5; i++) {
        if (proposition[i] == secret[i]) {
            printf("[Yes] %c ", proposition[i]); 
        } else {
            int present = 0;
            for (int j = 0; j < 5; j++) {
                if (proposition[i] == secret[j]) {
                    present = 1;
                    break;
                }
            }
            if (present) {
                printf("[~] %c ", proposition[i]);
            } else {
                printf("[ ] %c ", proposition[i]); 
            }
        }
    }
    printf("\n");
}

int main() {
    charger_mots();

    char *secret = choisir_mot();
    char mot[WORD_LENGTH];

    int essais = 0;

    while (essais < 6) {
        printf("Entrez un mot de 5 lettres : ");
        scanf("%s", mot);

        if (strlen(mot) != 5 || !est_valide(mot)) {
            printf("Mot invalide ! Réessayez.\n");
            continue; 
        }

        essais++;

        comparer(secret, mot);

        if (strcmp(secret, mot) == 0) {
            printf(" Gagné !\n");
            return 0;
        }
    }

    printf("Perdu ! Le mot était : %s\n", secret);

   char choix;
   printf("Rejouer ? (o/n) : ");
   scanf(" %c", &choix);

   if (choix == 'o') {
      main();
   }
    return 0;
}

