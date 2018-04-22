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
};

#endif /* RectNode_hpp */
