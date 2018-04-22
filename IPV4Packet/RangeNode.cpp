//
//  RectNode.cpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#include "RangeNode.hpp"
#include "RangeTree.hpp"

RangeNode:: RangeNode(IP ip, RangeNode* l, RangeNode* r, RangeTree* tree)
{
    this->ip = ip;
    left = l;
    right = r;
    childTree = tree;
}
