#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char ouvrante() {
    int type = rand() % 3;
    switch(type) {
        case 0:
            return '(';
        case 1:
            return '[';
        case 2:
            return '{';
        default:
            exit(1);
        }
}

char fermante(char c) {
    switch (c)
    {
        case '(':
            return ')';
        case '[':
            return ']';
        case '{':
            return '}';
        default:
            exit(1);
    }
}

int main(int argc, char *argv[]) {

    srand( time( NULL ) );


    int i = 0;
    int stack_len = 0; // stack = PileVide()
    int longueur = atoi(argv[1]);
    int stack[2*longueur+1];
    char c = ' ';

    while (i < longueur) { // tant qu'il reste des caractères à imprimer
        int ajouter = rand() % 3; // choix aléatoire
        switch(ajouter) {
            case 0: // { c est une parenthèse ouvrante }
                c = ouvrante(); // parenthèse ouvrante
                stack[stack_len] = c; // Empiler(stack, c)
                stack_len++;
                break;
            case 1: // { c est une parenthèse fermante }
                if (stack_len > 0) { // non EstVide(stack)
                    //printf("stack_len = %d\n", stack_len);
                    c = fermante(stack[stack_len - 1]); // parenthèse fermante correspondant à Sommet(stack)
                    stack_len--; // Dépiler(stack)
                }
                else {
                    c = (rand() % 26) + 65; // caractère non parenthèse
                }
                break;
            case 2: // { c est un caractère quelconque }
                c = (rand() % 26) + 65; // caractère non parenthèse
                break;
        }
        printf("%c", c);
        i++;
    }
    while (stack_len > 0) { // refermer les parentheses ouvrantes quand la longueur a été atteinte
        c = fermante(stack[stack_len - 1]); // parenthèse fermante correspondant à Sommet(stack)
        stack_len--; // Dépiler(stack)
        printf("%c", c);
    }
    printf("\n");
}

