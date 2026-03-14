#include "repository.h"
#include <assert.h>


void test_add_product() {
	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	Product prd3 = { 3, "laptop", "apple", "mac", 5000, 4 };

	Inventory inv = { {prd1, prd2}, 2 };

	add_product_repo(&inv, prd3);
	assert(inv.length == 3);
	assert(inv.list[inv.length - 1].id == prd3.id);
}

void test_update_product_quantity_repo() {
	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	Inventory inv = { {prd1, prd2}, 2 };

	assert(update_product_quantity_repo(&inv, 1, 5) == 1);
	assert(inv.list[0].quantity == 5);

	assert(update_product_quantity_repo(&inv, 3, 100) == 0);
}

void test_update_product_price_repo() {
	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	Inventory inv = { {prd1, prd2}, 2 };

	assert(update_product_price_repo(&inv, 2, 500) == 1);
	assert(inv.list[1].price == 500);

	assert(update_product_price_repo(&inv, 3, 1000) == 0);
}

void test_delete_product() {
	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	Inventory inv = { {prd1, prd2}, 2 };

	assert(delete_product_repo(&inv, prd1.id) == 1);
	assert(inv.length == 1);
	assert(inv.list[0].id == prd2.id);

	assert(delete_product_repo(&inv, prd2.id) == 1);
	assert(inv.length == 0);

	assert(delete_product_repo(&inv, 4) == 0);
}

void test_repository_methods() {
	test_add_product();
	test_update_product_quantity_repo();
	test_update_product_price_repo();
	test_delete_product();
}