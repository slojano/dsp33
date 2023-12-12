/*Program Name: orders_dll.cpp
Programmer Name: Steve Lojano
Attempt Number: 1
Purpose: source file for orders_dll.h
Global Variable List: none

 */
#include "orders_dll.h"
#include "order_bst.h"
using namespace DS;


DS::Orders::Orders(const Orders &in) {
    lastOrderNumber = in.lastOrderNumber;
    currentOrder = in.currentOrder;
    inventory = in.inventory;
    auto * next = in.head->next();
    //auto * temp2 = in.head->next();
    head = new node (in.head->getData());
    auto * end = head;
    //currentOrder = head;
    orderCount = in.orderCount;
    while(next != nullptr){ //check to make sure next is still valid
        tail = end;
        end->next() = new node(next->getData(), nullptr,end);
        end->next()->prev() = end;
        end = end->next();

        next = next->next();

    }
}

Orders &DS::Orders::operator=(const Orders &in) {
    if(this != &in){//check to make sure it is not a self assignment
        clear();
        orderCount = in.orderCount;
        auto * next = in.head->next();
        head = new node(in.head->getData());
        currentOrder = head;
        while(next != nullptr) {
            tail = currentOrder;
            currentOrder->next() = new node (next->getData());
            currentOrder->next()->prev() = currentOrder;
            currentOrder = currentOrder->next();

            next = next->next();
        }
    }
    return *this;
}

Order *DS::Orders::insert(const std::string &customerName) {
    auto * temp = new Order(inventory,size(),customerName);
    auto * tempN = new node(*temp, nullptr);
    if(isCurrentValid()){
        if(head == currentOrder){
            tempN->next() = head;
            currentOrder->prev() = tempN;
            head = tempN;
            currentOrder = tempN;
        }
        else {
            tempN->prev() = currentOrder->prev();
            currentOrder->prev() = tempN;
            tempN->next() = currentOrder;
            tempN->prev()->next() = tempN;
            currentOrder = tempN;
        }

    }
    else{
        tempN->next() = head;
        head->prev() = tempN;
        head = tempN;
        currentOrder = tempN;
    }
    orderCount++;
    return temp;
}

Order *DS::Orders::append(const std::string &customerName) {

    if(isCurrentValid()){
        auto * temp = new Order(inventory,size(),customerName);
        auto *tempN = new node(*temp,currentOrder->next(),currentOrder);
        currentOrder->next()->prev() = tempN;
        currentOrder->next() = tempN;
        orderCount++;
        return temp;
    }
    else{
        auto * temp = new Order(inventory,size(),customerName);
        auto * tempN = new node(*temp, nullptr);
        if(head == nullptr){
            tempN->prev() = nullptr;
            head = tempN;
            return temp;
        }
        tail->next() = tempN;
        tempN->prev() = tail;
        tail = tempN;
        orderCount++;
        return temp;
    }
}

double DS::Orders::shipPendingOrders() {
    double totalPL = 0;
    for(const node * cursor = currentOrder; cursor!= nullptr; cursor = cursor->getNext()){//iterate through linked list
        Order s = cursor->getData();
        if (s.getStatusString() == "pending")
            s.shipOrder();
        totalPL += s.getOrderProfitLoss();

    }
    return totalPL;
}

size_t DS::Orders::compact() {
    size_t removed = 0;
    if(isCurrentValid()){
        for(; currentOrder != nullptr; currentOrder = currentOrder->next()) {//iterate through list
            Order s = currentOrder->getData();
            if(s.getStatusString() == "shipped" || s.size() == 0){
                deleteCurrent();
                removed++;
            }
        }
    }
    else{
        currentOrder = head;
        for(; currentOrder != nullptr; currentOrder = currentOrder->next()) {//iterate through list
            Order s = currentOrder->getData();
            if(s.getStatusString() == "shipped" || s.size() == 0){
                deleteCurrent();
                removed++;
            }
        }
    }
    orderCount -= removed;
    return removed;
}

Order* DS::Orders::previous() {
    currentOrder = currentOrder->prev();
    return getCurrent();
}

Order *DS::Orders::next() {
    currentOrder = currentOrder->next();
    return getCurrent();
}

void DS::Orders::deleteCurrent() {
    if(currentOrder == head){
        head = currentOrder->next();
        delete currentOrder;
        currentOrder = head;
    }
    else if(currentOrder == tail){
        tail  = currentOrder->prev();
        delete currentOrder;
        currentOrder = tail;
    }
    else{
        currentOrder->prev()->next() = currentOrder->next();
        currentOrder->next()->prev() = currentOrder->prev();
        auto * temp = currentOrder;
        currentOrder = currentOrder->next();
        delete temp;
    }
    orderCount--;
}

void DS::Orders::clear() {
    auto * currentTemp = head;
    while(currentTemp != nullptr){ //check to see if currentTemp is valid
        auto * temp = currentTemp->next();
        delete currentTemp;
        currentTemp = temp;
    }
    head = nullptr;
    tail = nullptr;
    currentOrder = nullptr;
    orderCount = 0;
}
