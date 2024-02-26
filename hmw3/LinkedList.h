//Sertaç Derya 22003208 Sec1
#ifndef LINKED_LIST
#define LINKED_LIST
#include <iostream>
#include "Node.h"

template<class ItemType>
class LinkedList {
    private:
        Node<ItemType>* headPtr = nullptr;
        int itemCount = 0;
        Node<ItemType>* getNodeAt(int position) const;
    public:
        LinkedList();
        ~LinkedList();
        LinkedList(const LinkedList<ItemType>& list);
        int getLength() const;
        bool isEmpty() const;
        bool remove(int position);
        bool insert(const ItemType& entry, int position);
        void clear();
        ItemType getEntry(int position) const;
        void setEntry(int position, const ItemType& newEntry);
        LinkedList<ItemType>& operator=(const LinkedList<ItemType>& aList);
};
//#include "LinkedList.cpp"
template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0){
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList() {
    //get entries then delete them from the end to the beginning
    this->clear();
    this->itemCount = 0;
}

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& list) {
    //from the beginning to the end copy the objects held by the nodes 
    //then put the nextPtr of that node to the next object that will be created
    /* if(this->itemCount == 0) {
        this->headPtr = new Node<ItemType>(0);
    } else {
        this->clear();
    }
    Node<ItemType>* currentPtr = this->headPtr;
    for(int i = 0; i < list.itemCount; i++) {//create copy constructor for the object to do deep copy
        currentPtr->setItem(list.getNodeAt(i)->getItem());
        if(i != list.itemCount - 1) {
            currentPtr->next = new Node<ItemType>(0);
            currentPtr = currentPtr->next;
            this->itemCount++;
        }
    }
    this->itemCount++; */
    for(int i = 0; i < list.getLength(); i++) {
        this->insert(list.getEntry(i), i);
    }
}

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const {//postion starts form 0
    if(position > this->itemCount) {
        std::cout << "THE POSITION EXCEEDS LIMIT" << std::endl;
        return nullptr;
    }
    Node<ItemType>* current = this->headPtr;
    for(int i = 0; i < position; i++) {
        current = current->next;
    }
    return current;
}

template<class ItemType>
int LinkedList<ItemType>::getLength() const {
    return this->itemCount;
}

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const{
    Node<ItemType>* current = this->headPtr;
    for(int i = 0; i < position; i++) {
        current = current->next;
    }
    return current->item;
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const {
    if(itemCount == 0) { return true; }
    return false;
}
//if itemcount == 0 then set headptr to null
template<class ItemType>
bool LinkedList<ItemType>::remove(int position) {// position starts from 0
    if(position >= this->itemCount) { return false; }
    else {
        Node<ItemType>* current;
        Node<ItemType>* before;
        if(this->itemCount == 1) {
            delete headPtr;
            headPtr = nullptr;
            this->itemCount--;
            return true;
        } else if(position == 0) {
            current = this->headPtr->next;
            this->headPtr->next = nullptr;
            delete this->headPtr;
            this->headPtr = current;
            this->itemCount--;
            return true;
        } else {
            before = this->getNodeAt(position - 1);
            current = before->next;
            before->next = current->next;
            current->next = nullptr;
            delete current;
            current = nullptr;
            this->itemCount--;
            return true;
        }
    }
    
}

// write this in MVS !!!!!!!!!!
/* template<class ItemType> 
bool LinkedList<ItemType>::add(const ItemType& entry) {//sort while insterting, find which position to add then insert the object with the position
    Node<ItemType>* current = headPtr;
    bool bigger = true;

    if(itemCount == 0) {
        return this->insert(entry, 0);
    }

    for(int i = 0; i < this->itemCount; i++) {
        if(entry.getIDforSort() < current->item.getIDforSort()) {
            return this->insert(entry, i);
        }
    }

    return this->insert(entry, this->itemCount);
} */

template<class ItemType>
bool LinkedList<ItemType>::insert(const ItemType& entry, int position) {// position starts from 0
    if(position > this->itemCount) { return false; }
    else {
        Node<ItemType>* aNode = new Node<ItemType>(entry);
        Node<ItemType>* before = headPtr;
        Node<ItemType>* current;
        if(this->itemCount > 0) {
            current = before->next;
        }
        if((position == 0) & this->itemCount == 0) {
            this->headPtr = aNode;
            this->itemCount++;
            return true;
        } else if(position == 0) {
            this->headPtr = aNode;
            aNode->next = before;
            this->itemCount++;
            return true;
        } else {
            for(int i = 0; i < position; i++) {
                if(i + 1 == position) {
                    before->next = aNode;
                    aNode->next = current;
                    this->itemCount++;
                    return true;
                }
                before = before->next;
                current = before->next;
            }
        }
    }
    return false;
}

template<class ItemType>
void LinkedList<ItemType>::clear() {
    while(!this->isEmpty()) {
        this->remove(0);
    }
    
}

template<class ItemType>//change the selected entrywith the new one. So we need to delete the node
void LinkedList<ItemType>::setEntry(int position, const ItemType& newEntry) {// position starts from 0
    /* Node<ItemType>* current = headPtr->next;
    Node<ItemType>* before = headPtr;
    if(itemCount <= position) { 
        return;
    } else if(position == 0) {
        this->headPtr = nullptr;
        delete this->headPtr;
        this->headPtr = new Node<ItemType>(newEntry);
        this->headPtr->next = current;
    } else {
        for(int i = 0; i < position; i++) {
            before = current;
            current = current->next;
            if(i + 1 == position) {
                delete before;
                before = new Node<ItemType>(newEntry);
                before->next = current;
            }
        }
    } */

    if(position > this->itemCount) { }
    else {
        Node<ItemType>* aNode = new Node<ItemType>(newEntry);
        Node<ItemType>* before = headPtr;
        Node<ItemType>* current = before->next;
        
        if(position == 0) {
            this->headPtr = aNode;
            aNode->next = current;
            before->next = nullptr;
            delete before;
        } else {
            for(int i = 0; i < position; i++) {
                if(i + 1 == position) {
                    before->next = aNode;
                    aNode->next = current->next;
                    current->next = nullptr;
                    delete current;
                }
                before = before->next;
                current = before->next;
            }
        }
    }
}

template<class ItemType>//do if needed
LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList<ItemType>& aList) {
    /* if(this->itemCount == 0) {
        this->headPtr = new Node<ItemType>(aList);
    } else {
        this->clear();
    }
    Node<ItemType>* currentPtr = this->headPtr;
    for(int i = 0; i < aList.itemCount; i++) {//create copy constructor for the object to do deep copy
        currentPtr->setItem(aList.getNodeAt(i)->getItem());
        if(i != aList.itemCount - 1) {
            currentPtr->next = new Node<ItemType>(0);
            currentPtr = currentPtr->next;
            this->itemCount++;
        }
    }
    this->itemCount++; */

    if(this->itemCount != 0) {
        this->clear();
    } 
    for(int i = 0; i < aList.getLength(); i++) {
        this->insert(aList.getEntry(i), i);
    }
    return *this;
}

#endif