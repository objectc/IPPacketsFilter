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
#include "Rule.hpp"

class DstTree;
class RangeNode
{
public:
    IPRange srcIP;
    IPRange dstIP;
    RangeNode* left;
    RangeNode* right;
    DstTree* childTree;
    bool action;
    int high;
    RangeNode(IPRange srcIP, IPRange dstIP, bool action, int height = 0);
    RangeNode(Rule rule, int height = 0);
    RangeNode();
    RangeNode* CpyNode();
};

#endif /* RectNode_hpp */
