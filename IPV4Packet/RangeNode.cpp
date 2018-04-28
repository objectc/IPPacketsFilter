//
//  RectNode.cpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#include "RangeNode.hpp"
#include "DstTree.hpp"
//#include "Rule.hpp"
RangeNode:: RangeNode(IPRange srcIP, IPRange dstIP, bool action, int height)
{
    this->srcIP = srcIP;
    this->dstIP = dstIP;
    this->action = action;
    high = height;
    left = nullptr;
    right = nullptr;
    childTree = nullptr;
}
RangeNode::RangeNode()
{
    left = nullptr;
    right = nullptr;
    childTree = nullptr;
}
RangeNode:: RangeNode(Rule rule, int height)
{
    srcIP = rule.src;
    dstIP = rule.dst;
    action = rule.allow;
    high = height;
    left = nullptr;
    right = nullptr;
    childTree = nullptr;
}
RangeNode* RangeNode:: CpyNode()
{
    RangeNode* tmp = new RangeNode(srcIP, dstIP, action);
    tmp->childTree = childTree->CpySelf();
    return tmp;
}
