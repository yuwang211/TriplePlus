

template <typename T_KEY, typename T_DATA> class Map
{

	public:
	
	
		typedef INT64(* hash_code)(const T_KEY&);
	
		Map(int sz);
		Map(int sz, hash_code hash);
		~Map();
		
		void reset();
		
		T_DATA& operator [] (const T_KEY& k);
		const T_DATA& operator [] (const T_KEY& k) const;
		const T_DATA& index(const T_KEY& k) const;
	
	private:
		
		int mul(int lhs, int rhs, int mod) const;
		int pow(int lhs, int rhs, int mod) const;
		bool isPrime(int p) const;
		
		int size;
		Block<int> flag;
		T_KEY *key;
		T_DATA *data;
		int cur;
		mutable int cnt;
		
		
		hash_code hashCode;
		
		
		Map(const Map<T_KEY, T_DATA> &m);
		Map<T_KEY, T_DATA>& operator = (const Map<T_KEY, T_DATA> &m);
};

namespace tpl_container_map{

	static const INT64 BIG_PRIME = 154590409516822759LL;
	static const int SMALL_PRIME= 59;
	static const int PRIME_LEN = 6;
	static const int PRIME[6] = { 2, 3, 5, 233, 331, 479};
			
	template <typename TK>
	INT64 defaultHash(const TK &k);
			
	template <>
	INT64 defaultHash<std::string>(const std::string &k);

}

#include "map.cpp"
