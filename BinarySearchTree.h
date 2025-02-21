
#ifndef __BINARYSEARCHTREE_H__
#define __BINARYSEARCHTREE_H__

#include <cassert>
#include <vector>

// Tips: use randomized BSTs (whenever inserting a node, insert it with some probability 
//       at the root of the current subtree on the path of insertion)
// Some balanced BSTs: RedBlack Trees, AVL Trees
// Treaps: BST + Heap of randomlygenerated priorities

namespace BSTlr { // Binary Search Tree - parent, left, right fields

	template <class T>
	class BST {
	
	public:
	
		typedef T type;

		BST(): root(NULL), size(0) {}
	
		BST(const BST& bst): root(NULL), size(0) {
			deepcopy(bst);
		}

		BST& operator= (const BST& bst) {
			if (this != &bst) {
				clear();
				deepcopy(bst);
			}
			return *this;
		}

		~BST() { 
			clear();
		}
	
		bool Insert(const type& data) {
			if (insert(data)) {
				++size;
				return true;
			}
			return false;
		}

		inline bool Find(const type& data) const {
			return find(data);
		}

		bool Delete(const type& data) {
			if (remove(data)) {
				--size;
				return true;
			}
			return false;
		}

		inline bool IsEmpty() const { return (root == NULL); }

		inline int Size() const { return size; }

		inline void Clear() { clear(); size = 0; }

		std::vector<type> Sort() const {
			std::vector<type> vt(size);

			if (!IsEmpty()) {				
				inorder(vt);
			}
			return vt;
		}

		void traverse() const {
			iterativeTraverse3in1(Inorder);
		}
	
	private:
		enum {
			LEFT = 0,
			RIGHT,
			LINKS
		};

		struct Node {
			type data;
			Node* link[LINKS];
			Node(type d = 0): data(d) { link[LEFT] = link[RIGHT] = NULL; }
			~Node() {
				/*if (link[LEFT] != NULL) {
					delete link[LEFT];
				}

				if (link[RIGHT] != NULL) {
					delete link[RIGHT];
				}*/
				link[LEFT] = link[RIGHT] = NULL;
			};
		};
		Node* root;
		int size;

		struct Iterator {
			// Solutions: - use a stack (saving the path(i.e. list of parents) to the current node)
			//            - use a parent field in the tree nodes
			//            - use threaded tree nodes: every NULL leaf is replaced by a pointer to the successor/predecessor 
		    //                                       and every node has a flag to indicate if it's a threaded node 
			//                                       (right-threaded trees are most common)
		};

		static bool inline eq(const T& d1, const T& d2) {
			return (!(d2 < d1) && !(d1 < d2));
		}

		inline bool find(const T& data) const {
			return iterativeFind(data);
		}

		inline bool insert(const T& data) {
			return iterativeInsert(data);
		}
		
		inline bool remove(const T& data) {
			return iterativeRemove(data);
		}

		inline void inorder(std::vector<T>& vt) const {
			iterativeTraverse3in1(vt, Inorder);
		}

		inline void preorder(std::vector<T>& vt) const {
			iterativeTraverse3in1(vt, Preorder);
		}

		inline void postorder(std::vector<T>& vt) const {
			iterativeTraverse3in1(vt, Postorder);
		}

		inline void clear() {
			iterativeClear();
		}

		bool iterativeFind(const T& data) const {
			const Node* it = root;
			
			while (it != NULL) {
				if (eq(it->data, data)) {
					return true;
				} else {
					it = it->link[(it->data < data)? RIGHT : LEFT];
				}
			}
			return false;
		}

		bool recursiveFind(const T& data) const {
			return _find_r(data, root);
		}

		static bool _find_r(const T& data, const Node* node) {
			if (node == NULL) {
				return false;
			}

			if (eq(node->data, data)) {
				return true;
			}
			return _find_r(node->link[(node->data < data)? RIGHT : LEFT]);
		}
		
		bool iterativeInsert(const T& data) {
			if (root == NULL) {
				root = new Node(data);
			} else {
				Node* it = root;
				int dir;
				
				while (it) {
					dir = (it->data < data)? RIGHT : LEFT;
					
					if (eq(it->data, data)) {
						return false;
					} else if (it->link[dir] == NULL) {
						it->link[dir] = new Node(data);
						break;
					}
					it = it->link[dir];
				}
			}
			return true;
		}

		bool recursiveInsert(const T& data) {
			bool success = false;
			root = _insert_r(data, root, success);
			return success;
		}

		Node* _insert_r(const T& data, Node* node, bool& success) {
			if (node == NULL) {
				node = new Node(data);
				success = true;
			} else if (!eq(node->data, data)) {
				int dir = (node->data < data)? RIGHT : LEFT;
				node->link[dir] = _insert_r(data, node->link[dir], success);
			}
			return node;
		}

		bool iterativeRemove(const T& data) {
			if (root != NULL) {
				Node head(0);
				Node* it = &head;
				Node* p = NULL;
				Node* f = NULL;
				int dir = RIGHT;
				it->link[RIGHT] = root;
				
				while (it->link[dir] != NULL) {
					p = it;
					it = it->link[dir];
					dir = (data < it->data)? LEFT : RIGHT; // it->data <= data
					
					if (eq(it->data, data)) {
						f = it;
					}
				}
				
				if (f != NULL) {
					f->data = it->data;
					p->link[(p->link[RIGHT] == it)? RIGHT : LEFT] = it->link[(it->link[LEFT] == NULL)? RIGHT : LEFT];
					delete it;
				}
				root = head.link[RIGHT];
			}
			return true;
		}

		bool recursiveRemove(const T& data) {
			bool success = false;
			root = _remove_r(data, root, success);
			return success;
		}

		Node* _remove_r(const T& data, Node* node, bool& success) {
			if (node == NULL) {
				success = true;
			} else {
				int dir;
				
				if (eq(node->data, data)) {
					if (node->link[LEFT] != NULL && node->link[RIGHT] != NULL) {
						Node* succ = node->link[RIGHT];
						
						while (succ->link[LEFT] != NULL) {
							succ = succ->link[LEFT];
						}
						data = succ->data;
						node->data = data;
					}
					else {
						Node* save = node;
						node = node->link[(node->link[LEFT] == NULL)? RIGHT : LEFT];
						delete save;
						success = true;
						return node;
					}
				}
				dir = (data < node->data)? LEFT : RIGHT;
				node->link[dir] = _remove_r(data, node->link[dir], success);
			}
			return node;
		}

		void iterativeClear() {
			Node* it = root;
			Node* save = NULL;
			
			while (it != NULL) {
				if (it->link[LEFT] != NULL) {
					/* Right rotation */
					save = it->link[LEFT];
					it->link[LEFT] = save->link[RIGHT];
					save->link[RIGHT] = it;
				} else {
					save = it->link[RIGHT];
					delete it;
				}
				it = save;
			}
		}

		void recursiveClear() {
			_clear_r(root);
			root = NULL;
		}

		void _clear_r(Node* node) {
			if (node != NULL) {
				_clear_r(node->link[LEFT]);
				_clear_r(node->link[RIGHT]);
				delete node;
			}
		}

		enum TraverseType {
			Inorder = 0,
			Preorder,
			Postorder
		};

		void iterativeTraverse3in1(std::vector<type>& vt, TraverseType traverse) const {
			int index = 0;
			Node** stack = new Node*[size];
			unsigned char* bitstack = new unsigned char[(size >> 3) + 1];
			memset(bitstack, 0, (size >> 3) + 1);
			int top = 0;
			stack[top++] = root;
			const unsigned char bits[][3] = {{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};
			
			while (top > 0) {
				Node* n = stack[--top];

				if ((bitstack[top >> 3] >> (top & 7)) & 1) {
					vt[index++] = n->data;
				} else {
					Node* a[][3] = {{n->link[RIGHT], n, n->link[LEFT]}, 
								    {n->link[RIGHT], n->link[LEFT], n}, 
								    {n, n->link[RIGHT], n->link[LEFT]}
								   };

					if (a[traverse][0]) {
						if (bits[traverse][0]) {
							bitstack[top >> 3] |= (bits[traverse][0] << (top & 7));
						} else {
							bitstack[top >> 3] &= ~(!bits[traverse][0] << (top & 7));
						}
						stack[top++] = a[traverse][0];
					}

					if (a[traverse][1]) {
						if (bits[traverse][1]) {
							bitstack[top >> 3] |= (bits[traverse][1] << (top & 7));
						} else {
							bitstack[top >> 3] &= ~(!bits[traverse][1] << (top & 7));
						}
						stack[top++] = a[traverse][1];
					}

					if (a[traverse][2]) {
						if (bits[traverse][2]) {
							bitstack[top >> 3] |= (bits[traverse][2] << (top & 7));
						} else {
							bitstack[top >> 3] &= ~(!bits[traverse][2] << (top & 7));
						}
						stack[top++] = a[traverse][2];
					}
				}
			}
			delete stack;
			delete bitstack;
		}

		void iterativeInorder(std::vector<type>& vt) const {
			int index = 0;
			Node** nodes = new Node*[size];
			int top = 0;
			Node* curr = root;
			
			while (true) {
				if (curr) {
					nodeStack[top++] = curr;
					curr = curr->link[LEFT];
					continue;
				}   
				
				if (top == 0) {
					break;
				}   
				curr = nodeStack[--top];
				vt[index++] = curr->data;
				curr = curr->link[RIGHT];
			}
			delete nodeStack;
		}

		void iterativePreorder(std::vector<type>& vt) const { // DFS
			int index = 0;
			Node** nodes = new Node*[size];
			int top = 0;
			nodes[top++] = root;
			Node* currentNode = NULL;
			
			while (top > 0) {
				currentNode = nodes[--top];
                Node* right = currentNode->link[RIGHT];
                
				if (right != NULL) {
					nodes[top++] = right;
                }
                Node* left = currentNode->link[LEFT];
                
				if (left != null) {
					nodes[top++] = left;
                }
                vt[index++] = currentNode->data;
			}
			delete nodes;
		}

		void iterativePostorder(std::vector<type>& vt) const {
			if (root == NULL) {
				return vt;
			}
			int index = 0;
			Node** nodeStack = new Node*[size];
			Node* curr = root;
			int top = 0;
			
			while (true) {
				if (curr) {
					if (curr->right) {
						nodeStack[top++] = curr->link[RIGHT];
                    }
                    nodeStack[top++] = curr;
                    cur = curr->link[LEFT];
                    continue;
				}
 
                if (top == 0) {
					break;
                }
                curr = nodeStack[--top];
 
                if (curr->link[RIGHT] && top > 0 && curr->link[RIGHT] == nodeStack[top - 1]) {
                    nodeStack[top - 1] = curr;
					curr = curr->link[RIGHT];
                } else {
					vt[index++] = cur->data;
					curr = NULL;
                }
			}
			delete nodeStack;
		}

		inline void recursiveInorder(std::vector<type>& vt) const {
			_inorder_r(root, vt, 0);
		}

		void _inorder_r(const Node* node, std::vector<type>& vt, int& index) const {
			if (node != NULL) {
				_inorder_r(node->link[LEFT], vt, index);
				vt[index++] = node->data;
				_inorder_r(node->link[RIGHT], vt, index);
			}
		}

		inline void recursivePreorder(std::vector<type>& vt) const {
			_preorder_r(root, vt, 0);
		}
		
		void _preorder_r(const Node* node, std::vector<type>& vt, int& index) const {
			if (node != NULL) {
				vt[index++] = node->data;
				_preorder_r(node->link[LEFT], vt, index);
				_preorder_r(node->link[RIGHT], vt, index);
			}
		}

		inline void recursivePostorder(std::vector<type>& vt) const {
			_postorder_r(root, vt, 0);
		}

		void _postorder_r(const Node* node, std::vector<type>& vt, int& index) const {
			if (node != NULL) {
				_postorder_r(node->link[LEFT], vt, index);
				_postorder_r(node->link[RIGHT], vt, index);
				vt[index++] = node->data;
			}
		}

		void tree2List() const {
		}

		void deepcopy(const BST& bst) {
		}

		// Tree to Doubly Linked List
		/*
		 helper function -- given two list nodes, join them
		 together so the second immediately follow the first.
		 Sets the .next of the first and the .previous of the second.
		*/
		static inline void join(Node* a, Node* b) {
			a->links[RIGHT] = b;
			b->links[LEFT] = a;
		}

		/*
		 helper function -- given two circular doubly linked
		 lists, append them and return the new list.
		*/
		static inline Node* append(Node* a, Node* b) {
			Node* aLast = NULL;
			Node* bLast = NULL;
    
			if (a == NULL) return b;
			if (b == NULL) return a;
    
			aLast = a->links[LEFT];
			bLast = b->links[LEFT];
    
			join(aLast, b);
			join(bLast, a);
    
			return a;
		}

		/*
		 --Recursion--
		 Given an ordered binary tree, recursively change it into
		 a circular doubly linked list which is returned.
		*/
		static Node* treeToList(Node* root) {
			Node* aList
			Node* bList;
    
			if (root == NULL) {
				return NULL;
			}

			/* recursively solve subtrees */
			aList = treeToList(root->links[LEFT]);
			bList = treeToList(root->links[RIGHT]);
    
			/* Make a length-1 list ouf of the root */
			root->links[LEFT] = root;
			root->links[RIGHT] = root;

			/* Append everything together in sorted order */
			aList = append(aList, root);
			aList = append(aList, bList);
    
			return aList;
		}

	};

}

namespace BSTplr { // Binary Search Tree - parent, left, right fields

	template <class T>
	class BST {

	public:
	
		typedef T type;

		BST(): root(NULL), size(0) {}
	
		BST(const BST& bst): root(NULL), size(0) {
			deepcopy(bst);
		}

		BST& operator= (const BST& bst) {
			if (this != &bst) {
				clear();
				deepcopy(bst);
			}
			return *this;
		}

		~BST() { 
			clear();
		}
	
		void Insert(const type& data) {
			if (root == NULL) {
				root = new Node(data, NULL);
				++size;
			} else {
				insert(root, data);
			}
		}

		inline bool Find(const type& data) const {
			return (find(root, data) != NULL);
		}

		void Delete(const type& data) {
			if (root != NULL) {
				Node* node = find(root, data);
			
				if (root == node) {
					clear();
				} else {
					deleteNode(node);
				}
			}
		}

		inline bool IsEmpty() const { return (root == NULL); }

		inline int Size() const { return size; }

		inline void Clear() { clear(); }

		std::vector<type> Sort() const {
			std::vector<type> vt(size);

			if (!IsEmpty()) {
				//int pos = 0;
				//inorder(root, vt, pos);
				inorder2(vt);
			}
			return vt;
		}

	private:
		struct Node {
			unsigned char visited; // for tree traversal
			type data;
			Node* left;
			Node* right;
			Node* parent;
			Node(type d, Node* p): visited(false), data(d), left(NULL), right(NULL), parent(p) {}
			~Node() {
				if (left != NULL) {
					delete left;
				}

				if (right != NULL) {
					delete right;
				}
				left = right = NULL;
				parent = NULL;
			};
		};
		Node* root;
		int size;

		Node* insert(Node* node, const type& data) {
			Node* nd = node;
			Node* last = nd;
			assert(node != NULL);

			while (nd != NULL) {
				last = nd;

				if (data < nd->data) {
					nd = nd->left;
				} else if (nd->data < data) {
					nd = nd->right;
				} else {
					break;
				}
			}

			if (nd == NULL) {
				assert(last != NULL);
				nd = new Node(data, last);
			
				if (data < last->data) {
					last->left = nd;
				} else if (last->data < data) {
					last->right = nd;
				}
				++size;
			}
			return nd;
		}

		Node* find(Node* node, const type& data) const {
			Node* nd = node;

			while (nd != NULL) {
				if (data < nd->data) {
					nd = nd->left;
				} else if (nd->data < data) {
					nd = nd->right;
				} else {
					break;
				}
			}
			return nd;
		}

		Node* findMin(Node* node) const {
			Node* nd = node;
		
			if (nd == NULL) {
				return nd;
			}

			while (nd->left != NULL) {
				nd = nd->left;
			}
			return nd;
		}

		void deleteNode(Node*& node) {
			assert(node != NULL);
			assert(node->parent != NULL); // node != root
			Node*& parentChild = ((node->parent->left == node)? node->parent->left : node->parent->right);

			if (node->left == NULL || node->right == NULL) {
				if (node->left == NULL) {
					parentChild = node->right;
				} else if (node->right == NULL) {
					parentChild = node->left;
				}
				Node* parent = node->parent;
				node->right = node->left = node->parent = NULL;
				delete node;
				node = (parentChild == NULL)? parent : parentChild;
				--size;
			} else {
				Node* minNode = findMin(node);
				assert(minNode != NULL);
				assert(minNode != node);
				node->data = minNode->data;
				deleteNode(minNode);
			}
		}

		void clear() {
			if (root == NULL) {
				size = 0;
				return;
			}
			Node** stack = new Node*[size];
			Node** nodes = new Node*[size];
			memset(stack, 0, size * sizeof(Node*));
			memset(nodes, 0, size * sizeof(Node*));
			int i = 0, st = 0;
			stack[st++] = root;

			while (st > 0) {
				Node* p = stack[--st];
				assert (p != NULL);
				nodes[i++] = p;

				if (p->left != NULL) { 
					stack[st++] = p->left;
				}

				if (p->right != NULL) { 
					stack[st++] = p->right;
				}
			}

			for (--i; i > -1; --i) {
				assert(nodes[i] != NULL);
				nodes[i]->left = nodes[i]->right = NULL;
				delete nodes[i];
			}
			root = NULL;
			size = 0;
			delete [] nodes;
			delete [] stack;
		}

		void inorder(const Node* node, std::vector<type>& vt, int& pos) const {
			assert(node != NULL);
		
			if (node->left != NULL) {
				inorder(node->left, vt, pos);
			}
			vt[pos++]= node->data;

			if (node->right != NULL) {
				inorder(node->right, vt, pos);
			}
		}

		// implement inorder without flags and without a stack

		void inorder2(std::vector<type>& vt) const {
			assert(root != NULL);
			Node* node = root;
			int i = 0;

			while (node != NULL) {
				if (node->visited == 2) {
					node->visited = 0;
					node = node->parent;
					continue;
				}

				if (node->visited == 0 && node->left != NULL) {
					node->visited = 1;
					node = node->left;
					continue;
				}
				vt[i++] = node->data;
			
				if (node->right != NULL) {
					node->visited = 2;
					node = node->right;
				} else {
					node->visited = 0;
					node = node->parent;
				}
			}
			assert (i == int(vt.size()));
		}

		void deepcopy(const BST& bst) {
			if (bst.size == 0 || bst.root == NULL) {
				return;
			}
			assert(root == NULL);
			assert(size == 0);
			assert(bst.root != NULL);
			assert(bst.root->parent == NULL);
			assert(bst.size > 0);
			Node* node = bst.root;
			Node* parent = NULL;

			while (node != NULL) {
				if (node->visited == 2) {
					node->visited = 0;
					node = node->parent;
					parent = parent->parent;
					continue;
				}

				if (node->visited == 0) {
					Node* nd = new Node(node->data, parent);

					if (parent != NULL) {
						assert(node->parent != NULL);
						Node*& parentChild = ((node->parent->left == node)? parent->left : parent->right);
						parentChild = nd;
					}
					++size;
					parent = nd;

					if (root == NULL) {
						root = nd;
					}
				}

				if (node->visited == 0 && node->left != NULL) {
					node->visited = 1;
					node = node->left;
					continue;
				}
			
				if (node->right != NULL) {
					node->visited = 2;
					node = node->right;
				} else {
					node->visited = 0;
					node = node->parent;
					parent = parent->parent;
				}
			}
			assert(size == bst.size);
		}
	};

}

#endif // __BINARYSEARCHTREE_H__
