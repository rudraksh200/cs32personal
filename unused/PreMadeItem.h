#ifndef PREMADEITEM_H
#define PREMADEITEM_H
#include "IceCreamItem.h"

#include <string>
#include <sstream>     
#include <iomanip>     
#include <string>

class PreMadeItem : public IceCreamItem {
public:
	PreMadeItem(std::string name, std::string size);

	std::string composeItem() override;
	double getPrice() override;
    virtual ~PreMadeItem();
    std::string doubleToString(double value);
    
protected:
    std::string name;
};

#endif
