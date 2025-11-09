#ifndef LISTARRAY_H
#define LISTARRAY_H

#include "List.h"
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class ListArray:public List<T>{
	private:
		T* arr; //donde apunta
		int max; //tamaño max dle array
		int n; //tamaño array
		static const int MINSIZE=2;
		void resize(int new_size){
			T* new_arr = new T[new_size];
			for (int i = 0; i < n; i++) {
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
			max = new_size;
		}
	public:
		ListArray(){
            max=MINSIZE;
			arr= new T[max];			
			n=0;
		}
		~ListArray(){
			delete[] arr;
			arr=nullptr;
		}
		T operator[](int pos){
			if(pos<0 || pos>=n){
				throw out_of_range("La posicion esta fuera de los limites");
			}
			else{
				return arr[pos];
			}
		}
		friend ostream& operator<<(ostream &out,const ListArray<T> &list){
			out<< "[";
            for(int i=0;i<list.n;i++){
                out<<list.arr[i];
                if(i<list.n-1) out<<",";            
            }
            out<<"]";
            return out;
		}
        void insert(int pos, T e) override{
            if(pos<0 || pos>n){
				throw out_of_range("La posicion esta fuera de los limites");
			}
            if(n==max){
                resize(max*2);
            }
            for(int i=n;i>pos;i--){
                arr[i]=arr[i-1];
            }          
            arr[pos]=e;
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
            T e = arr[pos];
            for(int i=pos;i<n-1;i++){
                arr[i]=arr[i+1];
            }
            n--;
			if (max > MINSIZE && n < max / 4) { 
				resize(max / 2);
			}
            return e;

        }
		T get(int pos) override{
            if(pos<0 || pos>=n){
				throw out_of_range("La posicion esta fuera de los limites");
			}
            return arr[pos];
        }
		int search(T e) override{
            for(int i=0;i<n;i++){
                if(arr[i]==e){
                    return i;
                }
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