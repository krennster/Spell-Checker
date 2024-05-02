//constructors **********************************************************************************************************************************************

//default 
template <typename T>
HashTable<T>::HashTable(size_t size) : hashTable(size) {
  theSize = 0;
}

//destructor
template <typename T>
HashTable<T>::~HashTable() { 
  clear();
}

//other funcitons *************************************************************************************************************************************************

//bool contains
template <typename T>
bool HashTable<T>::contains(const T &x) const {
  size_t index = myhash(x);
  const auto &indexList = hashTable[index];

  for (const auto &element : indexList) {
    if (element == x) { return true; }
  }

  return false;
}

//bool insert
template <typename T>
bool HashTable<T>::insert(const T &x) {
    size_t index = myhash(x);
    auto &indexList = hashTable[index];

    for (const auto &element : indexList) {
      if (element == x) { return false; }
    }

    indexList.push_back(x);
    
    theSize++;
    if (theSize - 1  >= hashTable.size()) {
      cout << "rehashing..." << endl;
      rehash();
    }
    return true;
}

//bool insert move
template <typename T>
bool HashTable<T>::insert(T &&x) {
    size_t index = myhash(x);
    auto &indexList = hashTable[index];

    for (const auto &element : indexList) {
      if (element == x) { return false; }
    }

    indexList.push_back(std::move(x));

    theSize++;
    if (theSize - 1 >= hashTable.size()) {
      cout << "rehashing..." << endl;
      rehash();
    }
    return true;
}

//remove
template <typename T>
bool HashTable<T>::remove(const T &x) {
  size_t index = myhash(x);
  auto &indexList = hashTable[index];

  for (auto it = indexList.begin(); it != indexList.end(); ++it) {
    if (*it == x) { 
      indexList.erase(it);
      theSize--;
      return true; 
    }
  }
  return false;
}

//clear
template <typename T>
void HashTable<T>::clear() {
  hashTable.clear();
  theSize = 0;
}

//bool load
template <typename T>
bool HashTable<T>::load(const char *filename) {
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error" << endl;
    return false;
  }

  T val;
  while (getline(file, val)) {
    this->insert(val);
  }

  file.close();
  return true;
}

//dump
template <typename T>
void HashTable<T>::dump() const {
  int counter =0;
  for (int i =0; i < hashTable.size(); ++i) {
    cout << "v[" << i << "]: ";
    for (const auto &element : hashTable[i]) {
      cout << element << "\t";
    }
    cout << endl;
  }
}

//write to file 
template <typename T>
bool HashTable<T>::write_to_file(const char *filename) const {
  ofstream file(filename);

  if (!file.is_open()) {
    cout << "error" << endl;
    return false;
  }

  for (const auto &entry : hashTable) {
    for (const auto &element : entry) {
      file << element << endl;
    }
  }

  file.close();
  return true;
}

//custom functions *************************************************************************

//size
template <typename T>
size_t HashTable<T>::sizeOf() {
  return theSize;
}



//private functions *************************************************************************************************************************************************************************************

//Make empty
template <typename T>
void HashTable<T>::makeEmpty() {
  for (auto &entry : hashTable) {entry.clear(); }
}

template <typename T>
void HashTable<T>::rehash() {
    size_t newCapacity = prime_below(hashTable.size() * 2);
    vector<list<T>> newHash(newCapacity);

    for (const auto &entry : hashTable) {
      for (const auto &element : entry) {
        size_t newIndex = myhash(element);
        newHash[newIndex].push_back(element);
      }
    }

    // Move the newHash to hashTable
    hashTable = move(newHash);
}
template <typename T>
size_t HashTable<T>::myhash(const T &x) const {
    static hash<T> hf;

    // Check if hashTable size is greater than zero
    if (hashTable.size() > 0) {
      return hf(x) % hashTable.size();
    } 
    else { return 0; }
}

//provided definitions **************************************************************************************************************************************
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename T>
unsigned long HashTable<T>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename T>
void HashTable<T>::setPrimes(std::vector<long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

