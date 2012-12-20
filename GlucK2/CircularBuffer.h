/*******************************************************************************
 
 CircularBuffer
 
 Author: Spencer Salazar - spencer@ccrma.stanford.edu
 
 Notes: This class is defined entirely in this header file, as thats the only
 sane way to implement a C++ template class. 
 
 ******************************************************************************/


#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__


#include <sys/types.h>
#include "def.h"


template<typename T>
class CircularBuffer
{
public:
    
    CircularBuffer(size_t numElements) :
    m_read(0),
    m_write(0),
    m_numElements(numElements+1) // need 1 element to pad
    {
        m_elements = new T[m_numElements];
    }
    
    ~CircularBuffer()
    {
        SAFE_DELETE_V(m_elements);
    }
    
    // put one element
    // returns number of elements successfully put
    inline size_t put(T element)
    {
        if((m_write + 1)%m_numElements == m_read)
        {
            // no space
            return 0;
        }
        
        m_elements[m_write] = element;
        
        m_write = (m_write+1)%m_numElements;
        
        return 1;
    }
        
    // get one element
    // returns number of elements successfully got
    inline size_t get(T &element)
    {
        if(m_read == m_write)
        {
            // nothing to get
            return 0;
        }
        
        element = m_elements[m_read];
        
        m_read = (m_read+1)%m_numElements;
        
        return 1;
    }
    
    // peek at element i without removing it
    // i = 1 would correspond to the least recently put element;
    // i = -1 would correspond to the most recent
    // WARNING: doesn't sanity check that i is a valid index
    // returns number of elements successfully peeked
    inline size_t peek(T &element, size_t i)
    {
        if(i == 0)
            return 0;
        
        if(i > 0)
            element = m_elements[(m_read+(i-1))%m_numElements];
        if(i < 0)
            element = m_elements[(m_write-(i+1))%m_numElements];
        
        return 1;
    }
    
    inline void clear() { m_write = m_read; }
    
    // return maximum number of elements that can be held
    inline size_t maxElements() { return m_numElements-1; }
    
    // return if buffer is full
    inline bool atMaximum() { return (m_write + 1)%m_numElements == m_read; }
    
    // return number of valid elements in the buffer
    inline size_t numElements()
    {
        if(m_read == m_write)
            return 0;
        else if(m_read < m_write)
            return m_write - m_read;
        else
            return m_numElements - m_read + m_write;
    }
    
private:
    
    T * m_elements;
    
    size_t m_read, m_write;
    const size_t m_numElements;
    
};


#endif // __CIRCULAR_BUFFER_H__

