#include <list> 

#include "bst.h"
#include <cassert>
#include <iostream>
#include <iterator>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// Implementation of IntBST
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

IntEntry* IntBST::findRecursive(IntEntry* p, int k)
{

	//key is not found 
	if (p==NULL) return NULL;

	else if (p->key()==k)
	{
		return p; 
	}

	else if(p->key()< k)
	{
		return findRecursive(p->right(),k);
	}

	else
		return findRecursive(p->left(),k);

}

int IntBST::find(int k)
{

	IntEntry* ptr= findRecursive(T.getRoot(),k);
	if (ptr==NULL) return 0; 
	return ptr->value(); 
}
//////////////////////////////////////////////////////////////////////////

IntEntry* IntBST::insertRecursive(IntEntry* p, int k)
{


	//else other than root

	
	if (p==NULL) //at point of insertion 
	{
		IntEntry* entry= new IntEntry(k,1); 
		p=entry; 
		cnt++; 
	}

	else if (p->key()<k)
	{
		p->setRight(insertRecursive(p->right(), k));
		p->right()->setParent(p); 
	}

	else if (p->key()>k)
	{
		p->setLeft(insertRecursive(p->left(),k));
		p->left()->setParent(p); 
	}

	return p;
}

void IntBST::insert(int k)
{

	IntEntry* ptr= findRecursive(T.getRoot(), k);
	if (ptr) //already a key is found 
	{
		int m= find(k); //already the no of keys stored 
		ptr->setValue(ptr->value()+1);
		cnt++; 
		return;  
	}

	T.setRoot(insertRecursive(T.getRoot(),k)); 

}


//////////////////////////////////////////////////////////////////////////
int IntBST::minRecursive (IntEntry* p)
{
	if (p==NULL) return -1;
	else if(p->left()==NULL) return p->key();
	else
		return minRecursive(p->left()); 

}

int IntBST::min()
{
	return minRecursive(T.getRoot());
}
int IntBST::successorRecursive(IntEntry* p)
{
	if (p->right()!=NULL)
		return minRecursive(p->right());
	else
	{
		IntEntry* parent= p->parent();
		IntEntry* current= p; 

		while ((parent!=NULL)&&current==parent->right())
		{
			current=parent;
			parent=current->parent();
		}

		return parent==NULL? -1: parent->key();
	}

}

int IntBST::successor(int k)
{
	IntEntry* ptr= findRecursive(T.getRoot(), k);
	return (successorRecursive(ptr)); 

}

IntEntry* IntBST::removeRecursive(IntEntry* p, int key)
{
	if(p==NULL) return NULL; //given key not found
	if (p->key()==key) //target is found
	{
		//1. if the node is a leaf node, just remove it
		if (p->left()==NULL && p->right()==NULL){
			// p is left node of its parent
			if (p->isRoot())
			{
				T.setRoot(NULL);
				//delete p;
				//return NULL;
			}
			else if ((p->parent())->left()!=NULL && ((p->parent())->left())->key() == key) {
				(p->parent())->setLeft(NULL);
			}
			else
			{
				(p->parent())->setRight(NULL);
			}
			p=NULL;  
		}

		//2. it has only a right child
		else if (p->left()==NULL && p->right()!=NULL)
		{
			if (T.getRoot()->key() == key)
			{
				//if (!p->isRoot()) {
				//	std::cout<<"there is a problem here, p should have been a root and have a null parent\n";
				//}
				p->right()->setParent(NULL); // the right child is now the root
				//T.setRoot(p->right());
				p->right()->setColor(IntEntry::BLACK);
				//delete p;
				//return NULL;
			}
			else {p->right()->setParent(p->parent());
			if ((p->parent()->left())!=NULL && (p->parent()->left())->key() == key) {
				p->parent()->setLeft(p->right()); // if p was the left child for its parent
			}
			else {
				p->parent()->setRight(p->right()); // if p was the right child for its parent
			} }
			p=p->right(); 
		}

		else if (p->left()!=NULL && p->right()==NULL)
		{
			if (p->isRoot())
			{
				if (!p->isRoot()) {
					// std::cout<<"there is a problem here, p should have been a root and have a null parent\n";
				}
				p->left()->setParent(NULL); // the right child is now the root
				//T.setRoot(p->left());
				p->left()->setColor(IntEntry::BLACK);
				//delete p;
				//return NULL;
			}

			else {p->left()->setParent(p->parent());
			if ((p->parent()->left())!=NULL && (p->parent()->left())->key() == key) {
				p->parent()->setLeft(p->right()); // if p was the left child for its parent
			}
			else {
				p->parent()->setRight(p->right()); // if p was the right child for its parent
			}}
			p=p->left();
		}

		//3. has both children
		else
		{
			//find successor
			int s= successor(key);
			IntEntry* q = findRecursive(T.getRoot(), s);
			p->setKey(s);
			p->setValue(q->value());
			q  = removeRecursive(p->right(), s); 
			p->setRight(q);
			if (q) q->setParent(p);
		}
	}

	else if(p->key()<key)
	{

		//p->setRight(removeRecursive(p->right(),key));
		IntEntry* q  = removeRecursive(p->right(), key); 
		p->setRight(q);
		if (q) q->setParent(p);
	}
	else
	{
		//p->setLeft(removeRecursive(p->left(),key));
		IntEntry* q  = removeRecursive(p->left(), key); 
		p->setLeft(q);
		if (q) q->setParent(p);
	}

	return p; 

	}

bool IntBST::remove(int k)
{

	IntEntry* ptr= findRecursive(T.getRoot(), k);
	if (k==57)
	{
		cout<<k;
	}
	if(ptr==NULL) //no key found 
		return false; 
	if(ptr->value() >1) //key occurs more than once 
		{
			int m=ptr->value(); 
			ptr->setValue(m-1); //decrease value by 1 
			cnt--;
			return true; 
		}
	
	T.setRoot(removeRecursive(T.getRoot(),k));
	cnt--;
	return true;
}


void IntBST::countRangeRecursive(IntEntry* p, int k1, int k2, int& range)
{
	if (p==NULL) return;

	if (p->key()>k1)
	{
		countRangeRecursive(p->left(), k1, k2, range);
	}
	if (p->key()>k1 && p->key()<k2) range+=p->value();
	if (p->key()<k2)
		countRangeRecursive(p->right(), k1, k2, range); 
}

//////////////////////////////////////////////////////////////////////////
int IntBST::countRange(int k1, int k2)
{
	if(T.empty()) return 0;
	if(k1==k2) return 0;  
	int range = 0;
	if (k1<k2) countRangeRecursive(T.getRoot(), k1, k2, range);
	else countRangeRecursive(T.getRoot(), k2, k1, range);
	return range;

}
void IntBST::inorderRecursive(IntEntry* p)
{
    if (p != NULL) {

        inorderRecursive(p->left());
        cout<<p->key()<<'\t'<<p->color()<<endl; 
        inorderRecursive(p->right());
    }
}
void IntBST::inorder()
{
	IntEntry* ptr; 
	ptr=T.getRoot();
	inorderRecursive(ptr);
}

void IntBST::print()
{
	inorder(); 
	

}

//////////////////////////////////////////////////////////////////////////
// Implementation of IntRBTree
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////


IntEntry* IntRBTree::restructureRL(IntEntry* p)
{

	//cout<<"in restructuring"<<endl;
	IntEntry* parent= p->parent();
	IntEntry* gparent= p->parent()->parent(); 
	IntEntry* uncle= gparent->left(); 

	IntEntry* right=p->right();
	IntEntry* left=p->left();

	//link between parent and left
	if (right) right->setParent(parent); //other properties remain
	parent->setLeft(right); 

	//cout<<"1\n";
	//link between link between p and gparent
	p->setParent(gparent); 
	gparent->setLeft(p);

	//exchange key values 
	int m= gparent->key();
	int value = gparent->value();
	gparent->setKey(p->key());
	gparent->setValue(p->value());
	p->setKey(m);
	p->setValue(value);

	p->setLeft(uncle);
	if (uncle) uncle->setParent(p);

	p->setRight(left);
	if (left) left->setParent(p);

	return gparent; 
}

IntEntry* IntRBTree::restructureLR(IntEntry* p)
{

	IntEntry* parent= p->parent();
	IntEntry* gparent= p->parent()->parent(); 
	IntEntry* uncle= gparent->right(); 

	IntEntry* right=p->right();
	IntEntry* left=p->left();

	//link between parent and left
	if (left) left->setParent(parent); //other properties remain
	parent->setRight(left); 

	//cout<<"1\n";
	//link between link between p and gparent
	p->setParent(gparent); 
	gparent->setRight(p);

	//exchange key values 
	int m= gparent->key();
	int value = gparent->value();
	gparent->setKey(p->key());
	gparent->setValue(p->value());
	p->setKey(m);
	p->setValue(value);

	p->setRight(uncle);
	if (uncle) uncle->setParent(p);

	p->setLeft(right);
	if (right) right->setParent(p);

	return gparent; 
}


IntEntry* IntRBTree::restructureRR(IntEntry* p)
{
	IntEntry* parent= p->parent();
	IntEntry* gparent= p->parent()->parent(); 
	IntEntry* uncle= gparent->left(); 
	IntEntry* sibling= parent->left();

	//sibling and uncle could be null 

	//exchange key values parent and gparent 
	int m= gparent->key();
	int value = gparent->value();
	gparent->setKey(parent->key());
	gparent->setValue(parent->value());
	parent->setKey(m);
	parent->setValue(value);

	//link between p and gparent
	p->setParent(gparent); 
	gparent->setRight(p);

	// parent right and parent left
	parent->setRight(sibling);
	if(sibling) sibling->setParent(parent);
	parent->setLeft(uncle);
	if(uncle) uncle->setParent(parent);

	//link between parent and gparent
	parent->setParent(gparent);
	gparent->setLeft(parent); 

	return gparent; 
}

IntEntry* IntRBTree::restructureLL(IntEntry* p)
{
	IntEntry* parent= p->parent();
	IntEntry* gparent= p->parent()->parent(); 
	IntEntry* uncle= gparent->right(); 
	IntEntry* sibling= parent->right();

	//sibling and uncle could be null 

	//exchange key values parent and gparent 
	int m= gparent->key();
	int value = gparent->value();
	gparent->setKey(parent->key());
	gparent->setValue(parent->value());
	parent->setKey(m);
	parent->setValue(value);

	//link between p and gparent
	p->setParent(gparent); 
	gparent->setLeft(p);

	// parent right and parent left
	parent->setLeft(sibling);
	if(sibling) sibling->setParent(parent);
	parent->setRight(uncle);
	if(uncle) uncle->setParent(parent);

	//link between parent and gparent
	parent->setParent(gparent);
	gparent->setRight(parent); 

	return gparent; 
}





void IntRBTree::remedyDoubleRed(IntEntry*root, IntEntry*p)
{
	
	//cout<<p->key()<<" in remedy"<<endl;

	IntEntry* parent= p->parent();
	//IntEntry* gparent=p->parent()->parent(); 
	if (parent==root || parent->color()==IntEntry::BLACK )
		return; //everthing is good 
	IntEntry* gparent=p->parent()->parent(); 

	//case 1: restructuring 
	if (parent==gparent->right())
	{
		//cout<<"here"<<endl;
		IntEntry* uncle= gparent->left();
		if (uncle==NULL || uncle->color()==IntEntry::BLACK)
		{
			//cout<<"true"<<endl;
			if (parent->left()==p) //if p is left child 
			{
				parent= restructureRL(p);
				parent->setColor(IntEntry::BLACK);
				parent->left()->setColor(IntEntry::RED);
				parent->right()->setColor(IntEntry::RED); 
			}

			else //p is right child 
			{
				
				parent= restructureRR(p);
				parent->setColor(IntEntry::BLACK);
				parent->left()->setColor(IntEntry::RED);
				parent->right()->setColor(IntEntry::RED);
			}
		}

		else if (uncle->color()==IntEntry::RED)
		{
			//cout<<"recolor"<<endl;
			parent->setColor(IntEntry::BLACK);
			uncle->setColor(IntEntry::BLACK);
			if(gparent==root) return;
			//if grad parent is not root, color it red 
			gparent->setColor(IntEntry::RED);
			remedyDoubleRed(root, gparent); //because the parent of gparent
											//might also be red */
		}
	}

	else //parent->gparent->left()
	{
		
		IntEntry* uncle= gparent->right();
		if (uncle==NULL || uncle->color()==IntEntry::BLACK)
		{

			if (p==parent->left()) //LL
			{
				parent= restructureLL(p);
				parent->setColor(IntEntry::BLACK);
				parent->left()->setColor(IntEntry::RED);
				parent->right()->setColor(IntEntry::RED);

			}

			else if (p==parent->right())// LR
			{
				parent= restructureLR(p);
				parent->setColor(IntEntry::BLACK);
				parent->left()->setColor(IntEntry::RED);
				parent->right()->setColor(IntEntry::RED);
			}
 
		}

		else if (uncle->color()==IntEntry::RED)
		{
			parent->setColor(IntEntry::BLACK);
			uncle->setColor(IntEntry::BLACK);
			if(gparent==root) return;
			//if grad parent is not root, color it red 
			gparent->setColor(IntEntry::RED);
			remedyDoubleRed(root, gparent); //because the parent of gparent
											//might also be red 
		}
	}
}


void IntRBTree::insert(int k)
{
	IntEntry* ptr= findRecursive(T.getRoot(), k);
	if (ptr) //already a key is found 
	{
		// int m= find(k); //already the no of keys stored 
		ptr->setValue(ptr->value()+1);
		cnt++; 
		return;  
	}

	T.setRoot(insertRecursive(T.getRoot(),k));
	ptr= findRecursive(T.getRoot(), k);
	if (ptr->isRoot()) ptr->setColor(IntEntry::BLACK);
	else 
		{ptr->setColor(IntEntry::RED); 
		remedyDoubleRed(T.getRoot(), ptr);}

}

/////////////////////////////////////////////////////////////////////

void IntRBTree::doubleBlackRemedy(IntEntry* r)
{
	IntEntry* x= r->parent();
	IntEntry* y; //sibling of r 
	if (x->left()==NULL) y= x->right();
	else y=x->left(); 

	if (y->color()==IntEntry::BLACK)
	{
		//cout<<"black"<<endl;
		//case 1, y has atleast 1 red child 
		//restructure 
		if ((y->left()!=NULL && y->left()->color()==IntEntry::RED )||
			(y->right()!=NULL && y->right()->color()==IntEntry::RED))
		{
			//z is y's red child 
			IntEntry* z= (y->left()!=NULL && y->left()->color()==0? y->left() : y->right());
			int m= x->color();
			if (y==x->left())
			{
				if (z==y->left()) {z= restructureLL(z);}
				else {z= restructureLR(z);}
			}

			else if (y==x->right())
			{
				if (z==y->right()) {z=restructureRR(z);}
				else {z= restructureRL(z); }
			}

			if (m==0) z->setColor(IntEntry::RED);
			else z->setColor(IntEntry::BLACK);
			if (r) r->setColor(IntEntry::BLACK);
			z->left()->setColor(IntEntry::BLACK);
			z->right()->setColor(IntEntry::BLACK);
		}

		else //both children of y are black
		{
			if (r) r->setColor(IntEntry::BLACK);
			y->setColor(IntEntry::RED);
			if (x->color()==1 && !(x->isRoot()))
				doubleBlackRemedy(x);
			x->setColor(IntEntry::BLACK); 
		}
	}

	else //y is RED 
	{
		IntEntry* z= (y==x->right()? y->right(): y->left());
		// restructuring z 

		if (y==x->left())
		{
			if (z==y->left()) z= restructureLL(z);
			else z= restructureLR(z);
		}

		else if (y==x->right())
		{
			if (z==y->right()) z=restructureRR(z);
			else z= restructureRL(z);
		}

		y->setColor(IntEntry::BLACK);
		x->setColor(IntEntry::RED); 
		doubleBlackRemedy(x); 
	}
}


IntEntry* IntRBTree::deleted_node(IntEntry* root,int key)
{
	IntEntry* ptr= findRecursive(root,key);
	if (ptr->left()==NULL)
	{
		return ptr->left(); 
	}

	else if (ptr->right()==NULL)
	{
		return ptr->right(); 
	}
	else
	{
		IntEntry*p= ptr;
		p->setValue(successor(ptr->key()));
		return p;
	}
}





//////////////////////////////////////////////////////////////////////////
bool IntRBTree::remove(int k)
{
	IntEntry* ptr= findRecursive(T.getRoot(), k);
	if(ptr==NULL) //no key found
		return false; 
	if(ptr->value() >1) //key occurs more than once 
		{
			int m=ptr->value(); 
			ptr->setValue(m-1); //decrease value by 1 
			cnt--;
			return true; 
		}
	IntEntry* old_parent= ptr->parent(); 
	IntEntry* p= removeRecursive(T.getRoot(),k);
	
	T.setRoot(removeRecursive(T.getRoot(),k));

	if (p==T.getRoot())
	{
		if (p) p->setColor(IntEntry::BLACK);
	}

	else if (p!=NULL && p->color()==IntEntry::RED)
		p->setColor(IntEntry::BLACK);

	else if (old_parent->color()==IntEntry::RED)
	{
		if (p) 
			p->setColor(IntEntry::BLACK);
	}

	else 
		doubleBlackRemedy(p);
	cnt--;
	return true; 
}




