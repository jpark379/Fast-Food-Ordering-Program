/* jpark379proj4.h */
//
// <JUDY PARK>
// U. Of Illinois, Chicago
// CS 211: Fall 2019

// Project 4: A fast food ordering system using multiple source files to create a linked list that behaves like a queue-like data structure. 
// The program prompts the user for a command which allows the user to:
// 	- Add an order to the list
// 	- Call ahead
// 	- Notify the program that a group is waiting in the restaurant
// 	- Retrieve and remove an order that matches the food prepared
// 	- Display the number of orders in front of a given order and display them
// 	- Display the entire order list
// 	- Estimate the amount of time it will take for a given order
// This program also offers a debug mode with the "-d" flag which will print out a node's information any time the list is traversed

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES, NOT_IN = 0, IN} boolean;
extern int debugMode;

/* LINKED LIST STRUCT DECLARATION */
/* Each node will hold the customer's name, number of burgers ordered,
 * number of salads ordered, if they are in the restaurant or not, and a pointer
 * to the next node to link the list */
typedef struct NODE {
	char *name;
	int burgers;
	int salads;
	boolean status;
	struct NODE* pNext;
}NODE;

/* FUNCTION DECLARATIONS */
/* Functions in proj4a.c */
void clearToEoln ();
int getNextNWSChar ();
int getPosInt ();
char* getName ();
void printCommands ();

/* Functions in proj4b.c */
void doAdd (NODE** hd);
void doCallAhead (NODE** hd);
void doWaiting (NODE** hd);
void doRetrieve (NODE** hd);
void doList (NODE** hd);
void doDisplay (NODE** hd);
void doEstimateTime(NODE** hd);

/* Functions in proj4c.c */
void addToList (NODE** hd, char* name, int NumBurgers, int NumSalads, boolean status);
boolean doesNameExist (NODE** hd, char* name);
boolean updateStatus (NODE** hd, char* name);
char* retrieveAndRemove (NODE** hd, int preparedBurgers, int preparedSalads);
int countOrdersAhead (NODE** hd, char* name);
void displayOrdersAhead (NODE** hd, char* name);
void displayListInformation (NODE** hd);
int displayWaitingTime (NODE** hd, char* name);

