#include "vector.h"
#include<time.h>

struct Vector {
	int capacity;
	int count;
	void **array;
	release_func release;
};

static BOOL 
vector_extend(struct Vector *vector)
{
	vector->capacity = ((vector->capacity)<<1);
	vector->array = (void **)realloc(vector->array, sizeof(void *) * (vector->capacity));
	if(vector->array == NULL)
		return FALSE;
	return TRUE;
}

static BOOL 
vector_shrink(struct Vector *vector)
{
	vector->capacity = ((vector->capacity)>>1);
	vector->array = (void **)realloc(vector->array, sizeof(void *) * (vector->capacity));
	if(vector->array == NULL)
		return FALSE;
	return TRUE;
}

static BOOL
check_needs_extend(struct Vector *vector)
{	
	if(vector->count == vector->capacity) {
		BOOL extend_ret = vector_extend(vector);
		if(extend_ret == FALSE)
			return FALSE;
	}
	if(vector->count >= vector->capacity)
		return FALSE;
	return TRUE;
}

static BOOL
check_needs_shrink(struct Vector *vector)
{
	if(vector->capacity <= DEFAULT_CAPACITY)
		return TRUE;

	if((vector->count) <= ((vector->capacity)>>2)) {
		BOOL shrink_ret = vector_shrink(vector);
		if(shrink_ret == FALSE)
			return FALSE;
	}
	return TRUE;
}

struct Vector *
create_vector(int default_capacity, release_func rel)
{
	struct Vector *vector = (struct Vector *)malloc(sizeof(struct Vector));
	if(vector != NULL) {
		vector->capacity = default_capacity > 0 ? default_capacity : DEFAULT_CAPACITY;
		vector->count = 0;
		vector->release = rel;
		vector->array = (void **)malloc(sizeof(void *) * (vector->capacity));

		if(vector->array == NULL) {
			free(vector);
			vector = NULL;
		}else 
			memset(vector->array, 0, sizeof(void *)*(vector->capacity));
	}
	return vector;
}

void
destroy_vector(struct Vector *vector, BOOL mem_release)
{
	if(vector) {
		if(vector->array) {
			if(vector->release && mem_release) {
				int i;
				for(i=0; i<vector->count; ++i)
					vector->release(vector->array[i]);
			}
			free(vector->array);
			vector->array = NULL;
		}
		free(vector);
	}
}

BOOL
vector_push_back(struct Vector *vector, void *data)
{
	assert(vector != NULL);
	if(data == NULL)
		return FALSE;
	if(check_needs_extend(vector) == FALSE)
		return FALSE;

	vector->array[(vector->count)] = data;
	++(vector->count);
	return TRUE;
}

BOOL
vector_push_front(struct Vector *vector, void *data)
{
	return vector_insert(vector, data, 0);
}

BOOL
vector_insert(struct Vector *vector, void *data, int pos)
{	
	assert(vector != NULL);
	if(data == NULL)
		return FALSE;
	if(pos<0 || pos>=(vector->count))
		return FALSE;
	if(check_needs_extend(vector) == FALSE)
		return FALSE;

	int i = vector->count;
	for( ; i>pos; --i)
		vector->array[i] = vector->array[i-1];
	vector->array[pos] = data;
	++(vector->count);
	return TRUE;
}

BOOL
vector_remove_at(struct Vector *vector, int pos, BOOL mem_release)
{
	assert(vector != NULL);

	if(pos<0 || pos>=(vector->count))
		return FALSE;

	void *rmv = vector->array[pos];
	int i = pos+1;
	for( ; i<vector->count; ++i)
		vector->array[i-1] = vector->array[i];
	--(vector->count);

	if(vector->release && mem_release)
		vector->release(rmv);

	check_needs_shrink(vector);
	return TRUE;
}

BOOL
vector_remove(struct Vector *vector, void *data, compare_func compare, BOOL mem_release)
{
	int pos = vector_indexof(vector, data, compare);
	return vector_remove_at(vector, pos, mem_release);
}

void *
vector_at(struct Vector *vector, int pos)
{
	assert(vector != NULL);
	if(pos<0 || pos>=(vector->count))
		return NULL;

	return vector->array[pos];
}

int
vector_indexof(struct Vector *vector, void *target, compare_func compare)
{
	assert(vector!=NULL && compare!=NULL);
	if(target == NULL)
		return -1;
	int i;
	for(i=0; i<(vector->count); ++i)
		if(compare(vector->array[i], target) == 0)
			return i;
	return -1;
}

void
vector_foreach(struct Vector *vector, foreach_func apply)
{
	assert(vector != NULL);
	if(apply == NULL)
		return;

	int i;
	for(i=0; i<(vector->count); ++i)
		apply(vector->array[i]);
	return;
}

int
vector_count(struct Vector *vector)
{
	assert(vector != NULL);
	return (vector->count);
}

int
vector_capacity(struct Vector *vector)
{
	assert(vector != NULL);
	return (vector->capacity);
}

static void
vector_swap(void **array, int i, int j)
{
	if(i != j) {
		void *tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
}

BOOL
vector_exchange(struct Vector *vector, int i, int j)
{
	assert(vector != NULL);
	if(i<0 || i>=(vector->count))
		return FALSE;
	if(j<0 || j>=(vector->count))
		return FALSE;
	vector_swap(vector->array, i, j);
	return TRUE;
}

BOOL
vector_shuffle(struct Vector *vector)
{
	assert(vector != NULL);
	int i, j;
	srand(time(NULL));
	for(j=(vector->count)-1; j>0; --j) {
		i = (rand()%(j+1));
		vector_swap(vector->array, i, j);
	}
	return TRUE;
}

static int
vector_rpartition(void **array, int begin, int end, compare_func compare)
{
	srand(time(NULL));
	int i, j, r = begin + (rand()%(end-begin+1));
	vector_swap(array, begin, r);
	void *pivot = array[begin];
	i = begin;
	for(j=begin+1; j<=end; ++j)
		if(compare(array[j], pivot) <= 0)
			vector_swap(array, ++i, j);
	vector_swap(array, begin, i);
	return i;
}

static void
vector_qsort(void **array, int begin, int end, compare_func compare)
{
	if(begin < end) {
		int mid = vector_rpartition(array, begin, end, compare);

		vector_qsort(array, begin, mid-1, compare);
		vector_qsort(array, mid+1, end, compare);
	}
}

BOOL
vector_sort(struct Vector *vector, compare_func comp)
{
	assert(vector!=NULL && comp!=NULL);
	/* randomized quick-sort */
	vector_qsort(vector->array, 0, (vector->count)-1, comp);
	return TRUE;
}

int
vector_bsearch(struct Vector *vector, const void *target, compare_func compare)
{
	int lo, hi, mid, tmp;
	lo = 0;
	hi = (vector->count) - 1;
	while(lo <= hi) {
		mid = lo + ((hi - lo) >> 1);
		tmp = compare(vector->array[mid], target);
		if(tmp == 0)
			return mid;
		else if(tmp > 0)
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	return -1;
}

int
vector_lower(struct Vector *vector, const void *target, compare_func compare)
{
	int lo, hi, mid;
	lo = -1;
	hi = vector->count;
	/* distance between lo and hi at least larger than 1, which ensure mid won't equals to either lo or hi */
	while(lo+1 != hi) { 
		/* loop invariant: vector[lo]<target && vector[hi]>=target && lo<hi */
		mid = lo + ((hi - lo) >> 1);
		if(compare(vector->array[mid], target) >= 0)
			hi = mid;
		else 
			lo = mid;
	}
	if(hi>=(vector->count) || compare(vector->array[hi], target)!=0)
		return -1;
	return hi;
}

int
vector_upper(struct Vector *vector, const void *target, compare_func compare)
{
	int lo, hi, mid;
	lo = -1;
	hi = vector->count;
	/* distance between lo and hi at least larger than 1, which ensure mid won't equals to either lo or hi */
	while(lo+1 != hi) {
		/* loop invariant: vector[lo]<=target && vector[hi]>target && lo<hi */
		mid = lo + ((hi - lo) >> 1);
		if(compare(vector->array[mid], target) <= 0)
			lo = mid;
		else
			hi = mid;
	}
	if(lo<0 || compare(vector->array[lo], target)!=0)
		return -1;
	return lo;
}

#if 0
int
vector_upper(struct Vector *vector, const void *target, compare_func compare)
{
	assert(vector!=NULL && compare!=NULL);
	int lo, hi, mid;
	lo = 0;
	hi = (vector->count) - 1;
	while(lo < hi) {
		mid = lo + ((hi - lo + 1)>>1);
		if(compare(vector->array[mid], target) <= 0)
			lo = mid;
		else
			hi = mid - 1;
	}
	return lo;
}

int
vector_lower(struct Vector *vector, const void *target, compare_func compare)
{
	assert(vector!=NULL && compare!=NULL);
	int lo, hi, mid;
	lo = 0;
	hi = (vector->count) - 1;
	while(lo < hi) {
		mid = lo + ((hi - lo)>>1);
		if(compare(vector->array[mid], target) >= 0)
			hi = mid;
		else
			lo = mid + 1;
	}
	return lo;
}
#endif

struct Vector *
vector_duplicate(struct Vector *v)
{
	assert(v != NULL);

	struct Vector *vector = (struct Vector *)malloc(sizeof(struct Vector));
	if(vector) {
		vector->capacity = v->capacity;
		vector->count = v->count;
		vector->release = v->release;
		vector->array = (void **)malloc(sizeof(void *) * (vector->capacity));

		if(vector->array == NULL) {
			free(vector);
			vector = NULL;
		} else
			memcpy(vector->array, v->array, sizeof(void *)*(vector->capacity));
	}
	return vector;
}
