template <typename T>
class Deque{
	
	public:
	
		Deque();
		~Deque();
		
		void reset();
		void set_block_size(int n_b_size);
		bool empty() const;
		int size() const;
		
		const T& front() const;
		const T& back() const;
		void push_front(const T& t);
		void push_back(const T& t);
		void pop_front();
		void pop_back();
		
		T& operator [] (int k);
		const T& operator [] (int k) const;
		const T& index(int k) const;
		
		class iterator;
		
		iterator begin();
		iterator end();
				
	private:
		
		Deque<T>& operator = (const Deque<T> &b);
		Deque(const Deque<T> &b);
	
		class Node;
		
		static const int DEFAULT_B_SIZE = 255;

		int length;
		int b_size;
		Node *head, *tail;
		Node *o_head, *o_tail;
		
		
};

#include "deque.cpp"
