/* Copyright 2025 Abhinav libraries header file
*/

#ifndef FLUSH_INPUT
#define FLUSH_INPUT
static inline void flush_input(void){
	int charc;
	while((charc = getchar()) != '\n' && charc != EOF);
	
}
#endif
