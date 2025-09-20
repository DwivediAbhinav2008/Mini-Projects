#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	

	printf("\n==========Dequeue simulation program=======\n");
	char*userentered_string = malloc(100*sizeof(char)); // Allocating memory
	if(userentered_string == NULL){
		printf("Error allocating memory\n"); // Checking errors  for memory allocation
	}
	printf("\nEnter your string for retrieval of all of it's characters: ");
	fgets(userentered_string , 100 , stdin);
	if(userentered_string[strlen(userentered_string)-1] == '\n'){
		userentered_string[strlen(userentered_string)-1] = 0; // Removing extra newline
	}
	else{
		int c;
		while((c = getchar()) != '\n' && c != EOF); // Clearing buffer if needed
		}
	char* Lptr , *Rptr; // Two pointers L and R
	int length = strlen(userentered_string); // Calculating length of user entered string
	Lptr = userentered_string; // Initializing Left pointer at start of string 
        Rptr = &userentered_string[length-1]; // Initializing Right pointer at end of string
	char* retreived_characters_from_front = malloc(1000*sizeof(char)); 
	char* retreived_characters_from_back = malloc(1000*sizeof(char));
	
	if(retreived_characters_from_front == NULL || retreived_characters_from_back == NULL){
			perror("\nMemory allocation failure");
			return 1;
		}
	
	for(int i = 0 ; i<(length+1)/2 ; i++){

		*(retreived_characters_from_front+i) = *Lptr;
		*(retreived_characters_from_back+i) = *Rptr;
		Lptr++;
		Rptr--;
	}
	retreived_characters_from_front[(length+1)/2] = '\0';
    	retreived_characters_from_back[length/2] = '\0';

	printf("\nRetrived characters from front: %s\n" , retreived_characters_from_front);
	printf("\nRetrived characters from back: %s\n" , retreived_characters_from_back);
	
	printf("\n Now dequeue is empty!\n");
	printf("\n Now enter your characters first front and then back to insert them in this dequeue MAX %d\n" , length);
	char newelements[length + 1];
	fgets(newelements , (length+1) , stdin);
        if(newelements[strlen(newelements)-1] == '\n'){
                newelements[strlen(newelements)-1] = 0; // Removing extra newline
        }
        else{
                int c;
                while((c = getchar()) != '\n' && c != EOF); // Clearing buffer if needed
                }
	
	char* NewLptr = newelements , *NewRptr = &newelements[length-1];
	Lptr = userentered_string; // Initializing Left pointer at start of string 
        Rptr = &userentered_string[length-1];
	        for(int i = 0 ; i<(length+1)/2 ; i++){

                *(Lptr+i) = *(NewLptr+i);
                *(Rptr-i) = *(NewRptr-i);
        }
		
	printf("\n%s\n" , userentered_string);
	free(userentered_string);
	free(retreived_characters_from_front);
	free(retreived_characters_from_back);
	
	printf("\n");
	return 0;
}
