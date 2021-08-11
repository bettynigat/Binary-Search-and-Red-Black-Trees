# Binary Search and Red Black Trees
This project consists of implementing binary seach tree and red-black tree. 

### class IntEntry 
IntEntry serves as a node stored in the binary search tree or the red-black tree. This node contains
<key, value> where the key represents an integer value stored in the tree while the value is used to store how many copies of the *key* have been inserted. The value in the node is a signed integer with 31 bits, so its range is between -2^30 to (2^30)-1. For a red-black tree node, it uses 1 bit of the value to represent if it’s red or black. 


### Binary search tree for integers
The first part involves implementing a binary search tree for storing/looking up/removing integers in the class IntBST. Specifically, the following public
functions are implemented:
- *void insert(int k)* inserts an integer, k, into the tree. It allows to insert
multiple entries with the same key into the tree.
- *int find(int k)* returns 0 if k does not exist otherwise it returns the number of
nodes with the key, k, in the binary search tree. 
- *bool remove(int k)* removes a node whose key is k. If multiple nodes with the key,
k, exist, only one instance of it is removed. If removal is successful, it returns true. If k does not
exist in the tree, it returns false.
- *int countRange(int k1, int k2)* returns the number of keys stored in the tree
whose value is between k1 and k2. It is possible that k1 > k2, k1 == k2, or k1 < k2.

### Red-black tree for integers
The second part involves implementing red-black tree for IntEntry nodes in class IntRBTree. 
IntRBTree inherits from class IntBST, and all we need to update is the following two member functions so that the tree maintains
the properties of a red-black tree. 
- *void insert(int k)* inserts an integer, k, into the red-black tree. It is allowed to insert multiple
entries with the same key into the tree. After insertion, all red-black tree properties must hold.
- *bool remove(int k)* removes a node whose key is k. If multiple nodes with the key k
exist, only one instance of it is removed. If removal is successful, it returns true. If k does not exist
in the tree, it returns false, After removal, all red-black tree properties must hold.

### Performance difference between BST and RB trees
The RB tree is a self-balancing tree while the BST is not. For example, let’s say our input is the
sequence of words that goes like 1,2,3…….,999,1000. If we use BST to insert those key values,
they will be stored in a single chain of 1000 elements. (gives a skewed shape) In this case, which
could be the worst case scenario, finding and removing takes a linear time that is proportional
to the number of inputs. For large input sizes of such data type, this could be a very slow
process.
On the other hand, if we input the same data into our RB tree, we will not have the same
problem. Because the RB tree balances itself after every insertion of those keys. As a result,
finding and removing in the RB tree will take logarithmic time, not linear time. In cases like this
the RB tree outperforms the BST tree.
