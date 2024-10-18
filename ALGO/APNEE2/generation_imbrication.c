#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char ouvrante()
{
    int type = rand() % 3;
    switch (type)
    {
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

char fermante(char c)
{
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

int main(int argc, char *argv[])
{

    srand(time(NULL));

    int maj = 0;
    int i = 0;
    int stack_len = 0; // stack = PileVide()
    int longueur = atoi(argv[1]);
    int imbrication = atoi(argv[2]);
    int stack[2 * longueur];
    char c = ' ';
    int niveau_imbrication = 0;
    while (i < longueur)
    {
        while (niveau_imbrication < imbrication) // tant qu'il reste des caractères à imprimer
        {
            int ajouter = rand() % 2; // choix aléatoire
            switch (ajouter)
            {
            case 0:                   // { c est une parenthèse ouvrante }
                c = ouvrante();       // parenthèse ouvrante
                stack[stack_len] = c; // Empiler(stack, c)
                stack_len++;
                niveau_imbrication++;
                break;
            case 1: // { c est une parenthèse fermante }
                maj = rand() % 2;
                switch (maj)
                {
                case 0:
                    c = (rand() % 26) + 97; // caractère non parenthèse (minuscule)
                    break;
                case 1:
                    c = (rand() % 26) + 65; // caractère non parenthèse (majuscule)
                    break;
                default:
                    exit(1);
                }
                break;
            }
            printf("%c", c);
            i++;
        }
        while (niveau_imbrication > 0) // tant qu'il reste des caractères à imprimer
        {
            int ajouter = rand() % 3; // choix aléatoire
            switch (ajouter)
            {
            case 0:                                 // { c est une parenthèse ouvrante }
                c = fermante(stack[stack_len - 1]); // parenthèse fermante correspondant à Sommet(stack)
                stack_len--;                        // Dépiler(stack)
                niveau_imbrication--;
                break;
            case 1: // { c est une parenthèse fermante }
                maj = rand() % 2;
                switch (maj)
                {
                case 0:
                    c = (rand() % 26) + 97; // caractère non parenthèse (minuscule)
                    break;
                case 1:
                    c = (rand() % 26) + 65; // caractère non parenthèse (majuscule)
                    break;
                default:
                    exit(1);
                }
                break;
            case 2:
                c = ouvrante();       // parenthèse ouvrante
                stack[stack_len] = c; // Empiler(stack, c)
                stack_len++;
                niveau_imbrication++;
                break;
            }
            printf("%c", c);
            i++;
        }
    }

    printf("\n");
}
