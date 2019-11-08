#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "projet2019.h"

void test();
int main() 
{
	test();
	return 0;
}
void test_size();
void test_nb_blocs();
void test_ld_create();

void test()
{
	test_size();
	test_nb_blocs();
	test_ld_create();
}

void test_size()
{
	printf("sizeof(node) = %ld\n", sizeof(node));
	printf("sizeof(align_data) = %ld\n", sizeof(align_data));
	printf("sizeof(entete_tranche) = %ld\n", sizeof(entete_tranche));
	printf("sizeof(head) = %ld\n", sizeof(head));
}

void test_nb_blocs()
{
	int entree[] = {31,32,33};
	int sortie[] = {4,4,5};
	for (int i = 0; i < sizeof(entree)/sizeof(int); i++)
	{
		printf("nb_blocs(%d) = %d, attendu : %d\n", entree[i], nb_blocs(entree[i]), sortie[i]);
	}
}

void test_ld_create() {
	int entree[] = { 31,32,33 };
	for (int i = 0; i < sizeof(entree) / sizeof(int); i++)
	{
		head* tete = ld_create(entree[i]);
		printf("nb_blocs(%d) = %d, attendu : %d\n", entree[i], nb_blocs(entree[i]));
	}
}