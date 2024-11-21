#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;

struct Tree {
	int data;
	Tree *left;
	Tree *right;
};

void ISDP(Tree *&root, int l, int r);
void FreeTree(Tree *root);
void Print1(Tree *root);
double SumOfPaths(Tree *root, int level);
int HeightOfTree(Tree *root);
int SizeOfTree(Tree *root);
int SumOfElements(Tree *root);

int arr[100];

int main(void) {
	srand(time(NULL));
	
	Tree *root = NULL;

	for (int i = 0; i < 100; i++)
		arr[i] = rand() % 100 + 1;
	
	ISDP(root, 0, 99);

	Print1(root);
	cout << "\n";

	cout << "Размер дерева: " << SizeOfTree(root) << "\n";
	cout << "Высота дерева: " << HeightOfTree(root) << "\n";
	cout << "Средняя высота дерева: " << SumOfPaths(root, 1) / SizeOfTree(root) << "\n";
	cout << "Сумма элементов дерева: " << SumOfElements(root) << "\n";

	FreeTree(root);

	return 0;
}

void ISDP(Tree *&root, int l, int r) {
	if (l > r) {
		root = NULL;

		return;
	}

	int m = (l + r) / 2;
	Tree *p = new Tree;

	p->data = arr[m];
	ISDP(p->left, l, m - 1);
	ISDP(p->right, m + 1, r);
	
	root = p;
}

void FreeTree(Tree *root) {
	if (root == NULL) return;
	if (root->left != NULL) FreeTree(root->left);
	if (root->right != NULL) FreeTree(root->right);

	delete root;
}

void Print1(Tree *root) {
	if (root != NULL) {
		cout << root->data << " ";
		Print1(root->left);
		Print1(root->right);
	}
}

double SumOfPaths(Tree *root, int level) {
	if (root == NULL)
		return 0;
	else
		return level + SumOfPaths(root->left, level + 1) + SumOfPaths(root->right, level + 1);
	
}

int HeightOfTree(Tree *root) {
	if (root == NULL)
		return 0;
	else
		return 1 + max(HeightOfTree(root->left), HeightOfTree(root->right));
}

int SizeOfTree(Tree *root) {
	if (root == NULL)
		return 0;
	else
		return 1 + SizeOfTree(root->left) + SizeOfTree(root->right);

}

int SumOfElements(Tree *root) {
	if (root == NULL)
		return 0;
	else
		return root->data + SumOfElements(root->left) + SumOfElements(root->right);
}
