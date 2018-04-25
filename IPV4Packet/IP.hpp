//
//  IP.hpp
//  CS600
//
//  Created by Xue Kaiyun on 2018/4/21.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#ifndef IP_hpp
#define IP_hpp

#include <stdio.h>
#include <string>
#include <iostream>
class IP{
public:
    unsigned int intIP;
    unsigned int start;
    unsigned int end;
    char cidr;
    std::string ip;
    IP(std::string const& ipStr);
    IP();
    //    ~IP();
    bool IsContain(IP ip);
};

#endif /* IP_hpp */
