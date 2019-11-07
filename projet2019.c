#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "projet2019.h"

size_t nb_blocs(size_t o)
{
	return (o - 1) / sizeof(align_data) + 1;
}