#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int stack[20000];

char chaine[20000];

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

int main()
{

    srand(time(NULL));

    int i = 0;
    int stack_len = 0;
    int chaine_len = 0;

    int longueur = rand() % 100;

    while (i < longueur || stack_len > 0)
    {

        bool ajouter = rand() % 2;

        if (ajouter)
        {
            int type = rand() % 4;

            switch (type)
            {
            case 0:
                chaine[chaine_len] = (rand() % 26) + 65;
                chaine_len++;
                break;
            case 1:
                chaine[chaine_len] = '(';
                chaine_len++;
                stack[stack_len] = '(';
                stack_len++;
                break;
            case 2:
                chaine[chaine_len] = '[';
                chaine_len++;
                stack[stack_len] = '[';
                stack_len++;
                break;
            case 3:
                chaine[chaine_len] = '{';
                chaine_len++;
                stack[stack_len] = '{';
                stack_len++;
                break;
            default:
                exit(1);
            }
        }
        else
        {
            if (stack_len == 0)
            {
                continue;
            }

            int ascii = stack[stack_len - 1];
            stack_len--;
            chaine[chaine_len] = fermante(ascii);
            chaine_len++;
        }

        i++;
    }

    chaine[chaine_len] = '\0';
    printf("%s", chaine);
}
