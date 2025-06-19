#include "dqueue.h"

void create_dstack(node** s)
{
    *s = NULL;
}

int isEmpty_dstack(node* s)
{
    if(s == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push_dstack(node** s, element e)
{
    node* new = (node*)malloc(sizeof(node));
    if(new == NULL)
    {
	printf("Error memoria dPush.\n");
    }
    new->e = e;
    new->next = *s;
    *s = new;
}

element pop_dstack(node** s)
{
    element eaux;
    if(!isEmpty_dstack(*s))
    {
        eaux = (*s)->e;
        node* saux = (*s);
        *s = (*s)->next;
        free(saux);
    }
    else
    {
        eaux = 0;
        printf("Error underflow\n");
    }
    return eaux;
}

void delete_dstack(node** s)
{
    while(!isEmpty_dstack(*s))
    {
        element e = pop_dstack(s);
    }
}

void print_dstack(node** s)
{
    node* aux = NULL;
    element e;

    while(!isEmpty_dstack(*s))
    {
        e = pop_dstack(s);
        push_dstack(&aux,e);
	printf("%d", e);
    }
    while(!isEmpty_dstack(aux))
    {
        e = pop_dstack(&aux);
        push_dstack(s,e);
    }
    printf("\n");
}

//Funciones de cola dinamica con funciones de pila dinámica

void create_dqueue(node **s)
{
    create_dstack(s);
}

int isEmpty_dqueue(node *s)
{
    return isEmpty_dstack(s);
}

void enqueue_dqueue(node **s, element e)
{
    push_dstack(s, e);
}

element dequeue_dqueue(node **s)
{
    node *aux;
    create_dqueue(&aux);
    element e;

    while(!isEmpty_dqueue(*s))
    {
        e = pop_dstack(s);
        push_dstack(&aux,e);
    }

    element result = pop_dstack(&aux);

    while(!isEmpty_dstack(aux))
    {
        e = pop_dstack(&aux);
        push_dstack(s,e);
    }

    free(aux);
    return result;
}

void delete_dqueue(node **s)
{
    delete_dstack(s);
}

void print_dqueue(node **s)
{
    node *aux;
	element e;
	
	create_dqueue(&aux);
	
	while(!isEmpty_dqueue(*s))
	{
		e = dequeue_dqueue(s);
		printf(" %d",e);
		enqueue_dqueue(&aux, e);
	}
	while(!isEmpty_dqueue(aux))
	{
		e = dequeue_dqueue(&aux);
		enqueue_dqueue(s, e);
	}
}
