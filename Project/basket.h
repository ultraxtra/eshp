#pragma once
#include "listProduct.h"
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class basket
{
	uint32_t sumPrice;
	vector <employeee>* listBasket;
    public:
		basket() {
			sumPrice = 0;
			listBasket = new vector <employeee>();
		}
		~basket() {
			delete listBasket;
	    }
		void AddProduct(employeee&product) {
			listBasket->push_back(product);
		}
		void DelProduct(uint32_t id) {
			vector <employeee>::iterator it;
			it = listBasket->begin();
			if (!it->isEmpty()) {
				for (; it != listBasket->end(); it++) {
					if (it->getID() == id) {
						listBasket->erase(it);
					}
				}
			}
			else {
				cout << "\nList is empty!" << endl;
			}
		}
		void ShowList() {
			vector <employeee>::iterator it;
			it = listBasket->begin();
			for (; it != listBasket->end(); it++) {
				cout << *it << endl;
			}
		}
		uint32_t TotalSum(uint32_t discount) {
			vector <employeee>::iterator it;
			it = listBasket->begin();
			for (; it != listBasket->end(); it++) {
				this->sumPrice += it->getPrice();
			}
			return (this->sumPrice*(1-(discount/100)));
		}
		void SaveListInFile() {

		}

};

