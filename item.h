
#ifndef PROJECT3_ITEM_H
#define PROJECT3_ITEM_H
#include <string>
#include <ostream>


namespace DS {


// CLASS PROVIDED: Item (a container class for details on one item)
//
// CONSTRUCTOR for the Item class:
//Default constructor as is
//  and
//Item(size_t sku, std::string name, double cost, size_t quantity=0)
// Precondition: cost is >= 0
// Postcondition: Item is initialized with passed values
//
//
// MODIFICATION MEMBER FUNCTIONS for the Item class:
//bool pick(size_t requestQuantity)
// Precondition: Passed quantity is > 0
// Postcondition: If requested quantity is available, the items Inventory
//   will subtract the requested quantity. True will be returned in this case,
//   otherwise Inventory will remain unchanged and false returned.
//
//void receive(size_t receivedQuantity)
// Precondition: Passed quantity is > 0
// Postcondition: Adds the passed quantity to the items Inventory
//
// CONSTANT MEMBER FUNCTIONS for the Item class:
//size_t getSku() const { return sku; }
// Precondition: None
// Postcondition: Returns the item sku/upc
//
//const std::string& getName() const { return name; }
// Precondition: None
// Postcondition: Returns the inventory item name
//
//double getCost() const { return cost; }
// Precondition: None
// Postcondition: Returns the cost of the item
//
//size_t getQuantity() const { return quantity; }
// Precondition: None
// Postcondition: Returns the number of items on hand
//
// NONMEMBER FUNCTIONS for the Item class:
//std::ostream& operator<<(std::ostream& out, const Item& item_in)
// Precondition: None
// Postcondition: Outputs each field separated by comma
//
// VALUE SEMANTICS for the Item class:
//  Assignments and the copy constructor may be used with bag objects.
//
// DYNAMIC MEMORY USAGE by Item:
//  This class indirectly uses dynamic memory for string


    class Item {
    public:
        //Constructor
        Item(size_t sku, std::string name, double cost, size_t quantity=0):
                sku(sku), name(std::move(name)), cost(cost), quantity(quantity) {
        }
        //Mutators

        bool pick(size_t requestQuantity) {
            if ( requestQuantity > quantity)
                return false; //Ignore the request since we cannot satisfy it
            quantity -= requestQuantity;
            return true;
        }

        //Precondition: Passed quantity is > 0
        //Postcondition: Adds the passed quantity to the items Inventory
        void receive(size_t receivedQuantity) {
            quantity += receivedQuantity;
        }

        //Assessors
        [[nodiscard]] size_t getSku() const { return sku; }
        [[nodiscard]] const std::string& getName() const { return name; }
        [[nodiscard]] double getCost() const { return cost; }
        [[nodiscard]] size_t getQuantity() const { return quantity; }

    private:
        size_t sku;
        std::string name;
        double cost;
        size_t quantity;
    };

    inline std::ostream& operator<<(std::ostream& out, const Item& item_in) {
        out << item_in.getSku() << ", " << item_in.getName() << ", " << item_in.getCost() << ", " << item_in.getQuantity();
        return out;
    }
}

#endif //PROJECT3_ITEM_H
