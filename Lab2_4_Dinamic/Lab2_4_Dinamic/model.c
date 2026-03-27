#include "model.h"
#include <string.h>
#include <stdlib.h>



DinamicProduct create_product(int id, char* type, char* manufacturer, char* model, int price, int quantity) {
	DinamicProduct prd;
	prd.id = id;

	prd.type = malloc(MAX_TYPE_LEN * sizeof(char));
	strcpy_s(prd.type, MAX_TYPE_LEN * sizeof(char), type);

	prd.manufacturer = malloc(MAX_MANUFAC_LEN * sizeof(char));
	strcpy_s(prd.manufacturer, MAX_MANUFAC_LEN * sizeof(char), manufacturer);

	prd.model = malloc(MAX_MODEL_LEN * sizeof(char));
	strcpy_s(prd.model, MAX_MODEL_LEN * sizeof(char), model);

	prd.price = price;
	prd.quantity = quantity;
	return prd;
}

void destroy_product(DinamicProduct* prd) {
	free(prd->manufacturer);
	free(prd->model);
	free(prd->type);
}

DinamicProduct copy_product(DinamicProduct* prd) {
	DinamicProduct new_prd = create_product(prd->id, prd->type, prd->manufacturer, prd->model, prd->price, prd->quantity);
	return new_prd;
}