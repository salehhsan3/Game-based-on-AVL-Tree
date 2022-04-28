//
// Created by ahmad on 11/27/2021.
//

#ifndef AVL_IMP_AO_TREE_NODE_H
#define AVL_IMP_AO_TREE_NODE_H

#include <stdlib.h>
#include <iostream>

#define MAX(a,b) ((a)>(b)?(a):(b))

template<class Key, class Data>
class tree_node{
public:
    // fields
    Key *key;
    Data *data;
    tree_node<Key, Data> *parent;
    tree_node<Key, Data> *left_son;
    tree_node<Key, Data> *right_son;
    int height;
    int sons_num;
//    int sum;
//    int sons_sum;

    //methods
    tree_node(Key key, Data data, tree_node *parent, tree_node *left_son, tree_node *right_son, int height = 0,
              int sons_num = 1/*, int sum = 0, int sons_sum = 0*/):
    key(new Key(key)), data(new Data(data)), parent(parent), left_son(left_son), right_son(right_son), height(height)
    , sons_num(sons_num)/*, sum(sum), sons_sum(sons_sum)*/{}

    ~tree_node();

    void setData(Data* new_data);

    bool operator==(const tree_node &node_to_cmp) const;

    bool operator!=(const tree_node &node_to_cmp) const;

    bool operator<(const tree_node &node_to_cmp) const;

    bool operator<=(const tree_node &node_to_cmp) const;

    bool operator>(const tree_node &node_to_cmp) const;

    bool operator>=(const tree_node &node_to_cmp) const;

   //tree_node<Key, Data>& operator=(tree_node<Key,Data> *tree_node);

    void updateHeight();

    void updateNum();

//    void updateSum();

    int getBalance();

    static void printInorder(std::ostream &out, tree_node *node);

    tree_node<Key, Data> *getMin();

    tree_node<Key, Data> *findMin();

    tree_node<Key, Data> *findMax();



};

//methods implementation


template<class Key, class Data>
tree_node<Key, Data>::~tree_node<Key, Data>() {
    delete key;
    delete data;
    left_son = nullptr;
    right_son = nullptr;
    parent = nullptr;
}

template<class Key, class Data>
void tree_node<Key, Data>::setData(Data *new_data) {
    delete data;
    data = new_data;
}

template<class Key, class Data>
bool tree_node<Key, Data>::operator==(const tree_node<Key, Data> &node_to_cmp) const {
    return *this->key == *node_to_cmp.key;
}

template<class Key, class Data>
bool tree_node<Key, Data>::operator!=(const tree_node<Key, Data> &node_to_cmp) const {
    return *this->key != *node_to_cmp.key;
}

template<class Key, class Data>
bool tree_node<Key, Data>::operator>(const tree_node<Key, Data> &node_to_cmp) const {
    return *this->key > *node_to_cmp.key;
}

template<class Key, class Data>
bool tree_node<Key, Data>::operator>=(const tree_node<Key, Data> &node_to_cmp) const {
    return *this->key >= *node_to_cmp.key;
}

template<class Key, class Data>
bool tree_node<Key, Data>::operator<(const tree_node<Key, Data> &node_to_cmp) const {
    return *this->key < *node_to_cmp.key;
}

template<class Key, class Data>
bool tree_node<Key, Data>::operator<=(const tree_node<Key, Data> &node_to_cmp) const {
    return *this->key <= *node_to_cmp.key;
}
/*
template<class Key, class Data>
tree_node<Key, Data>& tree_node<Key,Data>::operator=(tree_node<Key, Data> *tree_node) {
    if(!this){
        delete this;
    }
    key = tree_node->key;
    data = tree_node->data;
}
*/
template<class Key, class Data>
void tree_node<Key, Data>::updateHeight() {
    if (this->left_son == nullptr && this->right_son == nullptr) {
        this->height = 0;
        return;
    }
    if (this->left_son == nullptr) {
        this->height = this->right_son->height + 1;
    } else if (this->right_son == nullptr) {
        this->height = this->left_son->height + 1;
    } else {
        this->height = MAX(this->left_son->height, this->right_son->height) + 1;
    }
}

template<class Key, class Data>
void tree_node<Key, Data>::updateNum() {
    if (this->left_son == nullptr && this->right_son == nullptr) {
        this->sons_num = 1;
        return;
    }
    if (this->left_son == nullptr) {
        this->sons_num = this->right_son->sons_num + 1;
    } else if (this->right_son == nullptr) {
        this->sons_num = this->left_son->sons_num + 1;
    } else {
        this->sons_num = this->right_son->sons_num + this->left_son->sons_num + 1;
    }
}

//template<class Key, class Data>
//void tree_node<Key, Data>::updateSum() {
//    if (this->left_son == nullptr && this->right_son == nullptr) {
//        this->sons_sum = sum;
//        return;
//    }
//    if (this->left_son == nullptr) {
//        this->sons_sum = this->right_son->sons_sum + sum;
//    } else if (this->right_son == nullptr) {
//        this->sons_sum = this->left_son->sons_sum + sum;
//    } else {
//        this->sons_sum = this->right_son->sons_sum + this->left_son->sons_sum + sum;
//    }
//}


template<class Key, class Data>
int tree_node<Key, Data>::getBalance() {
    if (this == nullptr) {
        return 0;
    } else if (this->left_son == nullptr) {
        if (this->right_son == nullptr) {
            return 0;
        }
        return -1 -(this->right_son->height); //needs to be checked********************
    } else if (this->right_son == NULL) {
        return (this->left_son->height) + 1;
    }
    return this->left_son->height - this->right_son->height;
}

template<class Key, class Data>
void tree_node<Key, Data>::printInorder(std::ostream &out, tree_node<Key, Data> *node) {
    if(node == NULL){
        return;
    }
    printInorder(out, node->left_son);
    std::cout <<  *node->key << " -> ";
    printInorder(out, node->right_son);
}

template<class Key, class Data>
tree_node<Key, Data>* tree_node<Key, Data>::getMin() {
    tree_node<Key, Data>* tmp = this->right_son;
    while (tmp->left_son){
        tmp = tmp->left_son;
    }
    return tmp;
}

template<class Key, class Data>
tree_node<Key, Data>* tree_node<Key, Data>::findMin() {
    tree_node<Key, Data>* tmp = this;
    if(!tmp){
        return nullptr;
    }
    while (tmp->left_son){
        tmp = tmp->left_son;
    }
    return tmp;
}

template<class Key, class Data>
tree_node<Key, Data>* tree_node<Key, Data>::findMax() {
    tree_node<Key, Data>* tmp = this;
    if(!tmp){
        return nullptr;
    }
    while (tmp->right_son){
        tmp = tmp->right_son;
    }
    return tmp;
}



#endif //AVL_IMP_AO_TREE_NODE_H
