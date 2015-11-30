#include "list.h"

list_t *list_create(void){	
	list_t *l;
	l = malloc(sizeof(list_t));
	l->pFirst = l->pLast = NULL;

	return l;
}

void list_delete(list_t *_list, int delete_data){	
	if(NULL == _list){
		return;
	}

	delete_data ? list_clear(_list) : list_clean(_list);
	free(_list);
}

// delete links
void list_clean(list_t *_list){	
	link_t *_lnk;
	link_t *_nlnk;

	if((NULL == _list)||(0 == _list->count)){
		return;
	}

	_nlnk = _list->pFirst;
	while(NULL != _nlnk){
		_lnk = _nlnk;
		_nlnk = _lnk->pNext;
		free(_lnk);
	}
}

// delete links and data
void list_clear(list_t *_list){	
	link_t *_lnk;
	link_t *_nlnk;

	if((NULL == _list)||(0 == _list->count)){
		return;
	}

	_nlnk = _list->pFirst;
	while(NULL != _nlnk){
		_lnk = _nlnk;
		_nlnk = _lnk->pNext;
		free(_lnk->data);
		free(_lnk);
	}
}

link_t *list_first(list_t *_list){	
	if((NULL == _list)||(0 == _list->count)){
		return NULL;
	}

	return _list->pFirst;
}

link_t *list_last(list_t *_list){	
	if((NULL == _list)||(0 == _list->count)){
		return NULL;
	}

	return _list->pLast;
}

link_t *list_next(list_t *_list, link_t *_link){	
	if((NULL == _list)||(0 == _list->count)){
		return NULL;
	}

	return _link->pNext;
}

link_t *list_find(list_t *_list, list_compare_func func, void *_pattern){

	if((NULL == _list)||(0 == _list->count)){
		return NULL;
	}

	for(link_t *_lnk = _list->pFirst;
		_lnk != NULL;
		_lnk = _lnk->pNext){
		if(0 == func(_lnk->data, _pattern)){
			return _lnk;
		}
	}
}

link_t *list_push(list_t *_list, void *_data, int _id){	
	link_t *_lnk;

	if((NULL == _list)||(NULL == _data)){
		return NULL;
	}
	
	_lnk = malloc(sizeof(link_t));
	_lnk->data = _data;
	_lnk->id = _id;

	if(NULL == _list->pFirst){
		_list->pFirst = _list->pLast = _lnk;
		_lnk->pPrev = _lnk->pNext = NULL;
	} else {
		_lnk->pPrev = _list->pLast;
		_list->pLast->pNext = _lnk;
		_list->pLast = _lnk;
	}
	_list->count++;

	return _lnk;
}

void list_pop(list_t *_list, link_t *_link){	
	
	if((NULL == _list)||(0 == _list->count)){
		return;
	}

	if(NULL == _link){
		_link = _list->pLast;
	}

	if(NULL != _link->pPrev){
		_link->pPrev->pNext = _link->pNext;
	}
	
	if(NULL != _link->pNext){
		_link->pNext->pPrev = _link->pPrev;
	}

	if(_list->pFirst == _link){
		_list->pFirst = _list->pFirst->pNext;
	}

	if(_list->pLast == _link){
		_list->pLast = _list->pLast->pPrev;
	}

	free(_link->data);
	free(_link);
	_list->count--;
}

void list_process(list_t *_list, list_process_func func){	
	if((NULL == _list)||(0 == _list->count)){
		return;
	}

	for(link_t *_lnk = _list->pFirst;
		_lnk != NULL;
		_lnk = _lnk->pNext){
		func(_lnk->data);
	}
}

