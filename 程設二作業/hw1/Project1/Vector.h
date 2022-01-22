#ifndef VECTOR_H
#define VECTOR_H

// vector class definition
class vector
{
public:
   using value_type = int;
   using pointer = value_type *;
   using size_type = size_t;

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
   // The content of val is copied to the new element.
   // This effectively increases the vector size by one,
   // which causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   void push_back( const value_type &val );

   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   vector& assign( const vector &right );

   // Resizes the vector so that it contains newSize elements.
   // If newSize is smaller than the current vector size,
   // the content is reduced to its first newSize elements, removing those beyond.
   // If newSize is greater than the current vector size,
   // the content is expanded by inserting at the end
   // as many elements as needed to reach a size of newSize.
   // The new elements are initialized as 0.
   // If newSize is also greater than the current vector capacity,
   // an automatic reallocation of the allocated storage space takes place.
   void resize( const size_type newSize );

   // Removes the last element in the vector,
   // effectively reducing the container size by one.
   void pop_back();

   // Removes all elements from the vector (which are destroyed),
   // leaving the container with a size of 0.
   // A reallocation is not guaranteed to happen,
   // and the vector capacity is not guaranteed to change due to calling this function.
   void clear();

   // Returns an pointer pointing to the first element in the vector.
   // If the container is empty, the returned pointer value shall not be dereferenced.
   pointer begin();

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   size_type size();

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   // This capacity is not necessarily equal to the vector size.
   // It can be equal or greater, with the extra space allowing to accommodate
   // for growth without the need to reallocate on each insertion.
   size_type capacity();

   // Returns a reference to the element at position "pos" in the vector container.
   value_type& element( const size_type pos );

private:
   pointer myFirst; // pointer to beginning of array
   pointer myLast;  // pointer to current end of sequence
   pointer myEnd;   // pointer to end of array
}; // end class vector

#endif