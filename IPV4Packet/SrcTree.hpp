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
#include <iostream>
#include "Rule.hpp"
#include "RangeNode.hpp"
#include "DstTree.hpp"
using namespace std;
//class Rule;
//class IPRange;
class DstTree;
class SrcTree
{
public:
    SrcTree();
    void Insert(const Rule rule);
    RangeNode* root;
    
    RangeNode* SearchPos(IPRange ip, RangeNode* searchRoot);
    //single left rotate
    RangeNode *single_rotate_left(RangeNode *root);
    //single right rotate
    RangeNode *single_rotate_right(RangeNode *root);
    //double left rotate
    RangeNode *double_rotate_left(RangeNode *root);
    //double right rotate
    RangeNode *double_rotate_right(RangeNode *root);
    //get each node's hight
    int hight(RangeNode * root);
    //get the max value of child tree's height.
    int max(int l, int r);
    RangeNode* InsertNode( Rule rule,RangeNode* searchRoot);
private:
    RangeNode* newNode;
};
#endif /* RangeTree_hpp */
