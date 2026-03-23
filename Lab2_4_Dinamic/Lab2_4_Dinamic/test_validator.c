#include "validator.h"
#include "repository.h"
#include <assert.h>


void test_validate_id() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicProduct prd3 = { 3, "laptop", "apple", "mac", 5000, 4 };
	
	DinamicInventory* inv = create_dinamic_inventory();

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);
	add_product_repo(inv, prd3);

	assert(validate_id(inv->products[0].id) == 1);
	assert(validate_id(inv->products[1].id) == 1);
	assert(validate_id(inv->products[2].id) == 1);
	assert(validate_id(4) == 1);
	assert(validate_id(2) == 1);
	assert(validate_id(0) == 0);
	assert(validate_id(-4) == 0);
	destroy_dinamic_inventory(inv);
}

void test_validate_type() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	int max_len = 30;

	assert(validate_type(prd1.type, max_len) == 1);
	assert(validate_type(prd2.type, max_len) == 1);
	assert(validate_type("a display", max_len) == 1);
	assert(validate_type("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa", max_len) == 1); // 29 characters

	assert(validate_type("", max_len) == 0);
	assert(validate_type("         ", max_len) == 0);
	assert(validate_type("1234567", max_len) == 0);
	assert(validate_type("4k display", max_len) == 0);
	assert(validate_type("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", max_len) == 0); // 30 characters
	assert(validate_type(" laptop", max_len) == 0);
}

void test_validate_manufacturer() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };

	assert(validate_manufacturer(prd1.manufacturer) == 1);
	assert(validate_manufacturer(prd2.manufacturer) == 1);
	assert(validate_manufacturer("generic builds") == 1);
	assert(validate_manufacturer("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 1); // 49 characters

	assert(validate_manufacturer("") == 0);
	assert(validate_manufacturer("         ") == 0);
	assert(validate_manufacturer("1234567") == 0);
	assert(validate_manufacturer("4k builds") == 0);
	assert(validate_manufacturer("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 0); // 50 characters
	assert(validate_manufacturer(" asus") == 0);
}

void test_validate_model() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };

	assert(validate_model(prd1.model) == 1);
	assert(validate_model(prd2.model) == 1);
	assert(validate_model("mk one") == 1);
	assert(validate_model("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 1); // 29 characters
	assert(validate_model("4k series") == 1);

	assert(validate_model("") == 0);
	assert(validate_model("         ") == 0);
	assert(validate_model("1234567") == 0);
	assert(validate_model("1 2  345 67") == 0);
	assert(validate_model("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 0); // 30 characters
	assert(validate_model(" aspire") == 0);
}

void test_validate_price() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };

	assert(validate_price(prd1.price) == 1);
	assert(validate_price(prd2.price) == 1);

	assert(validate_price(0) == 0);
	assert(validate_price(-1000) == 0);
}

void test_validate_quantity() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };

	assert(validate_quantity(prd1.quantity) == 1);
	assert(validate_quantity(prd2.quantity) == 1);
	assert(validate_quantity(0) == 1);

	assert(validate_quantity(-1000) == 0);
}

 

void test_validator_methods() {
	test_validate_id();
	test_validate_type();
	test_validate_manufacturer();
	test_validate_model();
	test_validate_price();
	test_validate_quantity();
}