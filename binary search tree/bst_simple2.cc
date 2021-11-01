#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <limits>
using namespace std;

// global variables for checking if Binary tree is BST
int INT_MIN = -1;
int INT_MAX = 1000;

struct Node {
  int data;
  Node* left;
  Node* right;
};


// Function to find some data in the tree
Node* Find(Node *root, int data) {
  if(root == NULL) return NULL;
  else if(root->data == data) return root;
  else if(root->data < data) return Find(root->right, data);
  else return Find(root->left, data);
}


//Function to find successor
Node* GetSuccessor(Node *root, int data) {
  //Search the node O(h)
  Node *current = Find(root, data);
  if(current == NULL) return NULL;

  //Case 1: Node has right subtree
  if(current->right != NULL) {
    Node *temp = current->right;
    while(temp->left != NULL) 
      temp = temp->left;
    return temp;
 }
  //Case 2: No right subtree
  else{
    Node *successor = NULL;
    Node *ancestor = root;
    while(ancestor != current) {
      if(current->data < ancestor->data) {
        successor = ancestor; // so far this is the deepest node for which current node is in left
        ancestor = ancestor->left;
      }
      else
        ancestor = ancestor->right;
    }
    return successor;
  }
}


int FindMin(Node* root) {  //FINDING MIN VAL IN A TREE
  if(root == NULL) {
    std::cout<<"Error: Tree is empty!";
    return -1;
  }
  Node* current = root;
  while(current->left != NULL) {
    current = current->left;
  }
  return current->data;
}


int FindMax(Node* root) {  //FINDING MAX VAL IN A TREE
  if(root == NULL) {
    std::cout<<"Error: Tee is empty!";
    return -1;
  }
  Node* current = root;
  while(current->right != NULL) {
    current = current->right;
  }
  return current->data;
}


// DELETING A node function from BST
Node* Delete(Node *root, int data) {
    if(root == NULL) return root;
    else if(data < root->data)
      root->left = Delete(root->left, data);
    else if(data > root->data)
      root->right = Delete(root->right, data);
    else {  //FOUND NODE, get ready 4 deleting
      //CASE 1: No child
      if(root->left == NULL && root->right == NULL) {
        delete root;  // object in heap is deleted
        root = NULL;
      }
      //CASE 2: One child
      else if(root->left == NULL) {
        struct Node *temp = root;
        root = root->right;
        delete temp;
      }
      else if(root->right == NULL) {
        struct Node *temp = root;
        root = root->left;
        delete temp;
      }
      //CASE 3: 2 children
      else {
        struct Node *temp; temp->data = FindMin(root->right);
        root->data = temp->data;
        root->right = Delete(root->right, temp->data);
      }
    }
    return root;
}


//Function BstUtil with MAX and MIN global
bool IsBstUtil(Node *root, int minValue, int maxValue) {
  if(root == NULL) return true;
  if(root->data > minValue && root->data < maxValue &&
    IsBstUtil(root->left, minValue, root->data) &&
    IsBstUtil(root->right, root->data, maxValue))
    return true;
  else
    return false;
}
// Function with just argument root
bool IsBinarySearchTree(Node *root) {
  return IsBstUtil(root, INT_MIN, INT_MAX);
}




// BREADTH SEARCH FIRST, LEVEL ORDER TRAVERSAL function
void LevelOrder(Node *root) {
  if(root == NULL) return;
  queue<Node*> Q;
  Q.push(root);
  while(!Q.empty()) {       //while Queue is not empty
    Node* current = Q.front();
    cout<<current->data<<" ";
    if(current->left != NULL)
      Q.push(current->left);
    if(current->right != NULL)
      Q.push(current->right);
    Q.pop();              //remove element at front
  }
}


// DFS Traversal Preorder (root, left, right)
void PreorderDFS(Node *root) {
  if(root == NULL) return;
  cout<<root->data<<" ";
  PreorderDFS(root->left);
  PreorderDFS(root->right);
}


// DFS Traversal Inorder (left, root, right)
void InorderDFS(Node *root) {
  if(root == NULL) return;
  InorderDFS(root->left);
  cout<<root->data<<" ";
  InorderDFS(root->right);
}


// DFS Traversal Postorder (left, right, root)
void PostorderDFS(Node *root) {
  if(root == NULL) return;
  PostorderDFS(root->left);
  PostorderDFS(root->right);
  cout<<root->data<<" ";
}


//FINDING HEIGHT OF A TREE
int FindHeight(struct Node *root) {
  if(root == NULL) 
    return -1;
  return std::max(FindHeight(root->left), FindHeight(root->right)) + 1;
}



Node* GetNewNode(int data) {   //creating a node
  Node* newNode = new Node();
  newNode->data = data; 
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
};

Node* Insert(Node* root, int data);

bool Search(Node* root, int data) {  //searching node
  if(root == NULL) return false;
  else if(root->data == data) return true;
  else if(data <= root->data) return Search(root->left, data);
  else return Search(root->right, data);
}

int main() {
  Node* root = NULL;
  root = Insert(root, 15);   // Insert function
  root = Insert(root, 10);
  root = Insert(root, 20);
  root = Insert(root, 25);
  root = Insert(root, 8);
  root = Insert(root, 12);
  root = Insert(root, 13);

  int num = FindHeight(root); //TESTING finding height of a tree
  std::cout<<"Height of a tree is: "<<num<<"\n";


// Test function find max val in tree
  int max = FindMax(root);    
  cout<<"MAX value in tree: "<<max<<"\n";


// Test function find min val in tree
  int min = FindMin(root);    
  cout<<"MIN value in tree: "<<min<<"\n";


// TESTING BSF traversal
  cout<<"BSF Traversal: ";
  LevelOrder(root);    
  cout<<"\n";



//TEST DFS Preorder
  cout<<"DFS preorder: ";
  PreorderDFS(root);
  cout<<"\n";

//TEST DFS Inorder
  cout<<"DFS inorder: ";
  InorderDFS(root);
  cout<<"\n";

//TEST DFS Postorder
  cout<<"DFS postorder: ";
  PostorderDFS(root);
  cout<<"\n";


//Test fucntion that CHecks if this binary tree is BST
if (IsBinarySearchTree(root) == true) cout<<"This Binary tree is BST! \n";
else cout<<"This binary tree is NOT BST!";


//DELETING A NODE FROM BST
  cout<<"DFS inorder before deleting: ";
  InorderDFS(root);
  Delete(root, 20);
  //cout<<"\n";
  cout<<"DFS inorder after deleting: ";
  InorderDFS(root);



  //int number;
  //std::cout<<"Enter number be searched\n";
  //std::cin>>number;
  //if(Search(root, number) == true) std::cout<<"Found\n";        //TESTING SEARCH
  //else std::cout<<"Not Found";
} 


Node* Insert(Node* root, int data) {
  if(root == NULL) {
    root = GetNewNode(data);
  }
  else if(data <= root->data) {
    root->left = Insert(root->left, data);
  }
  else {
    root->right = Insert(root->right, data);
  }
  return root;
}
