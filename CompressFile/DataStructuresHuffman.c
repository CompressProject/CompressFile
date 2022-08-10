#include "DataStructuresHuffman.h"
// A utility function allocate a new
// min heap node with given character
// and frequency of the character
MinHeapNode* newNode(char data, unsigned freq)
{
	MinHeapNode* temp = (MinHeapNode*)malloc(sizeof(MinHeapNode));
	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;
	return temp;
}
// A utility function to create
// a min heap of given capacity
MinHeap* createMinHeap(unsigned capacity)
{
	MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
	// current size is 0
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (MinHeapNode**)malloc(minHeap->capacity * sizeof(MinHeapNode*));
	return minHeap;
}
// A utility function to
// swap two min heap nodes
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
	MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}
// The standard minHeapify function.
void minHeapify(MinHeap* minHeap, int index)
{
	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
		smallest = left;
	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		smallest = right;
	if (smallest != index)
	{
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
		minHeapify(minHeap, smallest);
	}
}
// A utility function to check
// if size of heap is 1 or not
int isSizeOne(MinHeap* minHeap)
{
	return (minHeap->size == 1);
}
// A standard function to extract
// minimum value node from heap
MinHeapNode* extractMin(MinHeap* minHeap)
{
	MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}
// A utility function to insert
// a new node to Min Heap
void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode)
{
	++minHeap->size;
	int i = minHeap->size - 1;
	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
	{
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = minHeapNode;
}
// A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap)
{
	int n = minHeap->size - 1;
	int i;
	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}
// Utility function to check if this node is leaf
int isLeaf(MinHeapNode* root)
{
	return !(root->left) && !(root->right);
}
// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
	MinHeap* minHeap = createMinHeap(size);
	//int data;
	for (int i = 0; i < size; ++i)
	{
		//data = fgetc(intermediateFile);
		minHeap->array[i] = newNode(data[i], freq[i]);
	}
	minHeap->size = size;
	buildMinHeap(minHeap);
	return minHeap;
}
