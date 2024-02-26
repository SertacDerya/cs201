//Sertaç Derya 22003208 Sec1
#ifndef NODE
#define NODE

template<class ItemType>
class Node  {
    public:
        Node();
        Node(const ItemType& item);
        Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
        void setItem(const ItemType& anItem);
        void setNext(Node<ItemType>* nextNodePtr);
        ItemType getItem() const;
        Node<ItemType>* getNext() const;
        ItemType item;
        Node<ItemType>* next;
};
//#include "Node.cpp"
template<class ItemType>
Node<ItemType>::Node() {
    this = nullptr;
    this->next = nullptr;
}
template<class ItemType>
Node<ItemType>::Node(const ItemType& item, Node<ItemType>* nextNodePtr) {
    this->next = nextNodePtr;
    this->item = item;
}
template<class ItemType>
Node<ItemType>::Node(const ItemType& item) {
    this->next = nullptr;
    this->item = item; 
}
template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr) {
    this->next = nextNodePtr;
}
template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anitem) {
    item = anitem;
}

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const {
    return this->next;
}
template<class ItemType>
ItemType Node<ItemType>::getItem() const {
    return this->item;
}

#endif