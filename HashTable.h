#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "Dict.h"
#include "TableEntry.h"

// MODIFICAR RUTA SI ES NECESARIO
#include "ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;   // número de elementos almacenados
    int max; // tamaño de la tabla (nº de cubetas)
    ListLinked<TableEntry<V>>* table;  // array de listas enlazadas

    // Función hash (suma ASCII mod tamaño tabla)
    int h(std::string key) {
        int sum = 0;
        for (int i = 0; i < (int)key.size(); i++) {
            sum += int(key.at(i));
        }
        return sum % max;
    }

public:

    // Constructor
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Capacidad total de cubetas
    int capacity() {
        return max;
    }

    // Insertar par clave->valor
    void insert(std::string key, V value) override {
        int idx = h(key);
        TableEntry<V> searchKey(key);

        if (table[idx].search(searchKey) != -1) {
            throw std::runtime_error("Clave duplicada en insert()");
        }

        table[idx].append(TableEntry<V>(key, value));
        n++;
    }

    // Buscar si existe clave
    bool search(std::string key) override {
        int idx = h(key);
        TableEntry<V> searchKey(key);
        return table[idx].search(searchKey) != -1;
    }

    // Eliminar par clave->valor
    void remove(std::string key) override {
        int idx = h(key);
        TableEntry<V> searchKey(key);

        int pos = table[idx].search(searchKey);
        if (pos == -1)
            throw std::runtime_error("Clave no encontrada en remove()");

        table[idx].remove(pos);
        n--;
    }

    // Operador []: devuelve el valor asociado a key
    V operator[](std::string key) {
        int idx = h(key);
        TableEntry<V> searchKey(key);

        int pos = table[idx].search(searchKey);
        if (pos == -1)
            throw std::runtime_error("Clave no encontrada en operator[]");

        return table[idx].get(pos).value;
    }

    // Operador << para imprimir tabla
    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &ht) {
        for (int i = 0; i < ht.max; i++) {
            out << "Cubeta " << i << ": ";
            out << ht.table[i];
        }
        return out;
    }
};

#endif
