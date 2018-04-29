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
class DestNode;
class SourceNode;
class IPRangeNode{
public:
    unsigned int start;
    unsigned int end;
    IPRangeNode *left = nullptr;
    IPRangeNode *right = nullptr;
    virtual void InsertNode(unsigned int start, unsigned int end ,IPRangeNode*& currentNode) = 0;
    virtual IPRangeNode *deepcopy() = 0;
    virtual IPRangeNode *Search(unsigned packetIP, IPRangeNode* currentNode = nullptr) = 0;
};

class SourceNode:public IPRangeNode{
    bool IsPacketAllow(unsigned int packetSRC, unsigned int packetDST, IPRangeNode * currentNode);
    SourceNode *Search(unsigned packetIP, IPRangeNode* currentNode = nullptr);
    DestNode *dstChild;
};
class DestNode:public IPRangeNode{
public:
    bool isAllow;
    DestNode *Search(unsigned int packetIP, IPRangeNode* currentNode = nullptr);
};
#endif /* IPRangeNode_hpp */
