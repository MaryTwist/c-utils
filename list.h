#ifndef CUTILS_H
#define CUTILS_H

#include <stdlib.h>

typedef struct _link_t {
	struct _link_t *pPrev;
	struct _link_t *pNext;
	void *data;
	unsigned int id;
} link_t;

typedef struct _list_t {
	unsigned int count;
	struct _link_t *pFirst;
	struct _link_t *pLast;
} list_t;

typedef void (list_process_func)(void *);
typedef int (list_compare_func)(void *, void *);

list_t *list_create(void);
void list_delete(list_t *, int);
// delete links
void list_clean(list_t *);
// delete links and data
void list_clear(list_t *);
link_t *list_first(list_t *);
link_t *list_last(list_t *);
link_t *list_next(list_t *, link_t *);
link_t *list_find(list_t *, list_compare_func, void *);
link_t *list_push(list_t *, void *, int);
void list_pop(list_t *, link_t *);
void list_process(list_t *, list_process_func);

#endif // CUTILS_H
