/*In BST a number of nodes contain a NULL pointer, either in their left or right fields or in both.This
space that is wasted in storing a NULL pointer can be efficiently used to store some other useful piece
of information. For example, the NULL entries can be replaced to store a pointer to the in-order 
predecessor or the in-order successor of the node. These special pointers are called threads and binary
trees containing threads are called threaded trees.

Threaded binary tree may correspond to one-way threading or a two way threading.In one-way threading,a
thread will appear either in the right field or the left field of the node.

A one-way threaded tree is also called a single-threaded tree. If the thread appears in the left field
then the left field will be made to point to the in-order predecessor of thenode. Such a one-way 
threaded tree is called a left-threaded binary tree.

On the contrary,if the thread appears in the right field, then it will point to the in-order successor
of the node.Such a one-way threaded tree is called a rightthreaded binary tree.

In a two-way threaded tree, also called a double-threaded tree, threads will appear in both the left
and the right field of the node.While the left field will point to the in-order predecessor of the
node,the right field will point to its successor.A two-way threaded binary tree is also called a fully
threaded binary tree.

Advantages of Threaded Binary Tree
1.It enables linear traversal of elements in the tree.traversal is faster.
2.Linear traversal eliminates the use of stack which inturn consume a lot ofmemory space andcomputer
 time.
3.It enables to find the parent of a given element without explicit use of parent pointers.
4.Since nodes contain pointers to in-order predecessor and successor,the threaded tree enables
forward and backward traversal of the nodes as given by in-order fashion.***
5.By doing threading we neglect the recursive method of traversing a Tree which makes use of stack
 and consumes many memory and time 
6.The node can keep record of its root(PARENT)
7.Backword track is possible
8.bY USING null LINES in a binary tree to the special links called threads it is possible to 
  execute traversal insertion and deltion without using stack or recursion

Thus,we see the basic difference between binary tree and threaded binary tree is that in binary
tree a node stores a NULL pointer if it has no child and so there is no way to traverse back.

Disadvantage 
1.This makes the Tree more difficult

2.More prone to errors when both the child are not present & both values of nodes
 pointer to their ansentors
3.Insertion and deletion operation takes more time.
4.Tree traversal algorithm becomes difficult.
5.Memory required to store node increases.Each node has to store the information whether the links
 is normal links or threaded links.
 
SITUATION to use
1.Threaded trees are a important data structure where trees are created once with very less of 
insertions and deletions operations and more of traversal operations (specifically 
depth first traversals) are more in number to do.In such situations the threaded trees act as a 
boon for the system performance by reducing the space required for stacks.
2.when stack size is limited then we can use it.
3.application ->game tree,decision tree, expression treee

Time complexity of traversing TBST is O(n) where n is number of node in tree.
For insertion operation time complexity of TBST is also O(n) because is follows simple
rule of insertion of BST.
VIDEO->Threaded Binary Tree | Types, Conversion, Traversing, Insertion 
 Dr.Krishan Kumar, Gurukul Kangri University, India*/
 
#include<stdio.h>
#include<stdlib.h>
struct threadedtree
{
 char leftflag;//taken char data type to save space
 char rightflag;
 int data;
 struct threadedtree *right,*left;	
}*rootnode=NULL;//since global variable no need to assign NULL to rootnode
void insertion_orcreate_threaded_binattree (void);
void display(void);
struct threadedtree *leftmost(struct threadedtree* node);
int main()
{
	int option;
	do
	{
	printf("\n1.Create Traded Binary tree.");
	printf("\n2. Display.");
	printf("\nEnter Your option: ");
	scanf("%d",&option);
	switch(option)
	{
	 case 1:insertion_orcreate_threaded_binattree();
		    break;
	 case 2:display();
		    break;
	}
   }while(option<5);
	return 0;
}
void insertion_orcreate_threaded_binattree (void)//O(n)
{
 struct threadedtree *p;
 int element,flag;
 printf("\nEnter -1 to stop");
 printf("\nEnter element: ");
 scanf("%d",&element); 
 while(element != -1)
 {
  flag=0;
  struct threadedtree *newnode=(struct threadedtree*)malloc(sizeof(struct threadedtree));
  newnode->data=element;
  newnode->leftflag='Z';//Z means no child and predecessor and successor linke is present
  newnode->rightflag='Z';
  newnode->right=NULL;
  newnode->left=NULL;
  if(rootnode==NULL)
  {
  	rootnode=newnode;
  }
  else
  {
  	p=rootnode;
  	while((p->leftflag != 'Z' || p->rightflag != 'Z') )
  	{
  	 if(p->data == element)//to detech duplicate elements
     {
       flag=1;
       printf("\nElement %d already exist enter another element",p->data);
	   free(newnode);//because newnode is created so we have todelete becauseelement is same and memory
	   break;                                                                           //was allocated
     }
  	 if(p->data > element)
	  {
	  	if(p->leftflag == 'Z')//if it it true that means p node contain predecessor so break;
	  	  break;//terminate while loop so that newnode would be added
		 p=p->left; 	
	  }
	 else if(p->data < element)	
	  {
	  	if(p->rightflag=='Z')//if it is true that means p node contain successor so break;
	  	  break;//terminate while loop  so that newnode would be added
		 p=p->right; 	
	  }
	}	 	 	
	if(p->data != element)//if while loop and break statement execute then this statement execute
	{  
	  if(p->data > element)//element is smaller 
	  {
	   newnode->left=p->left;//p->left is predecessor node so assigning to newnode->left
	   newnode->right=p;//p will be successor of newnode
	   p->left=newnode;//linking child to left side as element is small
	   p->leftflag='C';//c indicate left side has child	
	  }
	  else if(p->data < element)//element is greater
	  {
	   newnode->right=p->right;//p->right is successor node so assigning to newnode->right
	   newnode->left=p;//p will be predecessor of newnode
	   p->right=newnode;//linking child to right side as element is greater
	   p->rightflag='C';//c indicate right side has child
	  }
    }
    else
    {
     if(flag==0)//when break statement execute then this statement will execute
      {
     printf("\nElement %d already exist enter another element",p->data);
    
	 free(newnode);//because newnode is created so we have todelete becauseelement is same and memory
	  }                                                                               //was allocated
	}
  }
   printf("\nEnter element: ");
   scanf("%d",&element); 
 }
}
void display(void)//O(n)
{
/*First go to leaft most child then print then go to rightside if link or thread is present then
   print and if link is not present then go to left most child and print repeat untill Null */
   struct threadedtree *cur=leftmost(rootnode);
   printf("\nIn order traversal Tradedbinary tree:");
   while(cur != NULL)
   {
   	printf(" %d",cur->data);
     if(cur->rightflag=='Z')//if cur->rightflag==Z indicate that node rightpointer contain inorder
     {                                                                             //successorlink
     	cur=cur->right;
	 }
	 else if(cur->rightflag =='C')//if cur->rightflag==C indicate that node has right child
	 {
	 	cur=leftmost(cur->right);
	 }
   }
}
struct threadedtree *leftmost(struct threadedtree* node)
{
	if(node==NULL)
	{
		return NULL;
	}
	else
	{
		while(node->leftflag=='C' && node->left!=NULL)//node->leftflag=='C'indicate left side is
		  {                //not link so go to left pointer if not terminate while loop 
			node=node->left;
		  }
		return node;
	}
}
