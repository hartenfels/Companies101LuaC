#include "c101_Vector.h"
#include "c101_Util.h"
#include <assert.h>
#include <stdlib.h>

struct c101_Vector
c101_newVector(size_t cap, void (*call)(void*))
{
    struct c101_Vector v;
    v.data     = c101_calloc(cap ? cap : 1, sizeof(void*));
    v.size     = 0;
    v.capacity = cap;
    v.destroy  = call;
    return v;
}

void c101_clearVector(struct c101_Vector* v)
{
    if (v->destroy)
        c101_map(c101_begin(v), c101_end(v), v->destroy);
    v->size = 0;
}

void c101_freeVector(struct c101_Vector* v)
{
    c101_clearVector(v);
    free(v->data);
}


void
c101_resize(struct c101_Vector* v, size_t cap)
{
    if (cap > v->capacity) {
        v->data     = c101_realloc(v->data, cap * sizeof(void*));
        v->capacity = cap;
    }
}

void
c101_pushBack(struct c101_Vector* v, void* elem)
{
    if (v->size == v->capacity)
        c101_resize(v, v->capacity * 2);
    v->data[v->size++] = elem;
}

void
c101_insert(struct c101_Vector* v, size_t pos, void* elem)
{
    assert(pos <= v->size && "c101_insert: insert position out of range");
    if (v->size == v->capacity)
        c101_resize(v, v->capacity * 2);
    memmove(v->data[pos + 1], v->data[pos], v->size - pos);
    v->data[pos] = elem;
}


void
c101_popBack(struct c101_Vector* v)
{
    assert(v->size && "c101_popBack: pop from empty vector");
    --v->size;
}

void
c101_popBackDestroy(struct c101_Vector* v)
{
    assert(v->size && "c101_popBackDestroy: pop from empty vector");
    if (v->destroy)
        v->destroy(v->data[v->size - 1]);
    --v->size;
}

void
c101_remove(struct c101_Vector* v, size_t pos)
{
    assert(pos < v->size && "c101_remove: remove position out of range");
    memmove(v->data[pos], v->data[pos + 1], v->size - pos - 1);
}

void
c101_removeDestroy(struct c101_Vector* v, size_t pos)
{
    assert(pos < v->size && "c101_removeDestroy: remove position out of range");
    if (v->destroy)
        v->destroy(v->data[pos]);
    memmove(v->data[pos], v->data[pos + 1], v->size - pos - 1);
}


void*
c101_at(struct c101_Vector* v, size_t pos)
{
    assert(pos < v->size && "c101_at: vector index out of range");
    return v->data[pos];
}

void*
c101_front(struct c101_Vector* v)
{
    assert(v->size && "c101_front: accessing empty vector");
    return v->data[0];
}

void*
c101_back(struct c101_Vector* v)
{
    assert(v->size && "c101_back: accessing empty vector");
    return v->data[v->size - 1];
}

void**
c101_begin(struct c101_Vector* v)
{ return v->data; }

void**
c101_end(struct c101_Vector* v)
{ return v->data + v->size; }


void
c101_map(void** it, void** end, void (*call)(void*))
{
    assert(it <= end && "c101_map: iterator beyond end iterator");
    while (it != end)
        call(*it++);
}

void c101_fold(void** it, void** end, void* out, void (*call)(void*, void*))
{
    assert(it <= end && "c101_fold: begin iterator beyond end iterator");
    while (it != end)
        call(*it++, out);
}

