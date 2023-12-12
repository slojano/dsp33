//
// Created by Owner on 12/12/2023.
//

#ifndef PROJECT3_ORDER_BST_H
#define PROJECT3_ORDER_BST_H


#include <string>
#include <iomanip>
#include <ostream>
#include <utility>
#include "inventory.h"
#include "node_btree.h"

namespace DS {

    enum Status {
        empty, //Special Status that should only be used before object is initialized
        pending, //Order has not been fulfilled yet
        shipped //Order was fulfilled, warehouse had Inventory to satisfy Order
    };

    //This struct holds an order.
    //The price here is what the customer is paying for each item
    //The profit is price minus cost
    struct ItemOrdered {
        size_t sku;
        size_t orderedQuantity;
        double price;
        bool operator==(const ItemOrdered& rhs) const { return sku == rhs.sku && orderedQuantity == rhs.orderedQuantity && price == rhs.price; }
        bool operator!=(const ItemOrdered& rhs) const { return !(rhs == *this); }
        bool operator<(const ItemOrdered& rhs) const { return sku == rhs.sku ? (orderedQuantity == rhs.orderedQuantity ? price < rhs.price : orderedQuantity < rhs.orderedQuantity) : sku < rhs.sku; }
        bool operator<=(const ItemOrdered& rhs) const { return *this == rhs || *this < rhs; }
    };

    class Order {
    public:
        typedef DSBTREE::node<ItemOrdered> node;
        Order() : inventory(nullptr), orderNumber(0), customerName(), orderStatus(empty), items(nullptr), itemCount(0) {}
        explicit Order(Inventory * inventory) : inventory(inventory), orderNumber(0), customerName(), orderStatus(empty), items(nullptr), itemCount(0) {}
        Order(Inventory * inventory, size_t orderNumber, std::string customerName) : inventory(inventory),
                                                                                     orderNumber(orderNumber), customerName(std::move(customerName)), orderStatus(pending), items(nullptr), itemCount(0) {
        }

        Order(const Order& in);

        ~Order() { clearItems(); }

        //Mutators

        Order& operator=(const Order& in);

        void addItem(size_t sku, size_t quantity, double price);

        bool shipOrder();

        void clearItems() { clearItems(items); itemCount = 0; items = nullptr; };

        //Assessor functions
        [[nodiscard]] size_t size() const { return itemCount; }
        [[nodiscard]] const std::string& getCustomerName() const { return customerName; }
        [[nodiscard]] size_t getOrderNumber() const { return orderNumber; }
        [[nodiscard]] Status getStatus() const { return orderStatus; }
        [[nodiscard]] const Inventory * getInventory() const { return inventory; }
        [[nodiscard]] std::string getStatusString() const { return (orderStatus == Status::shipped ? "shipped" : orderStatus == Status::pending ? "pending" : "!INVALID!"); }
        [[nodiscard]] double getOrderProfitLoss() const;
        double outputItems(std::ostream &os) const { return outputItems(os, items); };

    private:
        Inventory * inventory;
        size_t orderNumber;
        std::string customerName;
        Status orderStatus;
        node* items; //Root pointer to a Binary search tree
        size_t itemCount;

        [[nodiscard]] double getItemProfitLoss(const ItemOrdered& item) const;

        void addItem(const ItemOrdered& item, node* root_ptr);

        void clearItems(node * root_ptr);

        node* tree_copy(const node* root_ptr);

        double outputItem(std::ostream& out, const ItemOrdered& item) const;
        double outputItems(std::ostream &os, node* root_ptr) const;

        bool shipOrder(node* root_ptr);
        [[nodiscard]] double getOrderProfitLoss(node* root_ptr) const;

    };

    inline std::ostream& operator<<(std::ostream& out, const Order& order) {
        //order.toStream(out);
        out << "\t[" << order.getOrderNumber() << "] " << order.getCustomerName() << std::endl
            << "\t\tStatus: " << order.getStatusString()
            << ", Item count: " << order.size() << std::endl;
        double order_profit = 0;
        if ( order.size() > 0 ) {
            out << "\t\tItems:" << std::endl << "\t\t\tCount\tProfit\t\tName" << std::endl;
            order_profit += order.outputItems(out);
        }
        out << "\t\tProfit: $" << order_profit << std::endl;
        return out;
    }

}


#endif //PROJECT3_ORDER_BST_H
