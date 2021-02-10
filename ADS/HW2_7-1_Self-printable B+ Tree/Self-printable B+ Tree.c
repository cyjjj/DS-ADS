#include <stdio.h>
#include <stdlib.h>

typedef struct Node* BNode;
typedef BNode BTree;
struct Node{
	int num;   //内部节点的孩子数或叶节点中元素个数
	int key[3];   //节点中的三个关键字,-1代表没有
	BNode child[3];//节点的三个孩子指针
	int isleaf;   //节点是否为叶节点
};

BTree initialize(){
	BTree T = (BTree)malloc(sizeof(struct Node));
	T->num = 0;
	T->isleaf = 0;
	int i;
	for(i=0;i<3;i++){
		T->key[i] = -1;
		T->child[i] = NULL;
	}
	return T;
}

int top=0;
BNode stack[5000];
BNode pop(void){
	if(top==0) return NULL;
	else return stack[--top];
}

void push(BNode x){
	stack[top++] = x;
}

int find(BNode tmp){
	while(tmp&&tmp->isleaf!=1){
		tmp = tmp->child[0];
	}
	return tmp->key[0];
}

BTree insert(BTree T, int x){
	top = 0;
	BTree root = T, tmp = T;
	if(T==NULL){
		T = initialize();
		T->key[0] = x;
		T->num = 1;
		T->isleaf = 1;
		return T;
	}
	while(!tmp->isleaf){
		push(tmp);
		if(tmp->num == 2){
			if(x<tmp->key[0]) tmp = tmp->child[0];
			else if(x>tmp->key[0]) tmp = tmp->child[2];
			else {
				printf("Key %d is duplicated\n",x);
				return T;
			}
		}else if(tmp->num == 3){
			if(x<tmp->key[0]) tmp = tmp->child[0];
			else if(x>tmp->key[0]&&x<tmp->key[1]) tmp = tmp->child[1];
			else if(x>tmp->key[1]) tmp = tmp->child[2];
			else {
				printf("Key %d is duplicated\n",x);
				return T;
			}
		}
	}
	//当叶节点没有满时
	if(tmp->num < 3){
		int i=tmp->num;
		if(x == tmp->key[0] || x == tmp->key[1] 
		 ||x == tmp->key[2]) {
			printf("Key %d is duplicated\n",x);
			return T;
		}
		while(i>0&&x<=tmp->key[i-1]){
			tmp->key[i] = tmp->key[i-1];
			i--;
		}
		tmp->key[i] = x;
		tmp->num++;
		return T;
	} else if(tmp->num == 3){ //叶节点满时
		int bomb[4]; //存放爆了的四个数
		if(x == tmp->key[0] || x == tmp->key[1] 
		 ||x == tmp->key[2]) {
			printf("Key %d is duplicated\n",x);
			return T;
		}
		bomb[0] = tmp->key[0];
		bomb[1] = tmp->key[1];
		bomb[2] = tmp->key[2];
		//将四个数排好序
		int j=2;
		while(x<bomb[j] && j>=0){
			bomb[j+1] = bomb[j];
			j--;
		}
		bomb[j+1] = x;
		//重建两个节点
		BNode parent = NULL;
		BNode node1 = tmp;
		BNode node2 = initialize();
		node1->num = node2->num = 2;
		node1->isleaf = node2->isleaf = 1;
		node1->key[0] = bomb[0];
		node1->key[1] = bomb[1];
		node1->key[2] = -1;
		node2->key[0] = bomb[2];
		node2->key[1] = bomb[3];

		while(tmp){
			parent = pop();

			//当前节点就是根节点
			if(!parent){
				root = initialize();
				root->child[0] = node1;
				root->child[2] = node2;
				root->num = 2;
				root->key[0] = find(root->child[2]);
				T = root;
				break;
			}
			//当前节点的父节点还未满,
			//即父节点有一个key，两个孩子
			else if(parent->num == 2){
				if(x < parent->key[0]){
					parent->child[0] = node1;
					parent->child[1] = node2;
				} else {
					parent->child[1] = node1;
					parent->child[2] = node2;
				}
				parent->num = 3;
				parent->key[0] = find(parent->child[1]);
				parent->key[1] = find(parent->child[2]);
				parent->key[2] = -1;
				parent->isleaf = 0;
				break;
			}
			//当前父节点已经满了，需要分裂父节点
			else if(parent->num == 3){
				BNode node3,node4;
				node3 = parent;
				node3->isleaf = 0;
				node4 = initialize();
				node3->num = node4->num = 2;
				if(x<parent->key[0]){
					node4->child[0] = parent->child[1];
					node4->child[2] = parent->child[2];
					node3->child[0] = node1;
					node3->child[2] = node2;
					node3->child[1] = NULL;
				}else if(x>parent->key[0]&&x<parent->key[1]){
					node4->child[0] = node2;
					node4->child[2] = parent->child[2];
					node3->child[0] = parent->child[0];
					node3->child[2] = node1;
					node3->child[1] = NULL;
				}else if(x>parent->key[1]){
					node4->child[0] = node1;
					node4->child[2] = node2;
					node3->child[0] = parent->child[0];
					node3->child[2] = parent->child[1];
					node3->child[1] = NULL;
				}
				node4->key[0] = find(node4->child[2]);
				node3->key[0] = find(node3->child[2]);
				node4->key[1] = node4->key[2] = -1;
				node3->key[1] = node3->key[2] = -1;
				node1 = node3;
				node2 = node4;
				tmp = parent;
			}
		}
	}
	return T;
}

BTree queue[5000];
int front = 0, rear = 0;

void enqueue(BNode x){
	queue[rear++] = x;
}

BNode dequeue(void){
	return queue[front++];
}
void print(BTree T){
	BTree tmp;
	front = 0;
	rear = 0;
	int row = 1;
	int nextrow = 0;
	enqueue(T);
	while(front!=rear){
		tmp = dequeue();
		if(tmp->isleaf){
			printf("[");
			printf("%d",tmp->key[0]);
			if(tmp->key[1]!=-1) printf(",%d",tmp->key[1]);
			if(tmp->key[2]!=-1) printf(",%d",tmp->key[2]);
			printf("]");
		} else{
			row--;
			printf("[");
			printf("%d",tmp->key[0]);
			if(tmp->key[1]!=-1){
				printf(",%d",tmp->key[1]);
			}
			printf("]");
			if(tmp->child[0]){
				nextrow++;
				enqueue(tmp->child[0]);
			}
			if(tmp->child[1]){
				nextrow++;
				enqueue(tmp->child[1]);
			}
			if(tmp->child[2]){
				nextrow++;
				enqueue(tmp->child[2]);
			}
			if(row==0){
				printf("\n");
				row = nextrow;
				nextrow = 0;
			}
		}
	}
}

int main()
{
	BTree t = NULL;
	int n, x;
	scanf("%d", &n);
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		t = insert(t,x);
	}
	print(t);
	return 0;
}
