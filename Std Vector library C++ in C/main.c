#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "flushinput.h"
#include "input.h"
#include <unistd.h>
int main(void)
{

    vector v1 = {0};
    init(&v1);

    if ((v1.capacity != 100) || (v1.ptr_to_mem == NULL))
    {
        fprintf(stderr, "\nError occured\n");
        return 1;
    }

    int choice_from_menu;
    char choice_for_continuation;
    int *check_ptr = NULL;

    while (1)
    {
        printf("\n\t\tCurrent valid integers stored %zu\n", v1.size);
        printf("\n\t\tSupported operations\n\n"
               "\t\t1. Push an integer\n"
               "\t\t2. Pop an integer\n");

        while (1)
        {
            read_int("\n\nEnter your choice_of operation ", &choice_from_menu);
            if (errno != ERANGE && (choice_from_menu < 1 || choice_from_menu > 2))
            {
                fprintf(stderr, "\nPlease choose a valid option\n");
                continue;
            }
            else if (errno == ERANGE)
                continue;
            else
                break;
        }

        switch (choice_from_menu)
        {
        case 1:
            check_ptr = push_back(&v1);
            if (!check_ptr)
                perror("\nPrevious push failed ");
            else
                v1.ptr_to_mem = check_ptr;
            break;

        case 2:
            pop_back(&v1);
            break;
        }

        printf("\nDo you want to continue manipulation [Y/n]? ");
        choice_for_continuation = getchar();
        flush_input();
        if (choice_for_continuation == 'n' || choice_for_continuation == 'N')
        {
            break;
        }
    }

    destruct(&v1);
    return 0;
}
