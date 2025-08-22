
#include "Building.h"

Building::Building(const std::string &address, int year): address(address), year(year) {
}

Block::Block(const std::string &address, int year, int apart, int occupied):Building(address,year), apart(apart), occupied(occupied) {
}

bool Block::Restored() {

    if (2025-year>40 && occupied/apart*100>80) {
        return true;
    }
    return false;
}

bool Block::Demolished() {
    if (occupied/apart*100<5) {
        return true;
    }
    return true;
}

std::string Block::toString() {
    return address+", "+std::to_string(year)+", "+std::to_string(apart)+", "+std::to_string(occupied)+"\n";
}

std::string Building::getAdd() {
    return address;
}

House::House(const std::string &address, int year, const std::string &type, bool hist):Building(address,year), type(type), hist(hist) {
}

bool House::Restored() {
    if (2025-year>100)
        return true;
    return false;
}

bool House::Demolished() {
    if (!hist)
        return true;
    return false;
}

std::string House::toString() {
    return address+", "+std::to_string(year)+", "+type+", "+std::to_string(hist)+"\n";
}
