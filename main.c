#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int computer;
    int user;
    int number_of_guesses = 0;
    srand(time(0) + clock());      // Shuffle once
    computer = (rand() % 100) + 1; // Assign random number to computer
    do
    {
        printf("Enter your choice between (1-100): ");
        scanf("%d", &user);
        if (user < computer)
        {
            printf("Higher number please!\n");
            number_of_guesses++;
        }
        else if (user > computer)
        {
            printf("Lower number please!\n");
            number_of_guesses++;
        }
        else
        {
            printf("Congrats! You guessed it in %d attempts\n", number_of_guesses);
            number_of_guesses++;
        }
    } while (computer != user);

    return 0;
}
