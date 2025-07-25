#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 32
#define SECRET_PASSWORD "papa123"
#define SCORE_FILE "score.txt"

// Fonction vulnérable : buffer overflow
void saisir_pseudo(char *pseudo) {
    char buffer[16]; // volontairement trop petit
    printf("\nEntrez votre pseudo : ");
    gets(buffer); // gets est dangereuse !
    strcpy(pseudo, buffer); // pas de vérification de taille
    printf("Bienvenue, %s !\n", pseudo);
}

// Fonction vulnérable : mot de passe en clair
void afficher_message_secret() {
    char mdp[32];
    printf("\nMot de passe pour le message secret : ");
    scanf("%31s", mdp);
    if (strcmp(mdp, SECRET_PASSWORD) == 0) {
        printf("Bravo ! Le message secret est : Papa, tu es un hacker !\n");
    } else {
        printf("Mauvais mot de passe !\n");
    }
}

// Fonction vulnérable : format string
void sauvegarder_score(const char *pseudo, int score) {
    FILE *f = fopen(SCORE_FILE, "a");
    if (!f) {
        printf("Erreur d'ouverture du fichier !\n");
        return;
    }
    printf("\nEntrez un commentaire pour ton score : ");
    char commentaire[64];
    scanf("%63s", commentaire);
    // Vulnérabilité format string !
    fprintf(f, commentaire);
    fprintf(f, " : %s a %d points\n", pseudo, score);
    fclose(f);
    printf("Score sauvegardé !\n");
}

// Fonction vulnérable : lecture non sécurisée
void charger_score() {
    char ligne[128];
    FILE *f = fopen(SCORE_FILE, "r");
    if (!f) {
        printf("Aucun score sauvegardé.\n");
        return;
    }
    printf("\n--- Scores sauvegardés ---\n");
    while (fgets(ligne, sizeof(ligne), f)) {
        printf(ligne); // Vulnérabilité format string !
    }
    fclose(f);
}

// Fonction cachée (bonus pour reverse engineering)
void fonction_cachee() {
    printf("\nBravo, tu as trouvé la fonction cachée !\nFlag : PAPA{reverse_is_fun}\n");
}

void menu() {
    char pseudo[MAX_NAME] = "Invité";
    int score = 0;
    int choix;
    while (1) {
        printf("\n--- Menu Principal ---\n");
        printf("1. Saisir pseudo\n");
        printf("2. Afficher message secret\n");
        printf("3. Sauvegarder score\n");
        printf("4. Charger score\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                saisir_pseudo(pseudo);
                break;
            case 2:
                afficher_message_secret();
                break;
            case 3:
                printf("\nEntrez ton score : ");
                scanf("%d", &score);
                sauvegarder_score(pseudo, score);
                break;
            case 4:
                charger_score();
                break;
            case 5:
                printf("Au revoir !\n");
                exit(0);
            default:
                printf("Choix invalide !\n");
        }
    }
}

int main() {
    printf("Bienvenue dans le défi Reverse Engineering pour Papa !\n");
    menu();
    return 0;
}

// Conseils pour la compilation :
// Sous Linux : gcc -o defi_papa.exe defi_papa.c -static
// Puis donne le .exe à ton père pour Windows !
// (Optionnel : strip defi_papa.exe pour enlever les symboles)