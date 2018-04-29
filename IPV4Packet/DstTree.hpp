//
//  DstTree.hpp
//  cs600
//
//  Created by Xue Kaiyun on 2018/4/27.
//  Copyright © 2018年 xbai9. All rights reserved.
//

#ifndef DstTree_hpp
#define DstTree_hpp

#include <stdio.h>
#include <iostream>
#include "Rule.hpp"
#include "RangeNode.hpp"
using namespace std;
//class Rule;
//class IPRange;
//class RangeNode;
class DstTree
{
public:
    RangeNode* root;
    DstTree();
    void Insert(const Rule rule);
    RangeNode* InsertNode( Rule rule,RangeNode* searchRoot);
    bool SearchPos(int dst, RangeNode* searchRoot);
    void Print(RangeNode *root);
    DstTree* CpySelf();
private:
    RangeNode* newNode;
    void CpyNode(RangeNode* node, RangeNode*& newN);
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
};
#endif /* DstTree_hpp */