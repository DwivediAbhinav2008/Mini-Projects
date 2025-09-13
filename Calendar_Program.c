#include<stdio.h>
#include<ncurses.h>
void Gregorian_Calendar(int month , int year);
int main(){
    int month, year;
	while(1){
    printf("\nEnter month and year respectively to get the calendar for that month: \n");
    int read = scanf("%d%d", &month , &year);
    if(read == 0){
		printf("\nWrong input! Try again\n");
		while((getchar()) != '\n'); // Clearing buffer
		continue;
		
	}
	else if(month<1 || year<1900){
		printf("\nEnter valid month between 1-12 and year after 1900\n");
		continue;
	
	}
	else{
		break;
	}
}
    
Gregorian_Calendar(month , year);
    return 0;
}
void Gregorian_Calendar(int month , int year){
    // Checking for leap year for current year entered by user
    unsigned int CurrentYearIs_leap = 0;
    if((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        CurrentYearIs_leap = 1;

    // Calculation of total no of years from 1900 to targetyear-1 and also checking for leap years in between
    unsigned int total_no_of_years_ = year - 1900;
    unsigned int total_no_of_leap_years = 0;
    for(unsigned int y = 1900 ; y <= year-1 ; y++){
        if((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
            total_no_of_leap_years++;
    }
	// calculating total no of days by multiplying days in a nonleap year between 1900 and target-1 and adding leap years in end because leap year has only one extra day and adding only leap years is same
    unsigned int total_no_of_days = 365 * total_no_of_years_ + total_no_of_leap_years;

    // Days in months
    int days_of_all_months_[12]; // Declared an array of months in a year
    if(!CurrentYearIs_leap){
        int temp[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        for(int i=0;i<12;i++) days_of_all_months_[i]=temp[i]; // Initialzing array with possible month's total no of days in a non leap year
    }
    else {
        int temp[12] = {31,29,31,30,31,30,31,31,30,31,30,31}; // Initializing array with possible month's total no of days in a leap year. One extra BTW
        for(int i=0;i<12;i++) days_of_all_months_[i]=temp[i];
    }

    // Add days of months before current month
    for(int m = 0; m < month-1; m++) // Looping from 0th element to entered month-1 and adding days of all months before target month
        total_no_of_days += days_of_all_months_[m];

    // Now compute start date
	int c;
    int startdate = total_no_of_days % 7;

	initscr(); //starting ncurses mode
	noecho(); // disabling echo
        cbreak(); // disabling line buffering so that input is taken immediately
	keypad(stdscr , TRUE); // Initializing keyboard arrow keys
	// Printing calendar header
	 switch(month){
                                case 1:  printw("\n\t\tJanuary  %d\n", year); break;
                                case 2:  printw("\n\t\tFebruary %d\n", year); break;
                                case 3:  printw("\n\t\tMarch    %d\n", year); break;
                                case 4:  printw("\n\t\tApril    %d\n", year); break;
                                case 5:  printw("\n\t\tMay      %d\n", year); break;
                                case 6:  printw("\n\t\tJune     %d\n", year); break;
                                case 7:  printw("\n\t\tJuly     %d\n", year); break;
                                case 8:  printw("\n\t\tAugust   %d\n", year); break;
                                case 9:  printw("\n\t\tSeptember %d\n", year); break;
                                case 10: printw("\n\t\tOctober  %d\n", year); break;
                                case 11: printw("\n\t\tNovember %d\n", year); break;
                                case 12: printw("\n\t\tDecember %d\n", year); break;
    }

    printw("Mon Tue Wed Thu Fri Sat Sun\n");
    // Print initial spaces
    for(int i=0; i<startdate; i++)
        printw("    ");
    // Print all days
    for(int i=1; i<=days_of_all_months_[month-1]; i++){
        printw("%3d ", i);
        if((startdate + i) % 7 == 0)
            printw("\n");
    }
    printw("\n");
	printw("\n1. Press q to exit\n\n2. Press UP key to go to next year same month\n\n3. Press DOWN key to go to Previous year same month\n\n4. Press RIGHT arrow key to go same year next month\n\n5. Press LEFT key to go to same year previous month\n");
		 while((c = getch() ) != 'q'){

		switch(c){

		case KEY_UP: 
			clear();
			    switch(month){
        			case 1:  printw("\n\t\tJanuary  %d\n", year); break;
        			case 2:  printw("\n\t\tFebruary %d\n", year); break;
        			case 3:  printw("\n\t\tMarch    %d\n", year); break;
        			case 4:  printw("\n\t\tApril    %d\n", year); break;
       	 			case 5:  printw("\n\t\tMay      %d\n", year); break;
        			case 6:  printw("\n\t\tJune     %d\n", year); break;
        			case 7:  printw("\n\t\tJuly     %d\n", year); break;
        			case 8:  printw("\n\t\tAugust   %d\n", year); break;
        			case 9:  printw("\n\t\tSeptember %d\n", year); break;
        			case 10: printw("\n\t\tOctober  %d\n", year); break;
        			case 11: printw("\n\t\tNovember %d\n", year); break;
        			case 12: printw("\n\t\tDecember %d\n", year); break;
    				}

				year++;
                CurrentYearIs_leap = 0;
                if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
                    CurrentYearIs_leap = 1;
                if (!CurrentYearIs_leap) {
                    int temp[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
                    for (int i=0; i<12; i++) days_of_all_months_[i]=temp[i];
                } else {
                    int temp[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
                    for (int i=0; i<12; i++) days_of_all_months_[i]=temp[i];
                }

    			// Calculation of total no of years from 1900 to targetyear-1 and also checking for leap years in between
    			total_no_of_years_ = year - 1900;
    			total_no_of_leap_years = 0;
    			for(unsigned int y = 1900 ; y <= year-1 ; y++){
        		if((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)){
            		total_no_of_leap_years++;}
    			}
	// calculating total no of days by multiplying days in a nonleap year between 1900 and target-1 and adding leap years in end because leap year has only one extra day and calculating only leap years is same 
    			total_no_of_days = 365 * total_no_of_years_ + total_no_of_leap_years;

    

    // Add days of months before current month
    			for(int m = 0; m < month-1; m++){ // Looping from 0 to entered month-1 and adding days of all months before target month
        		total_no_of_days += days_of_all_months_[m];
	}

    // Now compute start date
   			 startdate = total_no_of_days % 7;


			printw("Mon Tue Wed Thu Fri Sat Sun\n");
    			// Print initial spaces
    			for(int i=0; i<startdate; i++)
        			printw("    ");
    			// Print all days
    			for(int i=1; i<=days_of_all_months_[month-1]; i++){
        			printw("%3d ", i);
        		if((startdate + i) % 7 == 0)
            			printw("\n");
    }
    			printw("\n");
			break;

		case KEY_DOWN:
				
			clear();
			switch(month){
                         	case 1:  printw("\n\t\tJanuary  %d\n", year); break;
                                case 2:  printw("\n\t\tFebruary %d\n", year); break;
                                case 3:  printw("\n\t\tMarch    %d\n", year); break;
                                case 4:  printw("\n\t\tApril    %d\n", year); break;
                                case 5:  printw("\n\t\tMay      %d\n", year); break;
                                case 6:  printw("\n\t\tJune     %d\n", year); break;
                                case 7:  printw("\n\t\tJuly     %d\n", year); break;
                                case 8:  printw("\n\t\tAugust   %d\n", year); break;
                                case 9:  printw("\n\t\tSeptember %d\n", year); break;
                                case 10: printw("\n\t\tOctober  %d\n", year); break;
                                case 11: printw("\n\t\tNovember %d\n", year); break;
                                case 12: printw("\n\t\tDecember %d\n", year); break;
    				}
				year--;

                // FIX: recompute leap + month days
                CurrentYearIs_leap = 0;
                if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
                    CurrentYearIs_leap = 1;
                if (!CurrentYearIs_leap) {
                    int temp[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
                    for (int i=0; i<12; i++) days_of_all_months_[i]=temp[i];
                } else {
                    int temp[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
                    for (int i=0; i<12; i++) days_of_all_months_[i]=temp[i];
                }

			    // Calculation of total no of years from 1900 to targetyear-1 and also checking for leap years in between
    				total_no_of_years_ = year - 1900;
    				total_no_of_leap_years = 0;
    				for(unsigned int y = 1900 ; y <= year-1 ; y++){
        			if((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)){
            			total_no_of_leap_years++;}
    }
	// calculating total no of days by multiplying days in a nonleap year between 1900 and target-1 and adding leap years in end because leap year has only one extra day and calculating only leap years is same 
    				total_no_of_days = 365 * total_no_of_years_ + total_no_of_leap_years;

    

    // Add days of months before current month
    				for(int m = 0; m < month-1; m++){ // Looping from 0 to entered month-1 and adding days of all months before target month
        			total_no_of_days += days_of_all_months_[m];
	}

    // Now compute start date
    				startdate = total_no_of_days % 7;


				printw("Mon Tue Wed Thu Fri Sat Sun\n");
    			// Print initial spaces
    				for(int i=0; i<startdate; i++)
        				printw("    ");
    			// Print all days
    				for(int i=1; i<=days_of_all_months_[month-1]; i++){
        			printw("%3d ", i);
        			if((startdate + i) % 7 == 0)
            			printw("\n");
    }
    			printw("\n");
			break;

  			case KEY_RIGHT:
	
			clear();
			        switch(month){
                                case 1:  printw("\n\t\tJanuary  %d\n", year); break;
                                case 2:  printw("\n\t\tFebruary %d\n", year); break;
                                case 3:  printw("\n\t\tMarch    %d\n", year); break;
                                case 4:  printw("\n\t\tApril    %d\n", year); break;
                                case 5:  printw("\n\t\tMay      %d\n", year); break;
                                case 6:  printw("\n\t\tJune     %d\n", year); break;
                                case 7:  printw("\n\t\tJuly     %d\n", year); break;
                                case 8:  printw("\n\t\tAugust   %d\n", year); break;
                                case 9:  printw("\n\t\tSeptember %d\n", year); break;
                                case 10: printw("\n\t\tOctober  %d\n", year); break;
                                case 11: printw("\n\t\tNovember %d\n", year); break;
                                case 12: printw("\n\t\tDecember %d\n", year); break;
    				}
				month++;
                // FIX: wrap month
                if (month > 12) { month = 1; year++; }

                // FIX: recompute leap + month days
                CurrentYearIs_leap = 0;
                if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
                    CurrentYearIs_leap = 1;
                if (!CurrentYearIs_leap) {
                    int temp[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
                    for (int i=0; i<12; i++) days_of_all_months_[i]=temp[i];
                } else {
                    int temp[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
                    for (int i=0; i<12; i++) days_of_all_months_[i]=temp[i];
                }

			    // Calculation of total no of years from 1900 to targetyear-1 and also checking for leap years in between
    				total_no_of_years_ = year - 1900;
    				total_no_of_leap_years = 0;
    				for(unsigned int y = 1900 ; y <= year-1 ; y++){
        			if((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)){
           			 total_no_of_leap_years++;}
    				}
	// calculating total no of days by multiplying days in a nonleap year between 1900 and target-1 and adding leap years in end because leap year has only one extra day and calculating only leap years is same 
    				total_no_of_days = 365 * total_no_of_years_ + total_no_of_leap_years;

    

    // Add days of months before current month
    				for(int m = 0; m < month-1; m++){ // Looping from 0 to entered month-1 and adding days of all months before target month
        			total_no_of_days += days_of_all_months_[m];
				}

    // Now compute start date
    				startdate = total_no_of_days % 7;


				printw("Mon Tue Wed Thu Fri Sat Sun\n");
    			// Print initial spaces
    				for(int i=0; i<startdate; i++)
        				printw("    ");
    			// Print all days
    				for(int i=1; i<=days_of_all_months_[month-1]; i++){
        			printw("%3d ", i);
        			if((startdate + i) % 7 == 0)
            			printw("\n");
    }
    				printw("\n");
				break;

			case KEY_LEFT:
							
			clear();
			        switch(month){
                                case 1:  printw("\n\t\tJanuary  %d\n", year); break;
                                case 2:  printw("\n\t\tFebruary %d\n", year); break;
                                case 3:  printw("\n\t\tMarch    %d\n", year); break;
                                case 4:  printw("\n\t\tApril    %d\n", year); break;
                                case 5:  printw("\n\t\tMay      %d\n", year); break;
                                case 6:  printw("\n\t\tJune     %d\n", year); break;
                                case 7:  printw("\n\t\tJuly     %d\n", year); break;
                                case 8:  printw("\n\t\tAugust   %d\n", year); break;
                                case 9:  printw("\n\t\tSeptember %d\n", year); break;
                                case 10: printw("\n\t\tOctober  %d\n", year); break;
                                case 11: printw("\n\t\tNovember %d\n", year); break;
                                case 12: printw("\n\t\tDecember %d\n", year); break;
    }
				month--;
                // FIX: wrap month
                if (month < 1) { month = 12; year--; }

                // FIX: recompute leap + month days
                CurrentYearIs_leap = 0;
                if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
                    CurrentYearIs_leap = 1;
                if (!CurrentYearIs_leap) {
                    int temp[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
                    for (int i=0; i<12; i++) days_of_all_months_[i]=temp[i];
                } else {
                    int temp[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
                    for (int i=0; i<12; i++) days_of_all_months_[i]=temp[i];
                }

			    // Calculation of total no of years from 1900 to targetyear-1 and also checking for leap years in between
    				total_no_of_years_ = year - 1900;
    				total_no_of_leap_years = 0;
    				for(unsigned int y = 1900 ; y <= year-1 ; y++){
        			if((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)){
           			 total_no_of_leap_years++;}
    				}
	// calculating total no of days by multiplying days in a nonleap year between 1900 and target-1 and adding leap years in end because leap year has only one extra day and calculating only leap years is same 
    				total_no_of_days = 365 * total_no_of_years_ + total_no_of_leap_years;

    

    // Add days of months before current month
    				for(int m = 0; m < month-1; m++){ // Looping from 0 to entered month-1 and adding days of all months before target month
        			total_no_of_days += days_of_all_months_[m];
				}

    // Now compute start date
    				startdate = total_no_of_days % 7;


				printw("Mon Tue Wed Thu Fri Sat Sun\n");
    			// Print initial spaces
    				for(int i=0; i<startdate; i++)
        				printw("    ");
    			// Print all days
    				for(int i=1; i<=days_of_all_months_[month-1]; i++){
        			printw("%3d ", i);
        			if((startdate + i) % 7 == 0)
            			printw("\n");
    }
    				printw("\n");
				break;
}
printw("\n1. Press q to exit\n\n2. Press UP key to go to next year same month\n\n3. Press DOWN key to go to Previous year same month\n\n4. Press RIGHT arrow key to go same year next month\n\n5. Press LEFT key to go to same year previous month\n");

}
endwin();
}

