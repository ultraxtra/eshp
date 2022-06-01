#pragma once
#include <iostream>
#include "listProduct.h"
#include "basket.h"

using namespace std;

class Employee
{
protected:
	string name;
	string surname;
	string rang;
	string password;
	uint32_t discount;
	basket* Basket;
	listProduct* listOfproduct;
	
  public:
	  Employee(string name, string surname, string rang, string password) {
		  this->name = name;
		  this->password = password;
		  this->rang = rang;
		  this->surname = surname;
		  this->discount = 10;
		  this->Basket = new basket();
		  this->listOfproduct = new listProduct();
	  }
	  Employee() :Employee("", "", "", "") {};
	  ~Employee() {
		  this->name.clear();
		  this->password.clear();
		  this->rang.clear();
		  this->surname.clear();
		  delete this->listOfproduct;
		  delete this->Basket;
	  }
	  void Print() {
		  cout << "\nName: " << this->name << " " <<"Surname: "<<this->surname << " " << "\nRang: " 
			  << this->rang << endl;
	  }
	  friend ostream& operator <<(ostream& stream, Employee& employee) {
		  employee.Print();
		  return stream;
	  }
	  void setName(string name) { this->name = name; }
	  void setSurname(string surname) { this->surname = surname; }
	  void setPassword(string password) { this->password = password; }
	  void setRang(string rang) { this->rang = rang; }
	  string getName() { return this->name; }
	  string getSurname() { this->surname = surname; }
	  string getPassword() { return this->password; }
	  string getRang() { return this->rang; }
	  uint32_t getDiscount() { return discount; }
};

class Meneger:public Employee {
public:
	Meneger(string name, string surname, string rang, string password) {
		this->setName(name);
		this->setSurname(surname);
		this->setRang(rang);
		this->setPassword(password);
		this->discount = 20;
	}
	~Meneger() {
		this->name.clear();
		this->password.clear();
		this->rang.clear();
		this->surname.clear();
	}

};
class TopMeneger :public Employee {
public:
	TopMeneger(string name, string surname, string rang, string password) {
		this->setName(name);
		this->setSurname(surname);
		this->setRang(rang);
		this->setPassword(password);
	}
	~TopMeneger() {
		this->name.clear();
		this->password.clear();
		this->rang.clear();
		this->surname.clear();
		this->discount = 30;
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

class Employeee
{
	map <uint32_t, employeee>* listemp;
public:
        Employeee() {
		listemp = new map <uint32_t, employeee>();
	}
	~Employeee() {
		delete listemp;
	}
	void AddEmployeee(uint32_t id, string Name, string Surname, string password, string Role) {	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		employeee Empl(id, Name, Surname, password, Role);										//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		pair<uint32_t, employeee> prod(id, Empl);												//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		listemp->insert(prod);																//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}

	employeee* getEmployeee(uint32_t id) {
		auto item = this->listemp->find(id);
		employeee* tmp = &item->second;
		if (!tmp->isEmpty()) {
			return tmp;
		}
		else
		{
			return nullptr;
		}
	}
	
	void PrintEmploye() {
		auto item = listemp->begin();
		if (!listemp->empty()) {
			for (; item != listemp->end(); item++) {
				cout << item->first << ": " << item->second << endl;
			}
		}
		else {
			cout << "\nList is empty" << endl;
		}
	}
	void ChangeStock(uint32_t id, string stock) {
		auto item = listemp->find(id);
		item->second.getAvailbl().clear();
		item->second.setAvailadl(stock);
	}
	void Inventory()
	{
		uint32_t valueStock;
		string stock;
		char y;
		map <uint32_t, employeee>::iterator it;
		it = listemp->begin();
		while (true) {
			system("cls");
			for (; it != listemp->end(); it++) {
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
		map < uint32_t, employeee >* tmp = this->listemp;
		p->Save(tmp);
	}

};


