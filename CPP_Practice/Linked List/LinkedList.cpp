#include <iostream>
#include <stdexcept>
#include <cstdio>

class Node
{
public:
    int val;
    Node* next;
    Node* prev;
    Node(int value);
    ~Node(); //Not defined yet
};

Node::Node(int value) {

    val = value;
    next = NULL;
    prev = NULL;
}

Node::~Node() {
    std::cout << "Deleting node with val " << val << " at: " << this << std::endl; //prints pointer to node being deleted
}

class LinkedList
{

public:
    int len = 0;
    Node* head; //Sentinel (dummy node)

    LinkedList(); //Creates new lined list with created head
    ~LinkedList(); //Deletes entire list by making calls to deleteNode

    bool isEmpty(); //returns true if head points to NULL
    void appendNewNode(int val); //Creates new node and adds after head
    int deleteNode(Node* nodePtr); 
    /*
    returns: val of deleted node;
    deletes: node at nodePtr and adjusts ptrs;
    throws: runtime_error if attempting to delete head/NULL.
    */
    void insertNodeAfter(int val, Node* prevPtr);
    /*
    returns: void;
    inserts: new node with value val after prevPtr and adjusts ptrs;
    throws: runtime_error if attempting to insert after NULL.
    */

    void insertNodeBefore(int val, Node* nextPtr);
    /*
    returns: void;
    inserts: new node with value val befor nextPtr and adjusts ptrs;
    throws: runtime_error if attempting to insert before head/NULL.
    */
    void disp();

    void mergesort();
    void merge(LinkedList& left, LinkedList& right);

    void insertionSort();
};

void LinkedList::insertionSort() {

    if(isEmpty()) return;

    LinkedList list2; //create new linked list

    Node* current;
    int insertVal;
    
    list2.insertNodeAfter(deleteNode(this->head->next), list2.head); //delete first elt from l1 and insert to l2 after head
/*    disp();*/
    list2.disp();
    while(!this->isEmpty()) {
        insertVal = this->deleteNode(this->head->next); //delete from old linked list and store val to insert in l2
        current = list2.head->next;
        while(current->next != NULL && insertVal > current->val) current = current->next;

        //2 ways to breakout of loop
        if(insertVal <= current->val) { //current has greater or equal val

            list2.insertNodeBefore(insertVal, current);
            std::cout << "Inserting " << insertVal << " before " << current->val << std::endl;

        } else { //end reached and current has lesser value

            list2.insertNodeAfter(insertVal, current);
            std::cout << "Inserting " << insertVal << " after " << current->val << std::endl;
        }
/*        disp();*/
        list2.disp();
    }




    //Disgusting hack to move contents of l2 back to l1
    delete head;
    head = list2.head; 

    Node* head2 = new Node(0); //dummy node to replace current head of list2
    list2.head = head2;
}




LinkedList::LinkedList() {

    head = new Node(0);
}

LinkedList::~LinkedList() {

    while(!this->isEmpty()) {
        this->deleteNode(head->next);
    }

    std::cout << "Deleting Head" << std::endl;
    delete head;
}

bool LinkedList::isEmpty() {
    return (head->next == NULL);
}

void LinkedList::appendNewNode(int val) {
    Node* newPtr = new Node(val);

    newPtr->next = head->next;
    newPtr->prev = head;

    head->next = newPtr;

    if(newPtr->next != NULL) {
        newPtr->next->prev = newPtr;
    }

    ++len;
}

int LinkedList::deleteNode(Node* nodePtr) {

    if(nodePtr == NULL) {
        throw std::runtime_error("Attempting to delete memory pointed to by NULL\n");
    }

    if(nodePtr->prev == NULL) {
        throw std::runtime_error("Node element does not have a valid prev attr, or attempting to delete head.\n");
    }

    nodePtr->prev->next = nodePtr->next;

    if(nodePtr->next != NULL) {
        nodePtr->next->prev = nodePtr->prev;
    }

    int val = nodePtr->val;

    delete nodePtr;

    --len;

    return val;
}

void LinkedList::insertNodeAfter(int val, Node* prevPtr) {


    if (prevPtr == NULL) {
        throw std::runtime_error("Attempting to insert after NULL\n");
    }

    Node* newPtr = new Node(val);
    newPtr->prev = prevPtr;
    newPtr->next = prevPtr->next; //Could be NULL

    if (newPtr->next != NULL) {
        newPtr->next->prev = newPtr;
    }

    prevPtr->next = newPtr;

    ++len;
}

void LinkedList::insertNodeBefore(int val, Node* nextPtr) {


    if (nextPtr == NULL) {
        throw std::runtime_error("Attempting to insert before NULL\n");
    }

    if (nextPtr->prev == NULL) {
        throw std::runtime_error("Attempting to insert before head/invalid prev attrib.\n");
    }

    Node* newPtr = new Node(val);
    newPtr->next = nextPtr;
    newPtr->prev = nextPtr->prev; //Cannot be NULL

    newPtr->prev->next = newPtr;
    nextPtr->prev = newPtr;

    ++len;
}

void LinkedList::disp() {

    std::cout << "[";

    for (Node* current = head->next; current != NULL; current = current->next) {

        std::cout << " " << current->val << " ";
    }

    std::cout << "]" << std::endl;
}

int main() {

    LinkedList list;

    char quit;

    do {

        int choice;
        do {

            system("clear");

            std::cout << "Enter choice (int between 1 & 6):" << std::endl
            << "  1> Display List" << std::endl
            << "  2> Add new node at head" << std::endl
            << "  3> Delete node at head" << std::endl
            << "  4> Perform insertion sort" <<  std::endl
            << "  5> Perform merge sort" <<  std::endl
            << "  6> Perform quick sort" << std::endl;

            std::cout << "\nEnter choice: ";
            std::cin >> choice;

        } while(choice < 1 || choice > 6);


        switch(choice) {

            case 1: {
                list.disp();
                std::cout << "Length = " << list.len << std::endl;
            } break;

            case 2: {
                int val;
                std::cout << "\nEnter val to be inserted: ";
                std::cin >> val;
                list.appendNewNode(val);
                list.disp();
            } break;

            case 3: {
                try {
                    list.deleteNode(list.head->next);
                }
                catch(const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    std::cout << "Note: Probably attempting to delete from empty list" << std::endl;
                }
                list.disp();
            } break;

            case 4: {
                list.insertionSort();
                list.disp();
            } break;

            default: {
                std::cout << "Not yet implemented!" << std::endl;
            }
        }


        std::cout << "\nEnter 'q' to quit and any other char to continue: ";
        std::cin >> quit;
    } while (quit != 'q');


    return 0;
}