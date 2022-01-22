// vector standard header

#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

// CLASS vector
class vector // varying size array of values
{
public:
   using value_type = int;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = int &;
   using const_reference = const int &;
   using size_type = size_t;
   using difference_type = ptrdiff_t;

   using iterator = value_type *;
   using const_iterator = const value_type *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   vector();

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   vector( const size_type count );

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   vector( const vector &right );

   // Vector destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the vector.
   ~vector();

   // Adds a new element at the end of the vector, after its current last element.
   // The content of val is copied (or moved) to the new element.
   // This effectively increases the container size by one,
   // which causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   void push_back( const value_type &val );

   // The vector is extended by inserting a new element before the element
   // at the specified position, effectively increasing the container size by one.
   // This causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   // Relocates all the elements that were after "where" to their new positions.
//   iterator insert( const_iterator where, const value_type &val );

   // overloaded assignment operator
   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   vector& assign( const vector &right );

   // Resizes the container so that it contains "newSize" elements.
   // If "newSize" is smaller than the current container size,
   // the content is reduced to its first "newSize" elements, removing those beyond.
   // If "newSize" is greater than the current container size,
   // the content is expanded by inserting at the end as many elements as needed
   // to reach a size of "newSize".
   // The new elements are initialized as 0.
   // If "newSize" is also greater than the current container capacity,
   // an automatic reallocation of the allocated storage space takes place.
   void resize( const size_type newSize );

   // Removes the last element in the vector,
   // effectively reducing the container size by one.
   void pop_back();

   // Removes from the vector either a single element (where).
   // This effectively reduces the container size by one, which is destroyed.
   // Relocates all the elements after the element erased to their new positions.
//   iterator erase( const_iterator where );

   // Removes all elements from the vector (which are destroyed),
   // leaving the container with a size of 0.
   // A reallocation is not guaranteed to happen,
   // and the vector capacity is not guaranteed to change due to calling this function.
   void clear();

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin();

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const;

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   iterator end();

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   const_iterator end() const;

   // Returns a const_iterator pointing to the first element in the container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator cbegin() const;

   // Returns a const_iterator pointing to the past-the-end element in the container.
   // If the container is empty, this function returns the same as vector::cbegin.
   // The value returned shall not be dereferenced.
   const_iterator cend() const;

   // Returns whether the vector is empty (i.e. whether its size is 0).
   bool empty() const;

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   size_type size() const;

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   // This capacity is not necessarily equal to the vector size.
   // It can be equal or greater, with the extra space allowing to accommodate
   // for growth without the need to reallocate on each insertion.
   size_type capacity() const;

   // Returns a reference to the element at position "pos" in the vector container.
//   value_type& operator[]( const size_type pos );

   // Returns a reference to the element at position "pos" in the vector container.
//   const value_type& operator[]( const size_type pos ) const;

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   value_type& front();

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   const value_type& front() const;

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   value_type& back();

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   const value_type& back() const;

private:
   pointer myFirst; // pointer to beginning of array
   pointer myLast;  // pointer to current end of sequence
   pointer myEnd;   // pointer to end of array
};

#endif // VECTOR_H