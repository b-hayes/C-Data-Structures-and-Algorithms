#pragma once
#include "list.h"

typedef struct taxRecord {
	long tfn;
	char *name;
	List welfare;
	List tax;
} *TaxRecordPtr;