//
//  Rule.cpp
//  IPV4Packet
//
//  Created by tab on 4/18/18.
//  Copyright © 2018 tab. All rights reserved.
//

#include "Rule.hpp"
#include <iostream>
using namespace std;

Rule::Rule(IP const& src, IP const& dst, bool allow):src(src),dst(dst),allow(allow){
    
}

bool Rule::isContain(unsigned int const& srcPacket, unsigned int const& dstPacket){
    int src1 = src.intIP>>src.cidr;
    int src2 = srcPacket>>src.cidr;
    return src.intIP>>src.cidr == srcPacket>>src.cidr && dst.intIP>>src.cidr == dstPacket>>dst.cidr;
}

bool Rule::isAllow(unsigned int const& srcPacket, unsigned int const& dstPacket){
    return allow;
}

