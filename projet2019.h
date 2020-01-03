typedef union
{
	intmax_t a;
	void* adr;
	long doublec;
} align_data;

typedef struct node
{
	struct node* next;
	struct node* previous;
	size_t len;
	align_data data[];
} node;

typedef struct entete_tranche {
	struct entete_tranche* suivant;
	size_t nb_blocs;
} entete_tranche;

typedef struct {
	void* memory; //pointeur vers la memoire
	node* first; //ptrdiff_t ou pointeur
	node* last; //ptrdiff_t ou pointeur
	entete_tranche* libre; //ptrdiff_t ou pointeur si la liste de tranches
	//toute autre information
} head;

size_t nb_blocs(size_t o);
head* ld_create(size_t nboctets);
node* ld_first(head* liste);
node* ld_last(head* liste);
node* ld_next(head* liste, node* current);
node* ld_previous(head* liste, node* current);
void ld_destroy(head* liste);
size_t ld_get(node* current, size_t len, align_data* val);
node* recherche_libre_bis(head* liste, size_t len);
node* recherche_libre(entete_tranche* tranche, size_t len);
node* ld_create_node(head* liste, size_t len, align_data* p_data);
node* ld_insert_first(head* liste, size_t len, align_data* p_data);
node* ld_insert_last(head* liste, size_t len, align_data* p_data);
node* ld_insert_before(head* liste, node* n, size_t len, align_data* p_data);
node* ld_insert_after(head* liste, node* n, size_t len, align_data* p_data);
node* recherche_dernier(entete_tranche* tranche, node* noeud);
node* recherche_dernier_bis(head* liste, node* noeud);
head* ld_delete_node(head* liste, node* n);
size_t ld_total_free_memory(head* liste);
size_t ld_total_useful_memory(head* liste);
head* ld_add_memory(head* liste, size_t nboctets);
head* ld_compactify(head* liste);
void ld_toString_bis(head* list, char* string);
void ld_toString(node* noeud, char* string);