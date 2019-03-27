# Doubly-linked-list
Doubly linked list is a linked data structure that consists of a set of sequentially linked records called nodes. Each node contains three fields: two link fields (references to the previous and to the next node in the sequence of nodes) and one data field. The program includes the following functions: 
int GetSize();
void clear();
void push_front(T data);
void push_back(T data);
void pop_front();
void pop_back();
void insert(T data, int index);
void removeAt(int index);
T & operator [] (const int index);
void PrintFromHead();
void PrintFromTail();
