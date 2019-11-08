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
	assert(tete != NULL);
	tete->memory = malloc(nb_blocs(nboctets) * sizeof(align_data));
	assert(tete->memory != NULL);
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
	return (void*)liste == (void*)current ? ld_first(liste) : current->next;
}

node* ld_previous(head* liste, node* current)
{
	return (void*)liste == (void*)current ? NULL : current->previous;
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
	if (tranche==NULL || tranche->suivant == NULL)
		return NULL;
	if (tranche->suivant->nb_blocs < len)
		return recherche_libre(tranche->suivant->suivant, len);

	if (tranche->suivant->nb_blocs > len)
	{
		(tranche->suivant + len)->suivant = tranche->suivant->suivant;
		(tranche->suivant + len)->nb_blocs = tranche->suivant->nb_blocs - len;
		tranche->suivant = tranche->suivant + len;
	}
	return tranche;
}

node* ld_create_node(head* liste, size_t len, align_data* p_data)
{
	node* noeud = (node*)recherche_libre(liste->libre, len + sizeof(node));
	assert(noeud != NULL);
	for (int i = 0; i < len; i++)
	{
		noeud->data[i] = *(p_data+i);

	}
	noeud->len = len;
	noeud->next = NULL;
	noeud->previous = NULL;
	return noeud;
}

node* ld_insert_first(head* liste, size_t len, align_data* p_data)
{
	node* noeud = ld_create_node(liste, len, p_data);
	noeud->next = liste->first;
	liste->first = noeud;
	return noeud;
}

node* ld_insert_last(head* liste, size_t len, align_data* p_data)
{
	node* noeud = ld_create_node(liste, len, p_data);
	noeud->previous = liste->last;
	liste->last = noeud;
	return noeud;
}

node* ld_insert_before(head* liste, node* n, size_t len, align_data* p_data)
{
	node* noeud = ld_create_node(liste, len, p_data);
	noeud->previous = n->previous;
	noeud->next = n;
	n->previous->next = noeud;
	n->previous = noeud;
	return noeud;
}

node* ld_insert_after(head* liste, node* n, size_t len, align_data* p_data)
{
	node* noeud = ld_create_node(liste, len, p_data);
	noeud->previous = n;
	noeud->next = n->next;
	n->next->previous = noeud;
	n->next = noeud;
	return noeud;
}

node* ld_delete_node(head* liste, node* n)
{

}