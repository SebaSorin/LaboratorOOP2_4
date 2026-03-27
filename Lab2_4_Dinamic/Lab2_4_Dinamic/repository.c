#include "repository.h"
#include <stdlib.h>


DinamicInventory* create_dinamic_inventory() {
	DinamicInventory* dinam_inv = malloc(sizeof(DinamicInventory));
	dinam_inv->products = malloc(INITIAL_CAPACITY * sizeof(DinamicProduct));
	dinam_inv->capacity = INITIAL_CAPACITY;
	dinam_inv->length = 0;
	
	return dinam_inv;
}

void destroy_dinamic_inventory(DinamicInventory* d_inv) {
	for (int i = 0; i < d_inv->length; i++)
		destroy_product(&(d_inv->products[i]));
	free(d_inv->products);
	free(d_inv);
}

void resize(DinamicInventory* d_inv) {
	int new_cap = 2 * d_inv->capacity;
	DinamicProduct* new_products = malloc(new_cap * sizeof(DinamicProduct));
	
	for (int i = 0; i < d_inv->length; i++)
		new_products[i] = d_inv->products[i];
	free(d_inv->products);
	d_inv->products = new_products;
	d_inv->capacity = new_cap;
	
}

void add_product_repo(DinamicInventory* inv, DinamicProduct new_product) {
	if (inv->length == inv->capacity)
		resize(inv);

	inv->products[inv->length++] = new_product;
}

//DinamicInventory* copy_inventory(DinamicInventory* inv) {
//	DinamicInventory* inv_cpy = create_dinamic_inventory();
//	for (int i = 0; i < inv->length; i++)
//		add_product_repo(inv_cpy, copy_product(&(inv->products[i])));
//	return inv_cpy;
//}

int update_product_quantity_repo(DinamicInventory* inv, int product_id, int new_quantity) {
	for (int i = 0; i < inv->length; i++) {
		if (inv->products[i].id == product_id) {
			inv->products[i].quantity = new_quantity;
			return 1;
		}
	}
	return 0;
}

int update_product_price_repo(DinamicInventory* inv, int product_id, int new_price) {
	for (int i = 0; i < inv->length; i++) {
		if (inv->products[i].id == product_id) {
			inv->products[i].price = new_price;
			return 1;
		}
	}
	return 0;
}

int delete_product_repo(DinamicInventory* inv, int product_id) {
	for (int i = 0; i < inv->length; i++) {
		if (inv->products[i].id == product_id) {
			destroy_product(&(inv->products[i]));
			for (int j = i + 1; j < inv->length; j++)
				inv->products[j - 1] = inv->products[j];
			inv->length--;
			return 1;
		}
	}
	return 0;
}

