/*The key advantage of using an AVL tree is that it takes O(log n) time to perform search
 insert,and delete operations in an average case as well as the worst case because the
 height of the tree is limited to O(log n).
 
A binary search tree in which every
node has a balance factor of –1, 0, or 1 is said to be height balanced. A node with any other
balance factor is considered to be unbalanced and requires rebalancing of the tree.
  ***Balance factor = Height (left sub-tree) – Height (right sub-tree)
1.If the balance factor of a node is 1, then it means that the left sub-tree of the tree is one
 levelhigher than that of the right sub-tree. Such a tree is therefore called as a left-heavy
  tree.

2.If the balance factor of a node is 0, then it means that the height of the left sub-tree 
 (longest path in the left sub-tree) is equal to the height of the right sub-tree.
 
3.If the balance factor of a node is –1, then it means that the left sub-tree of the tree is one
 levellower than that of the right sub-tree. Such a tree is therefore called as a right-heavy 
 tree
 
 AVL Tree all operation O(log n) worst case
 1.Searching operation is faster then Red black tree due to strictly balanced tree
 2.Insert,and delete operations is slower then Red black tree because in AVL many rotation have to 
   perform.
 3.It is strictly balanced tree
 4.Used in situatiom when searching operation is more to performed because it will be fast 
 
 RED BLACK Tree all operation O(log n) worst case
 1.it is fast in insertion and dletion as less rotation required
 2.Searching operation is slower then AVL Tree because red black tree is not strictly balanced tree
 3.It is roughly balanced tree not strictly balanced tree 
 4.Used in situatiom when insertion and dletion are more to performed because it will be fast
 
 ROtation takes constant time
 DELETION OPERATION
 VIDEO->Deletion in AVL Tree with example BY FN GURUKUL with NAVAL KISHOR LODHI
 VIDEO->Deletion in AVL Tree BY FN GURUKUL with NAVAL KISHOR LODHI
 */
 
#include<stdio.h>
#include<stdlib.h>//duplicates element not allowed in AVL tree
struct avltree               //deletion not done due to complex
{
  struct avltree *left,*right;
  int data,balance;
}*rootnode=NULL,*parentnode=NULL;//globally pointer initialize to NULL andvariable to 0 by default

struct stack//used for deletion
{	 
  struct avltree *address;
  struct stack *next;
}*top=NULL;//globally pointer initialize to NULL by default and clanguage follows static scoping

struct stack2//for traversal inorder and preorder we need different stack other wise code not work properly
{	 
  struct avltree *address;
  struct stack2 *next;
}*top2=NULL; 

/*2 queues are needed because rotation require 2 queue both at same time*/
struct queue//linkedlist queue 1 to get critical and parent node
{
  struct avltree *address;
  struct queue *next;
}*front=NULL,*rear=NULL;//globally pointer initialize to NULL andvariable to 0 by default

struct linkedlist_queue//for balancing queue 2
{
	struct avltree* address;
	struct linkedlist_queue *next;
}*front2,*rear2;
 int entered_in_deletesinglechild_flag=0;
void enque_into_queue2(struct avltree* address);
struct avltree  *deque_into_queue2(void);
void enque(struct avltree*);  //linked queue
struct queue* deque(void);  //linked queue
void insertelement (void);
void balancetree_andenqueinto_queue_fromroot_tothat_inserted_element(int);
void updatebalance_factor_ofnode(struct avltree*);
int heightoftree(struct avltree *);
void rotate_imbalance_node(void);
void inordertraversal(void);
void preordertraversal(void);
void pushintostack(struct avltree *);
void pushintostack2(struct avltree *);//for information
struct avltree *pop(void);
struct avltree *pop2(void);
void insertafterrotate(struct avltree *startPfrom_this_node,struct avltree *addresstoinsert,int elementofaddress);
void levelordertraversal(void);//also known as breath first search
void deletion_of_AVLtree(void);
void deletetwochild(struct avltree*,int);
int inordersuccessor(struct avltree*,int );
void deletesinglechild(struct avltree*,int);
void deletezerochild(struct avltree*,int);
struct avltree *searchnodereturnparentnode(int);
int checkfornumberofchild(struct avltree*,int);
void rrRotation(struct avltree *parentnode,struct avltree *critical,struct avltree *second);
void rLRotation(struct avltree *parentnode,struct avltree *critical,struct avltree *second,struct avltree *third);
void lLRotation(struct avltree *parentnode,struct avltree *critical,struct avltree *second);
void lRRotation(struct avltree *parentnode,struct avltree *critical,struct avltree *second,struct avltree *third);
void do_inordersuccessor_andpush_all_elements_thatcomes_inway(struct avltree *rootnode);//to catch unbalanced node
void balance_factorof_all_nodeforinformation(void);

int main()
{
	int option;
	do
	{
		printf("\n\n1.Insert Element.");printf("\n2.Display balanced tree");printf("\n3.DELETION");
		printf("\n4.level order traversal and balance factor of all node ");printf("\nEnter your option: ");
		
		scanf("%d",&option);
		if(option==1)//same as switch case
		{
		  insertelement ();//during insertion once rotation is performed then no need to check other node balance
		}
		else if(option==2)
		{
			printf("\nElements in AVL TREE");
			inordertraversal();
		}
		else if(option==3)
		{
		 deletion_of_AVLtree();	
		}
		else if(option==4)
		{
		 levelordertraversal();
		 balance_factorof_all_nodeforinformation();
		}
	}while(option<=55436534);
	return 0;
}
void insertelement (void)
{
 struct avltree *newnode,*ptr,*r;
 int element;
 printf("\nEnter -1 to stop.");  //same as insertion in BST
 printf("\nEnter element: ");
 scanf("%d",&element);
 while(element!=-1)
 {
  newnode=(struct avltree*)malloc(sizeof(struct avltree));
  newnode->left=NULL;
  newnode->data=element;
  newnode->right=NULL;
  newnode->balance=0;//we are not using NULL because 0 is data and null is not data
  if(rootnode==NULL)
  {
   rootnode=newnode;//initializing to root node 
  }
  else  
  {
   ptr=rootnode;
   while(ptr!=0)
   {
	r=ptr;
	if(ptr->data == element)
	{
	 printf("\nElement %d already exist enter another element",ptr->data);
	 free(newnode);//because newnode is created so we have to delete because element is same and
     break;                                                               //memory was allocated
	}
	else if(ptr->data > element)
	{
	  ptr=ptr->left;
	}
	else if(ptr->data < element)
	{
	  ptr=ptr->right;	            
	}
   }
   if(r->data != element)//if element is same it will not execute it will ask user to enter another
    {                                                                                     //element
	 if(r->data > element) 
	 {
	  r->left=newnode;
	  printf("inserted= %d ",newnode->data);
	  balancetree_andenqueinto_queue_fromroot_tothat_inserted_element(element);
	  //we have to balance node from root to that inserted node.
	  rotate_imbalance_node( );
	  //after rotation of imbalance node then no need to check other node or rotate other node****
	 }
	 else if(r->data < element)
	 {
	  r->right=newnode;
	  printf("inserted= %d ",newnode->data);
	  balancetree_andenqueinto_queue_fromroot_tothat_inserted_element(element);
	  rotate_imbalance_node( );	
	 }
	}
   }
	printf("\nEnter element: ");
    scanf("%d",&element);
  }
}
void rotate_imbalance_node(void)
{
 struct avltree *critical=NULL,*second=NULL,*third=NULL,*globalparent;
 struct queue *frontoflinkedqueue=NULL;
 int flag=0,indicatetofree;//it will check for critical ,second,third node
   
/*HOW it is working? first we have store node from root to that node in queue and we are checking
 critical node if it is critical node then we sotre that address in critical pointer then second
 and third addrsess as for rotation werequired only 3nodes.if consequently we found critical node
 then continue statement executed we want critical node which is NEAR to inserted node it is used
 to take nearest unbalance  ancestor that is critical node*/   
 while( 1)//we can improve using circular array of size 3 to get critical,second,third,parent**
 {       //frontoflinkedqueue is queue address which is created dynamically so memeory is freed
   flag=0; 
   indicatetofree=0;       
   frontoflinkedqueue=deque();//linkr=edlist queue
   if(frontoflinkedqueue==NULL)//when queue will become empty then it will break loop
   {
   	printf("\n1.FREE  NULL");
   	free(frontoflinkedqueue);
	break; //It will break while loop
   }					   
   if(frontoflinkedqueue->address->balance!=0 && frontoflinkedqueue->address->balance!=-1 && frontoflinkedqueue->address->balance!=1 )//checking it is critical node or not
   {
	indicatetofree=1;	 
	critical=frontoflinkedqueue->address;
	printf("critical= %d",critical->data);//for getting information
	if(frontoflinkedqueue->next->address->balance!=0 && frontoflinkedqueue->next->address->balance!=-1 && frontoflinkedqueue->next->address->balance!=1 ) //Checking in advance for critical node
	{
	  printf("\n2.FREE %d",frontoflinkedqueue->address->data);
	  free(frontoflinkedqueue); 
	  continue;
	}
	else
	{
	 printf("\n3.FREE %d",frontoflinkedqueue->address->data);
	 free(frontoflinkedqueue);
	 frontoflinkedqueue=deque();
	 second=frontoflinkedqueue->address;
	 printf("second= %d",second->data);	
	 if(front==NULL)//it is used to catch two node suppose if rootnode->right has height -4 now user enter leftnode of rootnode a number which will be first node on left side  which is smaller than rootnode
	  {               //then program will execute and search for critical,second,third node but on leftside of rootnode there is only two node rootnode and no. entered by user then we will get critical node
	                  //as rootnode which balance is -3 one is decrease due to enter new node by user and second node is new node and third node is not there because on left side only two node is present
	                  //but program will search for third node which will produce error SO AFTER GETTING SECOND NODE WE ARE CHECKING IN ADVANCE FOR THIRD NODE IF QUEUE IS EMPTY THEN FRONT WILL BECOME 0
	                  //SO BREAK STATEMENT WILL EXECUTE AND BREAK WHILE LOOP
	  	printf("\n4.FREE %d",frontoflinkedqueue->address->data);
	    free(frontoflinkedqueue);            
		flag=1;     
		break;      
	  }              
	}
	if(frontoflinkedqueue->next->address->balance!=0 && frontoflinkedqueue->next->address->balance!=-1 && frontoflinkedqueue->next->address->balance!=1) //Checking in advance for critical node
	{
	 printf(" %d",frontoflinkedqueue->next->address->balance);
	 printf("\n5.FREE %d",frontoflinkedqueue->address->data);
	 free(frontoflinkedqueue);
	 continue;
	}
	else
	{
	 printf("\n6.FREE %d",frontoflinkedqueue->address->data);
	 free(frontoflinkedqueue);
	 frontoflinkedqueue=deque();
	 third=frontoflinkedqueue->address;
	 printf("third=%d",third->data);
	 printf("\n7.FREE %d",frontoflinkedqueue->address->data);
	 free(frontoflinkedqueue);
	}
   }
   if(indicatetofree==0)
   {
   	printf("\n8.FREE %d",frontoflinkedqueue->address->data);
   	free(frontoflinkedqueue);
	} 
 }
if(flag==0)//IF it is 0 it means that there is critical ,second,third node
{                                          // 
 if(critical!=NULL)//if there is critical node then only it will execute //WHAT HAPPENS IF WE REMOVE THIS LINE?? suppose if user enter first node and  while entering second node then program will search for
                    // critical node but tree has only two node so no critical node so control will not enter in if statement that checke for critical node so critical node will be NULL as initialze and 
        //ALSO FLAG WILL NOT BE updated 1 which indicate only two node so flag==0 will be executed due to flag is not updated to 1 then if this if(critical!=NULL) statement is not there  then control will
             //enter in this if(flag==0) statement and execute  if((critical->right==second)&&(second->right==third)) which is illegal because critical node is null and it is tryingto execute critical->right
{                    
 if((critical->right==second)&&(second->right==third)) //RR rotation  three are 5 condition to check
 {
 	globalparent=parentnode;//here parentnode is global pointer which is updated in linked list queue so passing to function
    rrRotation(globalparent,critical,second);  	   	
 }
 else if((critical->left==second)&&(second->left==third))//LL Rotation
 {
   globalparent=parentnode;//here parentnode is global pointer which is updated in linked list queue so passing to function
   lLRotation(globalparent,critical, second);	
 }
 else if((critical->left==second)&&(second->right==third))//LR Rotation
 {
 	globalparent=parentnode;//here parentnode is global pointer which is updated in linked list queue so passing to function
 	lRRotation( globalparent,critical,second,third);		   	
 }
 else if((critical->right==second)&&(second->left==third))//RL Rotation try example 5 3 8 2 10 9
 {
 	globalparent=parentnode;//here parentnode is global pointer which is updated in linked list queue so passing to function
 	rLRotation(globalparent,critical,second,third);
 }
}//if statement
}//if stateement flag =0
}
void insertafterrotate(struct avltree *startPfrom_this_node,struct avltree *addresstoinsert,int elementofaddress)
{
	struct avltree *p,*r;
	p=startPfrom_this_node;//orp=rootnode;
	while(p)
	{
		r=p;
	  if(p->data > elementofaddress)  //here no element will be same so no need to check
	  {
	  	p=p->left;
	  }
	  else if(p->data < elementofaddress)
	  {
	  	p=p->right;
	  }
    }
    if(r->data > elementofaddress)
    {
    	r->left=addresstoinsert;
	}
	else if(r->data < elementofaddress)
	{
		r->right=addresstoinsert;
	}
}
void inordertraversal(void)
{
	
	struct avltree *p;
	p=rootnode;
    printf("\nIn-Order Traversal:");
	while(1)
	{
			if(rootnode==0) //here this will not execute not necessary
      	{
        	printf(" Tree is empty.");
	       break;
        }
		while(p)
		{
			pushintostack2( p);
			p=p->left;
		}
		if(top2==0)
		{
	    	break;
		}
			p=pop2();
			printf(" %d",p->data);
			p=p->right;	
	}
}
void preordertraversal(void)
{
	struct avltree *p;       //after function complete execution top becomes 0
	p=rootnode;
    printf("\nPre-Order Traversal:");
	while(1)
	{
			if(rootnode==0)
      	{
        	printf(" Tree is empty.");
	       break;
        }
		while(p)
		{
			printf(" %d",p->data);
			pushintostack2( p);
			p=p->left;
		}
		if(top2==0)//if stack is empty then it will execute which means every node is traversed
		{
	    	break;
		}
			p=pop2();
			p=p->right;	
	}
}
void pushintostack(struct avltree *add)
{
	struct stack *newnode;
	newnode=(struct stack*)malloc(sizeof(struct stack));
	newnode->address=add;                 
	newnode->next=top;
	top=newnode;	
}
void pushintostack2(struct avltree *add)
{
 struct stack2 *newnode;
	newnode=(struct stack2*)malloc(sizeof(struct stack2));
	newnode->address=add;                 
	newnode->next=top2;
	top2=newnode;	
}
struct avltree *pop(void)
{
   	struct stack *temp;
   	struct avltree *hold_address_toreturn;
   	if(top==NULL)
   	{
   		printf("\nstack is empty.");
	}
	else
	{
   	temp=top; 
	hold_address_toreturn=temp->address;//holding address to return 
   	top=top->next;//top is updated
   	free(temp);//stack memory is created dynamically so freeing it to avoid memory leak
    }
   	return hold_address_toreturn;   	                                    
}
struct avltree *pop2(void)
{
 struct stack2 *temp;
   	struct avltree *hold_address_toreturn;
   	if(top2==NULL)
   	{
   		printf("\nstack is empty.");
	}
	else
	{
   	temp=top2; 
	hold_address_toreturn=temp->address;//holding address to return 
   	top2=top2->next;//top is updated
   	free(temp);//stack memory is created dynamically so freeing it to avoid memory leak
    }
   	return hold_address_toreturn;  	
}
void enque(struct avltree *address) //linked list queue
{
    struct queue* newnode;//IN queue insertion is done using rear pointer
	newnode=(struct queue*)malloc(sizeof(struct queue));
	newnode->address=address;
	newnode->next=NULL;
	if(front==NULL)
	{
	  rear=front=newnode;
	}
	else
	{
	  rear->next=newnode;
	  rear=newnode;
	}
}
struct queue* deque(void) //linked list queue
{
 struct queue *temp;//IN queue enque is done using front pointer
 if(front==NULL)
 {
  //printf("\nQueue is empty now after deque");  
  return NULL; //returning null function to execute properly other wise error
 }
 else
 {
  temp=front; 
  if((front->next!=NULL) && (front->next->address->balance!=0 && front->next->address->balance!=-1 && front->next->address->balance!=1))//Checking in ADVANCE for critical node if it is critical node 
   {                                        //we need parentnode of critical node so this code is for                                //then we will hold address that will be parentnode of criticalnode
	 parentnode=front->address;//parentnode is global variable it is used to hold parentnode of critical node.it is only possible here to catch parentnode in ADVANCE Because here is queue
   }
	front=front->next;      
	return temp;        //if we copy original address into another pointer and free the original address then copied address in that pointer will become dangalling pointer
 }
}
void balancetree_andenqueinto_queue_fromroot_tothat_inserted_element(element)
{ 
 struct avltree *ptr;
 ptr=rootnode;
 while(ptr!=NULL) 
 {
  if(ptr->data >= element)//using >=because itcheck from root tothat node then at first root->data
   {                              //is checked so root->data will be equal to element so = is used
	 enque(ptr);  //linked list queue
	 updatebalance_factor_ofnode(ptr); //balancing the node
	 ptr=ptr->left;
   }
  else if(ptr->data <= element) 
   {
	 enque(ptr);   	  
	 updatebalance_factor_ofnode(ptr);
	 ptr=ptr->right;
   }
 }	
}
void updatebalance_factor_ofnode(struct avltree *ptr_act_as_rootnode )
{	
   int heightof_left_subtree , heightof_right_subtree;
   heightof_left_subtree = heightoftree( ptr_act_as_rootnode->left );
   heightof_right_subtree = heightoftree( ptr_act_as_rootnode->right );
   
   ptr_act_as_rootnode->balance = heightof_left_subtree - heightof_right_subtree;//formula
   printf(" NODE=%d balance=%d\n",ptr_act_as_rootnode->data,ptr_act_as_rootnode->balance);
}
int heightoftree(struct avltree *rootof_leftor_rightsubtree)
{
 struct avltree* temp=rootof_leftor_rightsubtree;//using levelorder technique to find the height
 int countlevel=0;
 if(rootof_leftor_rightsubtree==NULL)
 {
  return 0;
 }
 else
 {
  front2=rear2=NULL;/*frontand rear are globalvariable resetting toNULL sowhen secondtime execute
                   always start from beginning and not produce error because deque circularqueue 
				   wound execute completely if it execute properly then front=rear=NULL; is coded
				   in deque function so using here */
  enque_into_queue2(temp);                                                           
  enque_into_queue2(NULL);  //to indicate the level
  while(1)
  {
   temp=deque_into_queue2();
   if(temp==NULL)
   {
	countlevel=countlevel+1;
	enque_into_queue2(NULL);
	if(front2->address == NULL)//whenin queue two NULL appearsconsequetly thatmeans program should
	{//stop so front index is checking in ADVANCE whether it has consequetly NULLor not we cantuse
    //rear2 index front2 is increase by advance so we  Are able to check in advance
	  break;							  
	}
   }
   else
   {
	if(temp->left!=NULL)
	{
	 enque_into_queue2(temp->left);
	}
	if(temp->right!=NULL)
	{
	 enque_into_queue2(temp->right);	
	}
   }
  }
	return countlevel;
 }
}
/*void enquecircularqueue(struct avltree* address) //it is used for finding height of tree that is level order traversal
{                  //using array circular queue
	if(front2==-1)
	{
		rear2=front2=0;
		circularqueue[rear2]=address;
	}
	else if((rear2+1)%6==front2)
	{
		printf("\ncircular que is full increase size"); //it will not occur
	}
	else
	{
		rear2=(rear2+1)%6;
		circularqueue[rear2]=address;
	}
}*/
void enque_into_queue2(struct avltree* add) 
{//enque is done from rear 

/*Here we cant use circular array because when tree is large circularqueue may becomes full
  if wedont give right size of array but we dontknow exactly what the size would be because
  size of tree may be small or large depends on user so linked list queue is better to use.
  we can solve by creating dynamic array and maximum size of circular queue array would be
  height of tree 2^h-1 then only no error will be produce.so we have to find height of tree*/    	 
struct linkedlist_queue *newnode=(struct linkedlist_queue*)malloc(sizeof(struct linkedlist_queue));
newnode->address=add;
newnode->next=NULL;
 if(rear2==NULL)	//initially rear would be null
 {
   rear2=front2=newnode;	
 } 
 else
 {
 	rear2->next=newnode;
 	rear2=newnode;
 }	 
}

/*struct avltree *dequecircularqueue(void)
{                         //using array circular queue
	int holdnode;
	if(front2==-1 && rear2==-1)  //this statement wound execute it will execute if it run completely since cirqueue will hold atmost 5 nodes and size of queue is 6 so it will never execute
	{
		  //printf("\nCircular queue is empty"); //not needed
		return NULL;
	}
	else if(front2==rear2) 
	{
		 holdnode=front2;
		 front2=rear2=-1;
		return circularqueue[holdnode];
	}
	else
	{
	  holdnode=front2;
	  front2=(front2+1)%6;
	  return circularqueue[holdnode]
	}
}*/
struct avltree *deque_into_queue2(void)
{//deque is done from front pointer
	 
if(front2==NULL)//when front is null then this function should return NULL.In absence of these
{             //statement else statement will work and illegal operation will be performed
   return NULL;
}
else
{
  struct avltree  *temp;
  struct linkedlist_queue *temp2;
  temp=front2->address;//address is stored to temp to return
  temp2=front2;//queue node to free to prevent memory leak
  front2=front2->next;//front is updated
  
/*if statement will work only in situation when queue is empty then front will be NULL so that
  time when enque operation is called rear pointer should contain NULL so rear is updated to
  NULL because rear is global pointer.SO that next time same function perform correctly*/
  if(front2==NULL) 
  {              
  	rear2=NULL;//rear is updated when front is null
  }
  free(temp2);//freeing linkedlist_queue node
  return temp; 	
}	 
}
void levelordertraversal(void)
{
  struct avltree* temp=rootnode;  //using levelorder technique to find the height 
 if(rootnode==NULL)
 {
   printf("Tree is empty");
 }
 else
 {
   front2=rear2=NULL;//front and rear are global variable resetting to NULL sowhen second time
   enque_into_queue2(temp);    //execute always start from beginning and not produce error
   enque_into_queue2(NULL);  //to indicate the level
   while(1)
   {
	 temp=deque_into_queue2();//circular queue is made using linked list
	 if(temp!=NULL)
	 {
	  printf(" %d",temp->data);
	 }
	 if(temp==NULL)
	 {
	    printf("\n");
	   enque_into_queue2(NULL);/*when in queue two 0 appears consequetly that means end of
	                   checking level so program should stop so front index check in advance
					   whether it has consequetly 0 or not we cant use rear index*/ 
	   if(front2->address == NULL)//This is tricky when we are enquecircularqueue(NULL) thatmeans
	    {            //null is inserted to queue not address so checking in advance to terminate
	      break;//terminate while loop
		}
	 }
	 else
	 {
	   if(temp->left!=NULL)
		{
		  enque_into_queue2(temp->left);//left node
	    }
	   if(temp->right!=NULL)
		{
		  enque_into_queue2(temp->right);//right node
	    }
	 }
	}
  }
}
void deletion_of_AVLtree(void)
{//HOW IT works?-> we are first deleting node like BST deletion and the rotating to balance.
//we have to check balance of node from deleted node to root node and if any node is unbalanced then
//we have to perform rotation on that node which is not balanced
 struct avltree *parentnode,*curleft,*curright,*critical2,*second2,*third2,*parentnode2;
 int element,noofchild,flagelement_notfound=0;
 if(rootnode==NULL)
 {
		printf("Tree is empty");
 }
else
{
  printf("\nEnter Element to delete: ");
  scanf("%d",&element);//code can be make short
  
 if((element==rootnode->data && rootnode->left!=NULL) && rootnode->right!=NULL)
 {//to delete root node there are 3 condition .it is just like deleting two child node due to taking dummy node
 
  struct avltree *fake_parentnode=(struct avltree *)malloc(sizeof(struct avltree));//taken as dummy node
  fake_parentnode->left=NULL;
  fake_parentnode->right=rootnode;
  deletetwochild(fake_parentnode,element);
  free(fake_parentnode); //dynamically created so relesing it
  printf("\n1Rootnode is %d",rootnode->data);
  
  if(rootnode->right != NULL)//only execute when rootnode->right not equal to null 
  {//it is used to catch all unbalanced node 
  	printf("\nFree all node from stack to catch unbalanced node");
   while(top!=NULL)
   {//due to stack it will automatically termnate top will become null
  	printf("\nFREE %d",pop()->data);
   }
   //after popping all elemnets from stack this function will push all element from root to last inordersuccessor
   do_inordersuccessor_andpush_all_elements_thatcomes_inway(rootnode);
  }
  
 }
 else if((element==rootnode->data && rootnode->left!=NULL) && rootnode->right==NULL)
 {//this will execute in initial
   struct avltree *fake_parentnode=(struct avltree*)malloc(sizeof(struct avltree));
   fake_parentnode->left=NULL;
   fake_parentnode->right=rootnode;
   deletesinglechild(fake_parentnode,element);
   rootnode=fake_parentnode->right;//rootnode was deleted so updating rootnode
   free(fake_parentnode); 
   printf("\n2Rootnode is %d",rootnode->data); 
 }
 else if((element==rootnode->data && rootnode->left==NULL) && rootnode->right!=NULL)
 {//this will execute in initial
 	struct avltree *fake_parentnode=(struct avltree*)malloc(sizeof(struct avltree));
   fake_parentnode->left=NULL;
   fake_parentnode->right=rootnode;
   deletesinglechild(fake_parentnode,element);
   rootnode=fake_parentnode->right;//rootnode was deleted so updating rootnode
   free(fake_parentnode); 
   printf("\n3Rootnode is %d",rootnode->data);
 }
 else
{//node which have one child or Zero child then it will come here and ancestor will be pushed into the stack
  parentnode=searchnodereturnparentnode(element);
  if(parentnode==(struct avltree *)-11)//-11 should not contain in tree then only it
  {                                   //will work correctly.we can give -infinity
		printf("\nTREE is empty now");
  }
  else
  {
	if(parentnode==0)//if function return searchnodereturnparentnode(element); 0
	{                                  //then element is not there in tree
	printf("\nElement not found.");
	flagelement_notfound=1;	
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
 }//after deleting node from here avl tree is balanced by rotataion
//VIDEO->Deletion in AVL Tree BY FN GURUKUL with NAVAL KISHOR LODHI****
if(flagelement_notfound==1)
{//when element is deleted first it search the element at that time element is inserted into stack so when not found we have to free the dynamicall allocated memory from stack
 printf("\nEmpting the satck");
 while(top!=NULL)
 {
   	printf("\n %d",pop()->data);//freeing dynamically allocated memory
 }	
}
else
{
while(top!=NULL) //it will automatically terminate when stack become empty
{
 
 critical2=pop();
 printf("\npop critical %d",critical2->data);
 updatebalance_factor_ofnode(critical2);//necessary to check balance factor
 if(critical2->balance  >= 2 || critical2->balance <= -2 )//if this condition is true that means its balance factor is not 0 or 1 or -1.critical2 node is unbalanced
 {
 	
   if(top == NULL)//this if and else statement prevent illegal operation.when rootnode is critcal node then it will assign NULL to parentnode2 node and stack top pointer
   	parentnode2=NULL;                                                                       //will be null at that time when critical2 node is root node because of stack
   else	
    parentnode2=top->address;//since  stack is pop so its parent will be top poinrter.top pointer is updated during pop operartion
  
  if(critical2->balance <= -2)//that means critical2->balance may be -2,-3,-4...
  { 
    printf("\nCritical2 balance is negative %d so",critical2->balance);
   	second2=critical2->right;//right node because critical node is negative -2,-3...which means right subtree has more node then lefttree
   	printf("\nsecond2 node= %d",second2->data);
   	if(second2->balance == 0)
   	{
	 printf("\nsecond2 node balance is 0 so RR rotation");
	 rrRotation(parentnode2,critical2,second2);	
	}
	else if(second2->balance == -1)
	{
	 printf("\nsecond2 node balance is -1 so RR rotation");
	 rrRotation(parentnode2,critical2,second2);		
	}
	else if(second2->balance == 1)
	{
	 printf("\nsecond2 node balance is 1 so RL rotation");
	 third2=second2->left;//left node because third node will be left of second node
	 rLRotation( parentnode2,critical2,second2,third2);	
	}
  }
  else if(critical2->balance >= 2)//that means critical2->balance may be 2,3,4...
  {
    printf("\nCritical2 balance is positive %d so",critical2->balance);
    second2=critical2->left;//left node because critical node is positive 2,3,4....which means left subtree has more node then righttree
    printf("\nsecond2 node= %d",second2->data);
    
    if(second2->balance == 0)
   	{
	 printf("\nsecond2 node balance is 0 so LL rotation");
   	 lLRotation(parentnode2,critical2,second2);	
	}
	else if(second2->balance == -1)
	{
	 printf("\nsecond2 node balance is -1 so LR rotation");
	 third2=second2->right;//right node because third node will be right of second node
	 lRRotation(parentnode2,critical2,second2,third2);	
	}
	else if(second2->balance == 1)
	{
	 printf("\nsecond2 node balance is 1 so LR rotation");
	 lLRotation(parentnode2,critical2,second2);		
	}
  }   	
 }
}//while loop
printf("\nRotated and balanced");
}//else
}
void deletetwochild(struct avltree* parentnode,int element)
{
struct avltree *currentnode;
int datatoreplace;
entered_in_deletesinglechild_flag=0;//initializing to 0 to work for ssecond time correctly.it is global varaible
currentnode=((parentnode->right!=NULL) && parentnode->right->data==element)? parentnode->right : parentnode->left;//using ternary operator to short the code
	
   datatoreplace =inordersuccessor(parentnode,element); //this function returning data to replace
   printf("\nIgnore above: Current data: %d is  replaced with %d smallest element in right subtree ",currentnode->data,datatoreplace);//for information
   currentnode->data=datatoreplace;//datis replaced with inordersuccessor value
   
   if(entered_in_deletesinglechild_flag==1)//whenever while executing func. inordersuccessor if control enter to func. deletesinglechild then we should pop because this function insert 
   {      //element into stack which we dont want so we will pop only when control enter in func. deletesinglechild.if control not enter in func. deletesinglechild or zero child then no need to pop()
   	 printf("\nEntered in deletesinglechild function so pop from stack");
   	 pop();
   }
   
   pushintostack(currentnode);
}
int inordersuccessor(struct avltree* parentnode,int element)
{
   struct avltree *curleft, *curright,*temp,*holdparentnote; //code can be made shorter
   int datatoreplace;
   curleft=parentnode->left;//we can also use trenary operator to short the code
   curright=parentnode->right;
   if(curleft!=NULL && curleft->data==element)//we are checking curleft!=NULL because if parent contain 1 child then EITHER parentnode->left or parentnode->right will be null so checking ITS important
   {
   	  holdparentnote=curleft;//if temp->left is null then while loop will not execute then we wound get parent node so this statement is necessary
   	  temp=curleft->right;//since two child no need to check curleft!=NULL because curleft pointer will surely contain child
   	   if(temp->left==NULL && temp->right!=NULL)//if temp->left is null and temp->right is not null this means temp node has single child not zero child so we need function which delete SINGLERCHILD node
   	  {
		                                          //if temp->left is null and temp->right is also null this means temp node has zero child so  DELETEZEROCHILD function will be execute
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
	else//it is important it will work in situation ex: this is tree 25 15 10 22 50 35 70 31 44 66 90 and try to delete first 25,31 and 35 then else statement will work
	deletesinglechild(holdparentnote ,datatoreplace );

	return datatoreplace;//returning last node data after deleting because we have stored in int variable
}
void deletesinglechild(struct avltree* parentnode,int element)
{//this code can be make short
   entered_in_deletesinglechild_flag=1;//this will help to detech popn or not in func. deletetwochild
	printf("parent node = %d ",parentnode->data);
    struct avltree *curleft,*curright;
  	curleft=parentnode->left;
  	curright=parentnode->right;
  	if((parentnode->right!=NULL) && (parentnode->right->data==element))//checking element to decide element
  	{                                                                    //is present in left or right node
  		if(curright->right!=NULL)
  		{
  			parentnode->right=curright->right; //updating address to parent node
  			pushintostack(curright->right);//keep track of ancestor from root to search eleemnt
		}
		else if(curright->left!=NULL)
		  {
		  	parentnode->right=curright->left;
		  	pushintostack(curright->left);//keep track of ancestor from root to search eleemnt
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
			pushintostack(curleft->right);//keep track of ancestor from root to search eleemnt
		 }
		 else if(curleft->left!=NULL) 
		 {
		 		parentnode->left=curleft->left;
				pushintostack(curleft->left);//keep track of ancestor from root to search eleemnt
		 }
		 printf("\nDeleted node: %d",curleft->data);
		 free(curleft);
		 printf(" Left node");
	 }	
}
void deletezerochild(struct avltree* parentnode,int element)
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
struct avltree *searchnodereturnparentnode(int element)
{
 struct avltree *temp,*parent;
 temp=rootnode;
 while(1)
 {
  if((rootnode->left==NULL && rootnode->right==NULL) && (rootnode->data==element))//when
   {                                                            //there is only one node
	 printf("\nONLY ONE NODE IS PRESENT ROOT NODE : %d DELETED",temp->data);
	 free(temp);
	 rootnode=NULL;//since it is rootnode address is deleted so initializing to NULL
	 return ((struct avltree*)-11); 
   }
  if(element >= temp->data)//if element is greater then pointer will point to right side
   {
	if(element == temp->data)
	 {
	   return(parent);
	 }
	   parent=temp;//here previous address is stored
	   pushintostack(temp);//keep track of ancestor from root to search eleemnt
	   temp=temp->right;         //the rootnode cant be deleted evenif inorder successor
   }
  else if(element <= temp->data)//ifelement is smaller then pointer willpoint to leftside
   {
	 if(element == temp->data)
	  {
		return(parent);
	  }
		parent=temp;//here previous address is stored
		pushintostack(temp);//keep track of ancestor from root to search eleemnt
		temp=temp->left;
   }
	 if(temp==NULL)//it will be null when temp->left or temp->right is null it will become
	  {                                                      // null at the end of subtree
		return(0); //when Element not found.
	  }
 }	
}
int checkfornumberofchild(struct avltree*parentnode,int element)
{
	struct avltree *curleftnode,*currightnode;
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
void rrRotation(struct avltree *parentnode,struct avltree *critical,struct avltree *second) //here Parentnode is not globalpointer****
{
  struct avltree *temp; 
  printf("\n\nRR rotation to be performed");
  printf("\nCritical node: %d",critical->data); 
//suppose there is no parent node then it will be NULL  this parentnode!=NULL checks and prevent for illegal execution example at first while entering first node
  if(parentnode!=NULL && parentnode->left==critical && parentnode!= rootnode)//it work in this situation example  11 6 13 3 14 7 4 12 15 5
  {          //left and right condition
		   	                           
	printf("\nparentnode= %d ",parentnode->data);  
	temp= second->left; 
	parentnode->left=second;
	second->left=critical;
    critical->right=NULL;
	if(temp!=NULL)//if it has right child  then only it will execute
	{
	 printf("\nsecond node has left child %d",temp->data);
	 insertafterrotate(second,temp,temp->data);
	}
	else
    {
	 printf("\nsecond node has no child");
	} 
   }
   else if(parentnode!=NULL && parentnode->right==critical && parentnode!= rootnode)//it work in this situation example 12 6 15 5 8 13 18 4 20 21
   {
	 printf("\nparentnode=%d ",parentnode->data);
	 temp= second->left;   //if it has left child
	 parentnode->right=second;  //updating to parentnode before critical was right of parentnode so after rotation second node will be right side of parent node
     second->left=critical;  //rotating so critcal will become left child of second node
     critical->right=NULL;//because in critical node right side  was second node after execution critical node is under second node 
     if(temp!=NULL)//if it has left child  then only it will execute
	 {
	  printf("\nsecond node has left child %d",temp->data);
	  insertafterrotate(second,temp,temp->data);
	 }
	 else
	 {
	  printf("\nsecond node has no child");
	 } 
	}
	else
	{//it is important to check critical==rootnode first then parentnode==rootnode because if critical node is rootnode then oviously rootnode will not have parent so to avoid error check this condition first
	 if(critical==rootnode)//this is written down becaue only once or twice will execute //it work in this situation example 7 8 9
	{
	 printf("\ncritical node is rootnode %d so no parent node",critical->data);
	 temp= second->left;    //if it has left child
	 second->left=critical;  //rotating so critcal will become left child of second node
	 critical->right=NULL;    //because in critical node right side  was second node after execution critical node is under second node 
	 rootnode=second;   //since critical node was rootnode now second node will be rootnode because now critical node is under second node as left child
	 if(temp!=NULL)        //if it has left child  then only it will execute
	 {
		printf("\nsecond node has left child %d",temp->data);
		insertafterrotate(second,temp,temp->data);
	 }
	 else
	 {
		printf("\nsecond node has no child");
	 }	
	}
	else
	{
	 if(parentnode==rootnode)
	  {
	   printf("\nparentnode=%d ",parentnode->data);
	   printf("\nparentnode  is rootnode %d",parentnode->data); 
	   if(parentnode->right==critical)  //it work in this situation example 20 9 22 23 24 
		{
		 temp= second->left;   //if it has left child
		 parentnode->right=second;  //updating to parentnode before critical was right of parentnode so after rotation second node will be right side of parent node
         second->left=critical; //rotating so critcal will become left child of second node
         critical->right=NULL; //because in critical node right side  was second node after execution critical node is under second node 
         rootnode=parentnode;  //updating rootnode becaus parentnode was rootnode whatever changes in parentnode will reflect to rootnode so updating rootnode
		}
		else if(parentnode->left==critical)  //it work in this situation example 20 21 9 10 11 
		{ 
		 temp= second->left;
		 parentnode->left=second;
		 second->left=critical;
		 critical->right=NULL;
		 rootnode=parentnode;	
		}
	  }
	 if(temp!=NULL)//if it has left child  then only it will execute
	 {
	   printf("\nsecond node has left child %d",temp->data);
	   insertafterrotate(second,temp,temp->data);
	 }
	 else
	 {
		printf("\nsecond node has no child");
	 } 
	}
   }
		//printf("\nAfter Rotation");
		//inordertraversal();
	    //preordertraversal( );		   	
}	
void rLRotation(struct avltree *parentnode,struct avltree *critical,struct avltree *second,struct avltree *third)
{
 struct avltree *holdthirdleft,*holdthirdright;
  printf("\n\nRL rotation");
  //suppose there is no parent node then it will be NULL  this parentnode!=NULL checks and prevent for illegal execution example at first while entering first node
  if(parentnode!=NULL && parentnode->left==critical && parentnode!= rootnode)//this statement will work when situation like example 11 9 19 15 8 20 17 16 when parentnode and critical is not root node this
  {                                                                           //three condition is important we are checking parentnode!= rootnode because parentnode->left==critical can be true when
   //we have left and right condition	                                  //parentnode== rootnode but we dont want this here if we want then rootnode should be updated but in this block code is not written
		                                                                             //so this code is written see condition if(parentnode== rootnode ) 
   printf("\nParent node %d ",parentnode->data);
   printf("\nCritical node %d is left of parent node",critical->data);
   holdthirdleft=third->left;
   holdthirdright=third->right;
   critical->right=NULL;//critical->right was second node  after rotation critical will be left of third node so critical->right have to set to null  
   second->left=NULL;   //before second->left third node was there after rotation third node will go to top so setting second->left=NULL
   third->left=critical;//after rotation critical will be left of third node
   third->right=second; //after rotation second will be right of third node
   parentnode->left=third; //updating parentnode
   if(holdthirdleft!=NULL)
   {
    insertafterrotate(third,holdthirdleft,holdthirdleft->data);
   }
   if(holdthirdright!=NULL)
   {
    insertafterrotate(third,holdthirdright,holdthirdright->data);
   }
  }
  else if(parentnode!=NULL && parentnode->right==critical && parentnode!= rootnode)//this statement will work when situation like example 20 10 25 8 15 26 17 16 when parentnode and critical is not root node
  {
   printf("\nParent node %d ",parentnode->data);
   printf("\nCritical node %d is right of parent node",critical->data);
   holdthirdleft=third->left;
   holdthirdright=third->right;
   critical->right=NULL;//critical->right was second node  after rotation critical will be left of third node so critical->right have to set ot null  
   second->left=NULL;   //before second->left third node was there after rotation third node will go to top so setting second->left=NULL
   third->left=critical;//after rotation critical will be left of third node
   third->right=second; //after rotation second will be right of third node
   parentnode->right=third; //only here we have to change***********************************
   if(holdthirdleft!=NULL)
   {
    insertafterrotate(third,holdthirdleft,holdthirdleft->data);
   }
   if(holdthirdright!=NULL)
   {
    insertafterrotate(third,holdthirdright,holdthirdright->data);
   }
  }
  else
  {//it is important to check critical==rootnode first then parentnode==rootnode because if critical node is rootnode then oviously rootnode will not have parent so to avoid error check this condition first
   if(critical==rootnode) //we dont have  left and right condition //this code will work when critical==rootnode example 5 9 7
   {
	 printf("\nCritical node is rootnode %d so no parent node",critical->data);
	 holdthirdleft=third->left;
     holdthirdright=third->right;
     critical->right=NULL; //critical->right was second node  after rotation critical will be left of third node so critical->right have to set ot null  
     second->left=NULL;//before second->left third node was there after rotation third node will go to top so setting second->left=NULL
     third->left=critical;//after rotation critical will be left of third node
     third->right=second;//after rotation second will be right of third node
     rootnode=third;//since Critical is rootnode after rotation third node will be rootnode so updating
     if(holdthirdleft!=NULL)
     {
      insertafterrotate(third,holdthirdleft,holdthirdleft->data);
     }
     if(holdthirdright!=NULL)
     {
      insertafterrotate(third,holdthirdright,holdthirdright->data);
     }
   }
   else if(parentnode==rootnode) //we have here left and right condition
   {
    printf("\nparentnode  is rootnode %d",parentnode->data);
	printf("\nCritical node %d",critical->data);
	if(parentnode->right==critical)//this code will work when parentnode==rootnode example 5 3 8 10 9
	{
	 holdthirdleft=third->left; //third node both left and right wil be updated so storing in other pointer
     holdthirdright=third->right;
     third->left=critical; //after rotation critical will be left of third node
     third->right=second;  //after rotation second will be right of third node
     critical->right=NULL;  //before   critical->right was second node after rotation it will be below third node so  critical->right=NULL
     second->left=NULL;  //before  second->left was third node after rotation third node will move to top so setting second->left=null
     parentnode->right=third;
     rootnode=parentnode;   //since parentnode is rootnode after rotation it is updated so updating rootnode
    }  
    else if(parentnode->left==critical) //this statement work in situation example 10 6 11 8 7
    {
     holdthirdleft=third->left; //third node both left and right wil be updated so storing in other pointer
     holdthirdright=third->right;
     third->left=critical; //after rotation critical will be left of third node
     third->right=second;  //after rotation second will be right of third node
    critical->right=NULL;  //before   critical->right was second node after rotation it will be below third node so  critical->right=NULL
    second->left=NULL;  //before  second->left was third node after rotation third node will move to top so setting second->left=null
    parentnode->left=third;  //only this have to change parentnode->left **************************************************
     rootnode=parentnode;   //since parentnode is rootnode after rotation it is updated so updating rootnode
	}
	if(holdthirdleft!=NULL)
    {
     insertafterrotate(third,holdthirdleft,holdthirdleft->data);
    }
    if(holdthirdright!=NULL)
    {
     insertafterrotate(third,holdthirdright,holdthirdright->data);
    }
   }
 }
	//printf("\nAfter Rotation");
	//inordertraversal();
    //preordertraversal( );	
}
void lLRotation(struct avltree *parentnode,struct avltree *critical,struct avltree *second)
{
   struct avltree *temp;                      //there are 5 condition for LL ROTATION only few changes are there******.
   printf("\n\nLL rotation ");
   printf("\nCritical node: %d",critical->data);
   //suppose there is no parent node then it will be NULL this parentnode!=NULL checks and prevent for illegal execution example at first while entering first node
   //parentnode->left==critical then else statement will execute for parentnode->right==critical 
   if(parentnode!=NULL && parentnode->right==critical && parentnode!= rootnode)//work in situation like 20 10 22 15 9 23 14 12
   {
    printf("\nparentnode= %d ",parentnode->data);  
	temp= second->right; 
	parentnode->right=second;
	second->right=critical;
	critical->left=NULL;
    if(temp!=NULL)//if it has right child  then only it will execute
	{
	 printf("\nsecond node has right child %d",temp->data);
	 insertafterrotate(second,temp,temp->data);
	}
	else
    {
	 printf("\nsecond node has no child");
	} 
   }
   else if(parentnode!=NULL && parentnode->left==critical && parentnode!= rootnode) //work in situation like 15 19 14 18 13 20 17 16
   {
	printf("\nparentnode=%d ",parentnode->data);
	temp= second->right;  //if it has right child
    parentnode->left=second;  //updating to parentnode before critical was left of parentnode so after rotation second node will be left side of parent node
    second->right=critical;  //rotating so critcal will become right child of second node
    critical->left=NULL;//because in critical node left side  was second node after execution critical node is under second node 
    if(temp!=NULL)//if it has right child  then only it will execute
	{
	 printf("\nsecond node has right child %d",temp->data);
	 insertafterrotate(second,temp,temp->data);
	}
    else
	{
	 printf("\nsecond node has no child");
    } 
   }
   else
   {//it is important to check critical==rootnode first then parentnode==rootnode because if critical node is rootnode then oviously rootnode will not have parent so to avoid error check this condition first
	if(critical==rootnode)//this is written down becaue only once or twice will execute it work in situation example 5 4 3 only
	{
	 printf("\ncritical node is rootnode %d so no parent node",critical->data);
	 temp= second->right;    //if it has right child 
	 second->right=critical;  //rotating so critcal will become right child of second node
	 critical->left=NULL;    //because in critical node left side  was second node after execution critical node is under second node 
	 //critical->right=critical->right;  //whatever in right of critical node will be there as same not necessary
	 rootnode=second;   //since critical node was rootnode now second node will be rootnode because now critical node is under second node as right child
	 if(temp!=NULL)        //if it has right child  then only it will execute
	 {
	  printf("\nsecond node has right child %d",temp->data);
	  insertafterrotate(second,temp,temp->data);
     }
	 else
	 {
	  printf("\nsecond node has no child");
	 }	
	}
	else
	{
	 if(parentnode==rootnode) //it has left and right condition 
	 {
	  printf("\nparentnode=%d ",parentnode->data);
	  printf("\nparentnode  is rootnode %d",parentnode->data);
	  if(parentnode->left==critical)  //it work in situation example 7 5 8 4 3
	  {
	   temp= second->right;   //if it has right child
	   parentnode->left=second;  //updating to parentnode before critical was left of parentnode so after rotation second node will be left side of parent node
       second->right=critical; //rotating so critcal will become right child of second node
       critical->left=NULL; //because in critical node left side  was second node after execution critical node is under second node 
       rootnode=parentnode;  //updating rootnode becaus parentnode was rootnode whatever changes in parentnode will reflect to rootnode so updating rootnode
	  }
	  else if(parentnode->right==critical) //it work in situation example 7 5 19 15 13
	  {
	   temp= second->right;
	   parentnode->right=second; //only here is change from parentnode->left=second; to parentnode->right=second;	
	   second->right=critical;
	   critical->left=NULL;
	   rootnode=parentnode;
	  }
	  if(temp!=NULL)//if it has right child  then only it will execute
	  {
	   printf("\nsecond node has right child %d",temp->data);
	   insertafterrotate(second,temp,temp->data);
	  }
	  else
	  {
	   printf("\nsecond node has no child");
	  }
	 }
	}
   }
}
void lRRotation(struct avltree *parentnode,struct avltree *critical,struct avltree *second,struct avltree *third)
{
  struct avltree *holdthirdleft,*holdthirdright;
  printf("\n\nLR rotation");
  if(parentnode!=NULL && parentnode->left==critical && parentnode!= rootnode)//this statement will work when situation like example 6 11 4 9 12 3 7 8 
  {                                                                           
   //we have left and right condition
   printf("\nParent node %d ",parentnode->data);
   printf("\nCritical node %d is left of parent node",critical->data);
   holdthirdleft=third->left;
   holdthirdright=third->right;
   critical->left=NULL;  //code is copied from RL rotation only this is change from critical->right=NULL to critical->left=NULL 
   second->right=NULL;   //code is copied from RL rotation only this is change from second->left=NULL to second->right=NULL 
   third->left=second;   //code is copied from RL rotation only this is change from third->left=critical to third->left=second 
   third->right=critical; //code is copied from RL rotation only this is change from third->right=second to third->right=critical
   parentnode->left=third; //updating parentnode
   if(holdthirdleft!=NULL)
    {
     insertafterrotate(third,holdthirdleft,holdthirdleft->data);
    }
   if(holdthirdright!=NULL)
    {
     insertafterrotate(third,holdthirdright,holdthirdright->data);
    }
  }
  else if(parentnode!=NULL && parentnode->right==critical && parentnode!= rootnode)//this statement will work when situation like example 4 3 8 13 7 2 10 11  when parentnode and critical is not root node
  {
   printf("\nParent node %d ",parentnode->data);
   printf("\nCritical node %d is right of parent node",critical->data);
   holdthirdleft=third->left;
   holdthirdright=third->right;
   critical->left=NULL;  // code is copied from RL rotation only this is change from critical->right=NULL to critical->left=NULL 
   second->right=NULL;   //code is copied from RL rotation only this is change from second->left=NULL to second->right=NULL 
   third->left=second;   //code is copied from RL rotation only this is change from third->left=critical to third->left=second 
   third->right=critical; //code is copied from RL rotation only this is change from third->right=second to third->right=critical
   parentnode->right=third; //only here we have to change***********************************
   if(holdthirdleft!=NULL)
   {
    insertafterrotate(third,holdthirdleft,holdthirdleft->data);
   }
   if(holdthirdright!=NULL)
   {
    insertafterrotate(third,holdthirdright,holdthirdright->data);
   }
  }
  else
  {//it is important to check critical==rootnode first then parentnode==rootnode because if critical node is rootnode then oviously rootnode will not have parent so to avoid error check this condition first  
   if(critical==rootnode) //we dont have  left and right condition //this code will work when critical==rootnode example 9 7 8 
   {
    printf("\nCritical node is rootnode %d so no parent node",critical->data);
	holdthirdleft=third->left;
    holdthirdright=third->right;
    critical->left=NULL; // change critical->right=NULL to critical->left=NULL whole code is copied from RL rotation *****
    second->right=NULL;// change second->left=NUL to second->right=NUL whole code is copied from RL rotation *****
    third->left=second;//after rotation second will be left of third node
    third->right=critical;//after rotation critical will be right of third node
    rootnode=third;//since Critical is rootnode after rotation third node will be rootnode so updating
    if(holdthirdleft!=NULL)
    {
     insertafterrotate(third,holdthirdleft,holdthirdleft->data);
    }
    if(holdthirdright!=NULL)
    {
     insertafterrotate(third,holdthirdright,holdthirdright->data);
    }
   }
   else if(parentnode==rootnode) //we have here left and right condition
   {
    printf("\nparentnode  is rootnode %d",parentnode->data);
	printf("\nCritical node %d",critical->data);
    if(parentnode->right==critical)//this code will work when parentnode==rootnode example 10 23 8 19 20
	{
	 holdthirdleft=third->left; //third node both left and right wil be updated so storing in other pointer
     holdthirdright=third->right;
     third->left=second; //after rotation critical will be right of third node
     third->right=critical;  //after rotation second will be left of third node
     critical->left=NULL; 
     second->right=NULL;  
     parentnode->right=third;
     rootnode=parentnode;   //since parentnode is rootnode after rotation it is updated so updating rootnode
    }
    else if(parentnode->left==critical) //this statement work in situation example 10 8 12 5 6
    {
     holdthirdleft=third->left; //third node both left and right wil be updated so storing in other pointer
     holdthirdright=third->right;
     third->left=second;
     third->right=critical; 
     critical->left=NULL;  
     second->right=NULL;  
     parentnode->left=third; 
     rootnode=parentnode;   //since parentnode is rootnode after rotation it is updated so updating rootnode
	}
	if(holdthirdleft!=NULL)
    {
     insertafterrotate(third,holdthirdleft,holdthirdleft->data);
    }
    if(holdthirdright!=NULL)
     {
      insertafterrotate(third,holdthirdright,holdthirdright->data);
     }
   }
  }
	 //printf("\nAfter Rotation");
	 //inordertraversal();
     //preordertraversal( );
}
void balance_factorof_all_nodeforinformation(void)
{
 struct avltree *p;
	p=rootnode;
    printf("\nbalance factor of all node:\n");
	while(1)
	{
			if(rootnode==0) //here this will not execute not necessary
      	{
        	printf(" Tree is empty.");
	       break;
        }
		while(p)
		{
			pushintostack2( p);
			p=p->left;
		}
		if(top2==0)
		{
	    	break;
		}
			p=pop2();
			updatebalance_factor_ofnode(p);
			p=p->right;	
	}	
}
void do_inordersuccessor_andpush_all_elements_thatcomes_inway(struct avltree *rootnode)
{//all inorder successor will be pushed into stack to catch unbalanced node
	struct avltree *root=rootnode,*leftnode;
	pushintostack(root);
	leftnode=root->right;
	if(leftnode->left==NULL && leftnode->right!=NULL )
	{
	 pushintostack(leftnode);
	 return;	
	}
	pushintostack(leftnode);
	while(leftnode->left != NULL)
	{
	 leftnode=leftnode->left;
	 pushintostack(leftnode);
	}	
}
