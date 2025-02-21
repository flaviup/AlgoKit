
#ifndef __TRIE_H__
#define __TRIE_H__

#include <string>

const int ALPHABET_SIZE = 26;

class Trie {
	
	struct TrieNode {
		int words;
		int prefixes;
		TrieNode* edges[ALPHABET_SIZE];
		
		TrieNode(): words(0), prefixes(0) {
			memset(edges, 0, sizeof(edges));
		}
	};

public:

	Trie() {};

	inline void AddWord(const std::string& word) {
		AddWord(root, word);
	}

	inline bool RemoveWord(const std::string& word) {
		return RemoveWord(root, word);
	}

	inline int CountPrefixes(const std::string& prefix) {
		return CountPrefixes(root, prefix);
	}

	inline int CountWords(const std::string& word) {
		return CountWords(root, word);
	}

	inline int CountWords(const std::string& word, int missingLetters) {
		return CountWords(root, word, missingLetters);
	}

private:
	Trie(const Trie&);
	Trie& operator= (const Trie&);
	
	TrieNode root;

	static void AddWord(TrieNode& node, const std::string& word) {
		if (word.empty()) {
			++node.words;
		} else {
			++node.prefixes;
			char k = word[0] - 'a';
        
			if(node.edges[k] == NULL) {
				node.edges[k] = new TrieNode;
			}
			AddWord(*node.edges[k], word.substr(1));
		}
	}

	static bool RemoveWord(TrieNode& node, const std::string& word) {
		if (word.empty()) {
			if (node.words > 0) {
				--node.words;
			} else {
				return false;
			}
		} else {
			if (node.prefixes < 1) {
				return false;
			}
			char k = word[0] - 'a';
        
			if (node.edges[k] == NULL) {
				return false;
			}
			
			if (RemoveWord(*node.edges[k], word.substr(1))) {
				--node.prefixes;

				if (node.edges[k]->words == 0 && node.edges[k]->prefixes == 0) {
					delete node.edges[k];
					node.edges[k] = NULL;
				}
			} else {
				return false;
			}
		}
		return true;
	}

	static int CountPrefixes(const TrieNode& node, const std::string& prefix) {
		if (prefix.empty()) {
			return node.prefixes;
		}
		char k = prefix[0] - 'a';
		
		if (node.edges[k] == NULL) {
			return 0;
		}
        return CountPrefixes(*node.edges[k], prefix.substr(0));
	}

	static int CountWords(const TrieNode& node, const std::string& word) {
		if (word.empty()) {
			return node.words;
		}
		char k = word[0] - 'a';
		
		if (node.edges[k] == NULL) {
			return 0;
		}
        return CountWords(*node.edges[k], word.substr(0));
	}

	static int CountWords(const TrieNode& node, const std::string& word, int missingLetters) {
		if (word.empty()) {
			return node.words;
		}
		char k = word[0] - 'a';
		
		if (node.edges[k] == NULL && missingLetters < 1) {
			return 0;
		} else if (node.edges[k] == NULL) {
			return CountWords(node, word, missingLetters - 1);
		}
        int count = CountWords(node, word, missingLetters - 1);
		count += CountWords(*node.edges[k], word.substr(0), missingLetters);
		return count;
	}

};


#endif // __TRIE_H__
