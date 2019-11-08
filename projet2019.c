#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "projet2019.h"

size_t nb_blocs(size_t o)
{
	return (o - 1) / sizeof(align_data) + 1;
}


void* ld_create(size_t nboctets)
{
	head* tete = malloc(sizeof(head));
	tete->memory = malloc(nb_blocs(nboctets) * sizeof(align_data));
	tete->first = 0;
	tete->last = 0;
	tete->libre = tete->memory;
	(tete->libre)->suivant = 0;
	(tete->libre)->nb_blocs = nb_blocs(nboctets)-1;
	return tete;
}


void* ld_first(void* liste)
{
	ptrdiff_t first = ((head*) liste)->first;
	return first != 0 ? first : NULL;
}


void* ld_last(void* liste)
{
	ptrdiff_t last = ((head*) liste)->last;
	return last != 0 ? last : NULL;
}

void* ld_next(void* liste, void* current)
{
	if (liste == current)
	{
		return ld_first(liste);
	}
	else
	{
		ptrdiff_t next = ((node*) current)->next;
		return next != 0 ? next : NULL;
	}
}

void* ld_previous(void* liste, void* current)
{
	return liste == current ? NULL : ((node*)current)->previous;
}

void suppression(entete_tranche* libre)
{

}

void ld_destroy(void* liste)
{
	head* tete = (head*)liste;
	free(tete->memory);
	free(tete);
}

size_t ld_get(void* liste, void* current, size_t len, void* val)
{
	node* noeud = (node*)current;
	size_t nboctets = noeud->len < len ? noeud->len : len;
	for (int i = 0; i < nboctets; i++)
	{
		((align_data*) val)[i] = noeud->data[i];
	}
	return nboctets;
}

void* ld_create_node(void* liste, size_t len, void* p_data)
{
	node* noeud = 
}

void* ld_insert_first(void* liste, size_t len, void* p_data)
{
	
}