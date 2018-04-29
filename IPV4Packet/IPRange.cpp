//
//  IPAddress.cpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#include "IPRange.hpp"

IPRange::IPRange(const unsigned int start, const unsigned int end):start(start),end(end)
{
    if(start > end)
    {
        throw "start > end";
    }
}


IPRange::IPRange(const string &ipStr, const char &cidr)
{
    unsigned int ip = atoi(ipStr.c_str());
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

