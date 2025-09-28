#include<stdio.h>  

int main(){
	
	short int total_no_of_integers;   // variable to store how many integers we will enter
	
	// loop to ask user again and again until valid input is given
	for(;;){
		
		printf("\nPlease enter total no of integers before proceeding: ");
		int read_value = scanf("%hd", &total_no_of_integers);   // taking input from user
		
		if(read_value != 1){   // if user enters wrong data like character
			printf("\nError reading value\nWrong input type\n");
			int c;
			while((c = getchar()) != '\n' && c != EOF);   // clearing buffer
			continue;   // ask again
		}
		else if(total_no_of_integers <= 0 || total_no_of_integers >= 32766){  // invalid range check
			printf("\nPlease enter a positive integer Max range till 32766\n");
			continue;   // ask again
		}
		else{
			break;   // input is valid so break the loop
		}
		
	}
	
	int integers[total_no_of_integers];   // array to store the integers
	
	printf("\nEnter those: \n");
	// loop to take all integers
	for(int i = 0 ; i<total_no_of_integers ; i++){
		for(;;){   // loop until user gives correct integer
                int read_value = scanf("%d", integers+i);   // taking integer input
                if(read_value != 1){   // wrong type entered
                        printf("\nError reading value\nWrong input type\nEnter last value again: ");
                        int c;
                        while((c = getchar()) != '\n' && c != EOF);   // clearing buffer
                        continue;   // ask again
                }
		else{
			break;   // input is correct, go to next index
		}

		}
	}
	
	int user_choice_to_find_in_array;   // variable to store the number we want to find
	printf("\nValue Recording Successfull!\nEnter a value to start finding in array: ");
	int c;
	while((c = getchar()) != '\n' && c != EOF);   // clearing buffer
	
	// taking input to find
	while(1){
                int read_value = scanf("%d", &user_choice_to_find_in_array);
                if(read_value != 1){   // wrong input type
                        printf("\nError reading value\nWrong input type\nEnter again: ");
                        int c;
                        while((c = getchar()) != '\n' && c != EOF);
                        continue;   // ask again
                }
                else{
                        break;   // correct input
                }

    }

	int flag_found = 0;   // to check if element found
	int recorded_index;   // to store index if found
	
	// linear search loop
	for(int i = 0 ; i<total_no_of_integers ; i++){
		
		if(integers[i] == user_choice_to_find_in_array){   // if element matches
			flag_found = 1;
			recorded_index = i;   // store index
			break;   // stop searching
		}
		
	}
	
	// showing output
	if(flag_found){
		printf("\nSearching Successfull!\nFound at Index: %d\n", recorded_index);
	}
	else{
		printf("\nSearching Successfull but element not found\nArray ended\n");
	}
	
	
	return 0;   // program ends
}
