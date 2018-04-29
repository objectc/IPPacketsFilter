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
    IPRangeNode(unsigned int start, unsigned int end):start(start),end(end),range(start, end){};
    IPRangeNode(const IPRange& range):range(range){};
    
//    virtual void InsertNode(unsigned int start, unsigned int end) = 0;
//    virtual void InsertNode(IPRange &range) = 0;
    virtual IPRangeNode *Search(unsigned packetIP) = 0;
    
    unsigned int start;
    unsigned int end;
    IPRange range;
//    IPRangeNode *left = nullptr;
//    IPRangeNode *right = nullptr;
};

class SourceNode:public IPRangeNode{
    
    SourceNode(unsigned int start, unsigned int end):IPRangeNode(start, end){};
    SourceNode(const IPRange& range):IPRangeNode(range){};
    
//    void InsertNode(unsigned int start, unsigned int end);
    void InsertNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action);
    void InsertNode(const IPRange &rangeSRC, const DestNode *dst);
    
    bool IsPacketAllow(unsigned int packetSRC, unsigned int packetDST);
    SourceNode *Search(unsigned packetIP);
    
    SourceNode *left = nullptr;
    SourceNode *right = nullptr;
    DestNode *dstChild;
};
class DestNode:public IPRangeNode{
public:
    static DestNode* deepcopy(const DestNode * dstNode);
    
    DestNode(const IPRange &dstRange):IPRangeNode(dstRange), isAllow(false){};
    DestNode(const IPRange &dstRange, bool action):IPRangeNode(dstRange), isAllow(action){};
    
    void InsertNode(const IPRange &rangeDST, bool action);
    
    DestNode *Search(unsigned int packetIP);
    
    DestNode *left = nullptr;
    DestNode *right = nullptr;
    
    bool isAllow;
};
#endif /* IPRangeNode_hpp */
