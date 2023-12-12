//
// Created by Owner on 12/12/2023.
//

#ifndef PROJECT3_NODE_BTREE_H
#define PROJECT3_NODE_BTREE_H

#include <ostream>

namespace DSBTREE {

    template <typename T>
    class node
    {
    public:

        typedef T value_type;
        node(value_type d = value_type(), node * l = nullptr, node * r = nullptr)
                : data_field(d), left_ptr(l), right_ptr(r) {}

        //Accessors/Getters
        const value_type& data() const { return data_field; }
        node const * left () const { return left_ptr; }
        node const * right () const { return right_ptr; }
        bool isLeaf() const { return left_ptr == nullptr && right_ptr == nullptr; }

        //Mutators/Setters
        void setData (const value_type& d) {data_field = d; }
        void setLeft (node * new_link) {left_ptr= new_link; }
        void setRight (node * new_link) {right_ptr = new_link; }
        //Special accessors that give us a mutable item
        value_type& data() { return data_field; }
        node*& left() { return left_ptr; }
        node*& right () { return right_ptr; }

    private:
        value_type data_field;
        node* left_ptr;
        node* right_ptr;
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& out, const node<T>* n) {
        out << n->data();
        return out;
    }

} /* namespace DSBTREE */

#endif //PROJECT3_NODE_BTREE_H
