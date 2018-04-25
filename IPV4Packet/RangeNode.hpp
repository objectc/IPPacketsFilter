//
//  RectNode.hpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#ifndef RectNode_hpp
#define RectNode_hpp
#include <stdio.h>
#include "Rule.hpp"

class RangeTree;
class RangeNode
{
public:
    IP ip;
    RangeNode* left;
    RangeNode* right;
    RangeTree* childTree;
    bool action;
    
    int height;
    
    RangeNode(IP ip, RangeNode* l, RangeNode* r, RangeTree* tree);
    
    /*
     1.a may contain b or b conatin a.
     2. For the output result, there are 4 situations:
     i.  outLeft is null but outMid and outRight are not.
     e.g. a = 0-10, b = 0-5
     result: left = null mid = 0-5 right = 5-10
     ii. outRight is null but outMid and outLeft are not.
     e.g. a = 0-10, b = 5-10
     result: left = 0-5 mid = 5-10 right = null
     iii. outLeft and outRight are null but outMid is not.
     e.g. a = 0-10, b = 0-10
     result: left = null mid = 0-10 right = null
     iv. All are not null.
     e.g. a = 0-10, b = 4-7
     result: left = 0-4 mid = 4-7 right = 4-10
     */
    void Split(const IP& ip, IP* outLeft, IP* outMid, IP* outRight);
    
    bool IsContain(const IP& ip);
    
    bool IsContainByIP(const IP& ip);
};

#endif /* RectNode_hpp */
