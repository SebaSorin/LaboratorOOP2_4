#include <stdio.h>
#include "tests.h"
#include "service.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void print_main_menu() {
	printf("Alegeti o optiune: \n");
	printf("1. Adaugare produs nou/modificare cantitate\n");
	printf("2. Actualizare produs(cantitate/pret)\n");
	printf("3. Stergere produs\n");
	printf("4. Afisare produse ordonate dupa pret/cantitate\n");
	printf("5. Afisare produse cu acelasi producator/pret/cantitate\n");
	printf("10. Afisare produse(neordonat)\n");
	printf("0. Iesire\n");
}

void print_all_products(DinamicInventory* inv) {
	if (inv->length == 0) {
		printf("Nu exista produse disponibile!\n");
		return;
	}
	
	for (int i = 0; i < inv->length; i++) {
		printf("%d. ", inv->products[i].id);
		printf("tip: %s, ", inv->products[i].type);
		printf("prod: %s, ", inv->products[i].manufacturer);
		printf("model: %s, ", inv->products[i].model);
		printf("pret: %d, ", inv->products[i].price);
		printf("cant: %d\n", inv->products[i].quantity);
	}
}

/*
	Reads and stores an integer value

	number = pointer to the int variable that will store the read value
	msg = a message to be printed before reading for the user

	returns:
		- 1 = if the user input is valid
		- 0 = otherwise

	poscond:
		- if the user input was valid
				=> number points to a variable that contains the input
		- otherwise
				=> 0 is returned
*/
int read_integer(int* number, char msg[]) {
	printf("%s", msg);

	if (scanf_s("%d", number) != 1) {
		scanf_s("%*s");
		return 0;
	}
	return 1;
}

/*
	Reads and stores a string with the given length

	arr = the string that will contain the input
	arr_len = the maximum length of the string
	msg = a message to be printed before reading for the user

	returns:
		- 1 = if the user input is valid
		- 0 = otherwise

	poscond:
		- if the user input was valid
				=> arr points to a string that contains the input
		- otherwise
				=> 0 is returned
*/
int read_char_array(char arr[], int arr_len, char msg[]) {
	printf("%s", msg);
	if (scanf_s("%s", arr, arr_len) != 1) {
		scanf_s("%*s");
		return 0;
	}
	return 1;
}


int add_product_ui(DinamicService* serv) {
	int id;
	char type[30];
	char manufacturer[50];
	char model[30];
	int price;
	int quantity;

	if (!read_integer(&id, "id: ")) {
		printf("Id invalid!\n");
		return 0;
	}

	if (!read_char_array(type, 30, "tip: ")) {
		printf("Tip invalid!\n");
		return 0;
	}

	if (!read_char_array(manufacturer, 50, "producator: ")) {
		printf("Producator invalid!\n");
		return 0;
	}

	if (!read_char_array(model, 30, "model: ")) {
		printf("Model invalid!\n");
		return 0;
	}

	if (!read_integer(&price, "pret: ")) {
		printf("Pret invalid!\n");
		return 0;
	}

	if (!read_integer(&quantity, "cantitate: ")) {
		printf("Cantitate invalida!\n");
		return 0;
	}

	char error_list[7][30];
	int error_cnt = 0;
	add_product_serv(serv, id, type, manufacturer, model, price, quantity, error_list, &error_cnt);
	if (error_cnt != 0) {
		for (int i = 0; i < error_cnt; i++)
			printf("%s\n", error_list[i]);
		return 0;
	}
	return 1;
}

void update_product_price_ui(DinamicService* serv, int product_id) {
	int new_price = 0;
	
	while (1) {
		while (!read_integer(&new_price, "pret nou: "))
			printf("Pret invalid!\n");

		int err_cnt = 0;
		char err_lst[7][30];
		if (update_product_price_serv(serv, product_id, new_price, err_lst, &err_cnt)) {
			printf("Modificare efectuata cu succes!\n");
			break;
		}			

		for (int i = 0; i < err_cnt; i++)
			printf("%s\n", err_lst[i]);
	}
}

void update_product_quantity_ui(DinamicService* serv, int product_id) {
	int new_quantity = 0;

	while (1) {
		while (!read_integer(&new_quantity, "cantitate noua: "))
			printf("Cantitate invalida!\n");

		int err_cnt = 0;
		char err_lst[7][30];
		if (update_product_quantity_serv(serv, product_id, new_quantity, err_lst, &err_cnt)) {
			printf("Modificare efectuata cu succes!\n");
			break;
		}

		for (int i = 0; i < err_cnt; i++)
			printf("%s\n", err_lst[i]);
	}
}

void update_product_ui(DinamicService* serv) {
	int id;
	if (!read_integer(&id, "id: ")) {
		printf("Id invalid!\n");
		return;
	}

	int option;
	while (1) {
		printf("Alegeti tipul de modificare: \n");
		printf("1. Pret\n");
		printf("2. Cantitate\n");
		printf("0. Anulare\n");

		if (!read_integer(&option, ">>> "))
			printf("Optiune invalida!\n");
		else {
			if (option == 1) {
				update_product_price_ui(serv, id);
				break;
			}
			else if (option == 2) {
				update_product_quantity_ui(serv, id);
				break;
			}
			else if (option == 0)
				break;
			else
				printf("Optiune invalida!\n");
		}
	}
}

int delete_product_ui(DinamicService* serv) {
	int id;
	if (!read_integer(&id, "id: ")) {
		printf("Id invalid!\n");
		return 0;
	}

	char err_msg[30];
	if (delete_product_serv(serv, id, err_msg) == 0) {
		printf("%s", err_msg);
		return 0;
	}
	return 1;
}

void sort_products_ui(DinamicService* serv) {
	if (serv->inv->length == 0) {
		printf("Nu exista produse disponibile!\n");
		return;
	}
	
	printf("Alegeti tipul sortarii:\n");
	printf("10. Dupa pret(crescator)\n");
	printf("11. Dupa pret(descrescator)\n");
	printf("20. Dupa cantitate(crescator)\n");
	printf("21. Dupa cantitate(descrescator)\n");
	int option;
	if (!read_integer(&option, ">>> ")) {
		printf("Optiune invalida!\n");
		return;
	}

	if (option == 10)
		sort_by_price(serv, 0);
	else if (option == 11)
		sort_by_price(serv, 1);
	else if (option == 20)
		sort_by_quantity(serv, 0);
	else if (option == 21)
		sort_by_quantity(serv, 1);
	else {
		printf("Optiune invalida!\n");
		return;
	}
	print_all_products(serv->inv);
}

void sort_products_generalised_ui(DinamicService* serv) {
	if (serv->inv->length == 0) {
		printf("Nu exista produse disponibile!\n");
		return;
	}

	printf("Alegeti tipul sortarii:\n");
	printf("10. Dupa pret(crescator)\n");
	printf("11. Dupa pret(descrescator)\n");
	printf("20. Dupa cantitate(crescator)\n");
	printf("21. Dupa cantitate(descrescator)\n");
	int option;
	if (!read_integer(&option, ">>> ")) {
		printf("Optiune invalida!\n");
		return;
	}

	if (option == 10)
		sort_by_price_generalised(serv, 0);
	else if (option == 11)
		sort_by_price_generalised(serv, 1);
	else if (option == 20)
		sort_by_quantity_generalised(serv, 0);
	else if (option == 21)
		sort_by_quantity_generalised(serv, 1);
	else {
		printf("Optiune invalida!\n");
		return;
	}
	print_all_products(serv->inv);
}

void filter_by_manufacturer_ui(DinamicService* serv) {
	char manufacturer[30];
	while (!read_char_array(manufacturer, 30, "producator: "))
		printf("Producator invalid!\n");

	char err_msg[30];
	DinamicInventory* inv = filter_by_manufacturer_serv(serv, manufacturer, err_msg);
	if (inv->length == 0)
		printf(err_msg);
	else
		print_all_products(inv);
}

void filter_by_price_ui(DinamicService* serv) {
	int price;
	while (!read_integer(&price, "pret: "))
		printf("Pret invalid!\n");

	char err_msg[30];
	DinamicInventory* inv = filter_by_price_serv(serv, price, err_msg);
	if (inv->length == 0)
		printf(err_msg);
	else
		print_all_products(inv);
}

void filter_by_quantity_ui(DinamicService* serv) {
	int quantity;
	while (!read_integer(&quantity, "cantitate: "))
		printf("Cantitate invalida!\n");

	char err_msg[30];
	DinamicInventory* inv = filter_by_quantity_serv(serv, quantity, err_msg);
	if (inv->length == 0)
		printf(err_msg);
	else
		print_all_products(inv);
}

void filter_products_ui(DinamicService* serv) {
	if (serv->inv->length == 0) {
		printf("Nu exista produse disponibile!\n");
		return;
	}
	
	printf("Alegeti criteriul:\n");
	printf("1. Producator\n");
	printf("2. Pret\n");
	printf("3. Cantitate\n");
	
	int option;
	if (!read_integer(&option, ">>> ")) {
		printf("Criteriu invalid!\n");
		return;
	}

	switch (option) {
	case 1:
		filter_by_manufacturer_ui(serv);
		break;
	case 2:
		filter_by_price_ui(serv);
		break;
	case 3:
		filter_by_quantity_ui(serv);
		break;
	default:
		printf("Criteriu invalid!\n");
	}
}

void test_all() {
	test_repository_methods();
	test_service_methods();
	test_validator_methods();
}

int main() {
	test_all();
	if (_CrtDumpMemoryLeaks())
		printf("THERE ARE MEMORY LEAKS\n");
	else
		printf("TESTS PASSED!\n");
	

	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService serv = { inv };


	while (1) {
		print_main_menu();
		int option = 0;
		if (read_integer(&option, ">>> ")) {
			if (option == 0)
				break;
			else if (option == 1) {
				if (add_product_ui(&serv))
					printf("Operatie efectuata cu succes!\n");
			}
			else if (option == 2)
				update_product_ui(&serv);
			else if (option == 3) {
				if (delete_product_ui(&serv))
					printf("Operatie efectuata cu succes!\n");
			}
			else if (option == 4)
				sort_products_generalised_ui(&serv);
			else if (option == 5)
				filter_products_ui(&serv);
			else if (option == 10)
				print_all_products(serv.inv);
			else
				printf("Optiune invalida!\n");
		}
		else
			printf("Optiune invalida!\n");

		printf("\n\n");
	}

	destroy_dinamic_inventory(inv);
	

	return 0;
}

