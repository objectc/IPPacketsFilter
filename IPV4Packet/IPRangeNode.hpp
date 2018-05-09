//
//  IPRangeNode.hpp
//  RangeTree
//
//  Created by tab on 4/29/18.
//  Copyright © 2018 tab. All rights reserved.
//

#ifndef IPRangeNode_hpp
#define IPRangeNode_hpp

#include <stdio.h>

#include "IPRange.hpp"

class DestNode;
class SourceNode;
class IPRangeNode{
public:
    IPRangeNode(unsigned int start, unsigned int end):range(start, end){};
    IPRangeNode(const IPRange& range):range(range){};
    
    virtual IPRangeNode *Search(unsigned packetIP) = 0;
    
    IPRange range;
};

class SourceNode:public IPRangeNode{
public:
    SourceNode(unsigned int start, unsigned int end):IPRangeNode(start, end){};
    SourceNode(const IPRange &rangeSRC);
    SourceNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action);
    ~SourceNode();
    
    void InsertNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action);
    void InsertNode(const IPRange &rangeSRC, const DestNode *dst);
    
    bool IsPacketAllow(unsigned int packetSRC, unsigned int packetDST);
    SourceNode *Search(unsigned packetIP);
    
    SourceNode *left = nullptr;
    SourceNode *right = nullptr;
    DestNode *dstChild = nullptr;
};
class DestNode:public IPRangeNode{
public:
    static DestNode* deepcopy(const DestNode * dstNode);
    
    DestNode(const DestNode* node):IPRangeNode(node->range), isAllow(node->isAllow){};
    DestNode(const IPRange &dstRange):IPRangeNode(dstRange), isAllow(false){};
    DestNode(const IPRange &dstRange, bool action):IPRangeNode(dstRange), isAllow(action){};
    ~DestNode();
    
    void InsertNode(const IPRange &rangeDST, bool action);
    
    DestNode *Search(unsigned int packetIP);
    
    DestNode *left = nullptr;
    DestNode *right = nullptr;
    
    bool isAllow;
};
#endif /* IPRangeNode_hpp */
