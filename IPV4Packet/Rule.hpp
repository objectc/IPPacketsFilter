//
//  Rule.hpp
//  IPV4Packet
//
//  Created by tab on 4/18/18.
//  Copyright © 2018 tab. All rights reserved.
//

#ifndef Rule_hpp
#define Rule_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include "IP.hpp"

static unsigned int ip_to_int (const std::string &ip){
    /* The return value. */
    unsigned v = 0;
    /* The count of the number of bytes processed. */
    int i;
    /* A pointer to the next digit to process. */
    const char * start;
    
    start = ip.c_str();
    for (i = 0; i < 4; i++) {
        /* The digit being processed. */
        char c;
        /* The value of this byte. */
        int n = 0;
        while (1) {
            c = * start;
            start++;
            if (c >= '0' && c <= '9') {
                n *= 10;
                n += c - '0';
            }
            /* We insist on stopping at "." if we are still parsing
             the first, second, or third numbers. If we have reached
             the end of the numbers, we will allow any character. */
            else if ((i < 3 && c == '.') || i == 3) {
                break;
            }
            else {
                std::cout << "Incorrent IP address: " << ip << std::endl;
                return 0;
            }
        }
        if (n >= 256) {
            std::cout << "Incorrent IP address: " << ip << std::endl;
            return 0;
        }
        v *= 256;
        v += n;
    }
    return v;
}
class Rule{
public:
    IP src;
    IP dst;
    bool allow;
    Rule(IP const& src, IP const& dst, bool allow);
    bool isContain(unsigned int const& srcPacket, unsigned int const& dstPacket);
    bool isAllow(unsigned int const& srcPacket, unsigned int const& dstPacket);
//    ~Rule();
};
#endif /* Rule_hpp */
