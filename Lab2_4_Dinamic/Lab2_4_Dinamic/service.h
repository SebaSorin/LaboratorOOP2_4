#ifndef SERVICE_H_
#define SERVICE_H_

#include "repository.h"

/*
	Service:
	- inv = pointer to an Inventory object
*/

typedef struct {
	DinamicInventory* inv;
}DinamicService;

typedef struct {
	Inventory* inv;
}Service;

typedef int (*CompareMethod)(Product p1, Product p2);

/*
	Adds a product with the given values to the service

	serv = pointer to the Service object
	id = the id of the new product, unique positive integer
	type = the type of the new product, a string with at most 30 characters
	manufacturer = the manufacturer of the new product, a string with at most 50 characters
	model = the model of the new product, a string with at most 30 characters
	price = the price of the new product, positive integer
	quantity = the quantity of the new product, positive integer
	error_list = an array of strings that contains messages with wrong inputs
	error_count = a pointer to an integer that will represent the number of errors in the input

	postcond:
		- if the all values are valid
				=> a product with the given values is added to the inventory
				=> error_list is empty and the values error_count points to is 0
		- otherwise
				=> error_list contains messages relevant to the values that were invalid
				=> error_count points to an in that is equal to the number of errors
*/
void add_product_serv(DinamicService* serv, int id, char type[], char manufacturer[], char model[], int price, int quantity, char error_list[7][30], int* error_count);

/*
	Updates the price of the given product from the service

	serv = pointer to the Service object
	product_id = the id of the given product object
	new_price = the new price of the product
	error_list = an array of strings that contains messages with wrong inputs
	error_count = a pointer to an integer that will represent the number of errors in the input

	returns:
		- 1 = if the update has been made
		- 0 = otherwise

	postcond:
		- if all values are valid and there is a product with the given index
				=> the product with the given index now has the given price
				=> error_list is empty and the values error_count points to is 0
		- otherwise
				=> error_list contains messages relevant to the values that were invalid
				=> error_count points to an in that is equal to the number of errors
*/
int update_product_price_serv(DinamicService* serv, int product_id, int new_price, char error_msg[2][30], int* error_cnt);

/*
	Updates the quantity of the given product from the service

	serv = pointer to the Service object
	product_id = the id of the given product object
	new_quantity = the new quantity of the product
	error_list = an array of strings that contains messages with wrong inputs
	error_count = a pointer to an integer that will represent the number of errors in the input

	returns:
		- 1 = if the update has been made
		- 0 = otherwise

	postcond:
		- if all values are valid and there is a product with the given index
				=> the product with the given index now has the given quantity
				=> error_list is empty and the values error_count points to is 0
		- otherwise
				=> error_list contains messages relevant to the values that were invalid
				=> error_count points to an in that is equal to the number of errors
*/
int update_product_quantity_serv(DinamicService* serv, int product_id, int new_quantity, char error_lst[2][30], int* error_cnt);

/*
	Deletes a product from the Service object

	serv = a pointer to the given service
	product_id = the id of the product that will be deleted
	error_message = a char array that will describe the error in case the input is wrong

	returns:
		- 1 = if the product was deleted
		- 0 = otherwise

	postcond:
		- if the id was valid and there was a product with the given id stored in the serv
				=> that product has been removed from serv
				=> the length of the inventory has been decremented
				=> the string within error_message hasn't changed
		- otherwise
				=> the inventory remains the same
				=> error_message contains a message describing in what way the id was wrong
*/
int delete_product_serv(DinamicService* serv, int product_id, char error_message[]);

/*
	Swaps two products within the given service

	serv = pointer to the service object
	id1, id2 = the ids of the products that will be swapped

	returns:
		- 1 = if the swap has been made
		- 0 = otherwise

	postcond:
		- if the ids were valid and belonged to two products that were stored in the service
				=> the products are swapped
		- otherwise
				=> the service remains the same
*/
int swap_products(DinamicService* serv, int id1, int id2);

/*
	Sorts the products within the service by price in descending or ascending order

	serv = pointer to the Service object
	descending_flag = determines whether or not the sort is in descending order

	postcond: 
		- descending_flag = 0
				=> the inventory is sorted by price in ascending order
		- descending_flag = 1
				=> the inventory is sorted by price in descending order
*/
void sort_by_price(DinamicService* serv, int descending_flag);

/*
	Sorts the products within the service by quantity in descending or ascending order

	serv = pointer to the Service object
	descending_flag = determines whether or not the sort is in descending order

	postcond:
		- descending_flag = 0
				=> the inventory is sorted by quantity in ascending order
		- descending_flag = 1
				=> the inventory is sorted by quantity in descending order
*/
void sort_by_quantity(DinamicService* serv, int descending_flag);


void selection_sort(DinamicService* serv, CompareMethod cmp);

int compare_price_descending(Product p1, Product p2);

int compare_price_ascending(Product p1, Product p2);

int compare_quantity_descending(Product p1, Product p2);

int compare_quantity_ascending(Product p1, Product p2);

void sort_by_price_generalised(DinamicService* serv, int descending_flag);

void sort_by_quantity_generalised(DinamicService* serv, int descending_flag);

/*
	Filters the products that have the given manufacturer

	serv = pointer to the Service object
	prod_manufacturer = string that represents the given manufacturer
	error_message = string that will contain a message regarding the error in case of invalid input

	returns: a pointer to an Inventory object that will contain the relevant products

	postcond:
		- if the given manufacturer is valid and there are products that have it
				=> the pointer points to an inventory that contains all of those products
		- otherwise
				=> the pointer points to an empty inventory 
*/
DinamicInventory* filter_by_manufacturer_serv(DinamicService* serv, char prod_manufacturer[], char error_message[]);

/*
	Filters the products that have the given price

	serv = pointer to the Service object
	prod_price = string that represents the given price
	error_message = string that will contain a message regarding the error in case of invalid input

	returns: a pointer to an Inventory object that will contain the relevant products

	postcond:
		- if the given price is valid and there are products that have it
				=> the pointer points to an inventory that contains all of those products
		- otherwise
				=> the pointer points to an empty inventory
*/
DinamicInventory* filter_by_price_serv(DinamicService* serv, int prod_price, char error_message[]);

/*
	Filters the products that have the given quantity

	serv = pointer to the Service object
	prod_quantity = string that represents the given quantity
	error_message = string that will contain a message regarding the error in case of invalid input

	returns: a pointer to an Inventory object that will contain the relevant products

	postcond:
		- if the given quantity is valid and there are products that have it
				=> the pointer points to an inventory that contains all of those products
		- otherwise
				=> the pointer points to an empty inventory
*/
DinamicInventory* filter_by_quantity_serv(DinamicService* serv, int prod_quantity, char error_message[]);

#endif // !SERVICE_H_
