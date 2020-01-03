#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "projet2019.h"

size_t nb_blocs(size_t o)
{
	return o==0?0:(o - 1) / sizeof(align_data) + 1;
}

void ld_toString_bis(head* list, char* string)
{
	if (string == NULL)
		return;
	string[0] = '\0';
	if (list == NULL)
		return;

	strcat(string, "[ ");
	ld_toString(list->first, string);
	strcat(string, " ]");
}

void ld_toString(node* noeud, char* string)
{
	if (noeud == NULL)
		return;

	align_data data[] = { 0 };
	ld_get(noeud, 1, data);

	char s2[10];
	sprintf(s2, "%ld", data->doublec);
	strcat(string, s2);
	if (noeud->next == NULL)
		return;
	strcat(string, ", ");
	ld_toString(noeud->next, string);
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
	tete->libre->suivant = NULL;
	tete->libre->nb_blocs = nb_blocs(nboctets);
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

size_t ld_get(node* current, size_t len, align_data* val)
{
	if (val == NULL)
		return 0;
	val->doublec = 0;
	if (current == NULL)
		return 0;
	size_t nbBlocs = current->len - nb_blocs(sizeof(node)) < len ? current->len : len;
	for (int i = 0; i < nbBlocs; i++)
	{
		val[i] = current->data[i];
	}
	return nbBlocs;
}

node* recherche_libre_bis(head* liste, size_t len)
{
	if (liste == NULL || liste->libre == NULL)
		return NULL;
	printf("\nddfdf\n");
	if (liste->libre->nb_blocs <= len + nb_blocs(sizeof(entete_tranche))) {
		printf("\nddfdf\n");
		return recherche_libre(liste->libre, len);
	}

	node* noeud = (node*)liste->libre;

	if (liste->libre->nb_blocs == len) 
	{
		liste->libre = liste->libre->suivant;
		return noeud;
	}
	liste->libre = liste->libre + len * sizeof(align_data);
	liste->libre->suivant = ((entete_tranche*) noeud)->suivant;
	liste->libre->nb_blocs = ((entete_tranche*)noeud)->nb_blocs - len;
	return noeud;
}

node* recherche_libre(entete_tranche* tranche, size_t len)
{
	printf("\nddfdf\n");
	if (tranche == NULL || tranche->suivant == NULL)
		return NULL;

	if (tranche->suivant->nb_blocs <= len + nb_blocs(sizeof(entete_tranche)))
		return recherche_libre(tranche->suivant, len);

	node* noeud = (node*)tranche->suivant;

	if (tranche->suivant->nb_blocs == len)
	{
		tranche->suivant = tranche->suivant->suivant;
		return noeud;
	}

	tranche->suivant = tranche->suivant + len * sizeof(align_data);
	tranche->suivant = ((entete_tranche*)noeud)->suivant;
	tranche->nb_blocs = ((entete_tranche*)noeud)->nb_blocs - len;
	return noeud;
}

node* ld_create_node(head* liste, size_t len, align_data* p_data)
{
	node* noeud = (node*)recherche_libre_bis(liste, len + nb_blocs(sizeof(node)));
	if (noeud == NULL)
		return NULL;
	for (int i = 0; i < len; i++)
	{
		noeud->data[i] = p_data[i];

	}
	noeud->len = len + nb_blocs(sizeof(node));
	noeud->next = NULL;
	noeud->previous = NULL;
	return noeud;
}

node* ld_insert_first(head* liste, size_t len, align_data* p_data)
{
	node* noeud = ld_create_node(liste, len, p_data);
	if (noeud == NULL)
		return NULL;

	noeud->next = liste->first;
	if (liste->first != NULL)
		liste->first->previous = noeud;
	else
		liste->last = noeud;
	liste->first = noeud;
	return noeud;
}

node* ld_insert_last(head* liste, size_t len, align_data* p_data)
{
	node* noeud = ld_create_node(liste, len, p_data);
	if (noeud == NULL)
		return NULL;

	noeud->previous = liste->last;
	if (liste->last != NULL)
		liste->last->next = noeud;
	else
		liste->last = noeud;
	liste->last = noeud;
	return noeud;
}

node* ld_insert_before(head* liste, node* n, size_t len, align_data* p_data)
{
	node* noeud = ld_create_node(liste, len, p_data);
	if (noeud == NULL)
		return NULL;
	noeud->previous = n->previous;
	noeud->next = n;
	if (n->previous == NULL)
		liste->first = noeud;
	else
		n->previous->next = noeud;
	n->previous = noeud;
	return noeud;
}

node* ld_insert_after(head* liste, node* n, size_t len, align_data* p_data)
{
	node* noeud = ld_create_node(liste, len, p_data);
	if (noeud == NULL)
		return NULL;
	noeud->next = n->next;
	noeud->previous = n;
	if (n->next == NULL)
		liste->last = noeud;
	else
		n->next->previous = noeud;
	n->next = noeud;
	return noeud;
}

node* recherche_dernier(entete_tranche* tranche, node* noeud)
{
	if (tranche == NULL)
		return NULL;
	if (tranche->suivant == NULL)
	{
		tranche->suivant = (entete_tranche*)noeud;
		tranche->suivant->suivant = NULL;
		tranche->suivant->nb_blocs = noeud->len - sizeof(node) + sizeof(entete_tranche);
		return noeud;
	}
	return recherche_dernier(tranche->suivant, noeud);
}

node* recherche_dernier_bis(head* liste, node* noeud)
{
	if (liste == NULL)
		return NULL;
	if (liste->libre == NULL)
	{
		liste->libre = (entete_tranche*) noeud;
		liste->libre->suivant = NULL;
		liste->libre->nb_blocs = noeud->len - sizeof(node) + sizeof(entete_tranche);
		return noeud;
	}
	return recherche_dernier(liste->libre, noeud);
}

head* ld_delete_node(head* liste, node* n)
{
	node* previous = n->previous;
	node* next = n->next;
	if (recherche_dernier_bis(liste, n) == NULL)
		return NULL;
	if (next != NULL)
		next->previous = previous;
	else
		liste->last = previous;
	if (previous != NULL)
		previous->next = next;
	else
		liste->first = next;
	return liste;
}

size_t ld_total_free_memory(head* liste)
{
	size_t taille = 0;
	for (entete_tranche* next = liste->libre; next != NULL; next = next->suivant)
		taille += next->nb_blocs;
	return taille * sizeof(align_data);
}

size_t ld_total_useful_memory(head* liste)
{
	size_t taille = 0;
	for (entete_tranche* next = liste->libre; next != NULL; next = next->suivant)
	{
		if (next->nb_blocs>=sizeof(node))
			taille += next->nb_blocs;
	}
	return taille * sizeof(align_data);
}

head* ld_add_memory(head* liste, size_t nboctets)
{
	if (nboctets == 0)
		return liste;
	size_t nbblocs = nb_blocs(nboctets);
	size_t size = sizeof(liste->memory);
	liste->memory = realloc(liste->memory, sizeof(liste->memory) + nbblocs * sizeof(align_data));
	if (liste->memory == NULL)
		return NULL;
	entete_tranche* dernier = liste->memory + size;

	entete_tranche* next = liste->libre;
	if (next != NULL)
	{
		while (next->suivant != NULL)
			next = next->suivant;
		next->suivant = dernier;
	}
	else
	{
		liste->libre = dernier;
	}
	dernier->nb_blocs = nbblocs;
	dernier->suivant = NULL;
	return liste;
}
/*
head* ld_compactify(head* liste)
{
	head* newHead = ld_create(sizeof(liste->memory));

	for (node* noeud = liste->first; noeud != NULL; noeud = noeud->next)
	{
		if (ld_insert_last(newHead, noeud->len - sizeof(node), noeud->data) == NULL)
			return NULL;
	}
	liste->first = newHead->first;
	liste->last = newHead->last;
	liste->libre = newHead->libre;
	liste->memory = newHead->memory;
	return liste;
}
*/
head* ld_compactify(head* liste)
{
	head* new_liste = ld_create(sizeof(liste->memory));
	if (new_liste == NULL)
	{
		return NULL;
	}
	node* noeud = liste->first;
	node* new_node = new_liste->memory;
	new_liste->first = new_node;
	while (noeud != NULL)
	{
		new_node->next = NULL;
		new_node->previous = new_liste->last;
		new_node->previous->next = new_node;
		new_node->len = noeud->len + sizeof(node);
		for (int i = 0; i < noeud->len; i++)
		{
			new_node->data[i] = noeud->data[i];
		}
		new_liste->last = new_node;
		noeud = noeud->next;
		new_node += new_node->len * sizeof(align_data);
	}
	new_liste->libre = (entete_tranche*) new_node;
	new_liste->libre->nb_blocs = (void*)new_liste->memory - (void*)new_node;
	new_liste->libre->suivant = NULL;
	liste->memory = new_liste->memory;
	liste->libre = new_liste->libre;
	liste->first = new_liste->first;
	liste->last = new_liste->last;
	return liste;
}