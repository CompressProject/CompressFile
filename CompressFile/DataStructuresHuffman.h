#pragma once
//typedef struct TreeNode {
//	char data;
//	struct TreeNode* left;
//	struct TreeNode* right;
//}TreeNode;
//typedef struct NodeHeap {
//	int frequency;
//	struct NodeHeap* left;
//	struct NodeHeap* right;
//	struct NodeTree* tree;
//}NodeHeap;
#include "CommonFunction.h"
#define MAX_TREE_HT 100
// A Huffman tree node
typedef struct MinHeapNode {
	// One of the input characters
	char data;
	// Frequency of the character
	unsigned freq;
	// Left and right child of this node
	struct MinHeapNode* left, * right;
}MinHeapNode;

// A Min Heap: Collection of
// min-heap (or Huffman tree) nodes
typedef struct MinHeap {
	// Current size of min heap
	unsigned size;
	// capacity of min heap
	unsigned capacity;
	// Array of minheap node pointers
	 MinHeapNode** array;
}MinHeap;
MinHeapNode* newNode(char data, unsigned freq);
MinHeap* createMinHeap(unsigned capacity);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int index);
int isSizeOne(MinHeap* minHeap);
MinHeapNode* extractMin(MinHeap* minHeap);
void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode);
void buildMinHeap(struct MinHeap* minHeap);
int isLeaf(MinHeapNode* root);
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);