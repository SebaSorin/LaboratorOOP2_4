#include "service.h"
#include "validator.h"

void add_product_serv(Service* serv, int id, char type[], char manufacturer[], char model[], int price, int quantity, char error_list[7][30], int* error_count) {
	*error_count = 0;
	if (validate_id(id) == 0)
		strcpy(error_list[(*error_count)++], "Id invalid!");

	if (validate_type(type, 30) == 0)
		strcpy(error_list[(*error_count)++], "Tip invalid!");

	if (validate_manufacturer(manufacturer) == 0)
		strcpy(error_list[(*error_count)++], "Producator invalid!");

	if (validate_model(model) == 0)
		strcpy(error_list[(*error_count)++], "Model invalid!");

	if (validate_price(price) == 0)
		strcpy(error_list[(*error_count)++], "Pret invalid!");

	if (validate_quantity(quantity) == 0)
		strcpy(error_list[(*error_count)++], "Cantitate invalida!");

	if (*error_count == 0) {
		Product prd; // = { id, type, manufacturer, model, price, quantity };
		prd.id = id;
		strcpy(prd.type, type);
		strcpy(prd.manufacturer, manufacturer);
		strcpy(prd.model, model);
		prd.price = price;
		prd.quantity = quantity;

		if (!update_product_quantity_repo(serv->inv, id, quantity))
			add_product_repo(serv->inv, prd);
	}

}

int update_product_price_serv(Service* serv, int product_id, int new_price, char error_lst[2][30], int* error_cnt) {
	*error_cnt = 0;
	if (validate_id(product_id) == 0)
		strcpy(error_lst[(*error_cnt)++], "Id invalid!");
	
	if (validate_price(new_price) == 0) 
		strcpy(error_lst[(*error_cnt)++], "Pret invalid!");

	if (*error_cnt != 0)
		return 0;

	if (!update_product_price_repo(serv->inv, product_id, new_price)) {
		strcpy(error_lst[(*error_cnt)++], "Id nonexistent!");
		return 0;
	}

	return 1;
}

int update_product_quantity_serv(Service* serv, int product_id, int new_quantity, char error_lst[2][30], int* error_cnt) {
	*error_cnt = 0;
	if (validate_id(product_id) == 0)
		strcpy(error_lst[(*error_cnt)++], "Id invalid!");

	if (validate_quantity(new_quantity) == 0)
		strcpy(error_lst[(*error_cnt)++], "Cantitate invalida!");

	if (*error_cnt != 0)
		return 0;

	if (!update_product_quantity_repo(serv->inv, product_id, new_quantity)) {
		strcpy(error_lst[(*error_cnt)++], "Id nonexistent!");
		return 0;
	}

	return 1;
}

int delete_product_serv(Service* serv, int product_id, char error_message[]) {
	if (validate_id(product_id) == 0) {
		strcpy(error_message, "Id invalid!");
		return 0;
	}

	if (delete_product_repo(serv->inv, product_id) == 0) {
		strcpy(error_message, "Id nonexistent!");
		return 0;
	}
	return 1;
}

int swap_products(Service* serv, int id1, int id2) {
	if (!validate_id(id1) || !validate_id(id2))
		return 0;
	
	int ind1 = -1, ind2 = -1;
	for (int i = 0; i < serv->inv->length; i++) {
		if (serv->inv->list[i].id == id1)
			ind1 = i;
		if (serv->inv->list[i].id == id2)
			ind2 = i;
	}

	if (ind1 == -1 || ind2 == -1)
		return 0;

	int aux = serv->inv->list[ind1].id;
	serv->inv->list[ind1].id = serv->inv->list[ind2].id;
	serv->inv->list[ind2].id = aux;

	char temp[100];
	strcpy(temp, serv->inv->list[ind1].type);
	strcpy(serv->inv->list[ind1].type, serv->inv->list[ind2].type);
	strcpy(serv->inv->list[ind2].type, temp);

	strcpy(temp, serv->inv->list[ind1].manufacturer);
	strcpy(serv->inv->list[ind1].manufacturer, serv->inv->list[ind2].manufacturer);
	strcpy(serv->inv->list[ind2].manufacturer, temp);
	
	strcpy(temp, serv->inv->list[ind1].model);
	strcpy(serv->inv->list[ind1].model, serv->inv->list[ind2].model);
	strcpy(serv->inv->list[ind2].model, temp);

	aux = serv->inv->list[ind1].price;
	serv->inv->list[ind1].price = serv->inv->list[ind2].price;
	serv->inv->list[ind2].price = aux;

	aux = serv->inv->list[ind1].quantity;
	serv->inv->list[ind1].quantity = serv->inv->list[ind2].quantity;
	serv->inv->list[ind2].quantity = aux;
	
	return 1;
}

void sort_by_price(Service* serv, int descending_flag) {
	// flag = 0 ascending
	// flag = 1 descending
	Inventory* current_inv = serv->inv;
	for (int i = 0; i < current_inv->length - 1; i++) {
		int swap_ind = i;
		for (int j = i + 1; j < current_inv->length; j++) {
			if (descending_flag == 1 && current_inv->list[i].price < current_inv->list[j].price) 
				swap_ind = j;
			else if (descending_flag == 0 && current_inv->list[i].price > current_inv->list[j].price)
				swap_ind = j;
		}

		if (swap_ind != i) 
			swap_products(serv, serv->inv->list[i].id, serv->inv->list[swap_ind].id);
	}
}

void sort_by_quantity(Service* serv, int descending_flag) {
	// flag = 0 ascending
	// flag = 1 descending
	Inventory* current_inv = serv->inv;
	for (int i = 0; i < current_inv->length - 1; i++) {
		int swap_ind = i;
		for (int j = i + 1; j < current_inv->length; j++) {
			if (descending_flag == 1 && current_inv->list[i].quantity < current_inv->list[j].quantity)
				swap_ind = j;
			else if (descending_flag == 0 && current_inv->list[i].quantity > current_inv->list[j].quantity)
				swap_ind = j;
		}

		if (swap_ind != i)
			swap_products(serv, serv->inv->list[i].id, serv->inv->list[swap_ind].id);
	}
}

Inventory* filter_by_manufacturer_serv(Service* serv, char prod_manufacturer[], char error_message[]) {
	Inventory print_inv = { 0 };
	if (!validate_manufacturer(prod_manufacturer)) {
		strcpy(error_message, "Producator invalid!");
		return &print_inv;
	}
	
	Inventory* current_inv = serv->inv;
	for (int i = 0; i < current_inv->length; i++) {
		if (strcmp(current_inv->list[i].manufacturer, prod_manufacturer) == 0)
			add_product_repo(&print_inv, current_inv->list[i]);
	}

	if (print_inv.length == 0)
		strcpy(error_message, "Producator nonexistent!");
	return &print_inv;
}

Inventory* filter_by_price_serv(Service* serv, int prod_price, char error_message[]) {
	Inventory print_inv = { 0 };
	if (!validate_price(prod_price)) {
		strcpy(error_message, "Pret invalid!");
		return &print_inv;
	}

	Inventory* current_inv = serv->inv;
	for (int i = 0; i < current_inv->length; i++) {
		if (current_inv->list[i].price == prod_price)
			add_product_repo(&print_inv, current_inv->list[i]);
	}

	if (print_inv.length == 0)
		strcpy(error_message, "Pret nonexistent!");
	return &print_inv;
}

Inventory* filter_by_quantity_serv(Service* serv, int prod_quantity, char error_message[]) {
	Inventory print_inv = { 0 };
	if (!validate_price(prod_quantity)) {
		strcpy(error_message, "Cantitate invalida!");
		return &print_inv;
	}

	Inventory* current_inv = serv->inv;
	for (int i = 0; i < current_inv->length; i++) {
		if (current_inv->list[i].quantity == prod_quantity)
			add_product_repo(&print_inv, current_inv->list[i]);
	}

	if (print_inv.length == 0)
		strcpy(error_message, "Cantitate nonexistenta!");
	return &print_inv;
}