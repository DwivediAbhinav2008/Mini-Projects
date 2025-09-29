
/* Binary Search Algorithm.
 * Written by Abhinav
*/



#include<stdio.h>
#include<stdlib.h>
void BubbleSort(int* ptr_to_int , int total_no_of_elements); 
int main(void){
	
	short int total_no_of_integers; 
	// Taking input and handling errors for total_no_of_integers input
	for(;;){
		printf("\nPlease enter total no of integers before proceeding: ");
		int read_value = scanf("%hd", &total_no_of_integers);
		if(read_value != 1){
			printf("\nError reading value\nWrong input type\n");
			int c;
			while((c = getchar()) != '\n' && c != EOF);
			continue;
		}
		else if(total_no_of_integers <= 0 || total_no_of_integers >= 32766){
			printf("\nPlease enter a positive integer Max range till 32766\n");
			continue;
		}
		else{
			break;
		}
		
	}
	int* integers = malloc(total_no_of_integers*sizeof(int));
	printf("\nEnter those: \n");
	/* Asking user to input those numbers and also handling errors*/
	for(int i = 0 ; i<total_no_of_integers ; i++){
		for(;;){
                int read_value = scanf("%d", integers+i);
                if(read_value != 1){
                        printf("\nError reading value\nWrong input type\nEnter last value again: ");
                        int c;
                        while((c = getchar()) != '\n' && c != EOF);
                        continue;
                }
		else{
			
			break;
		}

		}
	}
	BubbleSort(integers , total_no_of_integers); // Sorting Array using Bubble sort algorithm
	 printf("\nValue Recording and Sorting Successfull! Sorted Array: \n");
        for(int i = 0 ; i<total_no_of_integers ; i++){
		printf("%d ", integers[i]);
        }

	/* Asking user to find a value in Array entered by him and also handling errors*/

	int user_choice_to_find_in_array , midindex; 
	int Low = 0 , High = total_no_of_integers-1; // Setting two variables Low and High to point to first and last elements of the array
	int found = 0; // flag
	printf("\nEnter a value to start finding in array: ");
	int c;
	while((c = getchar()) != '\n' && c != EOF); // Clearing buffer
	               
	while(1){
                int read_value = scanf("%d", &user_choice_to_find_in_array);
                if(read_value != 1){
                        printf("\nError reading value\nWrong input type\nEnter again: ");
                        int c;
                        while((c = getchar()) != '\n' && c != EOF);
                        continue;
                }
                else{
                        break;
                }

                }
		/* Looping as long as Low is less than or equal to High*/
		while(Low <= High){
		midindex = (Low+High)/2;
		if(user_choice_to_find_in_array == integers[midindex]){
			found = 1;
			printf("\nValue found\n");
			printf("\nAt index: %d\n", midindex);
			break;
			
		}
		else if(user_choice_to_find_in_array < integers[midindex]){
			High = midindex-1;
			
		}
		else if(user_choice_to_find_in_array > integers[midindex]){
			Low = midindex+1;
		}
	}
	// Not found the element	
	if(!found)
		printf("\nValue not in the Array\n");
	return 0;
}
	void BubbleSort(int* ptr_to_int , int total_no_of_elements){
		int flag = 0;
		for(int index = 0 ; index<(total_no_of_elements) ; index++){
			for(int jndex = 0 ; jndex<(total_no_of_elements-1) ; jndex++){
			if(ptr_to_int[jndex+1] < ptr_to_int[jndex]){
			flag = 1;
			int temp = ptr_to_int[jndex];
			ptr_to_int[jndex] = ptr_to_int[jndex+1];
			ptr_to_int[jndex+1] = temp;
			}
			
		}
			if(!flag)
				break;
			}

}



