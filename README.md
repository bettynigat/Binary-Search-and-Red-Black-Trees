# Binary Search and Red Black Trees
This project consists of implementing binary seach tree and red-black tree. 

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
- *void insert(int k)* to insert an integer, k, into the red-black tree. It is allowed to insert multiple
entries with the same key into the tree. After insertion, all red-black tree properties must hold.
- *bool remove(int k)* removes a node whose key is k. If multiple nodes with the key k
exist, only one instance of it is removed. If removal is successful, it returns true. If k does not exist
in the tree, it returns false, After removal, all red-black tree properties must hold.
