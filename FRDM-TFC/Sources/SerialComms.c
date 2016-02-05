/*
 * SerialComms.c
 *
 *  Created on: Feb 4, 2016
 *      Author: Jared
 */
#include "TFC\TFC.h"
#include "stdlib.h"
#include "Common.h"
#include "string.h"

#define STRING_SIZE (16 + 13 + 14 + 14)

char* fts( float f ){
	
	// String used for getting size
	char test[1];
	
	// Gets the size needed to store the float
	int size = snprintf( test, sizeof(test), "%f", f ) + 1;
	
	// Malloc's the memory needed to store the string
	char* string = (char*) malloc(size);
	
	// Writes the float to the string
	sprintf(string, "%f", f );
	
	// Returns the string
	return string;
}

void strcatv2(char* string, float f){
	
	// Turns the float into a string
	char* stringT = fts( f );
	
	// Concatenates the float string onto the given string
	strcat(string, stringT);
	
	// Frees the malloc'd memory for the float string
	free(stringT);
}

char* format( struct Command* command, uint8_t* cameraData ){
	
	int size;
	char test[1];
	char * stringT;
	
	// Determines the size needed to store the floats as a string
	size = snprintf( test, sizeof(test), "%f", command -> steerValue ) + 1;
	size += snprintf( test, sizeof(test), "%f", command -> speedL ) + 1;
	size += snprintf( test, sizeof(test), "%f", command -> speedR ) + 1;
	
	// Malloc's the needed memory for the string
	char* string = (char*) malloc( STRING_SIZE + size + USED_PIXELS * 5 + 1 );
	
	// Concatenates steering value "prompt" to the string
	strcat(string, "Steering Value: ");
	
	// Concatenates steering value to the string 
	strcatv2(string, command -> steerValue );
	
	// Concatenates left motor value "prompt" to the string
	strcat(string, "\nLeft Motor: ");
	
	// Concatenates left motor value to the string
	strcatv2(string, command -> speedL );
	
	// Concatenates right motor value "prompt" to the string
	strcat(string, "\nRight Motor: ");
	
	// Concatenates right motor value to the string
	strcatv2(string, command -> speedR );
	
	// Concatenates camera data "prompt" to the string
	strcat(string, "\nCamera Data: ");

	// TODO Implement camera data formatting
	
	return string;
}

void print( struct Command* command, uint8_t* cameraData){
	
	// TODO TFC_TASK() ?
	
	// Gets the formatted string of data
	char* string = format( command, cameraData );
	
	// Prints the formatted string of data
	printf( "%s", string );
	
	// Frees the malloc'd memory for the the string
	free(string);
	
}

void save( struct Command* command, uint8_t* cameraData){
	// TODO Implement save logic
}
