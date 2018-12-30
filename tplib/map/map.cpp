template <typename TK>
INT64 tpl_container_map::defaultHash(const TK &k)
{
	INT64 res = 0;
	int len = sizeof(k);
	BYTE *d = (BYTE *)(&k);
	for (int i = 0; i < len; ++i)
		res = (res * SMALL_PRIME + d[i]) % BIG_PRIME;
	return res;
}

template <>
INT64 tpl_container_map::defaultHash<std::string>(const std::string &k)
{
	INT64 res = 0;
	int len = k.size();
	for (int i = 0; i < len; ++i)
		res = (res * SMALL_PRIME + k[i]) % BIG_PRIME;
	return res;
}

template <typename T_KEY, typename T_DATA> 
int Map<T_KEY, T_DATA>::mul(int lhs, int rhs, int mod) const
{
	int res = 0;
	while (rhs != 0)
	{
		if (rhs & 1)
			res = (res + lhs) % mod;
		lhs = (lhs << 1) % mod;
		rhs >>= 1;
	}
	return res;
}

template <typename T_KEY, typename T_DATA> 
int Map<T_KEY, T_DATA>::pow(int lhs, int rhs, int mod) const
{
	int res = 1;
	while (rhs != 0)
	{
		if (rhs & 1) res = mul(res, lhs, mod);
		res = mul(res, res, mod);
		rhs >>= 1;
	}
	return res;
}

template <typename T_KEY, typename T_DATA> 
bool Map<T_KEY, T_DATA>::isPrime(int p) const
{
	if (p < 2 || (p != 2 && p % 2 == 0)) return false;
	int s = p - 1;
	while (!(s & 1)) s >>= 1;
	for (int i = 0; i < tpl_container_map::PRIME_LEN; ++i)
	{
		if (p == tpl_container_map::PRIME[i]) return true;
		int t = s, m = pow(tpl_container_map::PRIME[i], s, p);
		while (t != p - 1 && m != 1 && m != p - 1)
		{
			m = mul(m, m, p);
			t <<= 1;
		}
		if (m != p - 1 && !(t & 1)) return false;
	}
	return true;
}

template <typename T_KEY, typename T_DATA> 
Map<T_KEY, T_DATA>::Map(int sz)
{
	sz = Max(sz, 3);
	if ((sz & 1) == 0) ++sz;
	while (!isPrime(sz)) ++(++sz);
	size = sz;
	key = new T_KEY[sz];
	Assert(key, "malloc failed");
	data = new T_DATA[sz];
	Assert(data, "malloc failed");
	flag.resize(sz);
	flag.reset();
	cur = 1;
	hashCode = &tpl_container_map::defaultHash<T_KEY>;
	cnt = 0;
}

template <typename T_KEY, typename T_DATA> 
Map<T_KEY, T_DATA>::Map(int sz, hash_code hash)
{
	while (!isPrime(sz)) ++sz;
	size = sz;
	key = new T_KEY[sz];
	Assert(key, "malloc failed");
	data = new T_DATA[sz];
	Assert(data, "malloc failed");
	flag.resize(sz);
	flag.reset();
	cur = 1;
	hashCode = hash;
	cnt = 0;
}

template <typename T_KEY, typename T_DATA> 
Map<T_KEY, T_DATA>::~Map()
{
	delete [] key;
	delete [] data;
}

template <typename T_KEY, typename T_DATA> 
void Map<T_KEY, T_DATA>::reset()
{
	++cur;
	cnt = 0;
}

template <typename T_KEY, typename T_DATA> 
T_DATA& Map<T_KEY, T_DATA>::operator [] (const T_KEY& k)
{
	int index = ((*hashCode)(k)) % size;
	while (flag[index] == cur && k != key[index])
	{
		++index;
		if (index == size) index = 0;
	}
	if (flag[index] != cur)
	{
		flag[index] = cur;
		key[index] = k;
		Assert((++cnt) < size, "the capacity of hash map is full");
	}
	return data[index];
}

template <typename T_KEY, typename T_DATA> 
const T_DATA& Map<T_KEY, T_DATA>::operator [] (const T_KEY& k) const
{
	int index = ((*hashCode)(k)) % size;
	while (flag[index] == cur && k != key[index])
	{
		++index;
		if (index == size) index = 0;
	}
	if (flag[index] != cur)
	{
		flag[index] = cur;
		key[index] = k;
		Assert((++cnt) < size, "the capacity of hash map is full");
	}
	return data[index];
}

template <typename T_KEY, typename T_DATA> 
const T_DATA& Map<T_KEY, T_DATA>::index(const T_KEY& k) const
{
	int index = ((*hashCode)(k)) % size;
	while (flag[index] == cur && k != key[index])
	{
		++index;
		if (index == size) index = 0;
	}
	if (flag[index] != cur)
	{
		flag[index] = cur;
		key[index] = k;
		Assert((++cnt) < size, "the capacity of hash map is full");
	}
	return data[index];
}
