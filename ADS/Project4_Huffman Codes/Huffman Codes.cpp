#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define MAXN 64

int N; //number of distinct characters
int M; //number of student submissions
char ch[MAXN]; //character chosen from {'0'-'9','a'-'z','A'-'Z','_'}
int w[MAXN]; //the frequency of c[i]
int length; //length of weighted path of the optimal code

typedef struct HuffmanNode {
	char ch; //the character
	int weight; //the frequency of the character
	HuffmanNode *Left;
	HuffmanNode *Right;
} *HuffmanTree;

typedef struct Heap {
	HuffmanTree *data; //elements in the heap
	int size = 0; //size of the heap
	int capacity; //max size of the heap
} *MinHeap;

HuffmanTree CreateTree(); //Create a new HuffmanTree node
MinHeap CreateMinHeap(int Max); //Create a new MinHeap
int Insert(MinHeap H, HuffmanTree item); //Insert a HuffmanTree node into the MinHeap
HuffmanTree DeleteMin(MinHeap H); //Delete the root(the minimum item) from MinHeap
HuffmanTree Huffman(MinHeap H); //Build the Huffman Tree
int WPL(HuffmanTree T, int depth); //calculate the weighted path length
int Check(); //check if the student submission is correct

int main()
{
	cin >> N;
	MinHeap H = CreateMinHeap(2 * N);//Build MinHeap
	                                 //Huffman Tree with N leaf nodes has 2N-1 nodes
	for (int i = 0; i < N; i++)
	{
		HuffmanTree T = CreateTree();
		cin >> ch[i] >> w[i]; //character and its frequency
		T->ch = ch[i];
		T->weight = w[i];
		Insert(H, T); //insert it into the min heap
	}
	HuffmanTree HT = Huffman(H); //Build Haffman Tree
	length = WPL(HT, 0); //length of weighted path of the optimal code
	cin >> M;
	for (int i = 0; i < M; i++) //check each submission
	{
		if (Check())//the student submission is correct
			cout << "Yes" << endl; 
		else 
			cout << "No" << endl;
	}

	system("pause");
	return 0;
}

HuffmanTree CreateTree()
{
	HuffmanTree T = (HuffmanTree)malloc(sizeof(struct HuffmanNode));
	T->ch = '\0';  //empty
	T->weight = 0;
	T->Left = T->Right = NULL;
	return T;
}
MinHeap CreateMinHeap(int Max)
{
	MinHeap H = (MinHeap)malloc(sizeof(struct Heap));
	H->data = (HuffmanTree *)malloc((Max + 1) * sizeof(struct HuffmanNode));
	H->size = 0; //empty
	H->capacity = Max;
	return H;
}
int Insert(MinHeap H, HuffmanTree item)
{
	int i;
	if (H->size == H->capacity) //the MinHeap is full
		return 0; //fail

	i = ++H->size; //the position of the last element in the back heap
	for (; i > 1 && H->data[i / 2]->weight > item->weight; i /= 2)
		H->data[i] = H->data[i / 2];
	H->data[i] = item; //insert item

	return 1; //succeed
}
HuffmanTree DeleteMin(MinHeap H)
{
	int parent, child;
	HuffmanTree MinItem, temp;
	if (H->size == 0) //MinHeap is empty
		return NULL;

	MinItem = H->data[1];  //minimum item

	temp = H->data[H->size--];
	for (parent = 1; parent * 2 <= H->size; parent = child) {
		child = parent * 2;
		if ((child != H->size) && (H->data[child]->weight > H->data[child + 1]->weight))
			child++;
		if (temp->weight > H->data[child]->weight)
			H->data[parent] = H->data[child];
		else
			break; //find suitable positon
	}
	H->data[parent] = temp;

	return MinItem;
}
HuffmanTree Huffman(MinHeap H)
{
	int i, num;
	HuffmanTree T = NULL;

	num = H->size;
	for (i = 1; i < num; i++) {
		T = CreateTree();  //create a new node
		/*greedy*/
		T->Left = DeleteMin(H);  //delete root from min heap and attach it to left_child of node
		T->Right = DeleteMin(H);  //delete root from min heap and attach it to right_child of node
		T->weight = T->Left->weight + T->Right->weight;  //weight of node is the sum of weights of its children
		Insert(H, T);  //insert node into min heap 
	}
	return T;
}
int WPL(HuffmanTree T, int depth)
{
	if (T) {
		if (!T->Left && !T->Right) //leaf node
			return depth * T->weight;
		else
			return WPL(T->Left, depth + 1) + WPL(T->Right, depth + 1);
	}
	else //T is NULL
		return 0;
}
int Check()
{
	int i, j, weight;
	int flag = 0;  //flag to record whether it is a prefix code  
	char c, code[MAXN];

	HuffmanTree T = CreateTree();
	HuffmanTree pt = NULL;
	for (i = 0; i < N; i++) {
		cin >> c >> code;
		if (strlen(code) > N - 1) 
			return 0; //code word length of the Huffman tree composed of N leaf nodes is at most N-1
		for (j = 0; c != ch[j]; j++); //find the correcponding index of character c
		weight = w[j]; //get the frequency of character c
		pt = T;
		for (j = 0; code[j] != '\0'; j++) {
			if (code[j] == '0')
			{
				if (!pt->Left)
					pt->Left = CreateTree();
				pt = pt->Left;
			}
			else if (code[j] == '1')
			{
				if (!pt->Right)
					pt->Right = CreateTree();
				pt = pt->Right;
			}
			if (!pt->weight)  flag = 1; //is prefix code 
			if (code[j + 1] == '\0') //should be leaf node
				pt->weight = weight;
		}
	}
	if (!flag) //is not prefix code
		return 0;
	if (length == WPL(T, 0)) //its WPL is equal to length
		return 1;  //correct!
	else return 0;
}