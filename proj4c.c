#include "proj4.h"
/* LINKED LIST FUNCTIONS */

/* Function that adds a new node at the end of the linked list */
void addToList (NODE** hd, char* name, int NumBurgers, int NumSalads, boolean status)
{
	/* debugMode is TRUE. Notify user that list traversal will be printed */
        if ( debugMode == TRUE) {
                printf ("\nDebugging addToList traversal...\n");
        }

	/* Create a new node to traverse the list to the end */
	NODE* temp = *hd;

	/* initialize the new Node that will be added into the queue */
        NODE* newOrder = (NODE*) malloc (sizeof(NODE));
        newOrder->name = name;
        newOrder->burgers = NumBurgers;
        newOrder->salads = NumSalads;
        newOrder->status = status;
        newOrder->pNext = NULL;

        /* the list is empty, set the new order as the first one and return */
        if ( *hd == NULL) {
                /* Make hd point to newOrder */
		*hd = newOrder;
                
		/* debugMode is TRUE. Notify user that list is empty. */
		if ( debugMode == TRUE) {
			printf ("List was empty. Traversal is not needed. Adding the new order.\n");
		
		}

		/* Return out of the function */
		return;
        }

        /* make temp point to the end of the list */
        while ( temp != NULL) {
		/* debugMode is TRUE. Print the traversal */
		if ( debugMode == TRUE) {
			/* Print out temp's info */
                	printf ("Order name: %s", temp->name);
                	printf ("        Number of Burgers: %d", temp->burgers);
                	printf ("        Number of Salads: %d", temp->salads);
                	if ( temp->status == IN) {
                        	printf ("        Status: In");
                	}
                	else {
                        	printf ("        Status: Not In");
                	}
                	printf("\n");
		}

		/* end of the list has been reached */
		if ( temp->pNext == NULL) {
			break;
		}

		/* continue traversing */
		temp = temp->pNext;
        }
	
        /* insert the new order at the end of the list and return */
        temp->pNext = newOrder;
	return;
}

/* Function that returns TRUE if a name exists in the list and FALSE if it does not */
boolean doesNameExist (NODE** hd, char* name)
{
	/* debugMode is TRUE. Notify user that list traversal will be printed */
        if ( debugMode == TRUE) {
                printf ("\nDebugging doesNameExist traversal...\n");
        }

	/* Create a new node to traverse the list */
	NODE* temp = *hd;

	/* Check if the list is empty. If it is, return FALSE--name is not in the list */
	if ( *hd == NULL) {
                /* debugMode is TRUE. Notify user that list is empty. */
		if ( debugMode == TRUE) {
                        printf ("List was empty. Traversal is not needed. FALSE is returned.\n");

                }
		return FALSE;
	}

	/* Traverse the list using temp to check if the name is in the list */
	while ( temp != NULL) {
		
                /* debugMode is TRUE. Print the traversal */
		if ( debugMode == TRUE) {
                        /* Print out temp's info */
                        printf ("Order name: %s", temp->name);
                        printf ("        Number of Burgers: %d", temp->burgers);
                        printf ("        Number of Salads: %d", temp->salads);
                        if ( temp->status == IN) {
                                printf ("        Status: In");
                        }
                        else {
                                printf ("        Status: Not In");
                        }
                        printf("\n");
                }

		/* compare the name stored in node and the name passed in using strcmp */
		int cmpNum = strcmp(temp->name, name);
		
		/* the names match, return TRUE */
		if ( cmpNum == 0) {
			return TRUE;
		}
		
		/* Name was not the same, go on to the next node in the list */
		temp = temp->pNext;
	}

	/* Name does not exist in the list. Return FALSE */
	return FALSE;	
}

/* Function that changes the status of a call ahead group to IN.
 * If the list is empty or if the group is already IN, return FALSE. */
boolean updateStatus (NODE** hd, char* name)
{
	/* debugMode is TRUE. Notify user that list traversal will be printed */
        if ( debugMode == TRUE) {
                printf ("\nDebugging updateStatus traversal...\n");
        }

	/* Create a new node to traverse the list */
	NODE* temp = *hd;

	/* Check if the list is empty. If it is, status cannot be updated--return */
	if ( *hd == NULL) {
		/* debugMode is TRUE. Notify user that list is empty. */
                if ( debugMode == TRUE) {
                        printf ("List was empty. Traversal is not needed. FALSE is returned.\n");

                }
		return FALSE;
	}

	/* Traverse the list until name is found */
	while ( temp != NULL) {
		/* debugMode is TRUE. Print the traversal */
                if ( debugMode == TRUE) {
                        /* Print out temp's info */
                        printf ("Order name: %s", temp->name);
                        printf ("        Number of Burgers: %d", temp->burgers);
                        printf ("        Number of Salads: %d", temp->salads);
                        if ( temp->status == IN) {
                                printf ("        Status: In");
                        }
                        else {
                                printf ("        Status: Not In");
                        }
                        printf("\n");
                }

		/* Check if is pointing to the node that holds the name */
		int cmpNum = strcmp(temp->name, name);
		if ( cmpNum == 0) {
			
			/* Case where the status for the group is already IN */
			if ( temp->status == IN) {
				return FALSE;
			}

			/* Update the status to IN and return TRUE */
			temp->status = IN;
			return TRUE;
		}

		/* Go on to the next node */
		temp = temp->pNext;
	}

	/* Name was not found, return FALSE */
	return FALSE;
}

/* Function that finds the first group in line that is in the restaurant 
 * and matches the order prepared for pick up at the counter.
 * The name of the group is returned and the group is removed from the list */
char* retrieveAndRemove (NODE** hd, int preparedBurgers, int preparedSalads)
{
	/* debugMode is TRUE. Notify user that list traversal will be printed */
        if ( debugMode == TRUE) {
                printf ("\nDebugging retrieveAndRemove traversal...\n");
        }

	/* Create a new node to traverse the list */
	NODE* temp = *hd;
	NODE* prev = NULL;

	/* Create a string to hold the group name being removed */
	char* nameRemoved;

	/* Traverse the list until a group with an order that matches the prepared items are found */
	while ( temp != NULL) {
		/* debugMode is TRUE. Print the traversal */
                if ( debugMode == TRUE) {
                        /* Print out temp's info */
                        printf ("Order name: %s", temp->name);
                        printf ("        Number of Burgers: %d", temp->burgers);
                        printf ("        Number of Salads: %d", temp->salads);
                        if ( temp->status == IN) {
                                printf ("        Status: In");
                        }
                        else {
                                printf ("        Status: Not In");
                        }
                        printf("\n");
                }

		/* Check if the number of prepared items match temp's order and the group is in the restaurant */
		if ( temp->burgers <= preparedBurgers && temp->salads <= preparedSalads && temp->status == IN) {
		
			/* Store the group name in nameRemoved */
			nameRemoved = temp->name;

			/* Remove the group from the waiting list */
			/* Case where the order being removed is the only one in the list */
			if ( temp == *hd) {
				*hd = temp->pNext;
			}
			
			/* Case where the order is in the middle or the end of the list */
			else {
				prev->pNext = temp->pNext;
			}

			free(temp); // Free memory

			return nameRemoved; // Return the group name	
			
			
		}

		/* Keep searching */
		prev = temp;
		temp = temp->pNext;
	}

	/* None of the prepared items match the list's orders */
	return NULL;
}

/* Function that returns a number of orders waiting ahead of the order of given name */
int countOrdersAhead (NODE** hd, char* name)
{
	/* debugMode is TRUE. Notify user that list traversal will be printed */
        if ( debugMode == TRUE) {
                printf ("\nDebugging countOrdersAhead traversal...\n");
        }

	/* Create a new node to traverse the list */
	NODE* temp = *hd;

	/* Create a variable counter to count the number of orders */
	int counter = 0;

	/* Check if the list is empty. If it is, return. */
        if ( *hd == NULL) {
                /* debugMode is TRUE. Notify user that list is empty. */
                if ( debugMode == TRUE) {
                        printf ("List was empty. Traversal is not needed. NULL is returned.\n");

                }
                return counter;
        }

	/* Traverse the list */
	while ( temp != NULL) {
		/* debugMode is TRUE. Print the traversal */
                if ( debugMode == TRUE) {
                        /* Print out temp's info */
                        printf ("Order name: %s", temp->name);
                        printf ("        Number of Burgers: %d", temp->burgers);
                        printf ("        Number of Salads: %d", temp->salads);
                        if ( temp->status == IN) {
                                printf ("        Status: In");
                        }
                        else {
                                printf ("        Status: Not In");
                        }
                        printf("\n");
                }

		/* check if temp is pointing to the node that holds the given name */
		int cmpNum = strcmp(temp->name, name);
		
		/* Name matches, break the loop */
		if ( cmpNum == 0) {
			break;
		}

		/* Update the counter */
		counter++;

		/* Move onto the next node in the list */
		temp = temp->pNext;
	}

	/* Return the number stored in counter */
	return counter;
}

/* Function that traverses down the list until a specific order name is encountered. 
 * As the list is traversed, the function prints out the orders in the list. */
void displayOrdersAhead (NODE** hd, char* name)
{
	/* debugMode is TRUE. Notify user that list traversal will be printed */
        if ( debugMode == TRUE) {
                printf ("\nDebugging displayOrdersAhead traversal...\n");
        }

	/* Create a new node to traverse the list */
        NODE* temp = *hd;

	/* Notify if there are no nodes behind the node with the given name*/
        if ( (*hd)->pNext == NULL) {
                /* debugMode is TRUE. Notify user if list is empty. */
                if ( debugMode == TRUE) {
                        printf ("Nothing to traverse because there is nothing behind this order. Returning out of function.\n\n");
                }

                printf ("There are currently no orders ahead of this group.\n");
		return;
        }

	/* Check if the list is empty. If it is, return. */
        if ( *hd == NULL) {
                /* debugMode is TRUE. Notify user that list is empty. */
                if ( debugMode == TRUE) {
                        printf ("List was empty. Traversal is not needed. NULL is returned.\n");

                }
                return;
        }

        /* Traverse the list */
        while ( temp != NULL) {
                /* debugMode is TRUE. Print the traversal */
                if ( debugMode == TRUE) {
                        /* Print out temp's info */
                        printf ("Debug:");
			printf ("	 Order name: %s", temp->name);
                        printf ("        Number of Burgers: %d", temp->burgers);
                        printf ("        Number of Salads: %d", temp->salads);
                        if ( temp->status == IN) {
                                printf ("        Status: In");
                        }
                        else {
                                printf ("        Status: Not In");
                        }
                        printf("\n");
                }

		/* check if temp is pointing to the node that holds the given name */
                int cmpNum = strcmp(temp->name, name);

                /* Name matches, break the loop */
                if ( cmpNum == 0) {
                        break;
                }

                /* Print out temp's info */
                printf ("Order name: %s", temp->name);
		printf ("	Number of Burgers: %d", temp->burgers);
		printf ("	Number of Salads: %d", temp->salads);
		if ( temp->status == IN) {
			printf("	Status: In");
		}
		else {
			printf("	Status: Not In");
		}
		printf("\n");

                /* Move onto the next node in the list by updating temp */
                temp = temp->pNext;
        }

	/* Exit the function */
        return;
}

/* Function that traverses down the entire list and prints out all the information
 * that the each node holds--the name, number of burgers, number of salads, and restaurant status */
void displayListInformation (NODE** hd)
{
	/* debugMode is TRUE. Notify user that list traversal will be printed */
        if ( debugMode == TRUE) {
                printf ("\nDebugging displayListInformation traversal...\n");
        }

	/* Create a new node to traverse the list */
        NODE* temp = *hd;

	/* Notify if list is empty */
	if ( *hd == NULL) {
		/* debugMode is TRUE. Notify user if list is empty. */
		if ( debugMode == TRUE) {
			printf ("List is empty. No need to traverse. Returning out of function.\n");
		}

		printf ("There are currently no orders in the list.\n");
		return;
	}

        /* Traverse the list */
        while ( temp != NULL) {
		/* debugMode is TRUE. Print the traversal */
                if ( debugMode == TRUE) {
                        /* Print out temp's info */
                        printf ("Debug:");
                        printf ("        Order name: %s", temp->name);
                        printf ("        Number of Burgers: %d", temp->burgers);
                        printf ("        Number of Salads: %d", temp->salads);
                        if ( temp->status == IN) {
                                printf ("        Status: In");
                        }
                        else {
                                printf ("        Status: Not In");
                        }
                        printf("\n");
                }

                /* Print out temp's info */
                printf ("Order name: %s", temp->name);
                printf ("        Number of Burgers: %d", temp->burgers);
                printf ("        Number of Salads: %d", temp->salads);
                if ( temp->status == IN) {
                        printf("        Status: In");
                }
                else {
                        printf("        Status: Not In");
                }
                printf("\n");

                /* Move onto the next node in the list by updating temp */
                temp = temp->pNext;
        }

        /* Exit the function */
        return;

}

/* Function that returns the estimated waiting time for a given name based on the number of orders
 * that are ahead of the name, assuming that burgers take 10 minutes and salads take 5 minutes */
int displayWaitingTime(NODE** hd, char* name)
{
        /* debugMode is TRUE. Notify user that list traversal will be printed */
        if ( debugMode == TRUE) {
                printf ("\nDebugging displayWaitingTime traversal...\n");
        }

	/* Create a new node to traverse the list */
        NODE* temp = *hd;

        /* Create a variables to count the number of items before the given order */ 
        int numBurgers = 0;
	int numSalads = 0;

	/* Create variables to keep track of the time */
	int burgerTime = 0;
	int saladTime = 0;
	int time = 0;

	/* Check if the list is empty. If it is, return. */
        if ( *hd == NULL) {
                /* debugMode is TRUE. Notify user that list is empty. */
                if ( debugMode == TRUE) {
                        printf ("List was empty. Traversal is not needed. NULL is returned.\n");

                }
                return time;
        }

        /* Traverse the list */
        while ( temp != NULL) {
		/* debugMode is TRUE. Print the traversal */
                if ( debugMode == TRUE) {
                        /* Print out temp's info */
                        printf ("Order name: %s", temp->name);
                        printf ("        Number of Burgers: %d", temp->burgers);
                        printf ("        Number of Salads: %d", temp->salads);
                        if ( temp->status == IN) {
                                printf ("        Status: In");
                        }
                        else {
                                printf ("        Status: Not In");
                        }
                        printf("\n");
                }

                /* check if temp is pointing to the node that holds the given name */
                int cmpNum = strcmp(temp->name, name);

                /* Name matches, break the loop */
                if ( cmpNum == 0) {
                        break;
                }

                /* Update the variables */
                numBurgers = numBurgers + temp->burgers;
		numSalads = numSalads + temp->salads;

                /* Move onto the next node in the list */
                temp = temp->pNext;
        }

	/* Compute the time and return */
	burgerTime = numBurgers * 10;
	saladTime = numSalads * 5;
	time = burgerTime + saladTime;
	return time;

}

