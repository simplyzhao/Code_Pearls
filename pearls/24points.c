#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef int bool;
#define TRUE        1
#define FALSE       0

#define CARDS_NUM   4
#define GAME_TARGET 24
#define THRESHOLD   1E-6    /* since we're using 'double' */
#define LENGTH_MAX  18      /* four cards, three operator, three pair of parentheses, and '\0' */

double cards[CARDS_NUM];
char   oprecords[CARDS_NUM][LENGTH_MAX];

void
concatenates(char *result, char *arg1, char *op, char *arg2)
{
    strcpy(result, "(");
    strcat(result, arg1);
    strcat(result, op);
    strcat(result, arg2);
    strcat(result, ")");
}

void
solution_24points(double *cards, int cards_num)
{
    int i, j;
    double arg1, arg2;
    char arg1_str[LENGTH_MAX];
    char arg2_str[LENGTH_MAX];

    if (cards_num == 1)
    {
        if (fabs(cards[0] - GAME_TARGET) <= THRESHOLD)
        {
            printf("%s\n", oprecords[0]);
        }
        return;
    }

    /* Algorithm:
     * 1. pick up two random cards
     * 2. apply all allowed operators to the two cards
     * 3. insert the above result to the 'cards'
     * 4. repeat steps 1 to 3 until the number of cards reduced to 1
     * Refer: http://blog.csdn.net/hackbuteer1/article/details/6712385
     * */
    for (i = 0; i < cards_num; i++)
    {
        for (j = i + 1; j < cards_num; j++)
        {
            arg1 = cards[i];
            arg2 = cards[j];
            strncpy(arg1_str, oprecords[i], LENGTH_MAX);
            strncpy(arg2_str, oprecords[j], LENGTH_MAX);

            /* Trick: 
             * We dont need a new array here.
             * It just works by putting cards[cards_num -1 ] to cards[j] and putting
             * the calculation result to cards[i].
             */
            cards[j] = cards[cards_num - 1];
            strncpy(oprecords[j], oprecords[cards_num - 1], LENGTH_MAX);

            /* apply all allowed operators */
            cards[i] = arg1 + arg2;
            concatenates(oprecords[i], arg1_str, "+", arg2_str);
            solution_24points(cards, cards_num - 1);

            cards[i] = arg1 * arg2;
            concatenates(oprecords[i], arg1_str, "*", arg2_str);
            solution_24points(cards, cards_num - 1);

            cards[i] = arg1 - arg2;
            concatenates(oprecords[i], arg1_str, "-", arg2_str);
            solution_24points(cards, cards_num - 1);

            cards[i] = arg2 - arg1;
            concatenates(oprecords[i], arg2_str, "-", arg1_str);
            solution_24points(cards, cards_num - 1);

            if (arg1 != 0)
            {
                cards[i] = arg2 / arg1;
                concatenates(oprecords[i], arg2_str, "/", arg1_str);
                solution_24points(cards, cards_num - 1);
            }

            if (arg2 != 0)
            {
                cards[i] = arg1 / arg2;
                concatenates(oprecords[i], arg1_str, "/", arg2_str);
                solution_24points(cards, cards_num - 1);
            }

            /* Important */
            cards[i] = arg1;
            cards[j] = arg2;
            strncpy(oprecords[i], arg1_str, LENGTH_MAX);
            strncpy(oprecords[j], arg2_str, LENGTH_MAX);
        }
    }
}

int
main(int argc, char **argv)
{
    int i, card;
    for (i = 0; i < CARDS_NUM; ++i)
    {
        printf("Please Enter the %dth Card Number: ", i + 1);
        scanf("%d", &card);

        cards[i] = card;
        snprintf(oprecords[i], LENGTH_MAX, "%d", card);
    }

    solution_24points(cards, CARDS_NUM);
}
