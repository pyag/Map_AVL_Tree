#include <iostream>
#include <stdlib.h>

using namespace std;

template < typename _key, typename _value >
struct node{
    _key key;
	_value value;
	node *parent;
	node *left, *right;
	int height;
};

template < typename _key, typename _value >
class AVL{
	public:

	node < _key, _value > *root;
	typedef node < _key, _value > item;
	
	AVL(){
		root = NULL;
	}
	
	item * find(_key x){
		item *tmp = root;
		while(1){
			if(tmp == NULL || (x == tmp->key)) break;
			if(x < tmp->key){
				tmp = tmp->left;
			}else{
				tmp = tmp->right;
			}
		}
		return tmp;
	}
	
	item * newNode(_key k, _value v){
		item *t = new item();
		t->key = k;
		t->value = v;
		t->left = t -> right = t->parent = NULL;
		t->height = 1;
		return t;
	}
	
	int nodeHeight(item * x){
		if(x == NULL){
			return 0;
		}
		return x->height;
	}
	
	item * location(_key k){
		item *t = root, *prev;
		while(1){
			if(t == NULL) break;
			if(t->key == k) return NULL;
			prev = t;
			if(k < t->key){
				t = t->left;
			}else{
				t = t->right;
			}
		}
		return prev;
	}
	
	void updateHeight(item * x){
		while(x != NULL){
			x->height = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
			x = x->parent;
		}
	}
	
	void insert(_key k, _value v){
		item * t = newNode(k, v);
		if(root == NULL){
			root = t;
			return;
		}
		
		item * parent;
		parent = location(k);
		
		if(parent == NULL){
			parent = find(k);
			parent->value = v;
			return;
		}
		
		if(k < parent->key){
			parent->left = t;
		}else{
			parent->right = t;
		}
		t->parent = parent;
	
		updateHeight(parent);
		makeAVL(parent);
	}
	
	void inorder(){
		inorder(root);
		cout << "\n";
	}
	
	void inorder(item *root){
		if(root != NULL){
			inorder(root->left);
			inorder(root->right);
			cout << root->key << " with balance " << balance(root) << "\n";
		}
	}
	
	int balance(item * x){
		return nodeHeight(x->left) - nodeHeight(x->right);
	}
	
	void left(item * x){
		item *px = x->parent;
		item * y = x->right;
		item * b = y->left;
		
		y->parent = x->parent;
		if(px != NULL){
			if(px->left == x){
				px->left = y;
			}else{
				px->right = y;
			}
		}
		if(px == NULL) root = y;
		y->left = x;
		
		x->right = b;
		if(b != NULL) b->parent = x;
		x->parent = y;
		
		updateHeight(x);
	}
	
	void right(item * x){
		item *px = x->parent;
		item * y = x->left;
		item * b = y->right;
		
		y->parent = x->parent;
		if(px != NULL){
			if(px->left == x){
				px->left = y;
			}else{
				px->right = y;
			}
		}
		if(px == NULL) root = y;
		y->right = x;
		
		x->left = b;
		if(b != NULL) b->parent = x;
		x->parent = y;
		
		updateHeight(x);
	}
	
	void makeAVL(item * x){
		if(x == NULL) return;
		int balFactor = balance(x);
		while(balFactor >= -1 && balFactor <= 1){
			x = x->parent;
			if(x == NULL) return;
			balFactor = balance(x);
		}
		
		if(balFactor > 1){
			if(balance(x->left) > 0){
				right(x);
			}else{
				left(x->left);
				right(x);
			}
		}else{
			if(balance(x->right) < 0){
				left(x);
			}else{
				right(x->right);
				left(x);
			}
		}
	}
	
	_value get(_key k){
		return find(k)->value;
	}
	
	_value & operator[](_key k){
		item * i = find(k);
		if(i == NULL){
			_value v;
			insert(k, v);
			i = find(k);
		}
		return i->value;
	}
};
