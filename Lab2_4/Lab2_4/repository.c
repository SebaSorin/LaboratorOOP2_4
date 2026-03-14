#include "repository.h"


void add_product_repo(Inventory* inv, Product new_product) {
	inv->list[inv->length] = new_product;
	inv->length = inv->length + 1;
}


int update_product_quantity_repo(Inventory* inv, int product_id, int new_quantity) {
	for (int i = 0; i < inv->length; i++) {
		if (inv->list[i].id == product_id) {
			inv->list[i].quantity = new_quantity;
			return 1;
		}
	}
	return 0;
}

int update_product_price_repo(Inventory* inv, int product_id, int new_price) {
	for (int i = 0; i < inv->length; i++) {
		if (inv->list[i].id == product_id) {
			inv->list[i].price = new_price;
			return 1;
		}
	}
	return 0;
}

int delete_product_repo(Inventory* inv, int product_id) {
	for (int i = 0; i < inv->length; i++) {
		if (inv->list[i].id == product_id) {
			for (int j = i + 1; j < inv->length; j++)
				inv->list[j - 1] = inv->list[j];
			inv->length--;
			return 1;
		}
	}
	return 0;
}

