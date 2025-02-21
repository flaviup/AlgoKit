
#include "PrimalityTests.h"
#include "IsPrime.h"
#include "Fraction.h"
#include "StringTokenizer.h"
#include "BinarySearchTree.h"
#include "BigInteger.h"
#include "BinarySearch.h"
#include "Lists.h"
#include "Trie.h"

#include <iostream>
#include <map>

template <class T>
void print(const std::vector<T>& vt) {
	for (int i = 0; i < int(vt.size()); ++i) {
		std::cout << vt[i];
		
		if (i < int(vt.size()) - 1) {
			std::cout << ',';
		}
	}
	std::cout << std::endl;
}

void printList(const std::string& message, const SinglyLinkedList::Node* head) {
	int len = 0;
	len = SinglyLinkedList::Length(head);
	std::cout << message << (message.empty()? "" : "\n");
	
	for (int i = 0; i < len; ++ i) {
		std::cout << SinglyLinkedList::GetNth(head, i) << ' ';
	}
	std::cout << std::endl;
}

void testList(SinglyLinkedList::Node*& head) {
	std::cout << "TestList " << SinglyLinkedList::Length(head) << " elements:\n";
	printList("", head);
	std::cout << "Counting: " << SinglyLinkedList::Count(head, 3) << "\n";
	SinglyLinkedList::InsertNth(head, 0, 40);
	printList("Insertion", head);
	SinglyLinkedList::Pop(head);
	printList("Popping", head);
	SinglyLinkedList::InsertSort(head);
	printList("Sorting", head);
	SinglyLinkedList::RemoveDuplicates(head);
	printList("DuplicateRemoval", head);
}

void printVector(const std::vector<int>& v) {
	for (unsigned int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << ' ';
	}
	std::cout << std::endl;
}

class A {
public:
	A() {
		throw std::exception();
	}
};

namespace NS 
{
   class A {};
   void f(A *&, int) { std::cout << "ADL\n";}
}

void f(void*&, int) { std::cout << "Simplef\n"; }

int main () {
	std::map<A, int> mmx;
	std::map<A, int>::value_type;
	A* axy = NULL;
	try {
		axy = new A;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::vector<int> vi(10);
	vi.reserve(21);
	std::cout << vi.capacity() << std::endl;
	// ADL
	NS::A* aptr;
    f(aptr, 0);    //calls NS::f
	int n = 41;
	bool b = IsPrime<>(n);
	Fraction<int> f(3, 4), g(4, 5);
	std::cout << std::string(f + g) << std::endl; 
	std::cout << (f * g).ToString() << std::endl; 
	std::cout << (f - g).ToString() << std::endl; 
	std::cout << (f / g).ToString() << std::endl; 
	std::cout << Fraction<int>("+1/34").ToString() << std::endl;
	std::cout << b << std::endl;
	typedef BSTlr::BST<int> BST_Type1;
	BST_Type1 bstx;
	bstx.Insert(10);
	bstx.Insert(520);
	bstx.Insert(900);
	bstx.Insert(250);
	bstx.Insert(350);
	bstx.Insert(100);
	bstx.Insert(500);
	bstx.Insert(600);
	bstx.Insert(700);
	bstx.Insert(800);
	bstx.Insert(400);
	std::cout << "BST\n";
	printVector(bstx.Sort());
	typedef BSTplr::BST<int> BST_Type;
	std::vector<int>::iterator itx;
	BST_Type bst, bst2;
	bst.Insert(450);
	bst.Insert(340);
	bst.Insert(500);
	bst.Insert(230);
	bst2 = bst;
	bst.Delete(230);
	std::cout << "BST\n";
	print(bst.Sort());
	print(bst2.Sort());
	bst.Clear();
	bst2.Clear();
	std::cout << "Empty BST\n";
	print(bst.Sort());
	print(bst2.Sort());
	std::cout << "StringTokenizer\n";
	print(StrTok("", "", true));
	print(StrTok("abc , d e", "", true));
	print(StrTok("", ", ;.", true));
	print(StrTok(",", ",", true));
	print(StrTok(",a b c,d", " ,", true));
	print(StrTok("a b c,d,", " ,", true));
	print(StrTok(",a b c,d,", " ,", true));
	print(StrTok(",a ", " ,", true));
	print(StrTok(",a ", " ,"));
	BigInt<> bi;
	int a[] = {1, 2};
	std::cout << BinarySearch<> (a, 2, 4) << ' ' << binary_search(a, 2, 1) << std::endl;
	SinglyLinkedList::Node* list0 = NULL;
	SinglyLinkedList::Node* list1 = NULL;
	SinglyLinkedList::Push(list1, SinglyLinkedList::MakeNode(1));
	SinglyLinkedList::Node* list2 = NULL;
	SinglyLinkedList::Push(list2, SinglyLinkedList::MakeNode(1));
	SinglyLinkedList::Push(list2, SinglyLinkedList::MakeNode(2));
	SinglyLinkedList::Node* list3 = NULL;
	SinglyLinkedList::Push(list3, SinglyLinkedList::MakeNode(1));
	SinglyLinkedList::Push(list3, SinglyLinkedList::MakeNode(2));
	SinglyLinkedList::Push(list3, SinglyLinkedList::MakeNode(3));
	SinglyLinkedList::Node* list4 = NULL;
	SinglyLinkedList::Push(list4, SinglyLinkedList::MakeNode(1));
	SinglyLinkedList::Push(list4, SinglyLinkedList::MakeNode(2));
	SinglyLinkedList::Push(list4, SinglyLinkedList::MakeNode(3));
	SinglyLinkedList::Push(list4, SinglyLinkedList::MakeNode(4));
	SinglyLinkedList::Node* list5 = NULL;
	SinglyLinkedList::Push(list5, SinglyLinkedList::MakeNode(1));
	SinglyLinkedList::Push(list5, SinglyLinkedList::MakeNode(2));
	SinglyLinkedList::Push(list5, SinglyLinkedList::MakeNode(3));
	SinglyLinkedList::Push(list5, SinglyLinkedList::MakeNode(3));
	SinglyLinkedList::Push(list5, SinglyLinkedList::MakeNode(3));
	SinglyLinkedList::Push(list5, SinglyLinkedList::MakeNode(5));
	testList(list0);
	testList(list1);
	testList(list2);
	testList(list3);
	testList(list4);
	testList(list5);
	printList("LISTS", list3);
	printList("", list4);
	SinglyLinkedList::MoveNode(list3, list4);
	printList("MoveNode", list3);
	printList("", list4);
	SinglyLinkedList::Append(list3, list4);
	printList("Append", list3);
	printList("", list4);
	SinglyLinkedList::FrontBackSplit(list3, list3, list4);
	printList("FrontBackSplit", list3);
	printList("", list4);
	SinglyLinkedList::Node* listA = NULL;
	SinglyLinkedList::Node* listB = NULL;
	//SinglyLinkedList::AlternatingSplit(list4, listA, listB);
	//list4 = NULL;
	//printList("AlternatingSplit", listA);
	//printList("", listB);
	
	
	//SinglyLinkedList::FrontBackSplit(list3, listA, listB);
	//list3 = NULL;
	//printList("FrontBackSplit", listA);
	//printList("", listB);
	
	//listA = SinglyLinkedList::ShuffleMerge(listA, listB);
	//listB = NULL;
	//printList("ShuffleMerge", listA);

	list3 = SinglyLinkedList::ShuffleMerge(list3, list4);
	list4 = NULL;
	printList("ShuffleMerge", list3);
	list1 = SinglyLinkedList::SortedMerge(list1, list2);
	list2 = NULL;
	printList("SortedMerge", list1);
	printList("List5", list5);
	list1 = SinglyLinkedList::SortedMerge(list1, list5);
	list5 = NULL;
	printList("SortedMerge", list1);

	SinglyLinkedList::Node* list6 = NULL;
	SinglyLinkedList::Push(list6, SinglyLinkedList::MakeNode(1));
	SinglyLinkedList::Push(list6, SinglyLinkedList::MakeNode(2));
	SinglyLinkedList::Push(list6, SinglyLinkedList::MakeNode(3));
	SinglyLinkedList::Push(list6, SinglyLinkedList::MakeNode(3));
	SinglyLinkedList::Push(list6, SinglyLinkedList::MakeNode(3));
	SinglyLinkedList::Push(list6, SinglyLinkedList::MakeNode(5));
	
	//printList("MergeSort", list6);
	//SinglyLinkedList::MergeSort(list6);
	//printList("", list6);

	printList("QuickSort", list6);
	SinglyLinkedList::QuickSort(list6);
	printList("", list6);
	SinglyLinkedList::Node* list7 = SinglyLinkedList::Duplicate(list6);
	SinglyLinkedList::Push(list7, SinglyLinkedList::MakeNode(0));
	SinglyLinkedList::Node* nd = SinglyLinkedList::MakeNode(6);
	SinglyLinkedList::SortedInsert(list6, nd);
	printList("List6", list6);
	printList("List7", list7);
	SinglyLinkedList::Node* list8 = SinglyLinkedList::SortedIntersect(list6, list7);
	SinglyLinkedList::Node* list9 = SinglyLinkedList::SortedUnion(list6, list7);
	SinglyLinkedList::Node* list10 = SinglyLinkedList::SortedDifference(list6, list7);
	SinglyLinkedList::Node* list11 = SinglyLinkedList::SortedSymmetricDifference(list6, list7);
	printList("SortedIntersect: List6 ^ List7", list8);
	printList("SortedUnion: List6 v List7", list9);
	printList("SortedDifference: List6 - List7", list10);
	printList("SortedSymmetricDifference: (List6 - List7) v (List7 - List6)", list11);
	//SinglyLinkedList::Reverse(list9);
	//SinglyLinkedList::RecursiveReverse(list9);
	SinglyLinkedList::RecursiveReverse2(list9);
	printList("Reversed", list9);

	SinglyLinkedList::DeleteList(list7);
	assert(list7 == NULL);
	SinglyLinkedList::DeleteList(list8);
	assert(list8 == NULL);
	SinglyLinkedList::DeleteList(list9);
	assert(list9 == NULL);
	SinglyLinkedList::DeleteList(list10);
	assert(list10 == NULL);
	SinglyLinkedList::DeleteList(list11);
	assert(list11 == NULL);

	SinglyLinkedList::DeleteList(list0);
	assert(list0 == NULL);
	SinglyLinkedList::DeleteList(list1);
	assert(list1 == NULL);
	SinglyLinkedList::DeleteList(list2);
	assert(list2 == NULL);
	SinglyLinkedList::DeleteList(list3);
	assert(list3 == NULL);
	SinglyLinkedList::DeleteList(list4);
	assert(list4 == NULL);
	SinglyLinkedList::DeleteList(list5);
	assert(list5 == NULL);
	SinglyLinkedList::DeleteList(list6);
	assert(list6 == NULL);
	SinglyLinkedList::DeleteList(listA);
	assert(listA == NULL);
	SinglyLinkedList::DeleteList(listB);
	assert(listB == NULL);

	Trie trie;
	return 0;
}
