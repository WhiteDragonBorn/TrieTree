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

bool isLeafNode(TrieNode* root)
{
  return root->isEndOfWord != false;
}

void display(TrieNode* root, char str[], int level)
{
  // If node is leaf node, it indicates end
  // of string, so a null character is added
  // and string is displayed
  if (isLeafNode(root))
  {
    str[level] = '\0';
    cout << str << endl;
  }

  int i;
  for (i = 0; i < ALPHABET_SIZE; i++)
  {
    // if NON NULL child is found
    // add parent key to str and
    // call the display function recursively
    // for child node
    if (root->children[i])
    {
      str[level] = i + 'a';
      display(root->children[i], str, level + 1);
    }
  }
}

int main() {
  ifstream fin("input.txt");

  //string test = "catt";

  TrieNode* root = initNode();
  string temp = "";

  while (fin) {
    char c = fin.get();
    if (c == ' ') {
      insert(root, temp);
      temp = "";
    }
    else {
      temp = c + temp;
    }
  }
  int level = 0;
  char str[20];

  // Displaying content of Trie
  cout << "Content of Trie: " << endl;
  display(root, str, level);

  //insert(root, test);

  fin.close();
}
