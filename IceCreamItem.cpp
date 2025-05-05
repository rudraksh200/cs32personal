#include "IceCreamItem.h"

IceCreamItem :: IceCreamItem(std::string size){
    this->size = size;
    if(size == "small"){
        price = 3;
    }
    else if(size == "medium"){
        price = 5;
    }
    else if(size == "large"){
        price = 6.5;
    }
}

