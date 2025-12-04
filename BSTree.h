#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {

private:
    int nelem;
    BSNode<T>* root;

    // Búsqueda recursiva
    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr)
            throw std::runtime_error("Elemento no encontrado");

        if (e == n->elem)
            return n;
        else if (e < n->elem)
            return search(n->left, e);
        else
            return search(n->right, e);
    }

    // Inserción recursiva
    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);
        }

        if (e == n->elem)
            throw std::runtime_error("Elemento duplicado en insert()");
        else if (e < n->elem)
            n->left = insert(n->left, e);
        else
            n->right = insert(n->right, e);

        return n;
    }

    // Recorrido inorden recursivo
    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (n == nullptr) return;
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }

    // Máximo del subárbol
    T max(BSNode<T>* n) const {
        if (n->right == nullptr)
            return n->elem;
        return max(n->right);
    }

    // Elimina el máximo del subárbol
    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* leftChild = n->left;
            delete n;
            return leftChild;
        }
        n->right = remove_max(n->right);
        return n;
    }

    // Eliminación recursiva
    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr)
            throw std::runtime_error("Elemento no encontrado en remove()");

        if (e < n->elem) {
            n->left = remove(n->left, e);
        }
        else if (e > n->elem) {
            n->right = remove(n->right, e);
        }
        else { // Encontrado
            if (n->left == nullptr && n->right == nullptr) {
                delete n;
                nelem--;
                return nullptr;
            }
            else if (n->left == nullptr) {
                BSNode<T>* rightChild = n->right;
                delete n;
                nelem--;
                return rightChild;
            }
            else if (n->right == nullptr) {
                BSNode<T>* leftChild = n->left;
                delete n;
                nelem--;
                return leftChild;
            }
            else {
                // Nodo con dos hijos --> reemplazo por máximo del subárbol izquierdo
                T m = max(n->left);
                n->elem = m;
                n->left = remove_max(n->left);
                nelem--;
            }
        }

        return n;
    }

    // Destructor recursivo
    void delete_cascade(BSNode<T>* n) {
        if (n == nullptr) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:

    BSTree() : nelem(0), root(nullptr) {}

    int size() const {
        return nelem;
    }

    // Búsqueda externa
    T search(T e) const {
        BSNode<T>* result = search(root, e);
        return result->elem;
    }

    // Operador [] → busca elemento
    T operator[](T e) const {
        return search(e);
    }

    // Inserción externa
    void insert(T e) {
        root = insert(root, e);
    }

    // Eliminación externa
    void remove(T e) {
        root = remove(root, e);
    }

    // Operador << (recorrido inorden)
    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }

    // Destructor
    ~BSTree() {
        delete_cascade(root);
    }
};

#endif
