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
#include <stack>

#include "IPRange.hpp"

class DestNode;
class SourceNode;
class IPRangeNode{
public:
    IPRangeNode(unsigned int start, unsigned int end):range(start, end){};
    IPRangeNode(const IPRange& range):range(range){};
    
    virtual IPRangeNode *Search(unsigned packetIP) = 0;
    virtual IPRangeNode *getLeft() = 0;
    virtual IPRangeNode *getRight() = 0;
//    virtual void setRoot(IPRangeNode *node) = 0;
    virtual void setLeft(IPRangeNode *node) = 0;
    virtual void setRight(IPRangeNode *node) = 0;
    
//    static stack<IPRangeNode *>trackStackDst;
    
//    static stack<IPRangeNode *>trackStackSrc;
    
    IPRange range;
    IPRangeNode *left = nullptr;
    IPRangeNode *right = nullptr;
    
    int high;
    static IPRangeNode *root;
    int hight(IPRangeNode * root);
    IPRangeNode* single_rotate_left(IPRangeNode *root);
    IPRangeNode* single_rotate_right(IPRangeNode * root);
    IPRangeNode* double_rotate_left(IPRangeNode * root);
    IPRangeNode* double_rotate_right(IPRangeNode * root);
    
    
};





class SourceNode:public IPRangeNode{
public:
    SourceNode(unsigned int start, unsigned int end):IPRangeNode(start, end){};
    SourceNode(const IPRange &rangeSRC);
    SourceNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action);
    
    void InsertNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action);
    void InsertNode(const IPRange &rangeSRC, const DestNode *dst);
    
    bool IsPacketAllow(unsigned int packetSRC, unsigned int packetDST);
    SourceNode *Search(unsigned packetIP);
    SourceNode *getLeft()   {return left;}
    SourceNode *getRight()  {return right;}
    void setLeft(IPRangeNode *node) {left = dynamic_cast<SourceNode *>(node);}
    void setRight(IPRangeNode *node) {right = dynamic_cast<SourceNode *>(node);}
//    void setRight(IPRangeNode *node) {}
    
    SourceNode *left = nullptr;
    SourceNode *right = nullptr;
    DestNode *dstChild = nullptr;
    
    
    static stack<IPRangeNode *>trackStackSrc;
    
};

class DestNode:public IPRangeNode{
public:
    static DestNode* deepcopy(const DestNode * dstNode);
    
    DestNode(const DestNode* node):IPRangeNode(node->range), isAllow(node->isAllow){};
    DestNode(const IPRange &dstRange):IPRangeNode(dstRange), isAllow(false){};
    DestNode(const IPRange &dstRange, bool action):IPRangeNode(dstRange), isAllow(action){};
    
    void InsertNode(const IPRange &rangeDST, bool action);
    
    DestNode *Search(unsigned int packetIP);
    DestNode *getLeft()     {return left;}
    DestNode *getRight()    {return right;}
    void setLeft(IPRangeNode *node) {left = dynamic_cast<DestNode *>(node);}
    void setRight(IPRangeNode *node) {right = dynamic_cast<DestNode *>(node);}
    
    DestNode *left = nullptr;
    DestNode *right = nullptr;
    
    static stack<IPRangeNode *>trackStackDst;
    
    bool isAllow;
};
#endif /* IPRangeNode_hpp */
