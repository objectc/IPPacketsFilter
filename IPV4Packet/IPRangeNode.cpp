//
//  IPRangeNode.cpp
//  RangeTree
//
//  Created by tab on 4/29/18.
//  Copyright © 2018 tab. All rights reserved.
//

#include "IPRangeNode.hpp"
//TODO:Memory Leak
bool isRedudant = true;
void SourceNode::InsertNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action){
    if (rangeSRC.start>this->range.end) {
        if (this->right == nullptr) {
            this->right = new SourceNode(rangeSRC, rangeDST, action);
//            isRedudant = false;
        }else{
            this->right->InsertNode(rangeSRC, rangeDST, action);
        }
    }else if (rangeSRC.end<this->range.start){
        if (this->left == nullptr) {
            this->left = new SourceNode(rangeSRC, rangeDST, action);
//            isRedudant = false;
        }else{
            this->left->InsertNode(rangeSRC, rangeDST, action);
        }
    }else{
        IPRange *left = nullptr, *right = nullptr, *mid = nullptr;
        IPRange::Split(rangeSRC, this->range, left, mid, right);
        this->range = *mid;
        if(left != nullptr)
        {
            // if original contain, use original's action and dstTree
            if (rangeSRC.IsContain(*left)) {
                InsertNode(*left, rangeDST, action);
            }else{
                InsertNode(*left, this->dstChild);
            }
        }
        if(right != nullptr)
        {
            // if original contain, use original's action and dstTree
            if (rangeSRC.IsContain(*right)) {
                InsertNode(*right, rangeDST, action);
            }else{
                InsertNode(*right, this->dstChild);
            }
        }
        this->dstChild->InsertNode(rangeDST, action);
    }
}
SourceNode::SourceNode(const IPRange &rangeSRC):IPRangeNode(rangeSRC){
    
}
SourceNode::~SourceNode(){
    if(this->left != nullptr)
        delete this->left;
    if(this->right != nullptr)
        delete this->right;
    delete this->dstChild;
}

SourceNode::SourceNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action):IPRangeNode(rangeSRC){
    dstChild = new DestNode(rangeDST, action);
};

void SourceNode::InsertNode(const IPRange &rangeSRC, const DestNode *dst){
    if (rangeSRC.start>this->range.end) {
        if (this->right == nullptr) {
            this->right = new SourceNode(rangeSRC);
            this->right->dstChild = DestNode::deepcopy(dst);
//            isRedudant = false;
        }else{
            this->right->InsertNode(rangeSRC, dst);
        }
    }else if (rangeSRC.end<this->range.start){
        if (this->left == nullptr) {
            this->left = new SourceNode(rangeSRC);
            this->left->dstChild = DestNode::deepcopy(dst);
//            isRedudant = false;
        }else{
            this->left->InsertNode(rangeSRC, dst);
        }
    }else{
        throw "Insert Node Dest Error";
    }
}

bool SourceNode::IsPacketAllow(unsigned int packetSRC, unsigned int packetDST){
    SourceNode *srcRes = Search(packetSRC);
    DestNode *dstRes = srcRes->dstChild->Search(packetDST);
    return dstRes->isAllow;
};

SourceNode* SourceNode::Search(unsigned int packetIP){
    if (packetIP>this->range.end) {
        return this->right->Search(packetIP);
    }else if (packetIP<this->range.start) {
        return this->left->Search(packetIP);
    }else{
        return this;
    }
}




// MARK:DestNode

DestNode* DestNode::deepcopy(const DestNode *dstNode){
    DestNode *nodeCopy = new DestNode(dstNode);
    if (dstNode->right != nullptr) {
        nodeCopy->right = DestNode::deepcopy(dstNode->right);
    }
    if (dstNode->left != nullptr) {
        nodeCopy->left = DestNode::deepcopy(dstNode->left);
    }
    return nodeCopy;
}

DestNode* DestNode::Search(unsigned int packetIP){
    if (packetIP>this->range.end) {
        if (this->right == nullptr) {
            throw "right is null";
        }
        return this->right->Search(packetIP);
    }else if (packetIP<this->range.start) {
        if (this->left == nullptr) {
            throw "left is null";
        }
        return this->left->Search(packetIP);
    }else{
        return this;
    }
}

void DestNode::InsertNode(const IPRange &rangeDST, bool action){
    if (rangeDST.start>this->range.end) {
        if (this->right == nullptr) {
            this->right = new DestNode(rangeDST, action);
            isRedudant = false;
        }else{
            this->right->InsertNode(rangeDST, action);
        }
    }else if (rangeDST.end<range.start){
        if (this->left == nullptr) {
            this->left = new DestNode(rangeDST, action);
            isRedudant = false;
        }else{
            this->left->InsertNode(rangeDST, action);
        }
    }else{
        IPRange *left = nullptr, *right = nullptr, *mid = nullptr;
        IPRange::Split(rangeDST, this->range, left, mid, right);
        if(left != nullptr)
        {
            // only take new rule into consideration
            if (rangeDST.IsContain(*left)) {
                InsertNode(*left, action);
            }

        }
        if(right != nullptr)
        {
            // only take new rule into consideration
            if (rangeDST.IsContain(*right)) {
                InsertNode(*right, action);
            }
        }
    }
}
DestNode::~DestNode(){
    if(this->left != nullptr)
        delete this->left;
    if(this->right != nullptr)
        delete this->right;
}


