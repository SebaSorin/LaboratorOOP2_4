#include "service.h"
#include "validator.h"
#include <string.h>
#include <stdlib.h>

char** init_error_message(int message_count, int message_length) {
	char** error_list = malloc(sizeof(char*) * message_count);

	for (int i = 0; i < message_count; i++) {
		error_list[i] = malloc(sizeof(char) * message_length);
	}
	return error_list;
}

void destroy_error_message(char** error_list, int error_count) {
	for (int i = 0; i < error_count; i++)
		free(error_list[i]);
	free(error_list);
}

void destroy_dinamic_service(DinamicService* serv) {
	destroy_dinamic_inventory(serv->inv);
	serv->inv = NULL;
}

void add_product_serv(DinamicService* serv, int id, char* type, char* manufacturer, char* model, int price, int quantity, char** error_list, int* error_count) {
	*error_count = 0;
	if (validate_id(id) == 0)
		strcpy_s(error_list[(*error_count)++], sizeof("Id invalid!"), "Id invalid!"); 

	if (validate_type(type, 30) == 0)
		strcpy_s(error_list[(*error_count)++], sizeof("Tip invalid!"), "Tip invalid!");

	if (validate_manufacturer(manufacturer) == 0)
		strcpy_s(error_list[(*error_count)++], sizeof("Producator invalid!"), "Producator invalid!");

	if (validate_model(model) == 0)
		strcpy_s(error_list[(*error_count)++], sizeof("Model invalid!"), "Model invalid!");

	if (validate_price(price) == 0)
		strcpy_s(error_list[(*error_count)++], sizeof("Pret invalid!"), "Pret invalid!");

	if (validate_quantity(quantity) == 0)
		strcpy_s(error_list[(*error_count)++], sizeof("Cantitate invalida!"), "Cantitate invalida!");

	if (*error_count == 0) {
		if (!update_product_quantity_repo(serv->inv, id, quantity)) {
			DinamicProduct prd = create_product(id, type, manufacturer, model, price, quantity);
			add_product_repo(serv->inv, copy_product(&prd));
			destroy_product(&prd);
		}
	}

}

int update_product_price_serv(DinamicService* serv, int product_id, int new_price, char** error_lst, int* error_cnt) {
	*error_cnt = 0;
	if (validate_id(product_id) == 0)
		strcpy_s(error_lst[(*error_cnt)++], sizeof("Id invalid!"), "Id invalid!");
	
	if (validate_price(new_price) == 0) 
		strcpy_s(error_lst[(*error_cnt)++], sizeof("Pret invalid!"), "Pret invalid!");

	if (*error_cnt != 0)
		return 0;

	if (!update_product_price_repo(serv->inv, product_id, new_price)) {
		strcpy_s(error_lst[(*error_cnt)++], sizeof("Id nonexistent!"), "Id nonexistent!");
		return 0;
	}

	return 1;
}

int update_product_quantity_serv(DinamicService* serv, int product_id, int new_quantity, char** error_lst, int* error_cnt) {
	*error_cnt = 0;
	if (validate_id(product_id) == 0)
		strcpy_s(error_lst[(*error_cnt)++], sizeof("Id invalid!"), "Id invalid!");

	if (validate_quantity(new_quantity) == 0)
		strcpy_s(error_lst[(*error_cnt)++], sizeof("Cantitate invalida!"), "Cantitate invalida!");

	if (*error_cnt != 0)
		return 0;

	if (!update_product_quantity_repo(serv->inv, product_id, new_quantity)) {
		strcpy_s(error_lst[(*error_cnt)++], sizeof("Id nonexistent!"), "Id nonexistent!");
		return 0;
	}

	return 1;
}

int delete_product_serv(DinamicService* serv, int product_id, char* error_message) {
	if (validate_id(product_id) == 0) {
		strcpy_s(error_message, sizeof("Id invalid!"), "Id invalid!");
		return 0;
	}

	if (delete_product_repo(serv->inv, product_id) == 0) {
		strcpy_s(error_message, sizeof("Id nonexistent!"), "Id nonexistent!");
		return 0;
	}
	return 1;
}

int swap_products(DinamicService* serv, int id1, int id2) {
	if (!validate_id(id1) || !validate_id(id2))
		return 0;
	
	int ind1 = -1, ind2 = -1;
	for (int i = 0; i < serv->inv->length; i++) {
		if (serv->inv->products[i].id == id1)
			ind1 = i;
		if (serv->inv->products[i].id == id2)
			ind2 = i;
	}

	if (ind1 == -1 || ind2 == -1)
		return 0;

	int aux = serv->inv->products[ind1].id;
	serv->inv->products[ind1].id = serv->inv->products[ind2].id;
	serv->inv->products[ind2].id = aux;

	int type_len = sizeof(char) * MAX_MODEL_LEN;
	char* temp1 = malloc(type_len);
	strcpy_s(temp1, type_len, serv->inv->products[ind1].type);
	strcpy_s(serv->inv->products[ind1].type, type_len, serv->inv->products[ind2].type);
	strcpy_s(serv->inv->products[ind2].type, type_len, temp1);
	

	int man_len = sizeof(char) * MAX_MANUFAC_LEN;
	char* temp2 = malloc(man_len);
	strcpy_s(temp2, man_len, serv->inv->products[ind1].manufacturer);
	strcpy_s(serv->inv->products[ind1].manufacturer, man_len, serv->inv->products[ind2].manufacturer);
	strcpy_s(serv->inv->products[ind2].manufacturer, man_len, temp2);
	
	int model_len = sizeof(char) * MAX_MODEL_LEN;
	strcpy_s(temp1, model_len, serv->inv->products[ind1].model);
	strcpy_s(serv->inv->products[ind1].model, model_len, serv->inv->products[ind2].model);
	strcpy_s(serv->inv->products[ind2].model, model_len, temp1);
	
	free(temp1);
	free(temp2);
	aux = serv->inv->products[ind1].price;
	serv->inv->products[ind1].price = serv->inv->products[ind2].price;
	serv->inv->products[ind2].price = aux;

	aux = serv->inv->products[ind1].quantity;
	serv->inv->products[ind1].quantity = serv->inv->products[ind2].quantity;
	serv->inv->products[ind2].quantity = aux;
	
	return 1;
}

void sort_by_price(DinamicService* serv, int descending_flag) {
	// flag = 0 ascending
	// flag = 1 descending
	DinamicInventory* current_inv = serv->inv;
	for (int i = 0; i < current_inv->length - 1; i++) {
		int swap_ind = i;
		for (int j = i + 1; j < current_inv->length; j++) {
			if (descending_flag == 1 && current_inv->products[i].price < current_inv->products[j].price)
				swap_ind = j;
			else if (descending_flag == 0 && current_inv->products[i].price > current_inv->products[j].price)
				swap_ind = j;
		}

		if (swap_ind != i) 
			swap_products(serv, serv->inv->products[i].id, serv->inv->products[swap_ind].id);
	}
}

void sort_by_quantity(DinamicService* serv, int descending_flag) {
	// flag = 0 ascending
	// flag = 1 descending
	DinamicInventory* current_inv = serv->inv;
	for (int i = 0; i < current_inv->length - 1; i++) {
		int swap_ind = i;
		for (int j = i + 1; j < current_inv->length; j++) {
			if (descending_flag == 1 && current_inv->products[i].quantity < current_inv->products[j].quantity)
				swap_ind = j;
			else if (descending_flag == 0 && current_inv->products[i].quantity > current_inv->products[j].quantity)
				swap_ind = j;
		}

		if (swap_ind != i)
			swap_products(serv, serv->inv->products[i].id, serv->inv->products[swap_ind].id);
	}
}

// new sort methods

void selection_sort(DinamicService* serv, CompareMethod cmp) {
	DinamicInventory* current_inv = serv->inv;
	for (int i = 0; i < current_inv->length - 1; i++) {
		int swap_ind = i;
		for (int j = i + 1; j < current_inv->length; j++) {
			if (cmp(current_inv->products[i], current_inv->products[j]) > 0)
				swap_ind = j;
		}

		if (swap_ind != i)
			swap_products(serv, serv->inv->products[i].id, serv->inv->products[swap_ind].id);
	}
}

// 0 if p1 has the lower price
// 1 otherwise
int compare_price_descending(Product p1, Product p2) {
	return p1.price < p2.price;
}

// 1 if p1 has the lower price
// 0 otherwise
int compare_price_ascending(Product p1, Product p2) {
	return p1.price > p2.price;
}

// 0 if p1 has a lower quantity
// 1 otherwise
int compare_quantity_descending(Product p1, Product p2) {
	return p1.quantity < p2.quantity;
}

// 1 if p1 has a lower quantity
// 0 otherwise
int compare_quantity_ascending(Product p1, Product p2) {
	return p1.quantity > p2.quantity;
}

void sort_by_price_generalised(DinamicService* serv, int descending_flag) {
	// flag = 0 ascending
	// flag = 1 descending
	selection_sort(serv, descending_flag ? compare_price_descending : compare_price_ascending);
}

void sort_by_quantity_generalised(DinamicService* serv, int descending_flag) {
	// flag = 0 ascending
	// flag = 1 descending
	selection_sort(serv, descending_flag ? compare_quantity_descending : compare_quantity_ascending);
}



DinamicInventory* filter_by_manufacturer_serv(DinamicService* serv, char* prod_manufacturer, char* error_message) {
	DinamicInventory* print_inv = create_dinamic_inventory();
	if (!validate_manufacturer(prod_manufacturer)) {
		strcpy_s(error_message, sizeof("Producator invalid!"), "Producator invalid!");
		return print_inv;
	}
	
	DinamicInventory* current_inv = serv->inv;
	for (int i = 0; i < current_inv->length; i++) {
		if (strcmp(current_inv->products[i].manufacturer, prod_manufacturer) == 0)
			add_product_repo(print_inv, copy_product(&(current_inv->products[i])));
	}

	if (print_inv->length == 0)
		strcpy_s(error_message, sizeof("Producator nonexistent!"), "Producator nonexistent!");
	return print_inv;
}

DinamicInventory* filter_by_price_serv(DinamicService* serv, int prod_price, char* error_message) {
	DinamicInventory* print_inv = create_dinamic_inventory();
	if (!validate_price(prod_price)) {
		strcpy_s(error_message, sizeof("Pret invalid!"), "Pret invalid!");
		return print_inv;
	}

	DinamicInventory* current_inv = serv->inv;
	for (int i = 0; i < current_inv->length; i++) {
		if (current_inv->products[i].price == prod_price)
			add_product_repo(print_inv, copy_product(&(current_inv->products[i])));
	}

	if (print_inv->length == 0)
		strcpy_s(error_message, sizeof("Pret nonexistent!"), "Pret nonexistent!");
	return print_inv;
}

DinamicInventory* filter_by_quantity_serv(DinamicService* serv, int prod_quantity, char* error_message) {
	DinamicInventory* print_inv = create_dinamic_inventory();
	if (!validate_price(prod_quantity)) {
		strcpy_s(error_message, sizeof("Cantitate invalida!"), "Cantitate invalida!");
		return print_inv;
	}

	DinamicInventory* current_inv = serv->inv;
	for (int i = 0; i < current_inv->length; i++) {
		if (current_inv->products[i].quantity == prod_quantity)
			add_product_repo(print_inv, copy_product(&(current_inv->products[i])));
	}

	if (print_inv->length == 0)
		strcpy_s(error_message, sizeof("Cantitate nonexistenta!"), "Cantitate nonexistenta!");
	return print_inv;
}
