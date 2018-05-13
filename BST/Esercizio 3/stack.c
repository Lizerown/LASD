#include <stdlib.h>
#include "stack.h"
struct stack *pushst(struct stack *st, void *el) {
	struct stack *first;
	first = malloc(sizeof(struct stack));
	first->content = malloc(sizeof(void *));
	first->content = el;
	first->next = st;
	return first;
}
struct stack *popst(struct stack *st) {
	if(st){
		void *tmp = st;
		st = st->next;
		free(tmp);
	}
	return st;
}
void *topst(struct stack *st) {
	if(st) {
		return st->content;
	} else {
		return NULL;
	}
}

struct stack *svuotastackst(struct stack *st) {
	while(topst(st) != NULL) {
		st = popst(st);
	}
	return st;
}
