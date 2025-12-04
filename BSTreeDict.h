#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

private:
    BSTree<TableEntry<V>>* tree;

public:
    // Constructor: crea un ABB vacío en memoria dinámica
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    // Destructor: libera memoria del ABB
    ~BSTreeDict() {
        delete tree;
    }

    // Insertar par clave->valor (lanza std::runtime_error si ya existe)
    void insert(std::string key, V value) override {
        TableEntry<V> te(key, value);
        tree->insert(te);
    }

    // Buscar existencia de clave. Devuelve true si existe, false si no.
    bool search(std::string key) override {
        try {
            TableEntry<V> probe(key);
            tree->search(probe); // lanza si no existe
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }

    // Eliminar entrada por clave (lanza si no existe)
    void remove(std::string key) override {
        TableEntry<V> probe(key);
        tree->remove(probe);
    }

    // Operador []: devuelve el valor asociado a key o lanza std::runtime_error
    V operator[](std::string key) override {
        TableEntry<V> probe(key);
        TableEntry<V> found = tree->search(probe); // lanza si no existe
        return found.value;
    }

    // Imprimir contenido (delegamos en el operador << de BSTree)
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bd) {
        out << *(bd.tree);
        return out;
    }
};

#endif
