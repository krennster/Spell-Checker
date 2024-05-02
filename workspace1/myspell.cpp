#include "hashtable.h"
#include <iostream>
#include <string>
#include <limits>
#include <cstring>

using namespace std;
using namespace cop4530;

//menu
void menu() {
  cout << "\n\n";
  cout << "l - Load Dictionary From File" << endl;
  cout << "a - Add Word" << endl;
  cout << "r - Remove Word" << endl;
  cout << "c - Clear HashTable" << endl;
  cout << "f - Find Word" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

//handle choice
void handleChoice(HashTable<string> &hashTable, char choice) {
  switch(choice) {
    case 'l': {
      cout << "Enter file name." << endl;
      string filename;

      getline(cin, filename);
      hashTable.load(filename.c_str());

      break;
	}

    case 'a': {
      cout << "Enter word to be inserted." << endl;
      string word;

      getline(cin, word);

      if (hashTable.insert(word)) {
        cout << "Success." << endl;
      }

      else {
        cout << "Word is already in the hash table." << endl;
      }

      break;
	}

    case 'r': {
      cout << "Enter word to be removed." << endl;
      string word2;
      getline(cin, word2);

      if (hashTable.remove(word2)) { 
        cout << "Word: " << word2 << " has been removed" << endl;
      }

      else {
        cout << "This word does not exist in the hash table." << endl;
      }

      break;
	}

    case 'c': {
      hashTable.clear();
      break;
    }

    case 'f': {
      cout << "Enter word." << endl;
      string word3;
      cin >> word3;

      if (hashTable.contains(word3)) {
        cout << "The word was found." << endl;
      }

      else {
        cout << "The word was not found." << endl;
      }

      break;

	}

    case 'd': {
      hashTable.dump();
      break;
	}

    case 's': {
      cout << "Hash Table size: " << hashTable.sizeOf() << endl;
      break;
	}

    case 'w': {
      cout << "Enter file name." << endl;
      string filename2;

      getline(cin, filename2);
      hashTable.write_to_file(filename2.c_str());
      cout << "Written to file." << endl;

      break;
	}

    case 'x': {
      cout << "Exiting Program" << endl;
      break;
	}
  }
}

int main(int argc, char* argv[]) {
	//if (argc == 4) {
    const char *dictionary = argv[1];
    const char *test = argv[2];
    const char *output = argv[3];

    HashTable<string> spellHash();

    spellHash.load(dictionary);
    cout << "loaded." << endl;
  //}
  
  // else {
  //   cout << "Preferred hash capacity" << endl;
  //   int cap;
  //   cin >> cap;

  //   HashTable<string> hash1(cap);
  //   char choice;

  //   do {
  //     menu();
  //     cin >> choice;

  //     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer

  //     handleChoice(hash1, choice);
  //   } while (choice != 'x' );

  //   return 0;
  // }

}