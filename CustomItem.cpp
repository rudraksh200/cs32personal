#include "CustomItem.h"

CustomItem :: CustomItem(std::string size) : IceCreamItem(size){}

CustomItem :: ~CustomItem(){}

void CustomItem :: addTopping(std::string topping){
    if(toppings.find(topping) != toppings.end()){
        toppings[topping] += 1;
        price += 0.4;
        return;
    }
    toppings[topping] = 1;
    price += 0.4;

}

double CustomItem::getPrice(){
    return price;
}

std::string CustomItem::composeItem(){
    std::string output = "";
    output += "Custom Size: " + size + "\nToppings:\n";
    for(const auto& pair : toppings){
        output += pair.first + ": " + std::to_string(pair.second) + " oz\n";
    }

    output += "Price: $" + doubleToString(price) + "\n";

    return output;
}

std::string CustomItem::doubleToString(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value;
    return oss.str();
}
