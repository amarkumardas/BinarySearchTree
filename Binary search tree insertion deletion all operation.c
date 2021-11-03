/*Worst Time complexity of BST wheather insertion or deletion or search operation is O(h) h is height
of tree this occur when BST is not skrew binary tree
VIDEO->Time Complexities of Binary Search Trees Operations | Search, Insert and Delete Operations

In skrew binarysearch tree then worst time complexity (insertion,deletion,searching) of BST is O(n)
n is total no. of elements.

BEST case of BST occur when tree is balanced (AVL tree) insertion,deletion,searching with height log n
is O(logn)     

TIME COMPLEXITY of inorder,pre order,post order is O(n) where n is total number of elements because we
have to traverse all nodes
 
code will work fine tree must be correct and it should be binary search tree. 
 */
 
#include<stdio.h>
#include<stdlib.h> 
struct tree    
{
	int data;
	struct tree *left,*right;
}*rootnode=NULL;//globally variable contain 0 so no need to give NULL.C language follows static scoping
struct stack  
{	 
	struct tree *address;
	struct stack *next;
}*top=NULL;    //globally variable contain 0 so no need to give NULL
 
struct circular_queue//linked list queue
{
  struct tree *address;
  struct circular_queue *next;	
};
struct circular_queue *front,*rear;
void enque_linkedlist_queue(struct tree *);
struct tree *deque_linkedlist_queue(void);
void pushintostack(struct tree *);
struct tree *pop();                                 
void insertelement(void);
void preordertraversal(void);
void inordertraversal(void);
void postordertraversal(void);
void levelordertraversal(void);
void smallestandhigestnodeintree(struct tree*);
void deletenode(void);
struct tree *searchnodereturnparentnode(int);
int checkfornumberofchild(struct tree*,int);
void deletezerochild(struct tree*,int);
void deletesinglechild(struct tree*,int);
void deletetwochild(struct tree*,int);
int inordersuccessor(struct tree*,int );
void totalnumberofnodes(struct tree*);
void heightoftree(struct tree*);
void deleteentiretree(struct tree*);
int main()
{
	int option;
	enum{insertintotree=1,preorder,inorder,postorder,smallestandhigest,deletee,levelorder,totalnodes,height,deletetree};//it can be either golbally or locallly
	
	do
	{
		printf("\n\n1.To insert element into tree.");
		printf("\n2.Pre-Order traversal.");
		printf("\n3.In-Order Traversal.");
		printf("\n4.Post-order traversal");
		printf("\n5.Smallest and Higest node in Binary search tree.");
		printf("\n6.Delete node.");
		printf("\n7.Level order traversal.");
		printf("\n8.Total number of Nodes,Leaf node,Internal node.");
		printf("\n9.Height of tree.");
		printf("\n10.Delete Entire tree");
		printf("\nEnter your option.");
		scanf("%d",&option);
		switch(option)
		{
			case insertintotree:insertelement();
			     break;
			case preorder:preordertraversal();    //not in youtube at all
			     break;
			case inorder:inordertraversal();
			     break;
		    case postorder:postordertraversal();
		         break;
		    case smallestandhigest:smallestandhigestnodeintree(rootnode);
		         break;
		    case deletee: deletenode();
		    	 break;
		    case levelorder: levelordertraversal();
		         break;
		    case totalnodes:totalnumberofnodes(rootnode);
		         break;
		    case height:heightoftree(rootnode);
		         break;
		    case deletetree:deleteentiretree(rootnode );
		         break;
		}
	}while(option<=206546);
	return 0;
}
void insertelement(void)//average case O(logn) worst case O(n)
{
	int element;
	printf("\nEnter -1 to stop.");
	printf("\nEnter element: ");
	scanf("%d",&element);
	while(element!=-1)
	{ 
	    struct tree *newnode,*ptr,*r;
		newnode=(struct tree*)malloc(sizeof(struct tree));
		newnode->data=element;
		newnode->left=NULL;
		newnode->right=NULL;	
		if(rootnode==NULL)
		{
			rootnode=newnode; //it will execute only for first node
		}
		else
		{
			ptr=rootnode;
			while(ptr!=0)
			{
				r=ptr;//r hold previous pointer
				if(ptr->data==element)//checking double element is present or not
				{
					printf("\nElement %d already present enter another element",ptr->data);//or element
					free(newnode);//because newnode is created so we have to free because element is 
					break;        //same and memory was allocated
				}
				else if( ptr->data < element)
				{
					ptr=ptr->right;
				}
				else if( ptr->data > element )
				{
			     	ptr=ptr->left;
			   }
			}
		 if(r->data != element)//if element is same then it will not execute it will ask user to enter another element
		 {                                                                         
			if( r->data < element )
			{
				r->right=newnode;   //connecting newnode
			}
			else if(r->data > element)
			{
				r->left=newnode;  //connecting newnode
			}
		 }
		}	
	  printf("\nEnter element: ");
	  scanf("%d",&element); 	
	}
}
void pushintostack(struct tree *add)
{//video of Pointer type casting in C / c language tutorial videos
 struct stack *newnode;
 newnode=(struct stack*)malloc(sizeof(struct stack));
 newnode->address=add;
 newnode->next=top; 
 top=newnode;
}
struct tree *pop(void)
{	
  struct stack *temp;
  struct tree *hold_address_toreturn;
  if(top==0)
  {
   	printf("\nstack is empty.");
  }
  else
  {
   temp=top;
   hold_address_toreturn=temp->address; //address is stored in hold_address_toreturn
   top=top->next; 
   free(temp);//temp hold address of stack.Stack node is created using malloc so memory is created
                                                 //in heap so freeing memory to avoid memeory leak
  }
return hold_address_toreturn;//since return type of function is struct tree so hold_address_toreturn
}                                                                         //has datatype struct tree
void preordertraversal(void)
{//root left right  
/*iterative space complexity is O(h),where h is the height of the treeit is used to create copy of tree
it is used to extract prefix notation from expression tree.It is also known as depth first traversal*/

   if(rootnode==0)
   {
     printf(" Tree is empty.");
   }
   else 
   {
	struct tree *p;                     //after function complete execution global top becomes 0
	p=rootnode;
    printf("\nPre-Order Traversal:");
	while(1)
	{	
		while(p)
		{
			printf(" %d",p->data);//root is visited so printing element
			pushintostack(p);
			p=p->left;
		}
		if(top==0)//if stack is empty then it will execute which means every node is traversed
		{
	    	break;//terminate while loop
		}
		 p=pop();
		 p=p->right;	
	}
   }
}
void inordertraversal(void)
{//left root right
//it is usually used to display elements of tree in sorted order
 if(rootnode==0)
 {
  printf(" Tree is empty.");
 }
 else
 {
	struct tree *p;
	p=rootnode;
    printf("\nIn-Order Traversal:");
	while(1)
	{
		while(p)
		{
			pushintostack( p);
			p=p->left;
		}
		if(top==0)
		{
	    	break;
		}
			p=pop();
			printf(" %d",p->data);
			p=p->right;	
	}
 }
}
void postordertraversal(void)
{//VIDEO->Iterative Postorder Traversal using one stack Vivekanand Khyade
/*It is used to delete tree because child node is deleted before parent node.It is nature of
 postordertraversal.we can delete with other traversal also but that will require extra space
 complexity.It is used to extract postfix notation from an expression tree*/
if(rootnode==NULL)
{
  printf(" Tree is empty");
}
else
{
 struct tree *p;
 p=rootnode;
 printf("\nPost order traversal:");
  while(1)
  {
   if(p)
   	{
   	  pushintostack( p);
	  p=p->left;
	}
   else
	{
	 if(top==NULL)
	    break;//terminate while loop
	 else
	 {
	   if(top->address->right== NULL)//means left is null right is null then root is printed
	    {
	      p=pop();
	      printf(" %d",p->data);
	      if(top==NULL)//this will work when tree is like skrew eg: 5 4 3 2 1 so this will terminate
		  break;                                                //illegal operation may be performed
		  
	        while(top->address->right==p)//checking in advance if it is true then topnode is parent
	        {                                                 //of p.This loop is likeback tracking
	          printf(" %d",top->address->data);     
	          p=pop();
	          if(top==NULL)   
			    break;
			}
	     }
	     if(top!=NULL)
		    p=top->address->right;//it shift pointer to right side
		 else
		    p=NULL;//this will only execute when stack become empty
	  }
	 }
   }//while loop
 }
}
void smallestandhigestnodeintree(struct tree*rootnode)
{
	struct tree *currentnode;
	currentnode=rootnode;
	if(rootnode==NULL)
	{
		printf("\nTree is empty");
	}
	else
	{
	while(currentnode->left!=NULL)
	{
		currentnode=currentnode->left;
	}
	printf("Smallest node: %d",currentnode->data);
		currentnode=rootnode;
	while(currentnode->right!=NULL)
	{
		currentnode=currentnode->right;
	}
	printf("\nHigest node: %d",currentnode->data);
 }
}
void deletenode(void)//to delete node we need parent node that is necessary
{
	struct tree *parentnode,*curleft,*curright;
	int element,noofchild;
 if(rootnode==NULL)
 {
		printf("Tree is empty");
 }
else
{
  printf("\nEnter Element to delete: ");
  scanf("%d",&element);//code can be make short
 if((element==rootnode->data && rootnode->left!=NULL) && rootnode->right!=NULL)
 {//to delete root node there are 3 condition 
  struct tree *fake_parentnode=(struct tree*)malloc(sizeof(struct tree));//taken as dummy node
  fake_parentnode->left=NULL;
  fake_parentnode->right=rootnode;
  deletetwochild(fake_parentnode,element);
  free(fake_parentnode); //dynamically created so relesing it
  printf("\n1Rootnode %d",rootnode->data);	
 }
 else if((element==rootnode->data && rootnode->left!=NULL) && rootnode->right==NULL)
 {
   struct tree *fake_parentnode=(struct tree*)malloc(sizeof(struct tree));
   fake_parentnode->left=NULL;
   fake_parentnode->right=rootnode;
   deletesinglechild(fake_parentnode,element);
   rootnode=fake_parentnode->right;
   free(fake_parentnode); 
   printf("\n2Rootnode %d",rootnode->data); 
 }
 else if((element==rootnode->data && rootnode->left==NULL) && rootnode->right!=NULL)
 {
 	struct tree *fake_parentnode=(struct tree*)malloc(sizeof(struct tree));
   fake_parentnode->left=NULL;
   fake_parentnode->right=rootnode;
   deletesinglechild(fake_parentnode,element);
   rootnode=fake_parentnode->right;
   free(fake_parentnode); 
   printf("\n3Rootnode %d",rootnode->data);
 }
 else
{	
  parentnode=searchnodereturnparentnode(element);
  if(parentnode==(struct tree *)-11)//-11 should not contain in tree then only it
  {                                   //will work correctly.we can give -infinity
		printf("\nTREE is empty now");
  }
  else
  {
	if(parentnode==0)//if function return searchnodereturnparentnode(element); 0
	{                                  //then element is not there in tree
	printf("\nElement not found.");	
	}
   else 
    {
	 noofchild=checkfornumberofchild(parentnode,element);//sending element to
      if(noofchild==0)                            //identify left or right node
      {
         deletezerochild(parentnode,element);	
	  }
	  else if(noofchild==1)
	  {
	  	 deletesinglechild(parentnode,element);
	  }
	  else if(noofchild==2)
	  {
	  	deletetwochild(parentnode,element);
	  }
    }
  }
 }
}
}
struct tree *searchnodereturnparentnode(int element)
{
 struct tree *temp,*parent;
 temp=rootnode;
 while(1)
 {
  if((rootnode->left==NULL && rootnode->right==NULL) && (rootnode->data==element))//when
   {                                                            //there is only one node
	 printf("\nONLY ONE NODE IS PRESENT ROOT NODE : %d DELETED",temp->data);
	 free(temp);
	 rootnode=NULL;//since it is rootnode address is deleted so initializing to NULL
	 return ((struct tree*)-11); 
   }
  if(element >= temp->data)//if element is greater then pointer will point to right side
   {
	if(element == temp->data)
	 {
	   return(parent);
	 }
	   parent=temp;//here previous address is stored
	   temp=temp->right;         //the rootnode cant be deleted evenif inorder successor
   }
  else if(element <= temp->data)//ifelement is smaller then pointer willpoint to leftside
   {
	 if(element == temp->data)
	  {
		return(parent);
	  }
		parent=temp;//here previous address is stored
		temp=temp->left;
   }
	 if(temp==NULL)//it will be null when temp->left or temp->right is null it will become
	  {                                                      // null at the end of subtree
		return(0); //when Element not found.
	  }
 }	
}
int checkfornumberofchild(struct tree*parentnode,int element)
{
	struct tree *curleftnode,*currightnode;
	curleftnode=parentnode->left;
	currightnode=parentnode->right;
	if(((curleftnode!=NULL) && curleftnode->data==element) && curleftnode->left==curleftnode->right )//important concept applied here suppose curleftnode=parentnode->left;
	{                                //curleftnode is null then in if statement we are trying to access curleftnode->left which is illegal so concept of && and || operator
		return 0;  //for 0 child we have 2 possibilities
	}
	else if (((currightnode!=NULL) && currightnode->data==element) && currightnode->left==currightnode->right) //for 0 node both side will be null so checking
	{
		return 0;  //for 0 child 
	}                                                              //curleftnode has two possibilities so we used or operator
	else if(((curleftnode!=NULL) &&  curleftnode->data==element) && ((curleftnode->left==NULL && curleftnode->right!=NULL )|| (curleftnode->left!=NULL && curleftnode->right==NULL )))
	{                                                           
		return 1;   //for 1 child  we have 4 possibilities 
	}
	else if(((currightnode!=NULL) &&  currightnode->data==element) &&((currightnode->left==NULL && currightnode->right!=NULL )|| (currightnode->left!=NULL && currightnode->right==NULL)))
	{
		return 1;   //for 1 child 
	}
	else //if(curleftnode->left!=NULL && curleftnode->right!=NULL ||  currightnode->left!=NULL && currightnode->right!=NULL  )//not exact condition
	{
		return 2;  //for 2 child
	}
}
void deletezerochild(struct tree* parentnode,int element)
{
	printf("parent node = %d ",parentnode->data);
	if( (parentnode->left!=NULL) && parentnode->left->data == element)
	{
		
		printf("\nDeleted element: %d",parentnode->left->data );
		free(parentnode->left);
		parentnode->left=NULL;
		printf(" Leftnode");
	}
	else if((parentnode->right!=NULL) && parentnode->right->data == element)//or just else without condition
	{
		  printf("\nDeleted element: %d",parentnode->right->data );
		  free(parentnode->right);
	      parentnode->right=NULL;
		  printf(" Rightnode");	
	}	
}
void deletesinglechild(struct tree* parentnode,int element)
{//this code can be make short
	printf("parent node = %d ",parentnode->data);
    struct tree *curleft,*curright;
  	curleft=parentnode->left;
  	curright=parentnode->right;
  	if((parentnode->right!=NULL) && (parentnode->right->data==element))//checking element to decide element
  	{                                                                    //is present in left or right node
  		if(curright->right!=NULL)
  		{
  			parentnode->right=curright->right; //updating address to parent node
		}
		else if(curright->left!=NULL)
		  {
		  	parentnode->right=curright->left;
		  }
		  printf("\nDeleted node: %d",curright->data);
		  free(curright);
		  printf(" Right node");
	 }
	else if((parentnode->left!=NULL) && (parentnode->left->data==element))
	 {
	 	if(curleft->right!=NULL)
	 	{
	 	   	parentnode->left=curleft->right;	
		 }
		 else if(curleft->left!=NULL) 
		 {
		 		parentnode->left=curleft->left;	
		 }
		 printf("\nDeleted node: %d",curleft->data);
		 free(curleft);
		 printf(" Left node");
	 }	
}
void deletetwochild(struct tree* parentnode,int element)
{
struct tree* currentnode;
int datatoreplace;

currentnode=((parentnode->right!=NULL) && parentnode->right->data==element)? parentnode->right : parentnode->left;//using ternary operator to short the code
	
   datatoreplace =inordersuccessor(parentnode,element); //this function returning data to replace
   printf("\nIgnore above: Current data: %d is  replaced with %d smallest element in right subtree ",currentnode->data,datatoreplace);//for information
   currentnode->data=datatoreplace;//datis replaced with inordersuccessor value
}
int inordersuccessor(struct tree* parentnode,int element)
{
   struct tree *curleft, *curright,*temp,*holdparentnote; //code can be made shorter
   int datatoreplace;
   curleft=parentnode->left;//we can also use trenary operator to short the code
   curright=parentnode->right;
   if(curleft!=NULL && curleft->data==element)//we are checking curleft!=NULL because if parent contain 1 child then EITHER parentnode->left or parentnode->right will be null so checking ITS important
   {
   	  holdparentnote=curleft;//if temp->left is null then while loop will not execute then we wound get parent node so this statement is necessary
   	  temp=curleft->right;//since two child no need to check curleft!=NULL because curleft pointer will surely contain child
   	   if(temp->left==NULL && temp->right!=NULL)//if temp->left is null and temp->right is not null this means temp node has single child not zero child so we need function which delete SINGLERCHILD node
   	  {                                         //if temp->left is null and temp->right is also null this means temp node has zero child so  DELETEZEROCHILD function will be execute
   	  	datatoreplace=temp->data;
   	    deletesinglechild(holdparentnote,datatoreplace );	
   	    return datatoreplace;
	  }
   	  while(temp->left!=NULL)//we want smallest node of right sub tree so traversing to left till temp->left==NULL
   	  {
   	  	holdparentnote=temp;
   	  	temp=temp->left;
	  }   
   }
   else if(curright!=NULL && curright->data==element)
   {
   	  holdparentnote=curright;//parent node
   	  temp= curright->right;//temp is child node
   	  if(temp->left==NULL && temp->right!=NULL)//it is special condition.It indicate to deletesinglechild
   	  {
   	  	datatoreplace=temp->data;
   	    deletesinglechild(holdparentnote ,datatoreplace );	
	   	return datatoreplace;
	  }
   	  while(temp->left!=NULL)
   	  {
   	  	holdparentnote=temp;
   	  	temp=temp->left;
	  }
   }
    datatoreplace=temp->data;//data is taken
    if(temp->left==NULL && temp->right==NULL)//orif(temp->right==NULL) because we have already checked in while statement
	deletezerochild(holdparentnote,datatoreplace);
	else//it is important it will work in situation ex: this ia tree 25 15 10 22 50 35 70 31 44 66 90 and try to delete first 25,31 and 35
	deletesinglechild(holdparentnote ,datatoreplace );

	return datatoreplace;//returning last node data after deleting because we have stored in int variable
}                                                                        // datatoreplace before deletion
void enque_linkedlist_queue(struct tree *add) 
{//enque is done from rear

/*Here we cant use circular array because when tree is large circularqueue may becomes full
  if wedont give right size of array but we dontknow exactly what the size would be because
  size of tree may be small or large depends on user so linked list queue is better to use.
  we can solve by creating dynamic array and maximum size of circular queue array would be
  height of tree 2^h-1 then only no error will be produce.so we have to find height of tree*/    	 
struct circular_queue *newnode=(struct circular_queue*)malloc(sizeof(struct circular_queue));
newnode->address=add;
newnode->next=NULL;
 if(rear==NULL)	//initially rear would be null
 {
   rear=front=newnode;	
 } 
 else
 {
 	rear->next=newnode;
 	rear=newnode;
 }	 
}
struct tree *deque_linkedlist_queue(void)
{//deque is done from front
	 
if(front==NULL)//when front is null then this function should return NULL.In absence of these
{             //statement else statement will work and illegal operation will be performed
   return NULL;
}
else
{
  struct tree *temp;
  struct circular_queue *temp2;
  temp=front->address;//address is stored to temp to return
  temp2=front;//queue node to free to prevent memory leak
  front=front->next;//front is updated
  
/*if statement will work only in situation when queue is empty then front will be NULL so that
  time when enque operation is called rear pointer should contain NULL so rear is updated to
  NULL because rear is global pointer.SO that next time same function perform correctly*/
  if(front==NULL) 
  {              
  	rear=NULL;//rear is updated when front is null
  }
  
  free(temp2);//freeing circular queue node
  return temp; 	
 }	 
}
void levelordertraversal(void)
{//VODEO->Level Order Traversal of a Binary Tree (level by level and as a whole)
  struct tree *temp;
  temp=rootnode;
  if(temp==NULL)
  {
	printf("\nTree is empty");
  }
  else
  {
   front=rear=NULL;/*front and rear are global variable resetting to NULL so when second time 
		         execute always start from beginning and not produce error */
		   
	printf("\nLevel order traversal:");                                   
	enque_linkedlist_queue(temp);//circular queue is made using linked list
	while(1)
	{
	   temp=deque_linkedlist_queue();
	     if(temp==NULL)//when queue will be empty dequecircularqueue() function will return
	      {                                                                   //NULL to temp
	    	break;//terminate while loop
		  }
	     printf(" %d",temp->data);//pri
	     if(temp->left!=NULL)
	      {
	    	enque_linkedlist_queue(temp->left);	//left node
		  }
		 if(temp->right!=NULL)
		  {
			enque_linkedlist_queue(temp->right); //right node
	      }
	}
  }
}
void totalnumberofnodes(struct tree* rootnode)
{
   struct tree* p=rootnode;
   int totalnode=0,leafnode=0,internalnode=0;
   //p=rootnode;
   if(rootnode==NULL)
   {
   	printf("\nTree is empty");
   }
   else
   {
   while(1)
   {
   	 while(p)
   	 {                         //this code is similar as in order traversal
   	 		pushintostack( p);
   	 		p=p->left;
     }
		if(top==NULL)
		{
			break;
		}
		p=pop();
		if(p->left==NULL && p->right==NULL)
		{
			leafnode=leafnode+1;  ///for counting leafnode
		}
		if(p->left!=NULL && p->right!=NULL)
		{
		  internalnode=internalnode+1;	 //for counting internal node
		}
		totalnode=totalnode+1;   //for counting totalnode
		
		p=p->right;	
   }
 
   printf("Total Number of Nodes: %d",totalnode);
   printf("\nTotal Number of Leafnode: %d",leafnode);
   printf("\nTotal Number of internalnode: %d ",internalnode);
}
}
void heightoftree(struct tree* rootnode)
{ 
 struct tree* temp=rootnode;  //using levelorder technique to find the height
 int countlevel=0;
 if(rootnode==NULL)
 {
   printf("Tree is empty");
 }
 else
 {
   front=rear=NULL;//front and rear are global variable resetting to NULL sowhen second time
   enque_linkedlist_queue(temp);    //execute always start from beginning and not produce error
   enque_linkedlist_queue(NULL);  //to indicate the level
   while(1)
   {
	 temp=deque_linkedlist_queue();//circular queue is made using linked list
	 if(temp==NULL)
	 {
	   countlevel++;//or but countlevel=countlevel+1 is slower then countlevel++
	   enque_linkedlist_queue(NULL);/*when in queue two 0 appears consequetly that means end of
	                   checking level so program should stop so front index check in advance
					   whether it has consequetly 0 or not we cant use rear index*/ 
	   if(front->address == NULL)//This is tricky when we are enquecircularqueue(NULL) thatmeans
	    {            //null is inserted to queue not address so checking in advance to terminate
	      break;//terminate while loop
		}
	 }
	 else
	 {
	   if(temp->left!=NULL)
		{
		  enque_linkedlist_queue(temp->left);//left node
	    }
	   if(temp->right!=NULL)
		{
		  enque_linkedlist_queue(temp->right);//right node
	    }
	 }
	}
  }
   printf("\nHeight of tree: %d",countlevel);
}
void deleteentiretree(struct tree* rootnod)
{
  /*we are deleting using inorder tarversal.Optimised method to delete entire tree is by
    using post order traversal because child node is deleted before parent node.It is nature of
    postordertraversal.where as other traversal takes more space and time complexity to delete 
	whereas postordertraversal takes less time and space to delete.not exactly true.i think 
	inorder traversal take less space in stack and time to delete*/
	
	struct tree* p=rootnod;
	struct tree* holdtodelete;
	if(rootnod==NULL)
	{                            
		printf("\nTree is empty");
	}
	else
	{
		while(1)
		{
		  while(p)
		  {
		  	  pushintostack(p);//if we want to delete then function argument should be different
   	 		  p=p->left;     //not same as rootnode because at last rootnode is assigned to NULL
		  }
		  	if(top==NULL)
		    {
			break;
		   }
	    	p=pop();
	    	holdtodelete=p;
	    	p=p->right;
	    	printf(" %d",holdtodelete->data);
	    	free(holdtodelete);
		}
		/*int flag; //post order traversal
  while(1)             //disadvantage when tree is not balanced then it take more stack space
  {            //whereas inorder traversal takes less stack space if tree is skrew or full tree
   if(p)       
   	{
   	  pushintostack( p);
	  p=p->left;
	}
   else
	{
	 if(top==NULL)
	    break;//terminate while loop
	 else
	 {
	   if(top->address->right== NULL)//means left is null right is null then root is printed
	    {
	    	flag=0;
	      p=pop();
	      
	      if(top==NULL)//this will work when tree is like skrew eg: 5 4 3 2 1 so this will terminate
		  break;                                                //illegal operation may be performed
		  
	        while(top->address->right==p)//checking in advance if it is true then topnode is parent
	        {
			flag=1;
			printf(" %d",p->data);
			free(p);                                                 //of p.This loop is likeback tracking
	              
	          p=pop();
	          if(top==NULL) 
			  {
			  	printf(" %d",p->data);
			  	free(p);
			  	flag=2;
			    break;
			  }  
			    
			}
			if(flag==0)
			{
				printf(" %d",p->data);
				free(p);
			}
			else if(flag==1)
			{
				printf(" %d",p->data);
			    free(p);	
			}
	     }
	     if(top!=NULL)
		    p=top->address->right;//it shift pointer to right side
		 else
		    p=NULL;//this will only execute when stack become empty
	  }
	 }
   }*/
	rootnode=NULL;/*since all data isdeleted then actual globalvariable shouldbe initialize to null
	here rootnode isnot functionparameter if it is parameter then if we assign rootnode to null it
	will not asssign because since it is parameter it will not act as global variable*/
	printf("\nEntire node tree deleted");
  }                                    
}

