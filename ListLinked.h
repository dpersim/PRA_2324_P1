#ifndef LISTLINKED_H
#define LISTLINKED_H

#include "List.h"
#include "Node.h"

using namespace std;

template <typename T>

class ListLinked: public List<T>{
    private:
        Node<T>* first; //puntero al primer nodo
        int n;  //numero de elementos que contiene la lista
    public:
        ListLinked():n(0),first(nullptr){}
        ~ListLinked(){
            while (first != nullptr) {
                Node<T>* aux = first->next;
                delete first;
                first = aux;
            }
            n = 0;
            
        }
        T operator[](int pos){
            if(pos<0 || pos>n){
                throw out_of_range("La posicion esta fuera de los limites");
            }
            for(int i=0;i<pos;i++){
                Node<T>* aux=first->next;
                first->next=aux->next;
            }
            return first->data;
        }
        friend ostream& operator<<(ostream &out, const ListLinked<T> &list){
            Node<T>* aux=list.first;
            out<<"[";
            for(int i=0;i<list.n;i++){
                out<<aux->data;
                if(i<list.n-1){
                    out<<",";
                }
                aux=aux->next;
            }
            out<<"]";
            return out;
        }

        //Heredados de List
        void insert(int pos, T e) override{
            if(pos<0 || pos>n){
				throw out_of_range("La posicion esta fuera de los limites");
			}
            if(pos == 0){
                first = new Node<T>(e, first);
            }
            else {
                Node<T>* aux = first;
                for(int i = 0; i < pos - 1; i++){
                    aux = aux->next;
                }
                aux->next = new Node<T>(e, aux->next);
            }
            n++;
        }
		void append(T e) override{
            insert(n,e);
        }
		void prepend(T e) override{
            insert(0,e);
        }
		T remove(int pos) override{
            if(pos<0 || pos>=n){
				throw out_of_range("La posicion esta fuera de los limites");
			}
            T removedData;
            Node<T>* nodeToDelete;
            
            if(pos == 0){
                nodeToDelete = first;
                first = first->next;
                removedData = nodeToDelete->data;
            } else {
                Node<T>* aux = first;
                for(int i = 0; i < pos - 1; i++){
                    aux = aux->next;
                }
                nodeToDelete = aux->next;
                aux->next = nodeToDelete->next;
                removedData = nodeToDelete->data;
            }
            
            delete nodeToDelete;
            n--;
            return removedData;

        }
		T get(int pos) override{
            if(pos<0 || pos>=n){
				throw out_of_range("La posicion esta fuera de los limites");
			}
            Node<T>* aux = first;
            for(int i = 0; i < pos; i++){
                aux = aux->next;
            }
            return aux->data;
        }
		int search(T e) override{
            Node<T>* aux = first;
            for(int i = 0; i < n; i++){
                    if(aux->data==e){
                        return i;
                    }
                    aux = aux->next;
                }
            return -1;
        }
		bool empty() override{
            if(n==0){
                return true;
            }
            return false;
        }
		int size() override{
            return n;
        }
};

#endif