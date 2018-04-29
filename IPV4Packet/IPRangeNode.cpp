//
//  IPRangeNode.cpp
//  RangeTree
//
//  Created by tab on 4/29/18.
//  Copyright © 2018 tab. All rights reserved.
//

#include "IPRangeNode.hpp"

void SourceNode::InsertNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action){
    if (rangeSRC.start>this->end) {
        if (this->right == nullptr) {
            this->right = new SourceNode(rangeSRC);
            this->right->dstChild = new DestNode(rangeDST, action);
        }else{
            this->right->InsertNode(rangeSRC, rangeDST, action);
//            this->right->dstChild->InsertNode(rangeDST, action);
        }
    }else if (rangeSRC.end<this->start){
        if (this->left == nullptr) {
            this->left = new SourceNode(rangeSRC);
            this->left->dstChild = new DestNode(rangeDST, action);
        }else{
            this->left->InsertNode(rangeSRC, rangeDST, action);
        }
    }else{
        IPRange *left = nullptr, *right = nullptr, *mid = nullptr;
        IPRange::Split(rangeSRC, this->range, left, mid, right);
        //        TODO:memory leak
        this->range = *mid;
        this->dstChild->InsertNode(range, action);
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
    }
}

void SourceNode::InsertNode(const IPRange &rangeSRC, const DestNode *dst){
    if (rangeSRC.start>this->end) {
        if (this->right == nullptr) {
            this->right = new SourceNode(rangeSRC);
            this->right->dstChild = DestNode::deepcopy(dst);
        }else{
            this->right->InsertNode(rangeSRC, dst);
        }
    }else if (rangeSRC.end<this->start){
        if (this->left == nullptr) {
            this->left = new SourceNode(rangeSRC);
            this->left->dstChild = DestNode::deepcopy(dst);
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
    return nullptr;
}




// MARK:DestNode

DestNode* DestNode::deepcopy(const DestNode *dstNode){
    return nullptr;
}

DestNode* DestNode::Search(unsigned int packetIP){
    return nullptr;
}

void DestNode::InsertNode(const IPRange &rangeDST, bool action){
    if (rangeDST.start>this->range.end) {
        if (this->right == nullptr) {
            this->right = new DestNode(rangeDST, action);
        }else{
            this->right->InsertNode(rangeDST, action);
        }
    }else if (rangeDST.end<range.start){
        if (this->left == nullptr) {
            this->left = new DestNode(rangeDST, action);
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



