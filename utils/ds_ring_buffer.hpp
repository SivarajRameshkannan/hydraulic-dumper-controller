/*
 * ds_ring_buffer.cpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#pragma once
#include <stdint.h>

template<typename T, uint8_t size>
class RingBuffer
{
	public:
	    RingBuffer() : head(0), tail(0), count(0) {}
	
	    bool isFull() const { return count == size; }
	    bool isEmpty() const { return count == 0; }
	
	    bool enqueue(const T& item)
	    {
	        if (isFull())
	            return false;
	
	        buffer[head] = item;
	        head = (head + 1) % size;
	        count+=1;
	        return true;
	    }
	
	    bool dequeue(T& item)
	    {
	        if (isEmpty())
	            return false;
	
	        item = buffer[tail];
	        tail = (tail + 1) % size;
	        count-=1;
	        return true;
	    }

	private:
	    T buffer[size];
	
	    volatile uint8_t head;
	    volatile uint8_t tail;
	    volatile uint8_t count;
};
