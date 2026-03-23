#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include "model.h"

#define INITIAL_CAPACITY 100

typedef Product DinamicProduct;

typedef struct {
	DinamicProduct* products;
	int length;
	int capacity;
} DinamicInventory;

DinamicInventory* create_dinamic_inventory();

void destroy_dinamic_inventory(DinamicInventory* d_inv);

void resize(DinamicInventory* d_inv);


/*
	Inventory
	- list = an array of Product object, contains the current stock of the shop
	- lenght = the number of different product
*/

typedef struct {
	Product list[100];
	int length;
}Inventory;

/*
	Adds the given product to the inventory

	inv = a pointer to the Inventory object
	new_product = the product that will be added

	postcond: 
		- inv contains new_product 
		- the lenght of the inventory is incremented
*/

void add_product_repo(DinamicInventory* inv, DinamicProduct new_product);

/*
	Updates the quantity of a given Product object from the inventory

	inv = pointer to the Inventory object
	product_id = a positive integer that represents 
				 the id of the Product object that will be updated
	new_quantity = a positive integer that represents
				   the new quantity of the product

	returns:
		- 1 if the update has been made
		- 0 otherwise

	postcond:
		- if there is a product with the given id 
				=> that product's quantity is modified
		- otherwise
				=> the inventory doesn't change
*/
int update_product_quantity_repo(DinamicInventory* inv, int product_id, int new_quantity);

/*
	Updates the price of a given Product object from the inventory

	inv = pointer to the Inventory object
	product_id = a positive integer that represents
				 the id of the Product object that will be updated
	new_price = a positive integer that represents
				   the new price of the product

	returns:
		- 1 if the update has been made
		- 0 otherwise

	postcond:
		- if there is a product with the given id
				=> that product's price is modified
		- otherwise
				=> the inventory doesn't change
*/
int update_product_price_repo(DinamicInventory* inv, int product_id, int new_price);

/*
	Deletes the product with the given id from memory

	inv = pointer to the Inventory object
	product_id = the id of the product that will be deleted

	returns: 
		- 1 if the product has been deleted
		- 0 otherwise

	postcond: 
		- if there is a product with the given id
				=> that product is removed from the given inventory
				=> the inventory's length is decremented
		- otherwise
				=> the inventory doesn't change
*/
int delete_product_repo(DinamicInventory* inv, int product_id);

#endif