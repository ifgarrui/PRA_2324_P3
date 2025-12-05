#ifndef DICT_H
#define DICT_H
#include <string>
#include <stdexcept> // Para std::runtime_error

template <typename V> 
class Dict {
    public:
        // Inserta el par clave->valor en el diccionario
        // Lanza std::runtime_error si la clave ya existe
        virtual void insert(std::string key, V value) = 0;

        // Busca el valor asociado a la clave
        // Lanza std::runtime_error si la clave no existe
        virtual V search(std::string key) = 0;

        // Elimina el par clave->valor del diccionario
        // Lanza std::runtime_error si la clave no existe
        virtual V remove(std::string key) = 0;

        // Devuelve el número de elementos en el diccionario
        virtual int entries() = 0;

        // Destructor virtual
        virtual ~Dict() {}
};

#endif
