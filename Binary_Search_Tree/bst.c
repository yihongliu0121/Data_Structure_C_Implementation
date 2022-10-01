/*
  File: bst.c
  Implementation of the binary search tree data structure.
 
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "bst.h"
#include "structs.h"


struct Node {
    TYPE         val;
    struct Node *left;
    struct Node *right;
};

struct BSTree {
    struct Node *root;
    int          cnt;
};

/*----------------------------------------------------------------------------*/
/*
  function to initialize the binary search tree.
  param tree
  pre: tree is not null
  post:	tree size is 0
  root is null
*/

void initBSTree(struct BSTree *tree)
{
    tree->cnt  = 0;
    tree->root = 0;
}

/*
  function to create a binary search tree.
  param: none
  pre: none
  post: tree->count = 0
  tree->root = 0;
*/

struct BSTree*  newBSTree()
{
    struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
    assert(tree != 0);

    initBSTree(tree);
    return tree;
}

/*----------------------------------------------------------------------------*/
/*
  function to free the nodes of a binary search tree
  param: node  the root node of the tree to be freed
  pre: none
  post: node and all descendants are deallocated
*/

void _freeBST(struct Node *node)
{
    if (node != 0) {
	_freeBST(node->left);
	node->left = 0;
	_freeBST(node->right);
	node->right = 0;
	free(node);
    }
}

/*
  function to clear the nodes of a binary search tree
  param: tree    a binary search tree
  pre: tree ! = null
  post: the nodes of the tree are deallocated
  tree->root = 0;
  tree->cnt = 0
*/
void clearBSTree(struct BSTree *tree)
{
    _freeBST(tree->root);
    tree->root = 0;
    tree->cnt  = 0;
}

/*
  function to deallocate a dynamically allocated binary search tree
  param: tree   the binary search tree
  pre: tree != null;
  post: all nodes and the tree structure itself are deallocated.
*/
void deleteBSTree(struct BSTree *tree)
{
    clearBSTree(tree);
    free(tree);
}

/*----------------------------------------------------------------------------*/
/*
  function to determine if  a binary search tree is empty.

  param: tree    the binary search tree
  pre:  tree is not null
*/
bool isEmptyBSTree(struct BSTree *tree) { return (tree->cnt == 0); }

/*
  function to determine the size of a binary search tree

  param: tree    the binary search tree
  pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree) { return tree->cnt; }

/*----------------------------------------------------------------------------*/
/*
  recursive helper function to add a node to the binary search tree.
  param:  cur	the current root node
  val	the value to be added to the binary search tree
  pre:	val is not null
*/
struct Node *_addNode(struct Node *cur, TYPE val)
{
    /*write this*/
    struct Node *newnode;
    /* case1 - cur is null */
    if (cur == NULL)
    {/*create new node and return*/
        newnode = (struct Node *)malloc(sizeof(struct Node));
        assert(newnode != 0);
        newnode->val = val;
        newnode->left = newnode->right = 0;
        return newnode;
    }
    if (compare(val,cur->val) == -1)  //val < cur->val
        cur->left = _addNode(cur->left,val);
    else if (compare(val, cur->val) == 1)
        cur->right = _addNode(cur->right, val);
    return cur;
}

/*
  function to add a value to the binary search tree
  param: tree   the binary search tree
  val		the value to be added to the tree

  pre:	tree is not null
  val is not null
  pose:  tree size increased by 1
  tree now contains the value, val
*/
void addBSTree(struct BSTree *tree, TYPE val)
{
    tree->root = _addNode(tree->root, val);
    tree->cnt++;
}


/*
  function to determine if the binary search tree contains a particular element
  param:	tree	the binary search tree
  val		the value to search for in the tree
  pre:	tree is not null
  val is not null
  post:	none
  return true if val is in the tree, false if val is not in the tree
*/

/*----------------------------------------------------------------------------*/
bool containsBSTree(struct BSTree *tree, TYPE val)
{
    /* write this */
    struct Node *cur = tree->root;
    
    while (cur != 0) {
        if (compare(val,cur->val) == 0)
            return true; /* Return true if val found. */
        if (compare(val, cur->val) == -1)
            cur = cur->left; /* Otherwise, go to the left */
        else cur = cur->right; /* or right, depending on val. */
    }
    return false;

}

/*
  helper function to find the left most child of a node
  return a pointer of the left most child of cur
  param: cur		the current node
  pre:	cur is not null
  post: none
*/

/*----------------------------------------------------------------------------*/
struct Node *_leftMost(struct Node *cur)
{
    /*write this*/
    while (cur->left != 0)
        cur = cur->left;
    return cur->val;

}


/*
  recursive helper function to remove the left most child of a node
  HINT: this function returns cur if its left child is NOT NULL. Otherwise,
  it returns the right child of cur and free cur.

  Note:  If you do this iteratively, the above hint does not apply.

  param: cur	the current node
  pre:	cur is not null
  post:	the left most node of cur is not in the tree
*/
/*----------------------------------------------------------------------------*/
struct Node *_removeLeftMost(struct Node *cur)
{
    /*write this*/
    struct Node *node;
    
    if (cur->left != 0) {
        cur->left = _removeLeftMost(cur->left);
        return cur;
    }
    
    node = cur->right;
    free(cur);
    return node;

}
/*
  recursive helper function to remove a node from the tree
  param:	cur	the current node
  val	the value to be removed from the tree
  pre:	val is in the tree
  cur is not null
  val is not null
*/
/*----------------------------------------------------------------------------*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
    /*write this*/

    struct Node *temp;
    if (compare(val, cur->val) == 0) { /* Found val. */
        if (cur->right == 0) {
            temp = cur->left;
            free(cur);
            return temp;
        }
        cur->val = _leftMost(cur->right);
        cur->right = _removeLeftMost(cur->right);
    }
    else if (compare(val, cur->val) == -1)
        cur->left = _removeNode(cur->left, val);
    else
        cur->right = _removeNode(cur->right,val);
    return cur;

}
/*
  function to remove a value from the binary search tree
  param: tree   the binary search tree
  val		the value to be removed from the tree
  pre:	tree is not null
  val is not null
  val is in the tree
  pose:	tree size is reduced by 1
*/
void removeBSTree(struct BSTree *tree, TYPE val)
{
    if (containsBSTree(tree, val)) {
	tree->root = _removeNode(tree->root, val);
	tree->cnt--;
    }
}

/*----------------------------------------------------------------------------*/

/* The following is used only for debugging, set to "#if 0" when used 
   in other applications */
#if 1
#include <stdio.h>

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
    if (cur == 0)
	return;
    printf("(");
    printNode(cur->left);	 
    printNode(cur->right);
    printf(")");
}

void printTree(struct BSTree *tree) {
    if (tree == 0)
	return;	 
    printNode(tree->root);	 
}
/*----------------------------------------------------------------------------*/

#endif


/************************************************************************************************************************
from here to the end of this file are a set of fucntions for testing the fucntions of the BST
***************************************************************************************************************************/
/*
  function to built a Binary Search Tree (BST) by adding numbers in this specific order
  the graph is empty to start: 50, 13, 110 , 10

*/
struct BSTree *buildBSTTree() {
    /*     50
	 13  110
       10 
    */
    struct BSTree *tree	= newBSTree();		
		
    /*Create value of the type of data that you want to store*/
	
    /*add the values to BST*/
    addBSTree(tree, 50);
    addBSTree(tree, 13);
    addBSTree(tree, 110);
    addBSTree(tree, 10);
    
    return tree;
}

/*
  function to print the result of a test function
  param: predicate:  the result of the test 
  nameTestFunction : the name of the function that has been tested
  message

*/
void printTestResult(int predicate, char *nameTestFunction, char *message){
    if (predicate)
	printf("%s(): PASS %s\n",nameTestFunction, message);
    else
	printf("%s(): FAIL %s\n",nameTestFunction, message);        
}

/*
  fucntion to test each node of the BST and their children

*/
void testAddNode() {
   struct BSTree *tree	= newBSTree();
   addBSTree(tree, 50);
   //check the root node
   if (tree->root->val != 50) {
      printf("addNode() test: FAIL to insert 50 as root\n");
      return;
   }
   //check the tree->cnt value after adding a node to the tree
   else if (tree->cnt != 1) {
      printf("addNode() test: FAIL to increase count when inserting 50 as root\n");
      return;
   }
   else
      printf("addNode() test: PASS when adding 50 as root\n");


   addBSTree(tree, 13);

   //check the position of the second element that is added to the BST tree
   if (tree->root->left->val != 13)  {
      printf("addNode() test: FAIL to insert 13 as left child of root\n");
      return;
   }
   else if (tree->cnt != 2) {
      printf("addNode() test: FAIL to increase count when inserting 13 as left of root\n");
      return;
   }
   else
      printf("addNode() test: PASS when adding 13 as left of root\n");


   addBSTree(tree, 110);

   //check the position of the third element that is added to the BST tree    
   if (tree->root->right->val!=110) {
      printf("addNode() test: FAIL to insert 110 as right child of root\n");
      return;
   }
   else if (tree->cnt != 3) {
      printf("addNode() test: FAIL to increase count when inserting 110 as right of root\n");
      return;
   }
   else
      printf("addNode() test: PASS when adding 110 as right of root\n");

   addBSTree(tree, 10);

   //check the position of the fourth element that is added to the BST tree
   if (tree->root->left->left->val != 10) {
      printf("addNode() test: FAIL to insert 10 as left child of left of root\n");
      return;
   }
   else if (tree->cnt != 4) {
      printf("addNode() test: FAIL to increase count when inserting 10 as left of left of root\n");
      return;
   }
   else
      printf("addNode() test: PASS when adding 10 as left of left of root\n");

   printf("Deleting the BSTree...\n");
   deleteBSTree(tree);
   printf("Returning from testAddNode().\n");
}

/*
  fucntion to test that the BST contains the elements that we added to it

*/
void testContainsBSTree() {
    struct BSTree *tree = buildBSTTree();
    
    printTestResult(containsBSTree(tree, 50), "containsBSTree", "when test containing 50 as root");
        
    printTestResult(containsBSTree(tree, 13), "containsBSTree", "when test containing 13 as left of root");
    
    printTestResult(containsBSTree(tree, 110), "containsBSTree", "when test containing 110 as right of root");
        
    printTestResult(containsBSTree(tree, 10), "containsBSTree", "when test containing 10 as left of left of root");

    //check containsBSTree fucntion when the tree does not contain a node    
    printTestResult(!containsBSTree(tree, 111), "containsBSTree", "when test containing 111, which is not in the tree");

    printf("Deleting the BSTree...\n");
    deleteBSTree(tree);
    printf("Returning from testContainsBSTree().\n");

}

/*
  fucntion to test the left_Most_element 

*/
void testLeftMost() {
    struct BSTree *tree = buildBSTTree();
    
    printTestResult(_leftMost(tree->root)->val == 10, "_leftMost", "left most of root");
    
    printTestResult(_leftMost(tree->root->left)->val == 10, "_leftMost", "left most of left of root");
    
    printTestResult(_leftMost(tree->root->left->left)->val == 10, "_leftMost", "left most of left of left of root");
    
    printTestResult(_leftMost(tree->root->right)->val == 110, "_leftMost", "left most of right of root");

    printf("Deleting the BSTree...\n");
    deleteBSTree(tree);
    printf("Returning from testLeftMost().\n");

}

void testRemoveLeftMost() {
    struct BSTree *tree = buildBSTTree();
    struct Node *cur;
    
    cur = _removeLeftMost(tree->root);

    printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 1st try");
    
    cur = _removeLeftMost(tree->root->right);
    printTestResult(cur == NULL, "_removeLeftMost", "removing leftmost of right of root 1st try");
    if (!cur)
        tree->root->right = NULL;
    cur = _removeLeftMost(tree->root);
    printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 2st try");
    deleteBSTree(tree);
}

void testRemoveNode() {
    struct BSTree *tree = buildBSTTree();
    struct Node *cur;

    _removeNode(tree->root, 10);
    printTestResult(tree->root->val == 50 && tree->root->left->left == NULL, "_removeNode", "remove left of left of root 1st try");
	        
    _removeNode(tree->root, 110);
    printTestResult(tree->root->val == 50 && tree->root->right == NULL, "_removeNode", "remove right of root 2st try");
	   
    _removeNode(tree->root, 13);
    printTestResult(tree->root->val == 50 && tree->root->left == 0, "_removeNode", "remove left of root 3st try");
        
    cur = _removeNode(tree->root, 50);
    printTestResult(cur == NULL, "_removeNode", "remove root 4st try");
    if (!cur)
        tree->root = NULL;
    deleteBSTree(tree);
}

/*

  Main function for testing different fucntions of the Assignment#4.

*/

int main(int argc, char *argv[]){	

    //After implementing your code, please uncommnet the following calls to the test functions and test your code 

    testAddNode();
	
    printf("\n");
    testContainsBSTree();
	
    printf("\n");
    testLeftMost();
	
    printf("\n");
    testRemoveLeftMost();
	
    printf("\n");
    testRemoveNode();
	
    return 0;
}
