#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <fstream>
#include <ostream>
#include <functional>

using namespace std;

namespace cop4530 {

template <typename T>
class HashTable {
    public:
        //provided funcitons
        unsigned long prime_below(long);
        void setPrimes(std::vector<long> &);

        //Own functions ***************************************************************************************************************

        //constructors
        HashTable(size_t size = 101);
        ~HashTable();

        //other functions
        bool contains(const T &x) const;
        bool insert(const T & x);
        bool insert (T &&x);
        bool remove(const T &x);
        void clear();
        bool load(const char *filename);
        void dump() const;
        bool write_to_file(const char *filename) const;

        size_t sizeOf();
        void handleChoice(HashTable<T> hashTable, char choice);
        void menu();
        int defaultCap();


    private:
        //proivided
        static const unsigned int default_capacity = 101;
        static const unsigned int max_prime = 1301081;

        //own funcitons
        void makeEmpty();
        void rehash();
        size_t myhash(const T &x) const;
        unsigned long prime_below (unsigned long);  //definition given
        void setPrimes(vector<unsigned long>&);      //definition given

        //variables
        vector<list<T>> hashTable;
        size_t theSize;

};

// include the implementation file here
#include "hashtable.hpp"

} // end of namespace COP4530// 


