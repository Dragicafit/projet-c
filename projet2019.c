#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#include "projet2019.h"

size_t nb_blocs(size_t o)
{
	return (o - 1) / sizeof(align_data) + 1;
}


head* ld_create(size_t nboctets)
{
	head* tete = malloc(sizeof(head));
	assert(tete == NULL);
	tete->memory = malloc(nb_blocs(nboctets) * sizeof(align_data));
	assert(tete->memory == NULL);
	tete->first = NULL;
	tete->last = NULL;
	tete->libre = tete->memory;
	(tete->libre)->suivant = NULL;
	(tete->libre)->nb_blocs = nb_blocs(nboctets)-1;
	return tete;
}


node* ld_first(head* liste)
{
	return liste->first;
}


node* ld_last(head* liste)
{
	return liste->last;
}

node* ld_next(head* liste, node* current)
{
	return liste == current ? ld_first(liste) : current->next;
}

node* ld_previous(head* liste, node* current)
{
	return liste == current ? NULL : current->previous;
}

void ld_destroy(head* liste)
{
	free(liste->memory);
	free(liste);
}

size_t ld_get(head* liste, node* current, size_t len, align_data* val)
{
	size_t nboctets = current->len < len ? current->len : len;
	for (int i = 0; i < nboctets; i++)
	{
		val[i] = current->data[i];
	}
	return nboctets;
}

entete_tranche* recherche_libre(entete_tranche* tranche, size_t len)
{
	if (tranche == NULL)
		return NULL;
	if (tranche->nb_blocs < len)
		return recherche_libre(tranche->suivant, len);
	return tranche;
}

void* ld_create_node(head* liste, size_t len, void* p_data)
{

	node* noeud = 
}

void* ld_insert_first(head* liste, size_t len, void* p_data)
{
	
}