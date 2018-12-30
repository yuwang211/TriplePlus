template<typename T>
class Deque<T>::Node
{
	public:
		int l, r;
		Node *prev, *next;
		Block<T> data;
		Node(int size);
};

template <typename T>
Deque<T>::Node::Node(int size): data(size) {}

template <typename T>
Deque<T>::Deque():length(0), b_size(DEFAULT_B_SIZE) 
{
	head = new Node(0);
	Assert(head, "malloc failed");
	tail = new Node(0);
	Assert(tail, "malloc failed");
	head->l = tail->l = 0;
	head->r = tail->r = 0;
	head->prev = tail->prev = head;
	head->next = tail->next = tail;
	o_head = o_tail = NULL;
}

template <typename T>
Deque<T>::~Deque()
{
	Node *cur = head;
	while (cur != tail)
	{
		Node *next = cur->next;
		delete cur;
		cur = next;
	}
	delete cur;
	if (o_head != NULL) delete o_head;
	if (o_tail != NULL) delete o_tail;
}

template <typename T>
void Deque<T>::reset()
{
	Node *cur = head->next;
	while (cur != tail)
	{
		Node *next = cur->next;
		delete cur;
		cur = next;
	}
	length = 0;
}

template <typename T>
void Deque<T>::set_block_size(int n_b_size)
{
	b_size = n_b_size;
}

template <typename T>
bool Deque<T>::empty() const
{
	return length == 0;
}

template <typename T>
int Deque<T>::size() const 
{
	return length;
}

template <typename T>
const T& Deque<T>::front() const
{
	return head->next->data[head->next->l];
}

template <typename T>
const T& Deque<T>::back() const
{
	return tail->prev->data[tail->prev->r - 1];
}

template <typename T>
void Deque<T>::push_front(const T& t)
{
	if (head->next == tail)
	{
		Node *nb;
		if (o_head == NULL)
			nb = new Node(b_size);
		else
		{
			nb = o_head;
			o_head = NULL;
		}
		nb->prev = head;
		nb->next = head->next;
		nb->prev->next = nb;
		nb->next->prev = nb; 
		nb->l = nb->r = (nb->data.size() >> 1);
	}
	else if (head->next->l == 0)
	{
		Node *nb;
		if (o_head == NULL)
			nb = new Node(b_size);
		else
		{
			nb = o_head;
			o_head = NULL;
		}
		nb->prev = head;
		nb->next = head->next;
		nb->prev->next = nb;
		nb->next->prev = nb; 
		nb->l = nb->r = nb->data.size();
	}
	head->next->data[--head->next->l] = t;
	++length;
}

template <typename T>
void Deque<T>::push_back(const T& t)
{
	if (tail->prev == head)
	{
		Node *nb;
		if (o_tail == NULL)
			nb = new Node(b_size);
		else
		{
			nb = o_tail;
			o_tail = NULL;
		}
		nb->next = tail;
		nb->prev = tail->prev;
		nb->prev->next = nb;
		nb->next->prev = nb; 
		nb->l = nb->r = (nb->data.size() >> 1);
	}
	else if (tail->prev->r == tail->prev->data.size())
	{
		Node *nb;
		if (o_tail == NULL)
			nb = new Node(b_size);
		else
		{
			nb = o_tail;
			o_tail = NULL;
		}
		nb->next = tail;
		nb->prev = tail->prev;
		nb->prev->next = nb;
		nb->next->prev = nb; 
		nb->l = nb->r = 0;
	}
	tail->prev->data[tail->prev->r++] = t;
	++length;
}

template <typename T>
void Deque<T>::pop_front()
{
	if ((++head->next->l) >= head->next->r)
	{
		Node *db = head->next;
		db->next->prev = db->prev;
		db->prev->next = db->next;
		if (o_head == NULL)
			o_head = db;
		else
			delete db;
	}
	--length;
}

template <typename T>
void Deque<T>::pop_back()
{
	if ((--tail->prev->r) <= tail->prev->l)
	{
		Node *db = tail->prev;
		db->next->prev = db->prev;
		db->prev->next = db->next;
		if (o_tail == NULL)
			o_tail = db;
		else 
			delete db;
	}
	--length;
}

template <typename T>
T& Deque<T>::operator [] (int k)
{
	if (k >= 0)
	{
		if (k > length) k %= length;
		Node *cur = head->next;
		while (k >= cur->r - cur->l) 	
		{
			k -= cur->r - cur->l;
			cur = cur->next;
		}
		return cur->data[cur->l + k];
	}
	else
	{
		k = -k;
		if (k > length) k %= length;
		Node *cur = tail->prev;
		while (k > cur->r - cur->l)
		{
			k -= cur->r - cur->l;
			cur = cur->prev;
		}
		return cur->data[cur->r - k];
	}
}

template <typename T>
const T& Deque<T>::operator [] (int k) const
{
	if (k >= 0)
	{
		if (k > length) k %= length;
		Node *cur = head->next;
		while (k >= cur->r - cur->l) 
		{
			k -= cur->r - cur->l;
			cur = cur->next;
		}
		return cur->data[cur->l + k];
	}
	else
	{
		k = -k;
		if (k > length) k %= length;
		Node *cur = tail->prev;
		while (k > cur->r - cur->l)
		{
			k -= cur->r - cur->l;
			cur = cur->prev;
		}
		return cur->data[cur->r - k];
	}
}

template <typename T>
const T& Deque<T>::index(int k) const
{
	if (k >= 0)
	{
		if (k > length) k %= length;
		Node *cur = head->next;
		while (k >= cur->r - cur->l) 
		{
			k -= cur->r - cur->l;
			cur = cur->next;
		}
		return cur->data[cur->l + k];
	}
	else
	{
		k = -k;
		if (k > length) k %= length;
		Node *cur = tail->prev;
		while (k > cur->r - cur->l)
		{
			k -= cur->r - cur->l;
			cur = cur->prev;
		}
		return cur->data[cur->l - k];
	}
}


template<typename T>
class Deque<T>::iterator{
	
	public:
	
		iterator(): cur(NULL), pos(-1), c(NULL)		{}
	
		Deque<T>::iterator& operator++()
		{
			Assert(cur, "uninitialization iterator");
			Assert(0 <= pos && pos < cur->r - cur->l, "illegal iterator");
			if ((++pos) >= cur->r - cur->l)
			{
				pos = 0;
				cur = cur->next;
			}
			return (*this);
		}
		
		Deque<T>::iterator operator++(int)
		{
			typename Deque<T>::iterator ret(*this);
			Assert(cur, "uninitialization iterator");
			Assert(c, "uninitialization iterator");
			Assert(cur != c->tail, "reach-the-end iterator");
			Assert(0 <= pos && pos < cur->r - cur->l, "illegal iterator");
			if ((++pos) >= cur->r - cur->l)
			{
				pos = 0;
				cur = cur->next;
			}
			return ret;
		}
   
		T& operator*()
		{
			Assert(cur, "uninitialization iterator");
			Assert(c, "uninitialization iterator");
			Assert(cur != c->tail, "reach-the-end iterator");
			Assert(0 <= pos && pos < cur->r - cur->l, "illegal iterator");
			return cur->data[cur->l + pos];
		}
		
		friend class Deque<T>;

		inline bool operator == (const typename Deque<T>::iterator &y) const
		{
			return c == y.c && cur == y.cur && pos == y.pos;
		}

		inline bool operator != (const typename Deque<T>::iterator &y) const
		{
			return c != y.c || cur != y.cur || pos != y.pos;
		}
		
	private:
		iterator(typename Deque<T>::Node *cur, int pos, Deque<T> *c): cur(cur), pos(pos), c(c) {}
		typename Deque<T>::Node *cur;
		int pos;
		Deque<T> *c;
};


template<typename T>
typename Deque<T>::iterator Deque<T>::begin()
{
	return typename Deque<T>::iterator(head->next, 0, this);
}

template<typename T>
typename Deque<T>::iterator Deque<T>::end()
{
	return typename Deque<T>::iterator(tail, 0, this);
}
