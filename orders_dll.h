
#ifndef PROJECT3_ORDERS_DLL_H
#define PROJECT3_ORDERS_DLL_H

#include <string>
#include <ostream>
#include "inventory.h"
#include "order_bst.h"
#include "node_dll.h"

namespace DS {


    class Orders {
    public:
        typedef DSDLL::node<Order> node;
        Orders() = delete; //At the very least, need to know the shared inventory pointer
        explicit Orders(Inventory * pInventory)  : inventory(pInventory), lastOrderNumber(0), orderCount(0),
                                                   head(nullptr), tail(nullptr), currentOrder(nullptr) {}
        //Copy Constructor
        Orders(const Orders& in);

        //Destructor
        ~Orders() { clear(); }

        //Mutator Functions
        Inventory& getInventory() { return *inventory; }
        Orders& operator=(const Orders& in);

        Order * insert(const std::string& customerName);

        Order * append(const std::string& customerName);

        double shipPendingOrders();

        size_t compact();

        //Manipulating the current Order
        Order * reset() { return &(currentOrder = head)->data(); };
        Order * getCurrent() { return &currentOrder->data(); }
        Order * previous();
        Order * next();

        void deleteCurrent();

        //Assessor Functions
        [[nodiscard]] size_t size() const { return orderCount; }
        [[nodiscard]] bool isCurrentValid() const { return currentOrder != nullptr; }

    private:
        Inventory * inventory;
        size_t lastOrderNumber;
        size_t orderCount;
        node * head;
        node * tail;
        node * currentOrder;

        void clear();
    };

    inline std::ostream& operator<<(std::ostream& out, const Orders& orders_in) {
        //In Order to output we need to make a copy so that we can move the current pointer (non const)
        //Yes, this is NOT ideal, the better approach is to create an iterator, which we will not see until later
        //Note: You will want to avoid outputting Orders until all your copy and assignment operators are working
        Orders o(orders_in);
        for ( o.reset() ; o.isCurrentValid() ; o.next() ) {
            out << *o.getCurrent();
        }
        return out;
    }

} // DS


#endif //PROJECT3_ORDERS_DLL_H
