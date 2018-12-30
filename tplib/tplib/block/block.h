#ifndef _TPLIB_TPLIB_BLOCK_BLOCK_H__
#define _TPLIB_TPLIB_BLOCK_BLOCK_H__

template <typename T>
class Block{
	
	public:
	
		Block();
		Block(int s);
		Block(const Block<T> &b);
		~Block();
		
		int size() const;
		void reset();
		T& operator[] (int k);
		const T& operator[] (int k) const;
		const T& index(int k) const;
		void resize(int n_size);
		T* begin();
		T* end();
		
		Block<T>& operator = (const Block<T> &b) = delete;
		
	private:

		int _size;
		T *data;
};

#include "block.cpp"

#endif