
// SinglyLinked List
// DoublyLinked List
// XorList
// Queue
// Stack
// Deque
// SkipList

#ifndef __LISTS_H__
#define __LISTS_H__

#include <cassert>
#include <memory> // for NULL definition

namespace SinglyLinkedList {
	
	struct Node {
		int data;
		Node* next;
	};

	Node* MakeNode(int data) {
		Node* node = new Node;
		node->data = data;
		node->next = NULL;
		return node;
	}

	void Push(Node*& head, Node* node) {
		assert(node != NULL);
		node->next = head;
		head = node;
	}

	int Length(const Node* head) {
		int len = 0;
		
		while (head) {
			++len;
			head = head->next;
		}
		return len;
	}

	int Count(const Node* head, int n) {
		int c = 0;
		
		while (head) {
			c += (head->data == n);
			head = head->next;
		}
		return c;
	}

	int GetNth(const Node* head, int n) {
		assert(n >= 0);
		
		while (head && n) {
			head = head->next;
			--n;
		}
		
		if (head) {
			return head->data;
		}
		return -1;
	}

	void DeleteList(Node*& head) {
		Node* node = head;
		
		while (head) {
			head = head->next;
			delete node;
			node = head;
		}
	}

	int Pop(Node*& head) {
		int data = -1;
		
		if (head) {
			Node* temp = head;
			data = head->data;
			head = head->next;
			delete temp;
		}
		return data;
	}

	void InsertNth(Node*& head, int n, int value) {
		assert(n >= 0);
		Node* node = MakeNode(value);

		if (n == 0) {
			node->next = head;
			head = node;
			return;
		}
		
		if (head == NULL) {
			if (n > 0) {
				delete node;
				return;
			}
			head = node;
		} else {
			if (n == 0) {
				node->next = head;
				head = node;
				return;
			} else {
				Node* next = head;
				--n;
			
				while (next && n) {
					--n;
					next = next->next;
				}
			
				if (next) {
					node->next = next->next;
					next->next = node;
				} else {
					delete node;
				}
			}
		}
	}

	Node* Duplicate(const Node* list) {
		Node* head = NULL;
		Node* tail = NULL;
		
		while (list) {
			Node* node = MakeNode(list->data);

			if (head == NULL) {
				head = node;
			} else {
				tail->next = node;
			}
			tail = node;
			list = list->next;
		}
		return head;
	}

	Node* GetFirstOf(Node* head, int value) {
		while (head && ((head->data < value) || (value < head->data))) {
			head = head->next;
		}
		return head;
	}
	
	Node* GetLastOf(Node* head, int value) {
		Node* node = NULL;
		
		while (head) {
			if (!(value < head->data) && !(head->data < value)) {
				node = head;
			}
			head = head->next;
		}
		return node;
	}

	Node* GetTail(Node* head) {
		if (head == NULL) {
			return NULL;
		}

		while (head->next) {
			head = head->next;
		}
		return head;
	}

	Node* GetPrev(Node* head, Node* node) {
		if (head == NULL || node == head) {
			return NULL;
		}
		
		while (head->next && head->next != node) {
			head = head->next;
		}

		if (head->next == node) {
			return head;
		}
		return NULL;
	}

	void RemoveNotLast(Node* node) {
		assert(node->next != NULL);
		node->data = node->next->data;
		Node* temp = node->next;
		node->next = node->next->next;
		delete temp;
	}

	bool IsCircular(const Node* head) {
		if (head != NULL) {
			Node* node2 = head->next;
			
			if (node2) {
				node2 = node2->next;
			} else {
				return false;
			}

			while (head && node2 && (head != node2)) {
				node2 = node2->next;
				
				if (node2) {
					node2 = node2->next;
				} else {
					return false;
				}
				head = head->next;
			}
			return (head != NULL) && (head == node2);
		}
		return false;
	}

	// PreCondition: the list is sorted
	void SortedInsert(Node*& head, Node* newNode) {
		assert(newNode != NULL);
		assert(head != newNode);

		if (head == NULL) {
			head = newNode;
		} else {
			if (newNode->data < head->data) {
				newNode->next = head;
				head = newNode;
			} else {
				Node* node = head;
				Node* prev = NULL;

				while (node != NULL && !(newNode->data < node->data)) {
					prev = node;
					node = node->next;
				}

				if (!(newNode->data < prev->data)) {
					newNode->next = prev->next;
					prev->next = newNode;
				}
			}
		}
	}

	void InsertSort(Node*& head) {
		if (head == NULL) {
			return;
		}
		Node* node = head->next;
		Node* p = NULL;
		head->next = NULL;
		
		while (node) {
			p = node->next;
			node->next = NULL;
			SortedInsert(head, node);
			node = p;
		}
	}

	// PreCondition: the list is sorted
	void RemoveDuplicates(Node* head) {
		if (head == NULL) {
			return;
		}
		Node* node = head;

		while (node->next) {
			while (node->next && ((node->data < node->next->data) || (node->next->data < node->data))) {
				node = node->next;
			}

			while (node->next && !(node->data < node->next->data) && !(node->next->data < node->data)) {
				Node* p = node->next;
				node->next = node->next->next;
				delete p;
			}
		}
	}

	void MoveNode(Node*& dest, Node*& src) {
		assert(dest != src);

		if (src == NULL) {
			return;
		}

		if (dest == NULL) {
			dest = src;
			src = src->next;
			dest->next = NULL;
			return;
		}
		Node* temp = dest;
		dest = src;
		src = src->next;
		dest->next = temp;
	}

	void Append(Node*& a, Node*& b) {
		assert(a != b);

		if (b == NULL) {
			return;
		}
		
		if (a == NULL) {
			a = b;
			b = NULL;
			return;
		}
		Node* node = a;

		while (node->next) {
			node = node->next;
		}
		node->next = b;
		b = NULL;
	}

	void FrontBackSplit(Node* source, Node*& a, Node*& b) {
		assert(source != NULL);
		assert(&a != &b);
		a = source;
		b = source;

		if (source->next == NULL) {
			b = NULL;
			return;
		}
		Node* p = source;
		Node* prev = NULL;

		while (p) {
			if (p->next) {
				p = p->next->next; // make a 2-node step
			} else {
				break;
			}
			prev = b;
			b = b->next;
		}

		if (p) {
			prev = b;
			b = b->next;
		}
		prev->next = NULL;
	}

	void AlternatingSplit(Node* source, Node*& a, Node*& b) {
		assert(source != NULL);
		assert(&a != &b);
		a = source;
		b = source->next;
		Node* p1 = a;
		Node* p2 = b;
		
		while (p1 && p1->next && p2) {
			p1->next = p1->next->next;

			if (p2->next) {
				p2->next = p2->next->next;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	Node* ShuffleMerge(Node* a, Node* b) {
		assert(a != b);

		if (a == NULL) {
			return b;
		}

		if (b == NULL) {
			return a;
		}
		Node* head = a;
		Node* p = head;
		int k = 1;

		while (p && a && b) {
			if (k&1) {
				a = p->next;
				p->next = b;
			} else {
				b = p->next;
				p->next = a;
			}
			++k;
			p = p->next;
		}
		return head;
	}

	// PreCondition: the lists are sorted
	Node* SortedMerge(Node* a, Node* b) {
		assert(a != b);

		if (a == NULL) { 
			return b;
		}

		if (b == NULL) {
			return a;
		}
		Node* head = a;
		Node* prev1 = NULL;
		Node* prev2 = NULL;

		while (a && b) {
			while (a && a->data < b->data) {
				prev1 = a;
				a = a->next;
			}

			if (a == NULL) {
				prev1->next = b;
				continue;
			}

			if (prev1 == NULL) {
				head = b;
			} else {
				prev1->next = b;
			}

			while (b && !(a->data < b->data)) {
				prev2 = b;
				b = b->next;
			}
			prev2->next = a;

			if (b == NULL) {
				continue;
			}
		}
		return head;
	}

	void MergeSort(Node*& head) {
		if (head == NULL || head->next == NULL) {
			return;
		}
		Node* half2 = NULL;
		FrontBackSplit(head, head, half2);
		MergeSort(head);
		MergeSort(half2);
		head = SortedMerge(head, half2);
	}

	void QuickSort(Node*& head) {
		if (head == NULL || head->next == NULL) {
			return;
		}
		Node* half2 = NULL;
		FrontBackSplit(head, head, half2);
		Node* mid = NULL;

		if (half2 != NULL) {
			mid = half2;
			half2 = half2->next;
			mid->next = NULL;
			Node* temp = half2;
			Node* preHalf2 = NULL;
			Node* p = head;

			while (p) {
				if (mid->data < p->data) {					
					if (p == head || head == NULL) {
						MoveNode(half2, p);
						head = p;
					} else {
						MoveNode(half2, p);
					}

					if (preHalf2 == NULL) {
						preHalf2 = half2;
					}
				} else {
					p = p->next;
				}
			}
			p = temp;

			while (p) {
				if (!(mid->data < p->data)) {
					if (preHalf2 != NULL && preHalf2->next == p) {
						preHalf2->next = p->next;
					}

					if (p == half2 || half2 == NULL) {
						MoveNode(head, p);
						half2 = p;
					} else {
						MoveNode(head, p);
					}
				} else {
					p = p->next;
				}
			}
		}
		QuickSort(head);
		QuickSort(half2);
		Push(half2, mid);
		Append(head, half2);
	}

	void AppendOnTail(Node*& head, Node*& tail, int data) {
		Node* node = MakeNode(data);

		if (head == NULL) {
			head = node;
		} else {
			tail->next = node;
		}
		tail = node;
	}

	// PreCondition: the lists are sorted
	Node* SortedIntersect(const Node* a, const Node* b) {
		if (a == NULL || b == NULL) {
			return NULL;
		}
		Node* head = NULL;
		Node* tail = NULL;
		
		while (a && b) {
			while (a && b && !(a->data < b->data) && !(b->data < a->data)) {
				AppendOnTail(head, tail, a->data);
				a = a->next;
				b = b->next;
			}

			if (a && b) {
				while (a && a->data < b->data) {
					a = a->next;
				}

				if (a) {
					while (b && b->data < a->data) {
						b = b->next;
					}
				}
			}
		}
		return head;
	}

	// PreCondition: the lists are sorted
	Node* SortedUnion(const Node* a, const Node* b) {
		if (a == NULL && b == NULL) {
			return NULL;
		}
		Node* head = NULL;
		Node* tail = NULL;
		
		while (a || b) {
			while (a && (b == NULL || a->data < b->data)) {
				AppendOnTail(head, tail, a->data);
				a = a->next;
			}

			while (b && (a == NULL || !(a->data < b->data))) {
				AppendOnTail(head, tail, b->data);
				b = b->next;
			}
		}
		return head;
	}

	// PreCondition: the lists are sorted
	Node* SortedDifference(const Node* a, const Node* b) {
		if (a == NULL) {
			return NULL;
		}
		Node* head = NULL;
		Node* tail = NULL;
		
		while (a) {
			while (a && (b == NULL || a->data < b->data)) {
				AppendOnTail(head, tail, a->data);
				a = a->next;
			}

			if (a) {
				while (a && b && !(a->data < b->data) && !(b->data < a->data)) {
					a = a->next;
					b = b->next;
				}

				while (b && b->data < a->data) {
					b = b->next;
				}
			}
		}
		return head;
	}

	// PreCondition: the lists are sorted
	Node* SortedSymmetricDifference(const Node* a, const Node* b) {
		if (a == NULL && b == NULL) {
			return NULL;
		}
		Node* head = NULL;
		Node* tail = NULL;
		
		while (a || b) {
			while (a && b && !(a->data < b->data) && !(b->data < a->data)) {
				a = a->next;
				b = b->next;
			}

			while (a && (b == NULL || a->data < b->data)) {
				AppendOnTail(head, tail, a->data);
				a = a->next;
			}

			while (b && (a == NULL || b->data < a->data)) {
				AppendOnTail(head, tail, b->data);
				b = b->next;
			}
		}
		return head;
	}

	void Reverse(Node*& head) {
		if (head == NULL) {
			return;
		}
		Node* p = NULL;

		while (head) {
			Node* temp = head->next;
			head->next = p; 
			p = head;
			head = temp;
		}
		head = p;
	}

	Node*& rreverse(Node*& head, Node*& newHead) {
		assert(head != NULL);

		if (head->next != NULL) {
			Node*& tail = rreverse(head->next, newHead);
			tail->next = head;
			head->next = NULL;
		} else {
			newHead = head;
		}
		return head;
	}

	void RecursiveReverse(Node*& head) {
		if (head == NULL) {
			return;
		}
		Node* newHead = NULL;
		rreverse(head, newHead);
		head = newHead;
	}

	void RecursiveReverse2(Node*& head) {
		if (head == NULL || head->next == NULL) {
			return;
		}
		Node* rest = head->next;
		RecursiveReverse(rest);
		head->next->next = head;
		head->next = NULL;
		head = rest;
	}

	// (3->1->5) + (5->9->2) = (8->0->8)
	// 513 + 295 = 808
	Node* Add(const Node* a, const Node* b) {
		if (a == NULL && b == NULL) {
			return NULL;
		}
		Node* head = NULL;
		Node* tail = NULL;
		int carry = 0;
		
		while (a || b) {
			Node* node = new Node;
			node->data = (carry + ((a == NULL)? 0 : a->data) + ((b == NULL)? 0 : b->data));
			carry = node->data / 10;
			node->data %= 10;
			node->next = NULL;

			if (tail) {
				tail->next = node;
			}
			tail = node;

			if (head == NULL) {
				head = node;
			}
			
			if (a) {
				a = a->next;
			}

			if (b) {
				b = b->next;
			}
		}

		if (carry) {
			Node* node = new Node;
			node->data = carry;
			node->next = NULL;
			tail->next = node;
		}

		return head;
	}

}

namespace DoublyLinkedList {

	struct Node {
		int data;
		Node *prev, *next;
	};

}

namespace XorList {

	struct Node {
		int data;
		unsigned int xor; // sizeof(unsigned int) == sizeof(void*); xor = prev ^ next;
	};

}

#endif // __LISTS_H__
