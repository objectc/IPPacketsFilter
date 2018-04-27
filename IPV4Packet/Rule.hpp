//
//  Rule.hpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#ifndef Rule_hpp
#define Rule_hpp

#include <iostream>
#include <stdio.h>
#include "IPRange.hpp"
class Rule
{
public:
    IPRange dst;
    IPRange src;
    bool allow; //true: allow  false: block
    
    Rule(IPRange dest, IPRange source, bool action);
    Rule(std::string inputStr);
    
    void Print();
};
#endif /* Rule_hpp */

