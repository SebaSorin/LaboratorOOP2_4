#include "validator.h"
#include <assert.h>

void test_validate_id() {
	Product prd1 = { 1, "laptop", "acer", "aspire", 2500, 2 };
	Product prd2 = { 2, "display", "lenovo", "asdasd", 1000, 10 };
	Product prd3 = { 3, "laptop", "apple", "mac", 5000, 4 };

	Inventory inv = { {prd1, prd2, prd3}, 3 };

	assert(validate_id(&inv, 4) == 1);
	assert(validate_id(&inv, 2) == 0);
	assert(validate_id(&inv, 0) == 0);
	assert(validate_id(&inv, -4) == 0);
}



int main() {
	test_validate_id();

	return 0;
}