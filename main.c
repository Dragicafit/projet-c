#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "projet2019.h"

int main() 
{
	head* tete = ld_create(32);
	printf("%d\n", tete->memory);
	printf("%d\n", tete->first);
	printf("%d\n", tete->last);
	printf("%d\n", tete->libre->nb_blocs);
	printf("%d\n", tete->libre->suivant);
	return 0;
}