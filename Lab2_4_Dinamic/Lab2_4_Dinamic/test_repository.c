#include "repository.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>


void test_create_product() {
	DinamicProduct prd1 = create_product(1, "laptop", "acer", "aspire", 2500, 2);
	assert(prd1.id == 1);
	assert(strcmp(prd1.type, "laptop") == 0);
	assert(strcmp(prd1.manufacturer, "acer") == 0);
	assert(strcmp(prd1.model, "aspire") == 0);
	assert(prd1.price == 2500);
	assert(prd1.quantity == 2);
	destroy_product(&prd1);
}

void test_create_inventory() {
	DinamicInventory* inv = create_dinamic_inventory();
	assert(inv->capacity == INITIAL_CAPACITY);
	assert(inv->length == 0);
	destroy_dinamic_inventory(inv);
}

void test_resize() {
	DinamicProduct prd1 = create_product(1, "laptop", "acer", "aspire", 2500, 2);
	DinamicProduct prd2 = create_product(2, "display", "lenovo", "asdasd", 1000, 10);
	DinamicInventory* inv = create_dinamic_inventory();
	
	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);
	int initial_cap = inv->capacity;
	resize(inv);
	assert(inv->capacity == initial_cap * 2);
	assert(inv->products[0].id == prd1.id);
	assert(inv->products[1].id == prd2.id);

	destroy_dinamic_inventory(inv);
}

void test_add_product() {
	DinamicProduct prd1 = create_product(1, "laptop", "acer", "aspire", 2500, 2);
	DinamicProduct prd2 = create_product(2, "display", "lenovo", "asdasd", 1000, 10);
	DinamicProduct prd3 = create_product(3, "laptop", "apple", "mac", 5000, 4);
	DinamicProduct prd4 = create_product(4, "laptop", "acer", "better aspire", 5000, 1);
	
	DinamicInventory* inv = create_dinamic_inventory();
	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);
	add_product_repo(inv, prd3);
	assert(inv->length == 3);
	assert(inv->products[0].id == prd1.id);
	assert(inv->products[1].id == prd2.id);
	assert(inv->products[2].id == prd3.id);

	inv->capacity = 3;
	add_product_repo(inv, prd4);
	assert(inv->length == 4);
	assert(inv->capacity == 3 * 2);
	assert(inv->products[3].id == prd4.id);

	destroy_dinamic_inventory(inv);
}

void test_update_product_quantity_repo() {
	DinamicProduct prd1 = create_product(1, "laptop", "acer", "aspire", 2500, 2);
	DinamicProduct prd2 = create_product(2, "display", "lenovo", "asdasd", 1000, 10);
	DinamicInventory* inv = create_dinamic_inventory();

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);

	assert(update_product_quantity_repo(inv, 1, 5) == 1);
	assert(inv->products[0].quantity == 5);

	assert(update_product_quantity_repo(inv, 3, 100) == 0);
	destroy_dinamic_inventory(inv);
}

void test_update_product_price_repo() {
	DinamicProduct prd1 = create_product(1, "laptop", "acer", "aspire", 2500, 2);
	DinamicProduct prd2 = create_product(2, "display", "lenovo", "asdasd", 1000, 10);
	DinamicInventory* inv = create_dinamic_inventory();

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);

	assert(update_product_price_repo(inv, 2, 500) == 1);
	assert(inv->products[1].price == 500);

	assert(update_product_price_repo(inv, 3, 1000) == 0);
	destroy_dinamic_inventory(inv);
}

void test_delete_product() {
	DinamicProduct prd1 = create_product(1, "laptop", "acer", "aspire", 2500, 2);
	DinamicProduct prd2 = create_product(2, "display", "lenovo", "asdasd", 1000, 10);
	DinamicInventory* inv = create_dinamic_inventory();

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);

	assert(delete_product_repo(inv, prd1.id) == 1);
	assert(inv->length == 1);
	assert(inv->products[0].id == prd2.id);

	assert(delete_product_repo(inv, prd2.id) == 1);
	assert(inv->length == 0);

	assert(delete_product_repo(inv, 4) == 0);
	destroy_dinamic_inventory(inv);
}

void test_repository_methods() {
	test_add_product();
	test_update_product_quantity_repo();
	test_update_product_price_repo();
	test_delete_product();

	test_resize();
	test_create_inventory();
	test_create_product();
}