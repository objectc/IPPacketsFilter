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
extern bool isRedudant;
extern vector<IPRange> srcRanges,dstRanges;
extern vector<bool>diffActions;

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
    
    
    /**
     Insert new rule from rule set

     @param rangeSRC source range of the new rule
     @param rangeDST destination range of the new rule
     @param action allow or block
     @param isEquivalentCheck is used for equivalent check
     */
    void InsertNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action, bool isEquivalentCheck = false);
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
    
    DestNode(const DestNode* node):IPRangeNode(node->range), isAllow(node->isAllow), hasChecked(false){};
    DestNode(const IPRange &dstRange):IPRangeNode(dstRange), isAllow(false), hasChecked(false){};
    DestNode(const IPRange &dstRange, bool action):IPRangeNode(dstRange), isAllow(action){};
    ~DestNode();
    
    void InsertNode(const IPRange &rangeDST, bool action, bool isEquivalentCheck = false);
    
    DestNode *Search(unsigned int packetIP);
    
    DestNode *left = nullptr;
    DestNode *right = nullptr;
    
    bool isAllow;
//    flag of current dst node has been equivanlent checked
    bool hasChecked;
    static SourceNode* curSrcNode;
};
#endif /* IPRangeNode_hpp */
