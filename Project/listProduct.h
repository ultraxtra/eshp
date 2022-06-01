#pragma once
#include <iostream>
#include <map>
#include "File.h"

using namespace std;

class employeee {
	string  positionName;
	uint32_t price;
	uint32_t id;
	string isAvailable;
public:
	employeee(string  positionName, uint32_t price, uint32_t id, string isAvailable) {
		this->positionName = positionName;
		this->price = price;
		this->id = id;
		this->isAvailable = isAvailable;
	}
	bool isEmpty() {
		return((this->positionName == ""&& this->id==0&&this->isAvailable==""&&this->price==0) ? true : false);
	}
	employeee() :employeee("",0, 0,"") {};
	~employeee() {
		this->positionName.clear();
	}
	void setPrice(uint32_t price) { this->price = price; }
	void setPositionName(string  positionName) { this->positionName = positionName; }
	void setAvailadl(string availbale) { this->isAvailable = availbale; }
	string getAvailbl() { return this->isAvailable; }
	string getPositionName() { return this->positionName; }
	uint32_t getPrice() { return this->price; }
	uint32_t getID() { return this->id; }
	friend ostream& operator <<(ostream& stream, employeee& prod) {
		stream << prod.id << " " << prod.positionName << " " << prod.price << " " << prod.isAvailable 
			<< endl;
		return stream;
	}
};


class listProduct
{
	map <uint32_t, employeee>* listProd;
public:
	listProduct() {
		listProd = new map <uint32_t, employeee>();
	}
	~listProduct() {
		delete listProd;
	}
	void AddProduct(string  positionName, uint32_t price, uint32_t id, string available) {
		employeee Product(positionName, price, id, available);
		pair<uint32_t, employeee> prod(id, Product);
		listProd->insert(prod);
	}
	void ReadyProd() {
		const int N = 5;
		employeee p1("Sumsung p150", 15000, 1, "stock");
		employeee p2("Redmi", 12000, 2, "stock");
		employeee p3("Apple", 100000, 3, "stock");
		employeee p4("Macbook", 40000, 4, "stock");
		employeee p5("HP", 1000, 5, "stock");
		pair<uint32_t, employeee> prod[N] = {
			{1,p1},
			{2,p2},
			{3,p3},
			{4,p4},
			{5,p5},
		};
		for (size_t i = 0; i < N; i++) {
			listProd->insert(prod[i]);
		}
	}
	employeee* getProduct(uint32_t id) {
		auto item = this->listProd->find(id);
		employeee* tmp = &item->second;
		if (!tmp->isEmpty()) {
			return tmp;
		}
		else
		{
			return nullptr;
		}
	}
	void DelProd(uint32_t id) {
		map <uint32_t, employeee>::iterator it;
		it = listProd->find(id);
		if (!(it->second.isEmpty())){
			listProd->erase(id);
		}
		else {
			cout << "\nValue is not found!" << endl;
		}
	}
	void PrintList() {
		auto item = listProd->begin();
		if (!listProd->empty()) {
			for (; item != listProd->end(); item++) {
				cout << item->first << ": " << item->second << endl;
			}
		}
		else {
			cout << "\nList is empty" << endl;
		}
	}
	void ChangeStock(uint32_t id,string stock) {
		auto item = listProd->find(id);
		item->second.getAvailbl().clear();
		item->second.setAvailadl(stock);
	}
	void Inventory()
	{
		uint32_t valueStock;
		string stock;
		char y;
		map <uint32_t, employeee>::iterator it;
		it = listProd->begin();
		while (true) {
			system("cls");
			for (; it != listProd->end(); it++) {
				if (it->second.getAvailbl() == "not in stock") {
					cout << it->second << endl;
				}
				cout << "\n Input id for changes value of the stock: ";
			}
			cin >> valueStock;
			cout << "\n Input the value of the stock: ";
			cin >> stock;
			this->ChangeStock(valueStock, stock);
			cout << "\nDo you want to continue? (y/n): ";
			cin >> y;
			if (y == 'n') {
				return;
			}
		}
	}
	void SaveListInFile() {
		File<map < uint32_t, employeee>>* p = new File<map < uint32_t, employeee>>("", "File.bin");
		map < uint32_t, employeee >* tmp = this->listProd;
		p->Save(tmp);
	}

};

