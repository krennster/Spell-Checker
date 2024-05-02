#include "hashtable.h"
#include <iostream>
#include <string>
#include <limits>
#include <cstring>
#include <cctype>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <fstream>

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

//vector sort
bool candSort(const pair<string, int> &p1, const pair<string, int> &p2) { return p2.second < p1.second; }


int main(int argc, char* argv[]) {
  
  //if there are 4 commandline arguments run this code
  if (argc == 4) {
    const char* dictionary = argv[1];
    const char* testerFile = argv[2];
    const char* out = argv[3];

    string albet = "abcdefghijklmnopqrstuvwxyz";

    //intialize wordrank
    map<string, int> wordRank;
    vector<pair<string, int>> topCand;
    const char* wrFile = "wordrank.txt";
    ifstream rankFile(wrFile);

    string rankLine;
    while (getline(rankFile, rankLine)) {
      istringstream iss2(rankLine);
      string rankWord;
      int rank;

      if (iss2 >> rankWord >> rank) {
        wordRank[rankWord] = rank;
      }
    }
    rankFile.close();


    //initialize and load
    HashTable<string> spellHash(101);
    spellHash.load(dictionary);
    cout << "Loaded." << endl;

    ifstream inputFile(testerFile);
    ofstream outputFile(out, ios::app);
    //outputFile.open();


    string line;
    string currWord;
    int wordPosition = 0;
    string tempWord = "";
    string original = "";
    queue<string> maybeWords;

    // go through each line in input
    while (getline(inputFile, line)) {
        istringstream iss(line);

      while (iss >> currWord) {
        //clear
        if (!topCand.empty()) { topCand.clear(); }
          while (maybeWords.size() > 0) {
            maybeWords.pop();
          }

          //set original word for find
          original = currWord;

          //remove punct
          currWord.erase(remove_if(currWord.begin(), currWord.end(), ::ispunct), currWord.end());
          for (auto &x : currWord) { x = tolower(x); }

        if (!spellHash.contains(currWord)) {
          size_t wordPos = line.find(original);     //was originally (original)     bottom of code
          
          string newLine = line;

          //set word position
          for (int k = wordPos; k < wordPos + original.length(); k++){ 
            newLine[k] = toupper(newLine[k]);
          }

          cout << newLine << endl;
          cout << "The invalid word is: " << currWord << endl;

          //loop through the invalid word by character... changing the current character
          for (int character = 0; character < currWord.length(); ++character) {
            for (int i = 0; i < albet.length(); i++) {
              tempWord = currWord;
              tempWord[character] = albet[i];

              //add candidates to data structure 
              if (spellHash.contains(tempWord)) {
                //check if word is in wordrank
                if (wordRank.find(tempWord) != wordRank.end()) {
                  auto wordIt = wordRank.find(tempWord);
                  topCand.push_back(make_pair(wordIt->first, wordIt->second));
                }
                //add to maybe list if the word is not in word rank
                else {
                  maybeWords.push(tempWord);
                }
              }
            }
          }

          if (topCand.size() > 0) {
            //sort vector pair by value
            sort(topCand.begin(), topCand.end(), candSort);

            //see if there are space for maybe words
            while (topCand.size() < 10 && maybeWords.size() > 0) {
              topCand.push_back(make_pair(maybeWords.front(), 9999));
              maybeWords.pop();
            }

            //print candidates
            cout << "candidate list: " << endl;
            int candCheck = topCand.size();
            //print top ten candidates
            for (int j = 0; j < 10; j++) {

              cout << j << ") " << topCand[j].first << endl;
              candCheck--;

              if (candCheck == 0) { break; }

            }
            cout << "10) no change" << endl;


            //handle replacement
            int candChoice;
            cout << "Which word would you like to use for the replacement? (choose number)" << endl;
            cin >> candChoice;
            if (candChoice == 10) { break; } 
            else if (candChoice == 99) { abort(); }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (isupper(original[0])) {   //check if the original word is capital, if so make curr word capital
              topCand[candChoice].first[0] = toupper(topCand[candChoice].first[0]);
            }
            line.replace(wordPos, currWord.length(),topCand[candChoice].first );    //where wordPos was 
            cout << endl;
          }
        } 
      }
      //clear
      if (!topCand.empty()) { topCand.clear(); }
      if(!maybeWords.empty()) {
        for (int z = 0; z < maybeWords.size(); z++) {maybeWords.pop();}
      }
      outputFile << line << endl;
      cout << "***********************************************************************" << endl;
    }
    spellHash.clear();
    outputFile.close();
  }

  else {

    cout << "Preferred hash capacity" << endl;
    int cap;
    cin >> cap;

    HashTable<string> hash1(cap);
    char choice;

      do {
        menu();
        cin >> choice;

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer

        handleChoice(hash1, choice);
      } while (choice != 'x' );

    return 0;
  }
}
