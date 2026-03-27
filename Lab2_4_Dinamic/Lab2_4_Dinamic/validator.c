#include "model.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int validate_id(int product_id) {
	return product_id > 0;
}

int validate_type(char* product_type, int max_len) {
	// is not null
	// has less than 30 characters
	// only has spaces and letters

	size_t len = strlen(product_type);
	if (len == 0 || len >= max_len)
		return 0;
	if (product_type[0] == ' ')
		return 0;	// does not start with a space

	int space_cnt = 0;
	for (int i = 0; i < len; i++) {
		if (!isalpha(product_type[i])) {
			if (product_type[i] == ' ') {
				space_cnt++;
				continue;
			}
			return 0;
		}
	}

	return space_cnt != len; // is not made up of only spaces
}

int validate_manufacturer(char* product_man) {
	// same as type but with max size 50
	return validate_type(product_man, 50);
}

int validate_model(char* product_model) {
	// is not null
	// has less than 30 characters
	// can have spaces, letters and numbers

	size_t len = strlen(product_model);
	if (len == 0 || len >= 30)
		return 0;
	if (product_model[0] == ' ')
		return 0;	// does not start with a space

	int space_cnt = 0, digit_cnt = 0;
	for (int i = 0; i < len; i++) {
		if (product_model[i] == ' ')
			space_cnt++;
		else if (isdigit(product_model[i]))
			digit_cnt++;
	}

	return space_cnt != len && digit_cnt != len && space_cnt + digit_cnt != len; // is not made up of only spaces and numbers
}

int validate_price(int product_price) {
	// is positive 
	return product_price > 0;
}

int validate_quantity(int product_quantity) {
	// is positive 
	return product_quantity >= 0;
}