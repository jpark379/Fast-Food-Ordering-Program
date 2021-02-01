#include "proj4.h"

/* FUNCTIONS THAT INTERACT WITH THE LINKED LIST FUNCTIONS */

/* Function that adds a new order to the list.
 * Each order holds the group's name, the number of burgers and salads ordered, and their restaurant status. 
 * If they add their order it is assumed they are in the restaurant */
void doAdd (NODE** hd)
{
	/* Get number of burgers ordered from input */
 	int NumBurgers = getPosInt();
 	if (NumBurgers < 0) {
    		printf ("Error: Add command requires an integer value of at least 0\n");
    		printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    		printf ("  where:<# burgers> is the number of ordered burgers\n");
    		printf ("        <# salads> is the number of ordered salads\n");
    		printf ("        <name> is the name of the person putting the order\n");
    		return;
   	}

  	/* Get number of salads ordered from input */
 	int NumSalads = getPosInt(); 
 	if (NumSalads < 0) {
    		printf ("Error: Add command requires an integer value of at least 0\n");
    		printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    		printf ("  where:<# burgers> is the number of ordered burgers\n");
    		printf ("        <# salads> is the number of ordered salads\n");
    		printf ("        <name> is the name of the person putting the order\n");
    		return;
   	}  

 	/* Get group name from input */
 	char *name = getName();
 	if (NULL == name) {
    		printf ("Error: Add command requires a name to be given\n");
    		printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    		printf ("  where:<# burgers> is the number of ordered burgers\n");
    		printf ("        <# salads> is the number of ordered salads\n");
    		printf ("        <name> is the name of the person putting the order\n");
    		return;
   	}
	
	/* Check if the name already exists in the line */
	if ( doesNameExist(*&hd, name) == TRUE) {
		printf ("Error: Name already exists in the order list.\n");
		printf ("Please use another name.\n");
		return;
	}

	/* Set the status of the group */
	boolean status = IN;

	/* Notify the user that we are adding a new order and use the addToList function to add it onto the list */
 	printf ("\nAdding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);
	addToList(*&hd, name, NumBurgers, NumSalads, status);

}

/* Function adds an order to the list.
 * Each order holds the group's name, the number of burgers and salads ordered, and their restaurant status.
 * If they call their order it is assumed they are not in the restaurant */
void doCallAhead (NODE** hd)
{
	/* Get number of burgers ordered from input */
 	int NumBurgers = getPosInt();
 	if (NumBurgers < 0) {
    		printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    		printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    		printf ("  where:<# burgers> is the number of ordered burgers\n");
    		printf ("        <# salads> is the number of ordered salads\n");
    		printf ("        <name> is the name of the person putting the order\n");
    		return;
   	}

  	/* Get number of salads ordered from input */
 	int NumSalads = getPosInt();
 	if (NumSalads < 0) {
    		printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    		printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    		printf ("  where:<# burgers> is the number of ordered burgers\n");
    		printf ("        <# salads> is the number of ordered salads\n");
    		printf ("        <name> is the name of the person putting the order\n");
    		return;
   	}

 	/* Get group name from input */
 	char *name = getName();
 	if (NULL == name) {
    		printf ("Error: Call-ahead command requires a name to be given\n");
    		printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    		printf ("  where:<# burgers> is the number of ordered burgers\n");
    		printf ("        <# salads> is the number of ordered salads\n");
    		printf ("        <name> is the name of the person putting the order\n");
    		return;
   	}

	/* Check if the name already exists in the line */
        if ( doesNameExist(*&hd, name) == TRUE) {
                printf ("Error: Name already exists in the order list.\n");
                printf ("Please use another name.\n");
                return;
        }

	/* Set the status of the group */
	boolean status = NOT_IN;

	/* Notify the user that the call ahead order is being added and use addToList to add the order into the list */
 	printf ("\nAdding Call-ahead order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);
	addToList(*&hd, name, NumBurgers, NumSalads, status);

}

/* Function that changes a group order whose status is "not in the restaurant" to "in the restaurant" */
void doWaiting (NODE** hd)
{
	boolean statusUpdate; // Variable to hold a boolean to determine if status was changed
	
	/* Get order name from input */
	char *name = getName();
	if (NULL == name) {
    		printf ("Error: Waiting command requires a name to be given\n");
    		printf ("Waiting command is of form: w <name>\n");
    		printf ("  where: <name> is the name of the group that is now waiting\n");
    		return;
   	}
	
	/* Check if the name already exists in the list */
        if ( doesNameExist(*&hd, name) == FALSE) {
                printf ("Error: Name is not in the order list.\n");
                printf ("Please add your order or call ahead.\n");
                return;
        }

	/* Call updateStatus function to traverse the list for the group with the name sent in and change their status */
	statusUpdate = updateStatus(*&hd, name);

	/* Notify the user if the status was changed */
	if ( statusUpdate == TRUE) {
		printf ("\nCall-ahead order \"%s\" is now waiting in the restaurant\n", name);
	}

	/* Notify the user that the status was already in the restaurant so nothing was changed */
	else {
		printf ("\n%s is already waiting in the restaurant\n", name);
	}
	
}

/* Function that retrieves information of how many burgers and salads were prepared.
 * It then searches the list to see if any of the prepared meals match the orders in the list.
 * If it does, the first matched order will be removed from the list */
void doRetrieve (NODE** hd)
{
	char* name; // Variable to hold the name of the group being removed

	/* Get info of prepared food ready on the counter from input */
	int PreparedBurgers = getPosInt();
	if (PreparedBurgers < 0) {
    		printf ("Error: Retrieve command requires an integer value of at least 0\n");
    		printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    		printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    		printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    		return;
   	}

 	int PreparedSalads = getPosInt();
 	if (PreparedSalads < 0) {
    		printf ("Error: Retrieve command requires an integer value of at least 0\n");
    		printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    		printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    		printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    		return;
   	}

 	clearToEoln();
 
	/* Case where the list is empty */
        if ( *hd == NULL) {
                printf ("There are no orders in the list for anything to be retrieved.\n");
		if ( debugMode == TRUE) {
			printf ("Debug: List is empty. No need for traversal. Return out of function.\n");
		}
		return;
        }

	/* Call retrieveAndRemove function and store the result into name */
	name = retrieveAndRemove(*&hd, PreparedBurgers, PreparedSalads);

	/* If none of the orders matched, notify the user and return */
	if ( name == NULL) {
		printf ("The number of prepared items does not satisfy any of the orders or group with matching order is not in the restaurant\n");
		printf ("Nobody picked up the order.\n");
		return;
	}

	/* Display what got picked up and who picked up the order */
	printf ("\nRetrieve (and remove) the first group that can pick up the order of %d burgers and %d salads\n", PreparedBurgers ,PreparedSalads);
	printf ("%s picked up the order.\n", name);
	
}

/* Function that gives the number of orders that are in front of a given group and lists them out */
void doList (NODE** hd)
{
	int prevOrders; // Variable to store the number of orders in front of the group

	/* Get order name from input */
	char *name = getName();
	if (NULL == name) {
    		printf ("Error: List command requires a name to be given\n");
    		printf ("List command is of form: l <name>\n");
    		printf ("  where: <name> is the name of the order to inquire about\n");
    		return;
   	}
	
	/* Check if the name exists in the list. If it does not, notify the user and return. */
	if ( doesNameExist(*&hd, name) == FALSE) {
                printf ("Error: The name given is not in the list.\n");
                printf ("Please use another name.\n");
                return;
        }

	/* Store the number of orders in front of the group in front of the group in prevOrders by calling the countOrdersAhead function */
	prevOrders = countOrdersAhead(*&hd, name);	

	/* Display the results */
	printf ("\nThere are %d orders in front of %s\n", prevOrders, name);

 	printf ("\nOrder for \"%s\" is behind the following orders\n", name);

	displayOrdersAhead(*&hd, name);

}

/* Function that lists out the entire list */
void doDisplay (NODE** hd)
{
	clearToEoln();

	/* Call the displayListInformation to print out the name, food ordered and restaurant status of each order in the list */
	printf ("\nDisplay information about all orders\n");
	displayListInformation(*&hd);
}

/* Function that gives an estimation of how long the order for a specific group will take */
void doEstimateTime (NODE ** hd)
{
	int time = 0; // Variable to hold the waiting time

	/* Get order name from input */
	char *name = getName();
	if (NULL == name) {
    		printf ("Error: List command requires a name to be given\n");
    		printf ("List command is of form: t <name>\n");
    		printf ("  where: <name> is the name of the order to inquire about\n");
    		return;
   	}

	/* Check if the name exists in the list. If it does not, notify the user and return. */
	if ( doesNameExist(*&hd, name) == FALSE) {
                printf ("Error: The name given is not in the list.\n");
                printf ("Please use another name.\n");
                return;
        }

	/* Get the estimated time by calling displayWaitingTime function and store it into time */
	time = displayWaitingTime(*&hd, name);

	/* Notify the user how long it will take */
	printf ("\nWaiting time for %s is: %d minutes.\n", name, time);

}

