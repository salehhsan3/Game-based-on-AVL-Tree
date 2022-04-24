//
// Created by ahmad on 11/27/2021.
//

#ifndef AVL_IMP_AO_AVL_TREE_H
#define AVL_IMP_AO_AVL_TREE_H

#include "AO_Tree_node.h"


template<class Key, class Data>
class AVL_Tree{
public:
    tree_node<Key, Data>* root;
    tree_node<Key, Data>* min;
    tree_node<Key, Data>* max;
    int size;

    AVL_Tree() : root(NULL), min(NULL), max(NULL), size(0){}
    void delete_sub_tree(tree_node<Key, Data>* curr_root);
    ~AVL_Tree();
    void treeClear();
    // rotations
    tree_node<Key, Data>* LL(tree_node<Key, Data> *unbalanced_node);
    tree_node<Key, Data>* LR(tree_node<Key, Data> *unbalanced_node);
    tree_node<Key, Data>* RR(tree_node<Key, Data> *unbalanced_node);
    tree_node<Key, Data>* RL(tree_node<Key, Data> *unbalanced_node);
    tree_node<Key, Data>* addNode(Key key, Data data);
    tree_node<Key, Data>* addNodeAux(tree_node<Key, Data> *curr_root, tree_node<Key, Data> *parent, Key key, Data data, tree_node<Key, Data> *min_aux, tree_node<Key, Data> *max_aux );
    tree_node<Key, Data>* findNode(Key key);
    tree_node<Key, Data>* findNodeAux(tree_node<Key, Data>* curr_root, Key key);
    void removeNode(Key key);
    tree_node<Key, Data>* removeNodeAux(tree_node<Key, Data>* curr_root, Key key);
    void printTree() {
        tree_node<Key, Data>::printInorder(std::cout, this->root);
    }
    AVL_Tree<Key, Data>& operator=(AVL_Tree<struct player_level, int> *tree);

    tree_node<Key, Data> *copyTreeNode(tree_node<Key, Data> root);
};

template<class Key, class Data>
void AVL_Tree<Key, Data>::delete_sub_tree(tree_node<Key, Data> *curr_root) {
    if(!curr_root){
        return;
    }
    if(curr_root->left_son){
        delete_sub_tree(curr_root->left_son);
    }
    if(curr_root->right_son){
        delete_sub_tree(curr_root->right_son);
    }
    delete(curr_root);
    curr_root = nullptr;
}


template<class Key, class Data>
void AVL_Tree<Key, Data>::treeClear() {
    if(!this){
        return;
    }

    if(this->root){
        delete_sub_tree(this->root);
    }
    size = 0;
    root = nullptr;
    min = nullptr;
    max = nullptr;
}

template<class Key, class Data>
AVL_Tree<Key, Data>::~AVL_Tree() {
    treeClear();
}

template<class Key, class Data>
tree_node<Key, Data>* rightRotate(tree_node<Key, Data> *root){
    tree_node<Key, Data>* tmp1 = root->left_son;
    tree_node<Key, Data>* tmp2 = tmp1->right_son;
    root->left_son = tmp2;
    tmp1->right_son = root;
    if (tmp2 != NULL) {
        tmp2->parent = root;
    }
    tmp1->parent = root->parent;
    root->parent = tmp1;
    root->updateHeight();
    tmp1->updateHeight();
    return tmp1;
}

template<class Key, class Data>
tree_node<Key, Data>* leftRotate(tree_node<Key, Data> *root){
    tree_node<Key, Data>* tmp1 = root->right_son;
    tree_node<Key, Data>* tmp2 = tmp1->left_son;
    root->right_son = tmp2;
    tmp1->left_son = root;
    if (tmp2 != NULL) {
        tmp2->parent = root;
    }
    tmp1->parent = root->parent;
    root->parent = tmp1;
    root->updateHeight();
    tmp1->updateHeight();
    return tmp1;
}

template<class Key, class Data>
tree_node<Key, Data>* AVL_Tree<Key, Data>::LL(tree_node<Key, Data> *unbalanced_node) {
    return rightRotate(unbalanced_node);
}

template<class Key, class Data>
tree_node<Key, Data>* AVL_Tree<Key, Data>::LR(tree_node<Key, Data> *unbalanced_node) {
    unbalanced_node->left_son = leftRotate(unbalanced_node->left_son);
    return rightRotate(unbalanced_node);

}

template<class Key, class Data>
tree_node<Key, Data>* AVL_Tree<Key, Data>::RR(tree_node<Key, Data> *unbalanced_node) {
    return leftRotate(unbalanced_node);
}

template<class Key, class Data>
tree_node<Key, Data>* AVL_Tree<Key, Data>::RL(tree_node<Key, Data> *unbalanced_node) {
    unbalanced_node->right_son = rightRotate(unbalanced_node->right_son);
    return leftRotate(unbalanced_node);
}

template<class Key, class Data>
tree_node<Key, Data>* AVL_Tree<Key, Data>::addNode(Key key, Data data) {
    if(findNode(key)){
        return NULL;
    }
    if (this->root == NULL){
        root = new tree_node<Key, Data>(key, data, NULL, NULL, NULL, 0);
        min = root;
        max = root;
        size++;
        return root;
    }
    root = addNodeAux(root, nullptr, key, data, min, max);
    return root;
}

template<class Key, class Data>
tree_node<Key, Data>* AVL_Tree<Key, Data>::addNodeAux(tree_node<Key, Data> *curr_root, tree_node<Key, Data> *parent, Key key,
                                                      Data data, tree_node<Key, Data>* min_aux, tree_node<Key, Data>* max_aux) {
    if (curr_root == NULL) {
        curr_root = new tree_node<Key, Data>(key, data, parent, NULL, NULL, 0);
        size++;
            if (*this->min->key > key) {
                this->min = curr_root;
            }
            if (*this->max->key < key) {
                this->max = curr_root;
            }
        return curr_root;
        }
    if (key > *curr_root->key) {
        curr_root->right_son = addNodeAux(curr_root->right_son, curr_root, key, data, min_aux, max_aux);
    } else {
        curr_root->left_son = addNodeAux(curr_root->left_son, curr_root, key, data, min_aux, max_aux);
    }
    curr_root->updateHeight();
    int BF = curr_root->getBalance();
    //left left
    if (BF > 1 && key < *curr_root->left_son->key) {
        return LL(curr_root);
    }
    //right right
    if (BF < -1 && key > *curr_root->right_son->key) {
        return RR(curr_root);
    }
    // left right
    if (BF > 1 && key > *curr_root->left_son->key) {
        return LR(curr_root);
    }
    //right left
    if (BF < -1 && key < *curr_root->right_son->key) {
        return RL(curr_root);
    }
    return curr_root;
}

template<class Key, class Data>
tree_node<Key, Data>* AVL_Tree<Key, Data>::findNode(Key key) {
    return findNodeAux(this->root, key);
}

template<class Key, class Data>
tree_node<Key, Data>* AVL_Tree<Key, Data>::findNodeAux(tree_node<Key, Data> *curr_root, Key key) {
    if (curr_root == nullptr){
        return nullptr;
    }
    if (key == *curr_root->key){
        return curr_root;
    } else if (key > *curr_root->key){
       return findNodeAux(curr_root->right_son, key);
    } else if (key < *curr_root->key){
        return findNodeAux(curr_root->left_son, key);
    }
    //shouldnt get here
    return nullptr;
}

template<class Key, class Data>
void AVL_Tree<Key, Data>::removeNode(Key key) {
    if (!this || !findNode(key)){
        return;
    }
    root = removeNodeAux(root, key);
    size--;
    // update MIN and MAX
    if(root){
        min = root->findMin();
        max = root->findMax();
    } else{
        min = nullptr;
        max = nullptr;
    }
}
template<class Key, class Data>
tree_node<Key, Data>* AVL_Tree<Key, Data>::removeNodeAux(tree_node<Key, Data> *curr_root, Key key) {
    if (key < *curr_root->key) {
        curr_root->left_son = removeNodeAux(curr_root->left_son, key);
    } else if (key > *curr_root->key) {
        curr_root->right_son = removeNodeAux(curr_root->right_son, key);
    } else{
        //now curr_root is the node to be removed
        tree_node<Key, Data> *son;
        if(!curr_root->left_son || !curr_root->right_son) {
            son = curr_root->left_son ? curr_root->left_son : curr_root->right_son;
            /// Did not have childs
            if (son == NULL) {
                delete (curr_root);
                return NULL;
            } else { /// have one child
                son->parent = curr_root->parent;
                delete (curr_root);
                return son;
            }
        }
        else {/// if curr_root has two children
            tree_node<Key, Data> *tmp = curr_root->getMin();
            delete curr_root->key;
            delete curr_root->data;
            curr_root->key = new Key(*tmp->key);
            curr_root->data = tmp->data;
            tmp->data = nullptr;
            curr_root->right_son = removeNodeAux(curr_root->right_son, *tmp->key);
        }
    }
    curr_root->updateHeight();
    int BF = curr_root->getBalance();
    //left left
    if (BF > 1 && curr_root->left_son->getBalance() >= 0) {
        return LL(curr_root);
    }
    //right right
    if (BF < -1 && curr_root->right_son->getBalance() <= 0) {
        return RR(curr_root);
    }
    // left right
    if (BF > 1 && curr_root->left_son->getBalance() < 0) {
        return LR(curr_root);
    }
    //right left
    if (BF < -1 && curr_root->right_son->getBalance() > 0) {
        return RL(curr_root);
    }
    return curr_root;
}

template<class Key, class Data>
AVL_Tree<Key, Data>& AVL_Tree<Key, Data>::operator=(AVL_Tree<struct player_level, int> *tree) {
    treeClear();
    root = tree->root;
    size = tree->size;
    min = tree->min;
    max = tree->max;
    return *this;
}

template<class Key, class Data>
tree_node<Key, Data>* AVL_Tree<Key, Data>::copyTreeNode(tree_node<Key, Data> root) {
    if(root == NULL){
        return NULL;
    }
    tree_node<Key, Data>* left = copyTreeNode(root->left);
    tree_node<Key, Data>* right = copyTreeNode(root->right);

    tree_node<Key, Data>* new_node(new tree_node<Key, Data>(*root.key, *root.data, root.parent, root.left_son, root.right_son, root.height));
    return new_node;
}




#endif //AVL_IMP_AO_AVL_TREE_H
