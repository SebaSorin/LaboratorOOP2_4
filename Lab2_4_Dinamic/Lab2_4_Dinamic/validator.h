#ifndef VALIDATOR_H_
#define VALIDATOR_H_

#include "model.h"

/*
	Validates the given id

	product_id = the given id

	returns:
		- 1 = if the id is valid
		- 0 = otherwise
*/
int validate_id(int product_id);

/*
	Validates the given type

	product_type = the given type

	returns:
		- 1 = if the type is valid
		- 0 = otherwise
*/
int validate_type(char* product_type, int max_len);

/*
	Validates the given manufacturer

	product_manufacturer = the given manufacturer

	returns:
		- 1 = if the manufacturer is valid
		- 0 = otherwise
*/
int validate_manufacturer(char* product_man);

/*
	Validates the given model

	product_model = the given model

	returns:
		- 1 = if the model is valid
		- 0 = otherwise
*/
int validate_model(char* product_model);

/*
	Validates the given price

	product_price = the given price

	returns:
		- 1 = if the price is valid
		- 0 = otherwise
*/
int validate_price(int product_price);

/*
	Validates the given quantity

	product_quantity = the given quantity

	returns:
		- 1 = if the quantity is valid
		- 0 = otherwise
*/
int validate_quantity(int product_quantity);


#endif // !VALIDATOR_H_
