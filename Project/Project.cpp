#include <iostream>
#include "listProduct.h"

int main()
{
	listProduct* lp = new listProduct();
	lp->ReadyProd();
	lp->PrintList();
	lp->SaveListInFile();
   

}


