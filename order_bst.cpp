
#include "order_bst.h"
using namespace DS;

Order::Order(const Order &in) {
    

}

Order &Order::operator=(const Order &in) {
    return <#initializer#>;// TODO: implement this
}

void Order::addItem(size_t sku, size_t quantity, double price) {
// TODO: implement this
}

bool Order::shipOrder() {
    if(orderStatus == pending){
        int tf = 0;
        for(size_t = 0; i < itemCount;++i){
            if(inventory.get(items[i].sku).getQuantity() < i)
        }

    }
    return false;// TODO: implement this
}

double Order::getOrderProfitLoss() const {
    return 0;// TODO: implement this
}

double Order::getItemProfitLoss(const ItemOrdered &item) const {
    return 0;// TODO: implement this
}

void Order::addItem(const ItemOrdered &item, DSBTREE::node <ItemOrdered> *root_ptr) {
    if(root_ptr == nullptr)     //check root
        root_ptr = new node(item);
    else
        addItem(item, root_ptr);

    if(item < root_ptr){
        if(root_ptr->left() == nullptr){     //check left
            root_ptr->setLeft(new node(item));
        }
        else{
            addItem(item,root_ptr->left());
        }
    }
    else if(item>root_ptr->data()){
        if(root_ptr->right() == nullptr){     //check right
            root_ptr->setRight(new node(item))
        }
        else{
            addItem(item,root_ptr->right());
        }
    }
}

void Order::clearItems(DSBTREE::node <ItemOrdered> *root_ptr) {
    if(root_ptr!= nullptr){
        clearItems(root_ptr.left());
        clearItems(root_ptr.right());
        delete root_ptr;
    }
// TODO: implement this

}

DSBTREE::node <ItemOrdered> *Order::tree_copy(const DSBTREE::node <ItemOrdered> *root_ptr) {
    return nullptr;// TODO: implement this
}

double Order::outputItem(std::ostream &out, const ItemOrdered &item) const {
    if(item == nullptr)
        return;
    node * cursor = items;
    while (cursor != nullptr){
        if(item.sku == cursor)
            out << item;
        else if(item.sku < cursor){
            cursor = cursor.left();
            if(item.sku == cursor)
                out << item;
        }
        else if(item.sku > cursor){
            cursor = cursor.right();
            if(item.sku == cursor)
                out << item;
        }
    }
    return 0;// TODO: implement this
}

double Order::outputItems(std::ostream &os, DSBTREE::node <ItemOrdered> *root_ptr) const {
    if(root_ptr != nullptr){

    }
    return 0;// TODO: implement this
}

bool Order::shipOrder(DSBTREE::node <ItemOrdered> *root_ptr) {
    return false;// TODO: implement this
}

double Order::getOrderProfitLoss(DSBTREE::node <ItemOrdered> *root_ptr) const {
    return 0;// TODO: implement this
}
