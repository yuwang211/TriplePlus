#ifndef _TPLIB_TPLIB_BLOCK_BLOCK_CPP__
#define _TPLIB_TPLIB_BLOCK_BLOCK_CPP__

template <typename T>
Block<T>::Block(): _size(0), data(NULL) {}

template <typename T>
Block<T>::Block(int s): _size(s) 
{
	data = (T *)malloc(sizeof(T) * _size);
	Assert(data, "malloc failed");
}
		
template <typename T>
Block<T>::Block(const Block<T> &b): _size(b._size)
{
	data = (T *)malloc(sizeof(T) * _size);
	Assert(data, "malloc failed");
	memcpy(data, b.data, sizeof(T) * _size);
}
		
template <typename T>
Block<T>::~Block()
{
	if (data != NULL) free(data); 
}
		
template <typename T>
int Block<T>::size() const 
{
	return _size;
}
		
template <typename T>
void Block<T>::reset() 
{
	memset(data, 0, sizeof(T) * _size); 
}
		
template <typename T>
inline T& Block<T>::operator[] (int k) 
{
	Assert(0 <= k && k < _size, "index exceeded");
	return data[k];
}
		
template <typename T>
inline const T& Block<T>::operator[] (int k) const 
{
	Assert(0 <= k && k < _size, "index exceeded");
	return data[k];
}
		
template <typename T>
inline const T& Block<T>::index(int k) const
{
	Assert(0 <= k && k < _size, "index exceeded");
	return data[k];
}
		
template <typename T>
void Block<T>::resize(int n_length)
{
	T *tmp = NULL;
	if (data != NULL) tmp = (T *)realloc(data, sizeof(T) * n_length);
	if (tmp != NULL)
		data = tmp;
	else
	{
		tmp = (T *)malloc(sizeof(T) * n_length);
		Assert(tmp, "malloc failed");
		int len = (n_length < _size ? n_length : _size);
		memcpy(tmp, data, sizeof(T) * len);
		free(data);
		data = tmp;
	}
	_size = n_length;
}

template <typename T>
T* Block<T>::begin()
{
	return data;
}

template <typename T>
T* Block<T>::end()
{
	return data + _size;
}

#endif
