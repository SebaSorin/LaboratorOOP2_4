//#include "repository.h"
//#include "validator.h"
//#include "service.h"
//#include <assert.h>
//
//void test_add_product() {
//	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
//	Product prd3 = { 3, "laptop", "apple", "mac", 5000, 4 };
//	
//	Inventory inv = { {prd1, prd2}, 2 };
//
//	add_product_repo(&inv, prd3);
//	assert(inv.length == 3);
//	assert(inv.list[inv.length - 1].id == prd3.id);
//}
//
//void test_update_product_quantity_repo() {
//	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
//	Inventory inv = { {prd1, prd2}, 2 };
//
//	assert(update_product_quantity_repo(&inv, 1, 5) == 1);
//	assert(inv.list[0].quantity == 5);
//
//	assert(update_product_quantity_repo(&inv, 3, 100) == 0);
//}
//
//void test_update_product_price_repo() {
//	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
//	Inventory inv = { {prd1, prd2}, 2 };
//
//	assert(update_product_price_repo(&inv, 2, 500) == 1);
//	assert(inv.list[1].price == 500);
//
//	assert(update_product_price_repo(&inv, 3, 1000) == 0);
//}
//
//// -------------------------- VALIDATOR TESTS --------------------------
//
//void test_validate_id() {
//	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
//	Product prd3 = { 3, "laptop", "apple", "mac", 5000, 4 };
//
//	Inventory inv = { {prd1, prd2, prd3}, 3 };
//
//	assert(validate_id(&inv, 4) == 1);
//	assert(validate_id(&inv, 2) == 1);
//	assert(validate_id(&inv, 0) == 0);
//	assert(validate_id(&inv, -4) == 0);
//}
//
//void test_validate_type() {
//	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
//	int max_len = 30;
//
//	assert(validate_type(prd1.type, max_len) == 1);
//	assert(validate_type(prd2.type, max_len) == 1);
//	assert(validate_type("a display", max_len) == 1);
//	assert(validate_type("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa", max_len) == 1); // 29 characters
//
//	assert(validate_type("", max_len) == 0);
//	assert(validate_type("         ", max_len) == 0);
//	assert(validate_type("1234567", max_len) == 0);
//	assert(validate_type("4k display", max_len) == 0);
//	assert(validate_type("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", max_len) == 0); // 30 characters
//	assert(validate_type(" laptop", max_len) == 0);
//}
//
//void test_validate_manufacturer() {
//	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
//
//	assert(validate_manufacturer(prd1.manufacturer) == 1);
//	assert(validate_manufacturer(prd2.manufacturer) == 1);
//	assert(validate_manufacturer("generic builds") == 1);
//	assert(validate_manufacturer("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 1); // 49 characters
//
//	assert(validate_manufacturer("") == 0);
//	assert(validate_manufacturer("         ") == 0);
//	assert(validate_manufacturer("1234567") == 0);
//	assert(validate_manufacturer("4k builds") == 0);
//	assert(validate_manufacturer("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 0); // 50 characters
//	assert(validate_manufacturer(" asus") == 0);
//}
//
//void test_validate_model() {
//	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
//
//	assert(validate_model(prd1.model) == 1);
//	assert(validate_model(prd2.model) == 1);
//	assert(validate_model("mk one") == 1);
//	assert(validate_model("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 1); // 29 characters
//	assert(validate_model("4k series") == 1);
//					
//	assert(validate_model("") == 0);
//	assert(validate_model("         ") == 0);
//	assert(validate_model("1234567") == 0);
//	assert(validate_model("1 2  345 67") == 0);
//	assert(validate_model("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 0); // 30 characters
//	assert(validate_model(" aspire") == 0);
//}
//
//void test_validate_price() {
//	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
//
//	assert(validate_price(prd1.price) == 1);
//	assert(validate_price(prd2.price) == 1);
//
//	assert(validate_price(0) == 0);
//	assert(validate_price(-1000) == 0);
//}
//
//void test_validate_quantity() {
//	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
//
//	assert(validate_quantity(prd1.quantity) == 1);
//	assert(validate_quantity(prd2.quantity) == 1);
//	assert(validate_quantity(0) == 1);
//	
//	assert(validate_quantity(-1000) == 0);
//}
//
//// -------------------------- SERVICE TESTS --------------------------
//
//void test_add_product_serv() {
//	Product prd = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Inventory inv;
//	inv.length = 0;
//
//	int err_cnt = 0;
//	char error_list[7][30];
//	add_product_serv(&inv, prd.id, prd.type, prd.manufacturer, prd.model, prd.price, prd.quantity, error_list, &err_cnt);
//	assert(err_cnt == 0);
//	assert(inv.length == 1);
//	assert(inv.list[0].id == prd.id);
//
//	int prev_q = prd.quantity;
//	add_product_serv(&inv, prd.id, prd.type, prd.manufacturer, prd.model, prd.price, prd.quantity + 10, error_list, &err_cnt);
//	assert(err_cnt == 0);
//	assert(inv.length == 1);
//	assert(inv.list[0].id == prd.id);
//	assert(inv.list[0].quantity == prev_q + 10);
//
//
//	add_product_serv(&inv, -2, "", "   2", "44 23", 0, -10, error_list, &err_cnt);
//	assert(err_cnt == 6);
//	assert(strcmp(error_list[0], "Id invalid!") == 0);
//	assert(strcmp(error_list[1], "Tip invalid!") == 0);
//	assert(strcmp(error_list[2], "Producator invalid!") == 0);
//	assert(strcmp(error_list[3], "Model invalid!") == 0);
//	assert(strcmp(error_list[4], "Pret invalid!") == 0);
//	assert(strcmp(error_list[5], "Cantitate invalida!") == 0);
//	assert(inv.length == 1);
//}
//
//void test_update_product_price_serv() {
//	Product prd = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Inventory inv = { {prd}, 1 };
//
//	int err_cnt = 0;
//	char err_lst[2][30];
//	assert(update_product_price_serv(&inv, prd.id, prd.price + 1000, err_lst, &err_cnt) == 1);
//	assert(err_cnt == 0);
//	assert(inv.list[0].price == 3500);
//
//	assert(update_product_price_serv(&inv, 0, -1000, err_lst, &err_cnt) == 0);
//	assert(err_cnt == 2);
//	assert(strcmp(err_lst[0], "Id invalid!") == 0);
//	assert(strcmp(err_lst[1], "Pret invalid!") == 0);
//
//	assert(update_product_price_serv(&inv, 2, prd.price + 1000, err_lst, &err_cnt) == 0);
//	assert(err_cnt == 1);
//	assert(strcmp(err_lst[0], "Id nonexistent!") == 0);
//}
//
//void test_update_product_quantity_serv() {
//	Product prd = { 1, "laptop", "acer", "aspire", 2500, 2 };
//	Inventory inv = { {prd}, 1 };
//
//	int err_cnt = 0;
//	char err_lst[2][30];
//	assert(update_product_quantity_serv(&inv, prd.id, prd.quantity + 10, err_lst, &err_cnt) == 1);
//	assert(err_cnt == 0);
//	assert(inv.list[0].quantity == 12);
//
//	assert(update_product_quantity_serv(&inv, 0, -1000, err_lst, &err_cnt) == 0);
//	assert(err_cnt == 2);
//	assert(strcmp(err_lst[0], "Id invalid!") == 0);
//	assert(strcmp(err_lst[1], "Cantitate invalida!") == 0);
//
//	assert(update_product_quantity_serv(&inv, 2, prd.quantity + 10, err_lst, &err_cnt) == 0);
//	assert(err_cnt == 1);
//	assert(strcmp(err_lst[0], "Id nonexistent!") == 0);
//}
//
//
//
//
//int main() {
//	// RUN TESTS
//	test_add_product();
//	test_update_product_quantity_repo();
//	test_update_product_price_repo();
//
//	test_validate_id();
//	test_validate_type();
//	test_validate_manufacturer();
//	test_validate_model();
//	test_validate_price();
//	test_validate_quantity();
//
//	test_add_product_serv();
//	test_update_product_price_serv();
//	test_update_product_quantity_serv();
//
//	return 0;
//}