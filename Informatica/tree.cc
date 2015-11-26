#include <iostream>
#include <stack>

// DS Implementation : http://www.vogella.com/tutorials/JavaDatastructures/article.html#map

using namespace std;

	int height(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(height(root->left), height(root->right));
    }
    bool isBalanced(TreeNode* root) {
        int lh, rh;
        
        if (!root) return 1;
        
        lh = height(root->left);
        rh = height(root->right);
        
        if (abs(lh-rh) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
            return 1;
        }
        
        return 0;
    }

/*Queue - Linked List implementation*/
#include<stdio.h>
#include<stdlib.h>
struct Node {
	int data;
	struct Node* next;
};
// Two glboal variables to store address of front and rear nodes. 
struct Node* front = NULL;
struct Node* rear = NULL;

// To Enqueue an integer
void Enqueue(int x) {
	struct Node* temp = 
		(struct Node*)malloc(sizeof(struct Node));
	temp->data =x; 
	temp->next = NULL;
	if(front == NULL && rear == NULL){
		front = rear = temp;
		return;
	}
	rear->next = temp;
	rear = temp;
}

// To Dequeue an integer.
void Dequeue() {
	struct Node* temp = front;
	if(front == NULL) {
		printf("Queue is Empty\n");
		return;
	}
	if(front == rear) {
		front = rear = NULL;
	}
	else {
		front = front->next;
	}
	free(temp);
}

int Front() {
	if(front == NULL) {
		printf("Queue is empty\n");
		return;
	}
	return front->data;
}

void Print() {
	struct Node* temp = front;
	while(temp != NULL) {
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main(){
	/* Drive code to test the implementation. */
	// Printing elements in Queue after each Enqueue or Dequeue 
	Enqueue(2); Print(); 
	Enqueue(4); Print();
	Enqueue(6); Print();
	Dequeue();  Print();
	Enqueue(8); Print();
}

class tree {
	tree* left;
	tree* right;
	int data;

public:
	tree() {

	}
	
	 vector<int> postorderTraversal1(TreeNode* root) {
        vector<int> vec;
        if (!root) {
            return vec;
        }
        stack<TreeNode*> s1;
        s1.push(root);
        TreeNode* prev = NULL;
        while(!s1.empty()) {
            TreeNode* curr = s1.top();
            if (!prev || prev->left == curr || prev->right == curr) {
                if (curr->left) {
                    s1.push(curr->left);
                } else if (curr->right) {
                    s1.push(curr->right);
                }
            } else if (curr->left == prev) {
                if (curr->right) {
                    s1.push(curr->right);
                }
            } else {
                vec.push_back(curr->val);
                s1.pop();
            }
        }
        return vec;
    }
    
	vector<int> postorderTraversal(TreeNode* root) {
        vector<int> vec;
        if (!root) {
            return vec;
        }
        stack<TreeNode*> s1, s2;
        s1.push(root);
        while(!s1.empty()) {
            TreeNode* curr = s1.top();
            s2.push(curr);
            s1.pop();
            if (curr->left) {
                s1.push(curr->left);
            } 
            if (curr->right) {
                s1.push(curr->right);
            }
        }
        while(!s2.empty()) {
            vec.push_back(s2.top()->val);
            s2.pop();
        }
        return vec;
    }

	tree* newNode(int data) {
		tree* root = new tree;
		root->left = NULL;
		root->right = NULL;
		root->data = data;
		return root;
	}

	tree* insert(tree* root, int data) {
		if (!root) {
			return newNode(data);
		}
		if (root->data > data) {
			root->left = insert(root->left, data);
		} else if (root->data < data) {
			root->right = insert(root->right, data);
		}

		return root;
	}

	void preorder(tree* root) {
		if (root) {
			cout<<root->data<<" ";
			preorder(root->left);
			preorder(root->right);
		}	
	}

	void inorder(tree* root) {
		if (!root) {
			return;
		}
		inorder(root->left);
		cout<<root->data<<" ";
		inorder(root->right);
	}

	void postorder(tree* root) {
		if (!root) {
			return;
		}
		postorder(root->right);
		postorder(root->left);
		cout<<root->data<<" ";
	}
};

int main() {
	tree* root = NULL;
	root = root->insert(root, 4);
	root->insert(root, 2);
	root->insert(root, 1);
	root->insert(root, 3);
	root->insert(root, 6);
	root->insert(root, 5);
	root->insert(root, 7);
	cout<<"Pre-order\n";
	root->preorder(root);
	cout<<endl;
	cout<<"In-order\n";
	root->inorder(root);
	cout<<endl;
	cout<<"Post-order\n";
	root->postorder(root);
	cout<<endl;
	return 0;
}

#include <iostream>

using namespace std;

typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node;

node* create_node(int val)
{
    node* n = (node*) malloc(sizeof(node));
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    n->ht = 0;
    return n;
}

int height(node* n)
{
    if (n == NULL) {
        return -1;
    }
    return n->ht;
}

int calculate_height(node* n)
{
    return 1 + max(height(n->left), height(n->right));
}

int weight(node* n) {
    if (n == NULL) {
        return 0;
    }
    return height(n->left) - height(n->right);
}

node* right_rotate(node* root)
{
    node* oldRoot = root;
    root = oldRoot->left;
    oldRoot->left = root->right;
    root->right = oldRoot;

    oldRoot->ht = calculate_height(oldRoot);
    root->ht = calculate_height(root);

    return root;

}

node* left_rotate(node* root)
{
    node* oldRoot = root;
    root = oldRoot->right;
    oldRoot->right = root->left;
    root->left = oldRoot;

    oldRoot->ht = calculate_height(oldRoot);
    root->ht = calculate_height(root);

    return root;
}

node* balance(node* root)
{
    int w = weight(root);

    if (root == NULL || abs(w) <= 1) {
        return root;
    }

    if (w > 0) {
        if (weight(root->left) < 0) {
            root->left = left_rotate(root->left);
        }
        return right_rotate(root);
    } else {
        if (weight(root->right) > 0) {
            root->right = right_rotate(root->right);
        }
        return left_rotate(root);
    }

    return root;
}

node* insert(node* root, int val)
{
    if (val < root->val) {
        if (root->left == NULL) {
            root->left = create_node(val);
        } else {
            root->left = insert(root->left, val);
        }
    } else if (val > root->val) {
        if (root->right == NULL) {
            root->right = create_node(val);
        } else {
            root->right = insert(root->right, val);
        }
    }

    root->ht = calculate_height(root);

    return balance(root);
}

bool trees_equal(node* n1, node* n2)
{
    if (n1 == NULL && n2 == NULL) {
        return true;
    } else if (n1 == NULL || n2 == NULL || n1->val != n2->val) {
        return false;
    }

    return trees_equal(n1->left, n2->left) && trees_equal(n1->right, n2->right);
}

int main()
{
    // Dynamically create an AVL tree.
    node* root = create_node(3);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);

    // Make a tree to compare against to ensure the balancing works correctly.
    node* three = create_node(3);
    three->left = create_node(2);

    node* five = create_node(5);
    five->left = create_node(4);
    five->right = create_node(6);

    three->right = five;

    if (trees_equal(root, three)) {
        cout << "AVL tree is balanced!" << endl;
    } else {
        cout << "AVL tree is not balanced!" << endl;
    }

    return 0;
}