
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
    return false;// TODO: implement this
}

double Order::getOrderProfitLoss() const {
    return 0;// TODO: implement this
}

double Order::getItemProfitLoss(const ItemOrdered &item) const {
    return 0;// TODO: implement this
}

void Order::addItem(const ItemOrdered &item, DSBTREE::node <ItemOrdered> *root_ptr) {
// TODO: implement this
}

void Order::clearItems(DSBTREE::node <ItemOrdered> *root_ptr) {
// TODO: implement this
}

DSBTREE::node <ItemOrdered> *Order::tree_copy(const DSBTREE::node <ItemOrdered> *root_ptr) {
    return nullptr;// TODO: implement this
}

double Order::outputItem(std::ostream &out, const ItemOrdered &item) const {
    return 0;// TODO: implement this
}

double Order::outputItems(std::ostream &os, DSBTREE::node <ItemOrdered> *root_ptr) const {
    return 0;// TODO: implement this
}

bool Order::shipOrder(DSBTREE::node <ItemOrdered> *root_ptr) {
    return false;// TODO: implement this
}

double Order::getOrderProfitLoss(DSBTREE::node <ItemOrdered> *root_ptr) const {
    return 0;// TODO: implement this
}
