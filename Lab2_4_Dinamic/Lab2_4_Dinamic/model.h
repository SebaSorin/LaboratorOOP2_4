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

#define MAX_TYPE_LEN 31
#define MAX_MANUFAC_LEN 51
#define MAX_MODEL_LEN 31 

typedef struct {
	int id;
	char* type;
	char* manufacturer;
	char* model;
	int price;
	int quantity;
}Product;

typedef Product DinamicProduct;

DinamicProduct create_product(int id, char* type, char* manufacturer, char* model, int price, int quantity);

void destroy_product(DinamicProduct* prd);

DinamicProduct copy_product(DinamicProduct* prd);

#endif
