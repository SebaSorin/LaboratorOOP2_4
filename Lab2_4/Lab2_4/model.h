#ifndef MODEL_H_
#define MODEL_H_

/*
	 Contains the definition for the electronic product data type
	 with the following fields:
		- id = unique positive integer
		- type = a string with at most 30 characters
		- manufacturer = a string with at most 50 characters
	 	- model = a string with at most 30 characters
	    - price = positive integer
		- quantity = positive integer
*/

typedef struct {
	int id;
	char type[30];
	char manufacturer[50];
	char model[30];
	int price;
	int quantity;
}Product;



#endif
