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
forward and backward traversal of the nodes as given by in-order fashion.
5.By doing threading we neglect the recursive method of traversing a Tree which makes use of stack
 and consumes many memory and time 
6.The node can keep record of its root(PARENT)
7.Backword track is possible

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
Threaded trees are a important data structure where trees are created once with very less of 
insertions and deletions operations and more of traversal operations (specifically 
depth first traversals) are more in number to do.In such situations the threaded trees act as a 
boon for the system performance by reducing the space required for stacks.
VIDEO->Threaded Binary Tree | Types, Conversion, Traversing, Insertion Dr. Krishan Kumar, Gurukul
        Kangri University, India
VIDEO->Threaded Binary Tree (TBT) IN Data Structure Explaination Vivekanand Khyade
*/
#include<stdio.h>//this code is one way threaded binary tree.it will not work in second time 
#include<stdlib.h>//right way threaded binary tree
struct tradtree //the idea of making tbt is to make inorder traversal faster and do it without stack
{               //and recursion.binary tree is made threaded by making all right child pointer that
	struct tradtree *left; //would normally be nullpoint to inorder successor of the node if exists
	int leftflag;
	int data;
	int rightflag;        //we are fist creating treaded tree 2. doing inorder traversal we also
	struct tradtree *right;// set successor to node one by one while traversing
}*rootnode=NULL;
struct stack
{
	struct tradtree *tradaddress;
	struct stack *next;
}*top=NULL;
void insertnode(void);
void inordertraversal_and_replacing_o_with_predecessorandsuccessor(void);//creating threaded tree
struct tradtree *return_successor_address(struct tradtree* ,int element);
struct tradtree *return_predecessor_address(struct tradtree* ,int element);
void pushintostack(struct tradtree *);
struct tradtree *pop();
void checkingtradedtree(struct tradtree *); 
void inordertraversalofTBT(void);
struct tradtree *leftmost(struct tradtree*);
int main()
{
	int option;
	do
	{
	printf("\n1.Create Traded Binary tree.");
	printf("\n2. Inorder traversal of TBT.");
	printf("\nEnter Your option: ");
	scanf("%d",&option);
	switch(option)
	{
	 case 1:insertnode();
		    inordertraversal_and_replacing_o_with_predecessorandsuccessor();//creating threadedtree
		    break;
	 case 2:inordertraversalofTBT();
		    break;
	}
   }while(option<5);
	return 0;
}
void insertnode(void)
{
//same like creating BST with little difference
int element;
struct tradtree *ptr,*r;
printf("\nEnter -1 to stop");
printf("\nEnter element: ");
scanf("%d",&element);
while(element!=-1)
{
 struct tradtree *newnode;
 newnode=(struct tradtree*) malloc (sizeof(struct tradtree));
 newnode->left=NULL;//it is pointer so NULL can be stored
 newnode->leftflag=0;//it represents no left child 1 represent left child
/*newnode->leftflag=NULL; produce error because here we have datatype int so newnode->leftflag which
  point to int so using NULL produce error because integer datatype cannot store NULL.
  REASON:
  we cannot use 0 Instead of null in our programs even though null is represented by the value 0.
  it should be only be use when it make sence for an bject that is having no value associated with it
  NULL is not a value.it means abesece of data but 0 is data.NULL is used to terminate string and do
  not add additional data for string size in database 0 is a value and null means no value exists,null
  is not a memory location only pointer and variables hold memory locations.without a null charater 
  string would not terminate correctly which would cause problem*/ 
  
 newnode->data=element;     
 newnode->rightflag=0;//it represents no right child 1 represent right child
 newnode->right=NULL;      
 if(rootnode==NULL)      
 {   	    
  rootnode=newnode;
 }
 else
 {       	
  ptr=rootnode;		   
  while(ptr!=NULL)
  {
   r=ptr;
   if(ptr->data==element)
   {
    printf("\nElement %d already exist enter another element",ptr->data);
	free(newnode);//because newnode is created so we have to delete becauseelement is same and memory
	break;                                                                            //was allocated
   }
/*else if( ptr->data < element)
   {
	ptr=ptr->right;
   }
  else if( ptr->data > element )
   {
	ptr=ptr->left;
   }*/
	ptr=(ptr->data < element)?ptr->right:ptr->left;//using ternary operator to short the code
   }             
   if(r->data!=element)//if element is same then it will not execute it will ask user to enter
    {                                //another element.IT prevents to enter duplicates element
	 /*if(r->data > element)
        {
	     r->left=newnode;
		 r->leftflag=1;	//1 means it has right child no threads
		}
	  else if(r->data < element)
		{
	     r->right=newnode;
		 r->rightflag=1;//1 means it has right child no threads
		}*/
	(r->data > element)?((r->left=newnode)&&(r->leftflag=1)) :((r->right=newnode)&&(r->rightflag=1));
	}
	printf("\n%u %d %d %d %u",r->left,r->leftflag,r->data,r->rightflag,r->right);//for information
  }
    printf("\nEnter element: ");
	scanf("%d",&element);
}
}
void pushintostack(struct tradtree *tradaddress)
{
     struct stack *newnode;
	 newnode=(struct stack *)malloc(sizeof(struct stack));
	 newnode->tradaddress=tradaddress;
	 newnode->next=top;	
	 top=newnode;
}
struct tradtree *pop()
{
    struct tradtree *hold_toreturn_address;
    struct stack *hold_addresss_to_free;
    if(top==NULL)//this would never execute because while traversing we check top=null in advance
    {
    	printf("stack is empty");
	}
	else
	{
	hold_addresss_to_free = top;
	hold_toreturn_address = top->tradaddress;
	top=top->next;//updating top pointer
	free(hold_addresss_to_free);//freeing stack node to prevent memory leak
	
	return(hold_toreturn_address);
    }	
}
void inordertraversal_and_replacing_o_with_predecessorandsuccessor(void)//creating threaded tree
{                                          //only successor is applied not predecessor
if(rootnode==NULL)
 {
  printf(" Tree is empty.");
 }
else
{
 struct tradtree *p,*holdaddress,*holdsuccessoraddress,*holdpredecessoraddress;
 p=rootnode;                   //holdpredecessoraddress not needed for understanding using
 printf("\nIn-Order Traversal:");
 while(1)
 {
  //doing inorder traversal and node which rightflag is 0  is repaced with inorder successor
  while(p) 
  {
   pushintostack( p);
   p=p->left;
  }
  if(top==NULL) //advancce checking for NULL
  {
   break;
  } 
  holdaddress=p=pop();
  //printf(" %d",p->data); //to print inorder traversal but zig zag
  p=p->right;	
  if(holdaddress->rightflag==0)//it means we can store inordersuccessor node to point to ancestor
  {
   holdsuccessoraddress=return_successor_address(holdaddress,holdaddress->data);
   holdaddress->right=holdsuccessoraddress;//right pointer is updated inorder successor value
  }
  /*if(holdaddress->leftflag==0) //for inorder we are nor using it
     {
	  holdpredecessoraddress=return_predecessor_address(holdaddress,holdaddress->data);
	  holdaddress->left=holdpredecessoraddress;
	 }
 checkingtradedtree(holdaddress);*///if both if statement dont execute that means that node has
 }                                                                       //both left right node
}//else
}
struct tradtree *return_successor_address(struct tradtree* addressofnode,int element_ofaddressofnode)
{
/*Video->INORDER SUCCESSOR in binary search tree[CODE Explained] Vivekanand Khyade

 To find inorder successor there are two cases ie.1.if node has right sub tree then find the least
 value node from that right subtree and 2.if node has no right subtree then search from root to
 current node and find out the node from where it take last left that node is the answere.
 this condition is for inorder successor for inorder predecessor it has 2 case which is opposite.
 So in this alogorithm 2nd cindition will be applied because in threaded binary tree threads going
 to be applied to those node which right pointer is null so here second case is suitable so algo.will
 be made accordeing to second case.*/ 

  int flag=0;
  struct tradtree *s,*storerecentleftpointer;
  s=rootnode;
  while(s->data != element_ofaddressofnode )//traversing from root to last
  {
  	 /*if(element_ofaddressofnode < s->data)
  	 {
  	 	flag=1;
  	 	storerecentleftpointer=s; //to get successor node we have to take recent left pointer
  	 	s=s->left;
	 }
	 else if(element_ofaddressofnode > s->data)
	 {
	 	s=s->right;
	 }*/
	 (element_ofaddressofnode < s->data)? ((flag=1)&&(storerecentleftpointer=s))&&(s=s->left) : (element_ofaddressofnode > s->data)&&(s=s->right);//using ternary operator
  }
  if(flag==1)
  {
  return storerecentleftpointer;
  }
  else if(flag==0)//if there is no left turn that means it is the last node and should store
  {                                                                  //null due to last node
  	return NULL; 
  }
}
struct tradtree *return_predecessor_address(struct tradtree* addressofnode,int elementofaddressofnode)
{
	int flag=0;
	struct tradtree  *s,*storerecentrightpointer;
	s=rootnode;
	while(s->data!=elementofaddressofnode)
	{
		/*if(elementofaddressofnode > s->data )
		{
			flag=1;
			storerecentrightpointer=s;//to get predecessor node we have to take recent right pointer
			s=s->right;
		}
		else if(elementofaddressofnode < s->data)
		{
			s=s->left;
		}*/
	(elementofaddressofnode > s->data)? ((flag=1)&&(storerecentrightpointer=s))&&(s=s->right) : (elementofaddressofnode < s->data) && (s=s->left);//using ternary operator
	}
	if (flag==1)
	{
	  return storerecentrightpointer;	
	}
	else if(flag==0)//if there is no right turn that means it is the  last node and should store null since last node 
	{
		return NULL;
	}
}
/*void checkingtradedtree(struct tradtree *tradtreenode) //this fubc is just for checking left and right node
{
	printf("\n");
 if(tradtreenode->left!=0)
 {
 	printf("pre=%d leftflag=%d ",tradtreenode->left->data,tradtreenode->leftflag);
 }
 else
 {
 	printf("node %d left pointer is 0 so it is starting node ",tradtreenode->data);
 }
 printf(" node=%d ",tradtreenode->data);
 if(tradtreenode->right!=0)
 {
 	printf("rightflag=%d succ=%d",tradtreenode->rightflag,tradtreenode->right->data);
 }
 else
 {
 		printf(" node%d right pointer is 0 so it is last node",tradtreenode->data);
 }
//	printf("\npre=%d leftflag=%d curnode=%d rightflag=%d succ=%d",tradtreenode->left->data,tradtreenode->leftflag,tradtreenode->data,tradtreenode->rightflag,tradtreenode->right->data);// error
   //because when tradtreenode->left is null tradtreenode->left->data we r accessing data which is illegal
}*/
void inordertraversalofTBT(void)
{//VIDEO->Data Structure: Threaded Binary vinay singh                                         
//we are traversing without stack each right node contain inorder successor and each left pointer contain NULL
   struct tradtree *cur=leftmost(rootnode);
   printf("\nIn order traversal Tradedbinary tree:");
   while(cur != NULL)
   {
   	printf(" %d",cur->data);
     if(cur->rightflag==0)//if cur->rightflag==0 indicate that node right pointer contain inorder successor
     {                                                                                            //threads
     	cur=cur->right;
	 }
	 else if(cur->rightflag==1)//if cur->rightflag==1 indicate that node has right child
	 {
	 	cur=leftmost(cur->right);
	 }
   }
}
struct tradtree *leftmost(struct tradtree* node)
{
	if(node==NULL)
	{
		return NULL;
	}
	else
	{
		while(node->left!=NULL)
		{
			node=node->left;
		}
		return node;
	}
}
 
