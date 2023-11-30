#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
  TrieNode* children[ALPHABET_SIZE];
  bool isEndOfWord;
};

TrieNode* initNode() {
  TrieNode* temp = new TrieNode;
  temp->isEndOfWord = false;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    temp->children[i] = nullptr;
  }
  return temp;
}

void insert(TrieNode* root, string key) {
  TrieNode* pCrawl = root;

  for (int i = 0; i < key.length(); i++) {
    int index = key[i] - 'a';
    if (!pCrawl->children[index]) pCrawl->children[index] = initNode();

    pCrawl = pCrawl->children[index];
  }

  pCrawl->isEndOfWord = true;
}

bool isLeafNode(TrieNode* root) { return root->isEndOfWord != false; }

TrieNode* moveRoot(TrieNode* root, char str[]) {
  TrieNode* toReturn = root;

  for (size_t i = 0; i < strlen(str); i++) {
    toReturn = toReturn->children[str[i] - 'a'];
  }
  return toReturn;
}

void display(TrieNode* root, char str[], int level) {
  if (isLeafNode(root)) {
    str[level] = '\0';
    for (int i = strlen(str) - 1; i >= 0; i--) {
      cout << str[i];
    }
    cout << endl;
  }

  int i;
  for (i = 0; i < ALPHABET_SIZE; i++) {
    if (root->children[i]) {
      str[level] = i + 'a';
      display(root->children[i], str, level + 1);
    }
  }
}

int main() {
  ifstream fin("input.txt");

  TrieNode* root = initNode();
  string temp = "";

  while (fin) {
    char c = fin.get();
    if (c == ' ') {
      insert(root, temp);
      temp = "";
    } else {
      temp = c + temp;
    }
  }

  char str[15];

  cout << "Enter the end of the word: ";
  cin >> str;

  std::reverse(str, str + strlen(str));

  int level = strlen(str);
  TrieNode* temp_tr = moveRoot(root, str); // куда деть?

  cout << "Content of Trie: " << endl;
  display(temp_tr, str, level);

  fin.close();
}
