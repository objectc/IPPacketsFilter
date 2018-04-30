//
//  IPAddress.cpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#include "IPRange.hpp"

unsigned int IPRange::ip_to_int (const std::string &ip){
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

IPRange::IPRange(const unsigned int start, const unsigned int end):start(start),end(end)
{
    if(start > end)
    {
        throw "start > end";
    }
}


IPRange::IPRange(const string &ruleStr)
{
    std::string delimiter = "/";
    size_t pos = 0;
    pos = ruleStr.find(delimiter);
    string ipStr = ruleStr.substr(0, pos);
    unsigned int ip = ip_to_int(ipStr.c_str());
    char cidr = stoi(ruleStr.substr(pos+1)) - '\0';
    if (cidr==32) {
        start = 0;
    }else
        start = ip >> cidr << cidr;
    
    unsigned int _m = pow(2, cidr) - 1;
    end =start | _m;
}

void IPRange::TransformIP()
{
    start = a * pow(256, 3) + b * pow(256, 2) + c * 256 + d;
    //cout<<"min"<<minIP<<endl;
    unsigned int _m = pow(2, k) - 1;
    end =start | _m;
    if (k==32) {
        start = 0;
    }else
        start = start >> k << k;
}
bool IPRange::IsContain(IPRange b) const
{
    if(end >= b.end && start <= b.start)
        return true;
    else
        return  false;
}

