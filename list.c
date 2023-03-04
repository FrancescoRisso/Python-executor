#include "list.h"

typedef struct node_t* Node;

struct node_t {
	void* value;
	Node next;
};

struct list_t {
	Node head, tail;
	listType type;
	int items;
};

/*
	LIST_append
	---------------------------------------------------------------------
	Appends an item to a list
	---------------------------------------------------------------------
	PARAMETERS:
		- l: the list where to append
		- item: what to append
	---------------------------------------------------------------------
	OUTPUT:
		- true if all went smoothly, false if some problems occurred
*/
bool LIST_append(List l, void* item);

/*
	LIST_freeValue
	---------------------------------------------------------------------
	Frees the value of a node, depending on the type
	---------------------------------------------------------------------
	PARAMETERS:
		- node: the node whose value should be freed
		- type: the type of items in the list
*/
void LIST_freeValue(Node node, listType type);

/*
	LIST_toArray
	---------------------------------------------------------------------
	Converts the list of node values into an array
	---------------------------------------------------------------------
	PARAMETERS:
		- l: the list
	---------------------------------------------------------------------
	OUTPUT:
		- the array
		- NULL if allocation problems
*/
void** LIST_toArray(List l);


List LIST_init(listType type) {
	List l = malloc(sizeof(*l));
	if(l == NULL) return NULL;

	l->type = type;
	l->head = l->tail = NULL;
	l->items = 0;

	return l;
}

void LIST_free(List l, bool alsoFreeItems) {
	Node prev;

	if(l == NULL) return;

	if(l->head != NULL) {
		for(prev = l->head, l->head = l->head->next; l->head != NULL; prev = l->head, l->head = l->head->next) {
			if(alsoFreeItems) LIST_freeValue(prev, l->type);
			free(prev);
		}
		if(alsoFreeItems) LIST_freeValue(prev, l->type);
		free(prev);
	}

	free(l);
}

bool LIST_append(List l, void* item) {
	Node newNode;

	newNode = malloc(sizeof(*newNode));
	if(newNode == NULL) return false;

	newNode->next = NULL;
	newNode->value = item;

	if(l->head == NULL)
		l->head = l->tail = newNode;
	else {
		l->tail->next = newNode;
		l->tail = newNode;
	}

	l->items++;

	return true;
}

bool LIST_appendVariable(List l, Variable v) {
	if(l->type != variables) {
		printf("Cannot append variables to a non-variables list");
		return false;
	}
	return LIST_append(l, (void*) v);
}

void LIST_freeValue(Node node, listType type) {
	switch(type) {
		case variables: VAR_free((Variable) node->value); break;
	}
}

int LIST_getVariableArray(List l, Variable** arrayPtr) {
	if(l->type != variables) return -1;
	*arrayPtr = (Variable*) LIST_toArray(l);
	if(*arrayPtr == NULL) return -2;
	return l->items;
}

void** LIST_toArray(List l) {
	void** array;
	int i;
	Node node;

	array = malloc(l->items * sizeof(void*));
	if(array == NULL) return NULL;

	node = l->head;
	for(i = 0; i < l->items; i++) {
		array[i] = node->value;
		node = node->next;
	}

	return array;
}
