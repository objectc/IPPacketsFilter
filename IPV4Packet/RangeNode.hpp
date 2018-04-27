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
#include "IPRange.hpp"

class DstTree;
class RangeNode
{
public:
    IPRange ip;
    RangeNode* left;
    RangeNode* right;
    DstTree* childTree;
    bool action;
    int high;
    RangeNode(IPRange ip, int height = 0);
    RangeNode();
};

#endif /* RectNode_hpp */
