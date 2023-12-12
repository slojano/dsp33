//
// Created by Owner on 12/12/2023.
//

#ifndef PROJECT3_WAREHOUSE_H
#define PROJECT3_WAREHOUSE_H

#include <ostream>
#include <iomanip>
#include "inventory.h"
#if PROJECT_VERSION>=2
#include "orders_dll.h"
#else
#include "orders.h"
#include "orders_dll.h"

#endif

namespace DS {

// CLASS PROVIDED: Warehouse (a container class for a collection of items)
//
// Basically a wrapper class that contains both an inventory, orders (pending and shipped), and
// maintains the balance sheet of the warehouse.
//
// CONSTRUCTOR for the Warehouse class:
//Warehouse(double initialInvestment=0);
// Precondition: If initialInvestment is provided, it is greater than zero
// Postcondition: Each Item is sent to out with a tab separating each Item
//Default and value contructor. The passed value sets the initial cash on hand, inventory inits to empty
//
// MODIFICATION MEMBER FUNCTIONS for the Warehouse class:
//void inventoryAdd(size_t item_sku, const std::string& item_name, double cost, size_t quantity= 0)
// Precondition: cost >= 0
// Postcondition: Adds the passed item to inventory, if the sku already exists, it it replaced
//
//Order * ordersAppend(const std::string& customerName)
// Precondition: See Orders::append
// Postcondition: Passes the passed string to the orders objects append member function
//
//Order * ordersInsert(const std::string& customerName)
// Precondition: See Orders::insert
// Postcondition: Passes the passed string to the orders objects insert member function
//
//double ordersShip()
// Precondition: See Orders::shipPendingOrders()
// Postcondition: Receives the output from the orders objects shipPendingOrders and updates cash on hand with the value
//     returned.
//
//void ordersCompact()
// Precondition: See Orders::compact()
// Postcondition: Calls the compact member function on the orders object
//
//Order * ordersReset()
// Precondition: See Orders::reset
// Postcondition: Returns the result of the reset member function on the orders object
//
//Order * ordersGetCurrent()
// Precondition: See Orders::getCurrent
// Postcondition: Returns the result of the getCurrent member function on the orders object
//
//Order * ordersPrevious()
// Precondition: See Orders::previous
// Postcondition: Returns the result of the previous member function on the orders object
//
//Order * ordersNext()
// Precondition: See Orders::next();
// Postcondition: Returns the result of the next member function on the orders object
//
//void deleteOrder()
// Precondition: See Orders::deleteCurrent;
// Postcondition: Returns the result of the deleteCurrent member function on the orders object
//
// CONSTANT MEMBER FUNCTIONS for the Warehouse class:
//const Inventory& getInventory() const
// Precondition: None
// Postcondition: Returns a reference to the inventory object
//
//const Orders& getOrders() const
// Precondition: None
// Postcondition: Returns a reference to the orders object
//
//double getCash() const
// Precondition: None
// Postcondition: Returns the cash on hand
//
//bool ordersIsCurrentValid() const
// Precondition: See Orders::isCurrentValid();
// Postcondition: Returns the result of the isCurrentValid member function on the orders object
//
// NONMEMBER FUNCTIONS for the Warehouse class:
//   std::ostream& operator<<(std::ostream& out, const Warehouse& warehouse)
//   Precondition: None
//   Postcondition: Sends the inventory and orders to out as well as text to give detailed output
//
// VALUE SEMANTICS for the Warehouse class:
//   Assignments and the copy constructor may be used with bag objects.
//
// DYNAMIC MEMORY USAGE by Warehouse:
//   This class indirectly uses dynamic memory

    class Warehouse {
    public:
        Warehouse(double initialInvestment=0) : cash(initialInvestment), orders(&inventory) {}; // NOLINT(*-explicit-constructor)

        void inventoryAdd(size_t item_sku, const std::string& item_name, double cost, size_t quantity= 0) {
            inventory.add(item_sku, item_name, cost, quantity);
            cash -= cost * static_cast<double>(quantity);
        }

        Order * ordersAppend(const std::string& customerName) {
            return orders.append(customerName);
        }

        Order * ordersInsert(const std::string& customerName) {
            return orders.insert(customerName);
        }

        double ordersShip() {
            double profit = orders.shipPendingOrders();
            cash += profit;
            return profit;
        }

        void ordersCompact() {
            orders.compact();
        }

        //Manipulating the current Order
        Order * ordersReset() { return orders.reset(); }
        Order * ordersGetCurrent()  { return orders.getCurrent(); }
        Order * ordersPrevious()  { return orders.previous(); }
        Order * ordersNext()  { return orders.next(); }
        void deleteOrder()  { return orders.deleteCurrent(); }

        //Assessors
        [[nodiscard]] const Inventory& getInventory() const { return inventory; }
        [[nodiscard]] const Orders& getOrders() const { return orders; }
        [[nodiscard]] double getCash() const { return cash; }
        [[nodiscard]] bool ordersIsCurrentValid() const { return orders.isCurrentValid(); }

    private:
        double cash; //How much money the warehouse has, minus costs for purchasing things, plus shipped orders
        Orders orders; //Orders currently open
        Inventory inventory; //All items available in the warehouse, along with their associated wholesale cost
    };

    inline std::ostream& operator<<(std::ostream& out, const Warehouse& warehouse) {
        out << "Inventory:" << std::endl
            << warehouse.getInventory()
            << "Orders:" << std::endl
            << warehouse.getOrders()
            << "Cash On Hand:" << std::endl
            << "\t$" << std::fixed << std::setprecision(2) << warehouse.getCash();
        return out;
    }

} // DS

#endif //PROJECT3_WAREHOUSE_H
