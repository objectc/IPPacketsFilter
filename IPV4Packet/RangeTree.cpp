//
//  RangeTree.cpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/19.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#include "RangeTree.hpp"
#include "RangeNode.hpp"
#include "Rule.hpp"
//#include "IPAddress.hpp"

RangeTree::RangeTree()
{
    root = nullptr;
}
RangeTree::RangeTree(bool isSource)
{
    root = nullptr;
    this->isSource = isSource;
}
void RangeTree::Insert(const Rule rule)
{
    IP ip;
    if(isSource)
        ip = rule.src;
    else
        ip = rule.dst;
    RangeNode* pos = SearchPos(ip, root);
    if(pos == nullptr)
    {
        RangeTree newTree = RangeTree(false);
        RangeNode newNode = RangeNode(ip, nullptr, nullptr, &newTree);
        newNode.height = 0;
        pos = &newNode;
        if(isSource)
        {
            newNode.childTree->Insert(rule);
        }
    }
    else if(pos->ip.IsContain(ip) || ip.IsContain(pos->ip))
    {
        IP* left, *right, *mid;
        IP::Split(ip, pos->ip, left, mid, right);
        
        pos->ip = *mid;
        pos->childTree->Insert(rule);
        if(left != nullptr)
        {
            Rule leftRule = Rule(*left, rule.dst, rule.allow);
            Insert(leftRule);
        }
        if(right != nullptr)
        {
            Rule rightRule = Rule(*right, rule.dst, rule.allow);
            Insert(rightRule);
        }
    }
    else if(ip.intIP > pos->ip.intIP)
    {
        RangeTree newTree = RangeTree(false);
        RangeNode newNode = RangeNode(ip, nullptr, nullptr, &newTree);
        newNode.height = pos->height + 1;
        pos->right = &newNode;
        if(isSource)
        {
            newNode.childTree->Insert(rule);
        }
    }
    else if(ip.intIP < pos->ip.intIP)
    {
        RangeTree newTree = RangeTree(false);
        RangeNode newNode = RangeNode(ip, nullptr, nullptr, &newTree);
        pos->height = pos->height + 1;
        pos->left = &newNode;
        if(isSource)
        {
            newNode.childTree->Insert(rule);
        }
    }
}
RangeNode* RangeTree::SearchPos(IP ip, RangeNode* searchRoot)
{
    if(searchRoot == nullptr)
    {
        return searchRoot;
    }
    else if(searchRoot->ip.IsContain(ip))
    {
        return searchRoot;
    }
    else if(ip.IsContain(searchRoot->ip))
    {
        return searchRoot;
    }
    else if(ip.intIP > searchRoot->ip.intIP)
    {
        if(searchRoot->right == nullptr)
            return searchRoot;
        else
            return SearchPos(ip, searchRoot->left);
    }
    else
    {
        if(searchRoot->left == nullptr)
            return searchRoot;
        else
            return SearchPos(ip, searchRoot->right);
    }
}

