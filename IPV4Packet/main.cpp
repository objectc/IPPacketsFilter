//
//  main.cpp
//  IPV4Packet
//
//  Created by tab on 4/18/18.
//  Copyright © 2018 tab. All rights reserved.
//

#include <iostream>
#include "IPParser.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    generateRuleAndTestCase();
    IPParser parser;
    parser.printIP();
    parser.verifyData();
    return 0;
}
