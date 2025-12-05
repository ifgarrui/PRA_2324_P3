#include <ostream>
#include "List.h"
#include "Node.h"
using namespace std;

template <typename T>
class ListLinked : public List<T>
{

private:
	Node<T> *first;
	int n;

public:
	ListLinked() override
	{
		first = nullptr;
		n = 0;
	}
	~ListLinked() override
	{
		for (int i = 0; i < n; i++)
		{
			Node<T> *aux = first->next;
			delete first;
			first = aux;
		}
	}
	T operator[](int pos) override
	{
		if (pos < 0 || pos > n)
		{
			throw out_of_range("La posicion esta fuera del rango");
		}
		Node<T> *current = first;
		for (int i = 0; i < pos; i++)
		{
			current = current->next;
		}
		return current->data;
	}
	friend ostream &operator<<(ostream &out, const ListLinked<T> &list) override
	{
		out << list->first->data;
		return out;
	}
	void insert(int pos, T e) override{
		if(pos < 0 || pos > n) throw std::out_of_range("Posición fuera del rango de la array");
		if(pos == 0){
			Node<T>* aux = new Node<T>(e,first); 
			first = aux;
			n++;
		}
		else{
			Node<T>* prev = nullptr;
			Node<T>* aux = first;
			int i = 0;
			while(aux != nullptr && i < pos){
				prev = aux;
				aux = aux -> next;
				i++;
			}
			if(i == pos){
				prev->next = new Node<T>(e,aux); 
				n++;
			}	
		}
	}
	void append(T e) override
	{
		insert(n, e);
	}
	void prepend(T e) override
	{
		insert(0, e);
	}
	T remove(int pos) override
	{
		if (pos < 0 || pos >= n)
		{
			throw std::out_of_range("Posición fuera de rango");
		}
		T removed_value = arr[pos];
		for (int i = pos; i < n - 1; ++i)
		{
			arr[i] = arr[i + 1];
		}
		--n;
		if (n < max / 4 && max > MINSIZE)
		{
			resize(max / 2);
		}
		return removed_value;
	}
	T get(int pos) override{
		if(pos < 0 || pos >= n) throw std::out_of_range("Posición fuera del rango de la array");
		Node<T>* aux = first;
		for(int i= 0; i < pos; i++) aux = aux->next;
		return aux->data;
	}
	int search(T e) override {
        Node<T>* aux = first;
		int i = 0;
		while(aux != nullptr && aux-> data != e){
			aux = aux-> next;
			i++;
		}
		if(aux != nullptr){ 
			return i;
		}else{ 
			return -1;
        }
	}
	bool empty() override
	{
		return n == 0;
	}
	int size() override
	{
		return n;
	}
};
