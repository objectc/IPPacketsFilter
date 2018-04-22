//
//  RangeTree.hpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/19.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#ifndef RangeTree_hpp
#define RangeTree_hpp
#include <stdio.h>
#include "Rule.hpp"

class RangeNode;
class Rule;
class RangeTree
{
public:
    RangeTree();
    RangeTree(bool isSource);
    ~RangeTree();
    bool isSource;
    void Insert(const Rule rule);
private:
    RangeNode* root;
    RangeNode* SearchPos(IP ip, RangeNode* searchRoot);
};
#endif /* RangeTree_hpp */
