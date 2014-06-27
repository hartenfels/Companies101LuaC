#ifndef COMPANIES101_VECTOR_H
#define COMPANIES101_VECTOR_H
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

/**<!--===============================================================================-->

@file c101_Vector.h A vector (also known as ArrayList) class.


Feature
=======

101 Companies needs some type of resizable container type for virtually all of its
features. Since C doesn't provide such a type and linking against some huge library just
for a vector is neither very user-friendly nor necessary, this one was written from the
ground up.


How It Works
============

The vector is a resizable array of `void*`. When the array is full and another element is
to be added, the array is `realloc`ated to twice its current size (i.e. the vector will
grow exponentially. Elements can be added, accessed and removed just like if the vector
were either an array or a list.

This particular implementation also holds a callback function for destroying or `free`ing
elements that you can pass upon construction.


Usage
=====

Use ::c101_newVector to construct and ::c101_freeVector to destruct a vector.


Elements
--------

Due to the lack of templates in C, this vector handles its contents as an array of
`void*` that need to be cast to the appropriate type. You are encouraged to only store
things that you can safely cast, i.e. a single type or a `union` of types that you can
discern. For that reason there is also only a single destruction callback function for
the entire vector, instead of providing one for each element.


Iterators
---------

This vector implementation provides an iterator implementation similar to C++, which in
this case means they are `void**` pointing to the elemens of the vector. You can use
::c101_begin and ::c101_end to to prettier looping or even combine them with the
::c101_map and ::c101_fold functions to make things even more algorithmic.


Assertions
----------

Some of the functions in this vector `assert` their correct usage, for example when
accessing an empty vector. These are *not* exceptions, instead they signify programming
errors or bugs made by the caller of the function. These will be disabled when `NDEBUG`
is `#define`d.

<!--================================================================================-->*/



/** <!---------------------------------------------------------------------------------->
Represents a vector.
Unless you know what you're doing, don't directly use the `data`
member of this struct or modify the `size` and `capacity`, use the accessor functions
(``methods'') instead. It is fine to read the `size` and `capacity` members and modify
the `destroy` callback directly.
<!------------------------------------------------------------------------------------>*/
struct c101_Vector {
    void** data;			///< The underlying array of `void*`.
    size_t size;            ///< Number of elements currently in this vector.
    size_t capacity;        ///< Maximum number of elements the array can hold.
    void (*destroy)(void*); ///< Callback function for destroying elements.
};


/** <!---------------------------------------------------------------------------------->
Constructs a new vector.
@param capacity The number of elements that the vector can hold initially. This many
`void*` will be `calloc`'d. If you know the number of elements you'll be inserting in
advance, use that to avoid unecessary and slow reallocations.
@param destroy Callback for destroying an element or `NULL` if you don't need it.
@return A pointer to the new vector, which should be destroyed later via
::c101_freeVector.
<!------------------------------------------------------------------------------------>*/
struct c101_Vector c101_newVector  (size_t capacity,
                                    void (*destroy)(void*));


/** <!---------------------------------------------------------------------------------->
Clears the given vector.
This will call the destroy callback function on each element (if it's not `NULL`) and
set the vector's size to 0. It won't modify the vector's capacity.
@param vector A pointer to the vector to clear, `NULL` is undefined behavior.
<!------------------------------------------------------------------------------------>*/
void               c101_clearVector(struct c101_Vector* vector);


/** <!---------------------------------------------------------------------------------->
Destroys the given vector.
This will clear the vector as per ::c101_clearVector and then release its memory.
@param vector A pointer to the vector to be destroyed. Must have been created via
::c101_newVector and not be `NULL`, otherwise you get undefined behavior.
<!------------------------------------------------------------------------------------>*/
void               c101_freeVector (struct c101_Vector* vector);



/** <!---------------------------------------------------------------------------------->
Manually resizes the given vector to a larger size.
@param vector A pointer to the vector to be resized.
@param capacity The number of elements that the vector should hold after this operation.
If the given capacity is smaller or equal to the vector's actual capacity, nothing is
done.
<!------------------------------------------------------------------------------------>*/
void c101_resize  (struct c101_Vector* vector,
                   size_t capacity);


/** <!---------------------------------------------------------------------------------->
Adds an element to the end of the given vector.
If the vector's capacity is equal to its size, it is ::c101_resize'd to twice its current
capacity and all iterators are invalidated.
@param vector A pointer to the vector into which to insert.
@param element The element to insert.
<!------------------------------------------------------------------------------------>*/
void c101_pushBack(struct c101_Vector* vector,
                   void*               element);


/** <!---------------------------------------------------------------------------------->
Inserts an element into the given vector at the given position.
If the vector's capacity is equal to its size, it is ::c101_resize'd to twice its current
capacity and all iterators are invalidated. All elements after the given position will be
`memmove`d one element further.
@param vector The vector to insert into.
@param position The position that the element will have after insertion. It is asserted
that this value is less than or equal to the vector's size.
@param element The element to insert.
<!------------------------------------------------------------------------------------>*/
void c101_insert  (struct c101_Vector* vector,
                   size_t              position,
                   void*               element);



/** <!---------------------------------------------------------------------------------->
Removes the last element from the given vector.
The destroy callback function is not called when removing the element, use
::c101_popBackDestroy for that.
@param vector The vector to pop the element from. It is asserted that this vector is not
empty.
<!------------------------------------------------------------------------------------>*/
void c101_popBack       (struct c101_Vector* vector);


/** <!---------------------------------------------------------------------------------->
Destroys and removes the last element from the given vector.
If the destroy callback function is not `NULL`, it is called before removing the element.
If you don't want to destroy it, use ::c101_popBackDestroy.
@param vector The vector to pop the element from. It is asserted that this vector is not
empty.
<!------------------------------------------------------------------------------------>*/
void c101_popBackDestroy(struct c101_Vector* vector);


/** <!---------------------------------------------------------------------------------->
Removes the element at the given position from the given vector.
The destroy callback function is not called when removing the element, use
::c101_removeDestroy for that. All elements beyond the removed element will be `memmove`d
one space backwards.
@param vector The vector to remove the element from.
@param position The position of the element to remove. It is asserted that this is less
than the vector's size.
<!------------------------------------------------------------------------------------>*/
void c101_remove        (struct c101_Vector* vector,
                         size_t              position);


/** <!---------------------------------------------------------------------------------->
Destroys and removes the element at the given position from the given vector.
If the destroy callback function is not `NULL`, it is called before removing the element.
If you don't want to destroy it, use ::c101_popBackDestroy. All elements beyond the
removed element will be `memmove`d one space backwards.
@param vector The vector to remove the element from.
@param position The position of the element to remove. It is asserted that this is less
than the vector's size.
<!------------------------------------------------------------------------------------>*/
void c101_removeDestroy (struct c101_Vector* vector,
                         size_t              position);



/** <!---------------------------------------------------------------------------------->
Accesses the element at the given position in the given vector.
@param vector The vector to get the element from.
@param position The array index of the element. It is asserted that this is less than
the vector's size.
@return A pointer to the element.
@warning Don't save the reference to the element separately, as it is invalidated
whenever the vector is resized or the element is destroyed. Prefer to store the position
instead.
<!------------------------------------------------------------------------------------>*/
void*  c101_at   (struct c101_Vector* vector,
                  size_t              position);


/** <!---------------------------------------------------------------------------------->
Accesses the first element of the given vector.
@param vector The vector to get the element from. It is asserted that the vector is not
empty.
@return A pointer to the element.
@warning Don't save the reference to the element separately, as it is invalidated
whenever the vector is resized or the element is destroyed.
<!------------------------------------------------------------------------------------>*/
void*  c101_front(struct c101_Vector* vector);


/** <!---------------------------------------------------------------------------------->
Accesses the last element of the given vector.
@param vector The vector to get the element from. It is asserted that the vector is not
empty.
@return A pointer to the element.
@warning Don't save the reference to the element separately, as it is invalidated
whenever the vector is resized or the element is destroyed.
<!------------------------------------------------------------------------------------>*/
void*  c101_back (struct c101_Vector* vector);


/** <!---------------------------------------------------------------------------------->
Returns an iterator (a pointer) to the beginning of the given vector.
@param vector The vector.
@return A pointer with the address of the vector's `data` array.
@warning The iterator is invalidated whenever the vector is resized.
<!------------------------------------------------------------------------------------>*/
void** c101_begin(struct c101_Vector* vector);


/** <!---------------------------------------------------------------------------------->
Returns an off-the-end iterator (a pointer) to the given vector.
@param vector The vector.
@return A pointer with the address of the element one beyond the vector's `data` array.
@warning The iterator is invalidated whenever the vector is resized. It also will not
be the end of the vector when an element is added or removed.
<!------------------------------------------------------------------------------------>*/
void** c101_end  (struct c101_Vector* vector);



/** <!---------------------------------------------------------------------------------->
Applies the given function to each element of the given range.
It is asserted that begin is less than or equal to end.
@param begin The first element of the range.
@param end The end of the range, exclusive. That means it points to the  element one
beyond the last element of the range to be processed.
@param callback A function taking a pointer to a vector element as its argument.
@warning Do not remove any elements from the range, or else you will be working on
invalid iterators. Do not add elements unless you've made sure that the vector is not
resized during the operation.
<!------------------------------------------------------------------------------------>*/
void   c101_map  (void** begin,
                  void** end,
                  void (*callback)(void*));


/** <!---------------------------------------------------------------------------------->
Applies the given function to each element of the given range and computes a result.
It is asserted that begin is less than or equal to end.
@param begin The first element of the range.
@param end The end of the range, exclusive. That means it points to the  element one
beyond the last element of the range to be processed.
@param[out] out A pointer to the place in which to store the result.
@param callback A function taking a pointer to a vector element as its first argument
and out as its second argument.
@warning Do not remove any elements from the range, or else you will be working on
invalid iterators. Do not add elements unless you've made sure that the vector is not
resized during the operation.
<!------------------------------------------------------------------------------------>*/
void   c101_fold (void** begin,
                  void** end,
                  void*  out,
                  void (*callback)(void*, void*));


#ifdef __cplusplus
}
#endif
#endif

