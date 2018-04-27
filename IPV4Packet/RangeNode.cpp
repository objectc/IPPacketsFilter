//
//  RectNode.cpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#include "RangeNode.hpp"
//#include "Rule.hpp"
RangeNode:: RangeNode(IPRange ip, int height)
{
    this->ip = ip;
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
