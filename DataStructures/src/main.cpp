#include "main.h"
#include "customer.h"
#include "parcel.h"
#include "envelope.h"

std::string stripString(std::string str) {
    if(str.empty()) {
        return "";
    }
    while(isspace(str[0])) {
        str.erase(str.begin());
        if(str.empty()) {
            return "";
        }
    }
    while(isspace(str[str.size()-1])) {
        str.erase(str.end());
        if(str.empty()) {
            return "";
        }
    }
    return str;
}

int main() {
    return 0;
}