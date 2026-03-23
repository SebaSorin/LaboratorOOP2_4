#include "service.h"
#include <assert.h>
#include <string.h>



void test_add_product_serv() {
	DinamicProduct prd = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService serv = {inv};
	
	int err_cnt = 0;
	char error_list[7][30];
	add_product_serv(&serv, prd.id, prd.type, prd.manufacturer, prd.model, prd.price, prd.quantity, error_list, &err_cnt);
	assert(err_cnt == 0);
	assert(inv->length == 1);
	assert(inv->products[0].id == prd.id);

	int prev_q = prd.quantity;
	add_product_serv(&serv, prd.id, prd.type, prd.manufacturer, prd.model, prd.price, prd.quantity + 10, error_list, &err_cnt);
	assert(err_cnt == 0);
	assert(inv->length == 1);
	assert(inv->products[0].id == prd.id);
	assert(inv->products[0].quantity == prev_q + 10);


	add_product_serv(&serv, -2, "", "   2", "44 23", 0, -10, error_list, &err_cnt);
	assert(err_cnt == 6);
	assert(strcmp(error_list[0], "Id invalid!") == 0);
	assert(strcmp(error_list[1], "Tip invalid!") == 0);
	assert(strcmp(error_list[2], "Producator invalid!") == 0);
	assert(strcmp(error_list[3], "Model invalid!") == 0);
	assert(strcmp(error_list[4], "Pret invalid!") == 0);
	assert(strcmp(error_list[5], "Cantitate invalida!") == 0);
	assert(inv->length == 1);
	destroy_dinamic_inventory(inv);
}

void test_update_product_price_serv() {
	DinamicProduct prd = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService serv = { inv };

	add_product_repo(inv, prd);

	int err_cnt = 0;
	char err_lst[2][30];
	assert(update_product_price_serv(&serv, prd.id, prd.price + 1000, err_lst, &err_cnt) == 1);
	assert(err_cnt == 0);
	assert(inv->products[0].price == 3500);

	assert(update_product_price_serv(&serv, 0, -1000, err_lst, &err_cnt) == 0);
	assert(err_cnt == 2);
	assert(strcmp(err_lst[0], "Id invalid!") == 0);
	assert(strcmp(err_lst[1], "Pret invalid!") == 0);

	assert(update_product_price_serv(&serv, 2, prd.price + 1000, err_lst, &err_cnt) == 0);
	assert(err_cnt == 1);
	assert(strcmp(err_lst[0], "Id nonexistent!") == 0);
	destroy_dinamic_inventory(inv);
}

void test_update_product_quantity_serv() {
	DinamicProduct prd = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService serv = { inv };

	add_product_repo(inv, prd);

	int err_cnt = 0;
	char err_lst[2][30];
	assert(update_product_quantity_serv(&serv, prd.id, prd.quantity + 10, err_lst, &err_cnt) == 1);
	assert(err_cnt == 0);
	assert(inv->products[0].quantity == 12);

	assert(update_product_quantity_serv(&serv, 0, -1000, err_lst, &err_cnt) == 0);
	assert(err_cnt == 2);
	assert(strcmp(err_lst[0], "Id invalid!") == 0);
	assert(strcmp(err_lst[1], "Cantitate invalida!") == 0);

	assert(update_product_quantity_serv(&serv, 2, prd.quantity + 10, err_lst, &err_cnt) == 0);
	assert(err_cnt == 1);
	assert(strcmp(err_lst[0], "Id nonexistent!") == 0);
	destroy_dinamic_inventory(inv);
}

void test_delete_product_service() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService serv = { inv };

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);

	char err_msg[30];
	assert(delete_product_serv(&serv, 10, err_msg) == 0);
	assert(strcmp(err_msg, "Id nonexistent!") == 0);

	assert(delete_product_serv(&serv, -1, err_msg) == 0);
	assert(strcmp(err_msg, "Id invalid!") == 0);

	assert(delete_product_serv(&serv, prd1.id, err_msg) == 1);
	assert(inv->length == 1);
	assert(inv->products[0].id == prd2.id);
	destroy_dinamic_inventory(inv);
}

void test_swap_products() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService serv = { inv };

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);

	assert(swap_products(&serv, 3, 4) == 0);
	assert(swap_products(&serv, -1, 0) == 0);

	assert(swap_products(&serv, prd1.id, prd2.id) == 1);
	assert(serv.inv->products[0].id == 2);
	assert(strcmp(serv.inv->products[0].type, "display") == 0);
	assert(strcmp(serv.inv->products[0].manufacturer, "lenovo") == 0);
	assert(strcmp(serv.inv->products[0].model, "asdasd") == 0);
	assert(serv.inv->products[0].price == 1000);
	assert(serv.inv->products[0].quantity == 10);

	assert(serv.inv->products[1].id == 1);
	assert(strcmp(serv.inv->products[1].type, "laptop") == 0);
	assert(strcmp(serv.inv->products[1].manufacturer, "acer") == 0);
	assert(strcmp(serv.inv->products[1].model, "aspire") == 0);
	assert(serv.inv->products[1].price == 2500);
	assert(serv.inv->products[1].quantity == 2);
	destroy_dinamic_inventory(inv);
}

void test_sort_by_price() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicProduct prd3 = { 3, "asdasd", "dassa", "asdasdaw", 4000, 5 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService serv = { inv };

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);
	add_product_repo(inv, prd3);

	sort_by_price(&serv, 0);
	assert(serv.inv->products[0].id == prd2.id);
	assert(serv.inv->products[1].id == prd1.id);
	assert(serv.inv->products[2].id == prd3.id);

	sort_by_price(&serv, 1);
	assert(serv.inv->products[0].id == prd3.id);
	assert(serv.inv->products[1].id == prd1.id);
	assert(serv.inv->products[2].id == prd2.id);
	destroy_dinamic_inventory(inv);
}

void test_sort_by_quantity() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicProduct prd3 = { 3, "asdasd", "dassa", "asdasdaw", 4000, 5 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService serv = { inv };

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);
	add_product_repo(inv, prd3);

	sort_by_quantity(&serv, 0);
	assert(serv.inv->products[0].id == prd1.id);
	assert(serv.inv->products[1].id == prd3.id);
	assert(serv.inv->products[2].id == prd2.id);

	sort_by_quantity(&serv, 1);
	assert(serv.inv->products[0].id == prd2.id);
	assert(serv.inv->products[1].id == prd3.id);
	assert(serv.inv->products[2].id == prd1.id);
	destroy_dinamic_inventory(inv);
}

void test_compare_price_descending() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicProduct prd3 = { 3, "asdasd", "dassa", "asdasdaw", 4000, 5 };
	
	assert(compare_price_descending(prd1, prd2) == 0);
	assert(compare_price_descending(prd2, prd3) == 1);
	assert(compare_price_descending(prd3, prd1) == 0);

	assert(compare_price_descending(prd2, prd1) == 1);
	assert(compare_price_descending(prd3, prd2) == 0);
	assert(compare_price_descending(prd1, prd3) == 1);

	assert(compare_price_descending(prd1, prd1) == 0);
}

void test_compare_price_ascending() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicProduct prd3 = { 3, "asdasd", "dassa", "asdasdaw", 4000, 5 };

	assert(compare_price_ascending(prd1, prd2) == 1);
	assert(compare_price_ascending(prd2, prd3) == 0);
	assert(compare_price_ascending(prd3, prd1) == 1);
		   
	assert(compare_price_ascending(prd2, prd1) == 0);
	assert(compare_price_ascending(prd3, prd2) == 1);
	assert(compare_price_ascending(prd1, prd3) == 0);
		   
	assert(compare_price_ascending(prd1, prd1) == 0);
}

void test_compare_quantity_descending() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicProduct prd3 = { 3, "asdasd", "dassa", "asdasdaw", 4000, 5 };

	assert(compare_quantity_descending(prd1, prd2) == 1);
	assert(compare_quantity_descending(prd2, prd3) == 0);
	assert(compare_quantity_descending(prd3, prd1) == 0);
				   
	assert(compare_quantity_descending(prd2, prd1) == 0);
	assert(compare_quantity_descending(prd3, prd2) == 1);
	assert(compare_quantity_descending(prd1, prd3) == 1);
				   
	assert(compare_quantity_descending(prd1, prd1) == 0);
}

void test_compare_quantity_ascending() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicProduct prd3 = { 3, "asdasd", "dassa", "asdasdaw", 4000, 5 };

	assert(compare_quantity_ascending(prd1, prd2) == 0);
	assert(compare_quantity_ascending(prd2, prd3) == 1);
	assert(compare_quantity_ascending(prd3, prd1) == 1);
							
	assert(compare_quantity_ascending(prd2, prd1) == 1);
	assert(compare_quantity_ascending(prd3, prd2) == 0);
	assert(compare_quantity_ascending(prd1, prd3) == 0);
							
	assert(compare_quantity_ascending(prd1, prd1) == 0);
}

void test_sort_by_price_generalised() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicProduct prd3 = { 3, "asdasd", "dassa", "asdasdaw", 4000, 5 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService serv = { inv };

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);
	add_product_repo(inv, prd3);

	sort_by_price_generalised(&serv, 0);
	assert(serv.inv->products[0].id == prd2.id);
	assert(serv.inv->products[1].id == prd1.id);
	assert(serv.inv->products[2].id == prd3.id);

	sort_by_price_generalised(&serv, 1);
	assert(serv.inv->products[0].id == prd3.id);
	assert(serv.inv->products[1].id == prd1.id);
	assert(serv.inv->products[2].id == prd2.id);
	destroy_dinamic_inventory(inv);
}

void test_sort_by_quantity_generalised() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicProduct prd3 = { 3, "asdasd", "dassa", "asdasdaw", 4000, 5 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService serv = { inv };

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);
	add_product_repo(inv, prd3);

	sort_by_quantity_generalised(&serv, 0);
	assert(serv.inv->products[0].id == prd1.id);
	assert(serv.inv->products[1].id == prd3.id);
	assert(serv.inv->products[2].id == prd2.id);

	sort_by_quantity_generalised(&serv, 1);
	assert(serv.inv->products[0].id == prd2.id);
	assert(serv.inv->products[1].id == prd3.id);
	assert(serv.inv->products[2].id == prd1.id);
	destroy_dinamic_inventory(inv);
}

void test_filter_by_manufacturer() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	DinamicProduct prd3 = { 3, "asdasd", "acer", "asdasdaw", 4000, 5 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService srv = { inv };

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);
	add_product_repo(inv, prd3);

	char err_msg[30];
	DinamicInventory* print_inv = filter_by_manufacturer_serv(&srv, "dasdas", err_msg);
	assert(print_inv->length == 0);
	assert(strcmp(err_msg, "Producator nonexistent!") == 0);
	destroy_dinamic_inventory(print_inv);

	print_inv = filter_by_manufacturer_serv(&srv, "", err_msg);
	assert(print_inv->length == 0);
	assert(strcmp(err_msg, "Producator invalid!") == 0);
	destroy_dinamic_inventory(print_inv);

	print_inv = filter_by_manufacturer_serv(&srv, "acer", err_msg);
	assert(print_inv->length == 2);
	assert(print_inv->products[0].id == prd1.id);
	assert(print_inv->products[1].id == prd3.id);
	destroy_dinamic_inventory(print_inv);

	print_inv = filter_by_manufacturer_serv(&srv, "lenovo", err_msg);
	assert(print_inv->length == 1);
	assert(print_inv->products[0].id == prd2.id);
	destroy_dinamic_inventory(inv);
	destroy_dinamic_inventory(print_inv);
}

void test_filter_by_price() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 4000, 10 };
	DinamicProduct prd3 = { 3, "asdasd", "acer", "asdasdaw", 4000, 5 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService srv = { inv };

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);
	add_product_repo(inv, prd3);

	char err_msg[30];
	DinamicInventory* print_inv = filter_by_price_serv(&srv, 1000, err_msg);
	assert(print_inv->length == 0);
	assert(strcmp(err_msg, "Pret nonexistent!") == 0);
	destroy_dinamic_inventory(print_inv);

	print_inv = filter_by_price_serv(&srv, -1000, err_msg);
	assert(print_inv->length == 0);
	assert(strcmp(err_msg, "Pret invalid!") == 0);
	destroy_dinamic_inventory(print_inv);

	print_inv = filter_by_price_serv(&srv, 4000, err_msg);
	assert(print_inv->length == 2);
	assert(print_inv->products[0].id == prd2.id);
	assert(print_inv->products[1].id == prd3.id);
	destroy_dinamic_inventory(print_inv);

	print_inv = filter_by_price_serv(&srv, 2500, err_msg);
	assert(print_inv->length == 1);
	assert(print_inv->products[0].id == prd1.id);
	destroy_dinamic_inventory(inv);
	destroy_dinamic_inventory(print_inv);
}

void test_filter_by_quantity() {
	DinamicProduct prd1 = { 1, "laptop", "acer", "aspire", 2500, 10 };
	DinamicProduct prd2 = { 2, "display", "lenovo", "asdasd", 4000, 10 };
	DinamicProduct prd3 = { 3, "asdasd", "acer", "asdasdaw", 4000, 5 };
	DinamicInventory* inv = create_dinamic_inventory();
	DinamicService srv = { inv };

	add_product_repo(inv, prd1);
	add_product_repo(inv, prd2);
	add_product_repo(inv, prd3);

	char err_msg[30];
	DinamicInventory* print_inv = filter_by_quantity_serv(&srv, 100, err_msg);
	assert(print_inv->length == 0);
	assert(strcmp(err_msg, "Cantitate nonexistenta!") == 0);
	destroy_dinamic_inventory(print_inv);

	print_inv = filter_by_quantity_serv(&srv, -10, err_msg);
	assert(print_inv->length == 0);
	assert(strcmp(err_msg, "Cantitate invalida!") == 0);
	destroy_dinamic_inventory(print_inv);

	print_inv = filter_by_quantity_serv(&srv, 10, err_msg);
	assert(print_inv->length == 2);
	assert(print_inv->products[0].id == prd1.id);
	assert(print_inv->products[1].id == prd2.id);
	destroy_dinamic_inventory(print_inv);

	print_inv = filter_by_quantity_serv(&srv, 5, err_msg);
	assert(print_inv->length == 1);
	assert(print_inv->products[0].id == prd3.id);
	destroy_dinamic_inventory(inv);
	destroy_dinamic_inventory(print_inv);
}

void test_service_methods() {
	test_add_product_serv();
	test_update_product_price_serv();
	test_update_product_quantity_serv();
	test_delete_product_service();
	test_swap_products();
	test_sort_by_price();
	test_sort_by_quantity();
	test_filter_by_manufacturer();
	test_filter_by_price();
	test_filter_by_quantity();

	test_compare_price_descending();
	test_compare_price_ascending();
	test_compare_quantity_descending();
	test_compare_quantity_ascending();
	test_sort_by_price_generalised();
	test_sort_by_quantity_generalised();
}
