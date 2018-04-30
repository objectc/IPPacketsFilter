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

IP::IP(std::string const& ipStr){
    std::string delimiter = "/";
    size_t pos = 0;
    string ip;
    pos = ipStr.find(delimiter);
    ip = ipStr.substr(0, pos);
    this->cidr = stoi(ipStr.substr(pos+1)) - '\0';
    
    // Storing the IP
    if(cidr > 32 || cidr < 0) {
        cout << "Incorrent IP address: " << ip << endl << endl;
        return;
    }
    this->intIP = ip_to_int(ip);
    this->ip = ipStr;
}


Rule::Rule(IP const& src, IP const& dst, bool allow):src(src),dst(dst),allow(allow){
    
}

bool Rule::isContain(unsigned int const& srcPacket, unsigned int const& dstPacket){
    unsigned int ruleSrcShift = src.cidr==32?0:src.intIP>>src.cidr;
    unsigned int packetSrcShift = src.cidr==32?0:srcPacket>>src.cidr;
    unsigned int ruleDstShift = dst.cidr==32?0:dst.intIP>>dst.cidr;
    unsigned int packetDstShift = dst.cidr==32?0:dstPacket>>dst.cidr;
//    return src.intIP>>src.cidr == srcPacket>>src.cidr && dst.intIP>>dst.cidr == dstPacket>>dst.cidr;
    bool res = (ruleSrcShift == packetSrcShift && ruleDstShift == packetDstShift);
//    bool res = (ruleSrcShift == packetSrcShift);
    return res;
    
}

bool Rule::isAllow(unsigned int const& srcPacket, unsigned int const& dstPacket){
    return allow;
}

