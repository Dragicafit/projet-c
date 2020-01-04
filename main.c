#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "projet2019.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

void test();
int main() 
{
	test();
	return 0;
}
void test_size();
void test_nb_blocs();
void test_ld_create();
void test_ld_get();
void test_ld_total_free_memory();
void test_ld_compactify();

void test()
{
	test_size();
	test_nb_blocs();
	test_ld_create();
	test_ld_get();
	test_ld_total_free_memory();
	test_ld_compactify();
}

void test_size()
{
	printf("sizeof(node) = %ld, attendu : %ld\n", sizeof(node), 2 * sizeof(void*) + sizeof(size_t));
	printf("sizeof(align_data) = %ld, attendu : %ld\n", sizeof(align_data), max(max(sizeof(intmax_t), sizeof(void*)), sizeof(long)));
	printf("sizeof(entete_tranche) = %ld, attendu : %ld\n", sizeof(entete_tranche), sizeof(void*)+sizeof(size_t));
	printf("sizeof(head) = %ld, attendu : %ld\n", sizeof(head), 4 * sizeof(void*));
}

void test_nb_blocs()
{
	int64_t entree[] = {31,32,33};
	int64_t sortie[] = {4,4,5};
	for (int i = 0; i < sizeof(entree)/sizeof(int64_t); i++)
	{
		printf("nb_blocs(%ld) = %ld, attendu : %ld\n", entree[i], nb_blocs(entree[i]), sortie[i]);
	}
}

void test_ld_create() {
	int64_t entree[] = { 31,32,33 };
	for (int i = 0; i < sizeof(entree) / sizeof(int64_t); i++)
	{
		head* tete = ld_create(entree[i]);
		printf("ld_create(%ld)->memory = %p, attendu : %s\n", entree[i], tete->memory, "!null");
		printf("ld_create(%ld)->first = %p, attendu : %s\n", entree[i], tete->first, "null");
		printf("ld_create(%ld)->last = %p, attendu : %s\n", entree[i], tete->last, "null");
		printf("ld_create(%ld)->libre = %p, attendu : %p\n", entree[i], tete->libre, tete->memory);
		printf("ld_create(%ld)->libre->suivant = %p, attendu : %s\n", entree[i], tete->libre->suivant, "null");
		printf("ld_create(%ld)->libre->nb_blocs = %zi, attendu : %zi\n", entree[i], tete->libre->nb_blocs, nb_blocs(entree[i]));
		ld_destroy(tete);
	}
}

void test_ld_get() 
{
	align_data entree[][9] = { {{1},{2},{3},{4},{5},{6},{7},{8},{9}},{{1.},{2.},{3.},{4.},{5.},{6.},{7.},{8.},{9.}} };
	for (int i = 0; i < sizeof(entree) / (sizeof(align_data)*9); i++)
	{
		head* tete = ld_create(1000);
		ld_insert_first(tete, nb_blocs(sizeof(entree[i][0])), &entree[i][0]);
		ld_insert_last(tete, nb_blocs(sizeof(entree[i][1])), &entree[i][1]);
		ld_insert_first(tete, nb_blocs(sizeof(entree[i][2])), &entree[i][2]);
		ld_insert_first(tete, nb_blocs(sizeof(entree[i][3])), &entree[i][3]);
		ld_insert_last(tete, nb_blocs(sizeof(entree[i][4])), &entree[i][4]);
		ld_delete_node(tete, ld_insert_last(tete, nb_blocs(sizeof(entree[i][4])), &entree[i][4]));
		ld_insert_before(tete, tete->last, nb_blocs(sizeof(entree[i][5])), &entree[i][5]);
		ld_insert_before(tete, tete->first->next->next, nb_blocs(sizeof(entree[i][6])), &entree[i][6]);
		ld_insert_after(tete, tete->first, nb_blocs(sizeof(entree[i][7])), &entree[i][7]);
		ld_insert_after(tete, tete->first->next->next, nb_blocs(sizeof(entree[i][8])), &entree[i][8]);
		char string[100] = "";
		ld_toString_bis(tete, string);
		char s_entree[100] = "[ ";
		for (int j = 0; j < sizeof(entree[i]) / sizeof(align_data); j++)
		{
			char s2[10];
			sprintf(s2, "%ld, ", entree[i][j].doublec);
			strcat(s_entree, s2);
		}
		strcat(s_entree, "]");
		printf("ld_insert_*(%s) = %s, attendu : [ %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld ]\n", s_entree, string, entree[i][3].doublec, entree[i][7].doublec, entree[i][2].doublec, entree[i][8].doublec, entree[i][6].doublec, entree[i][0].doublec, entree[i][1].doublec, entree[i][5].doublec, entree[i][4].doublec);
		ld_destroy(tete);
	}
}

void test_ld_total_free_memory()
{
	head* tete = ld_create(100);
	align_data entree[3] = { {12}, {60}, {52} };
	ld_insert_first(tete, nb_blocs(sizeof(entree[0])), &entree[0]);
	ld_insert_first(tete, nb_blocs(sizeof(entree[1])), &entree[1]);
	ld_insert_first(tete, nb_blocs(sizeof(entree[2])), &entree[2]);
	printf("ld_total_free_memory(%ld), attendu : 88\n", ld_total_free_memory(tete));
}

void test_ld_compactify() 
{
	head* tete = ld_create(100);
	align_data entree[7] = { {12}, {60}, {52}, {75}, {3}, {24}, {145} };
	ld_insert_first(tete, nb_blocs(sizeof(entree[0])), &entree[0]);
	ld_insert_first(tete, nb_blocs(sizeof(entree[1])), &entree[1]);
	ld_insert_first(tete, nb_blocs(sizeof(entree[2])), &entree[2]);
	node* node = ld_insert_first(tete, nb_blocs(sizeof(entree[3])), &entree[3]);
	ld_insert_first(tete, nb_blocs(sizeof(entree[4])), &entree[4]);
	ld_insert_first(tete, nb_blocs(sizeof(entree[5])), &entree[5]);
	ld_insert_first(tete, nb_blocs(sizeof(entree[6])), &entree[6]);
	ld_delete_node(tete, node);
	char string[100] = "";
	ld_toString_bis(tete, string);
	printf("ld_total_useful_memory(%ld)\n", ld_total_useful_memory(tete));
	printf("memory : %s\n", string);
	ld_compactify(tete);
	char string1[100] = "";
	ld_toString_bis(tete, string1);
	printf("ld_total_useful_memory(%ld)\n", ld_total_useful_memory(tete));
	printf("memory : %s\n", string1);
}