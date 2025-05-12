#include "PreMadeItem.h"
PreMadeItem::PreMadeItem(std::string name, std::string size) : IceCreamItem(size), name(name){
    price += 1;
}

double PreMadeItem::getPrice(){
    return price;
}

std::string PreMadeItem::composeItem(){
    return "Pre-made Size: " + size + "\nPre-made Item: " + name + "\nPrice: $" + doubleToString(price) + "\n";
}

PreMadeItem::~PreMadeItem(){}

std::string PreMadeItem::doubleToString(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value;
    return oss.str();
}
