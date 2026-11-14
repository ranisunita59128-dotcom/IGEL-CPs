
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PLAYERS 3
#define ROUNDS 3

void showBoxes()
{
    printf("\n");
    printf("       +---------+\n");
    printf("       |  BOX 1  |\n");
    printf("       +---------+\n");

    printf("       +---------+\n");
    printf("       |  BOX 2  |\n");
    printf("       +---------+\n");

    printf("       +---------+\n");
    printf("       |  BOX 3  |\n");
    printf("       +---------+\n");
}

void openingAnimation()
{
    int i;

    printf("\nOpening your mystery box");

    for(i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        // Simple suspense effect
        for(volatile long j = 0; j < 15000000; j++);
    }

    printf("\n");
}

void showInstructions()
{
    printf("\n========== HOW TO PLAY ==========\n");
    printf("1. Three players can participate.\n");
    printf("2. Each player gets 3 rounds.\n");
    printf("3. Choose one box from 1, 2 or 3.\n");
    printf("4. Box 1 gives Rs. 500.\n");
    printf("5. Box 2 gives 1000 points.\n");
    printf("6. Box 3 gives 2000 points.\n");
    printf("7. Jackpot gives 5000 points.\n");
    printf("8. Highest scorer wins!\n");
    printf("=================================\n");
}

void playGame()
{
    char names[PLAYERS][50];
    int scores[PLAYERS] = {0, 0, 0};

    int choice, reward;
    int i, round, j, jackpot;
    int tempScore;
    char tempName[50];

    printf("\nEnter names of 3 players:\n");

    for(i = 0; i < PLAYERS; i++)
    {
        printf("Player %d Name: ", i + 1);
        scanf("%49s", names[i]);
    }

    for(i = 0; i < PLAYERS; i++)
    {
        printf("\n********************************\n");
        printf("          PLAYER: %s\n", names[i]);
        printf("********************************\n");

        for(round = 1; round <= ROUNDS; round++)
        {
            printf("\n========== ROUND %d ==========\n", round);

            showBoxes();

            printf("\nChoose your box (1-3): ");

            if(scanf("%d", &choice) != 1)
            {
                printf("Invalid input! Game cancelled.\n");
                return;
            }

            if(choice < 1 || choice > 3)
            {
                printf("Invalid box! Choose between 1 and 3.\n");
                round--;
                continue;
            }

            openingAnimation();

            jackpot = rand() % 10;

            if(jackpot == 0)
            {
                reward = 5000;

                printf("\n");
                printf("********************************\n");
                printf("       JACKPOT WINNER!\n");
                printf("********************************\n");
                printf("You won Rs. 5000!\n");
            }
            else if(choice == 1)
            {
                reward = 500;
                printf("\nCongratulations!\n");
                printf("You won Rs. 500!\n");
            }
            else if(choice == 2)
            {
                reward = 1000;
                printf("\nAmazing!\n");
                printf("You won a Smartphone!\n");
            }
            else
            {
                reward = 2000;
                printf("\nLucky Winner!\n");
                printf("You won a Gold Coin!\n");
            }

            scores[i] += reward;

            printf("\nPoints earned: %d\n", reward);
            printf("Total score: %d\n", scores[i]);
            printf("Remaining Chances: %d\n",
                   ROUNDS - round);
        }

        printf("\n%s completed the game!\n", names[i]);
    }

    // Leaderboard Sorting

    for(i = 0; i < PLAYERS - 1; i++)
    {
        for(j = 0; j < PLAYERS - 1 - i; j++)
        {
            if(scores[j] < scores[j + 1])
            {
                tempScore = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tempScore;

                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);
            }
        }
    }

    // Display Leaderboard

    printf("\n");
    printf("====================================\n");
    printf("             LEADERBOARD\n");
    printf("====================================\n");

    for(i = 0; i < PLAYERS; i++)
    {
        printf("\nRank %d: %s\n", i + 1, names[i]);
        printf("Score: %d\n", scores[i]);
    }

    printf("\n************************************\n");
    printf("          GAME WINNER\n");
    printf("************************************\n");

    printf("Winner: %s\n", names[0]);
    printf("Winning Score: %d\n", scores[0]);

    printf("\nCongratulations %s!\n", names[0]);
    printf("Thank you for playing!\n");
}

int main()
{
    int menuChoice;

    srand(time(NULL));

    do
    {
        printf("\n\n");
        printf("====================================\n");
        printf("          MYSTERY BOX GAME\n");
        printf("====================================\n");

        printf("\n1. START NEW GAME\n");
        printf("2. HOW TO PLAY\n");
        printf("3. EXIT GAME\n");

        printf("\nEnter your choice: ");

        if(scanf("%d", &menuChoice) != 1)
        {
            printf("\nInvalid input! Please restart.\n");
            return 0;
        }

        switch(menuChoice)
        {
            case 1:
                playGame();
                break;

            case 2:
                showInstructions();
                break;

            case 3:
                printf("\nThank you for playing!\n");
                printf("See you again!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while(menuChoice != 3);

    return 0;
}
