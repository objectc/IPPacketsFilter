//
//  IPRangeNode.cpp
//  RangeTree
//
//  Created by tab on 4/29/18.
//  Copyright © 2018 tab. All rights reserved.
//

#include "IPRangeNode.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//TODO:Memory Leak
bool isRedudant = true;
vector<IPRange> srcRanges,dstRanges;
vector<bool>diffActions;

//void writeToFile(IPRange src, IPRange dest, bool action,string fileName){
//    ofstream dataFile;
//    dataFile.open(fileName,ios::app);
//    if(dataFile.is_open()){
//        dataFile<<src.start<<","<<src.end<<","<<dest.start<<","<<dest.end<<","<<action<<endl;
//    }
//    dataFile.close();
//}

SourceNode* DestNode::curSrcNode = nullptr;
void SourceNode::InsertNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action, bool isEquivalentCheck){
    if (rangeSRC.start>this->range.end) {
        if (this->right == nullptr) {
            this->right = new SourceNode(rangeSRC, rangeDST, action);
        }else{
            this->right->InsertNode(rangeSRC, rangeDST, action, isEquivalentCheck);
        }
    }else if (rangeSRC.end<this->range.start){
        if (this->left == nullptr) {
            this->left = new SourceNode(rangeSRC, rangeDST, action);
        }else{
            this->left->InsertNode(rangeSRC, rangeDST, action, isEquivalentCheck);
        }
    }else{
        IPRange *left = nullptr, *right = nullptr, *mid = nullptr;
        IPRange::Split(rangeSRC, this->range, left, mid, right);
        this->range = *mid;
        if(left != nullptr)
        {
            // if original contain, use original's action and dstTree
            if (rangeSRC.IsContain(*left)) {
                InsertNode(*left, rangeDST, action, isEquivalentCheck);
            }else{
                InsertNode(*left, this->dstChild);
            }
        }
        if(right != nullptr)
        {
            // if original contain, use original's action and dstTree
            if (rangeSRC.IsContain(*right)) {
                InsertNode(*right, rangeDST, action, isEquivalentCheck);
            }else{
                InsertNode(*right, this->dstChild);
            }
        }
        DestNode::curSrcNode = this;
        this->dstChild->InsertNode(rangeDST, action, isEquivalentCheck);
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
        }else{
            this->right->InsertNode(rangeSRC, dst);
        }
    }else if (rangeSRC.end<this->range.start){
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

void DestNode::InsertNode(const IPRange &rangeDST, bool action, bool isEquivalentCheck){
    if (rangeDST.start>this->range.end) {
        if (this->right == nullptr) {
            this->right = new DestNode(rangeDST, action);
        }else{
            this->right->InsertNode(rangeDST, action, isEquivalentCheck);
        }
    }else if (rangeDST.end<range.start){
        if (this->left == nullptr) {
            this->left = new DestNode(rangeDST, action);
        }else{
            this->left->InsertNode(rangeDST, action, isEquivalentCheck);
        }
    }else{
        IPRange *left = nullptr, *right = nullptr, *mid = nullptr;
        IPRange::Split(rangeDST, this->range, left, mid, right);
        if(left != nullptr)
        {
            // only take new rule into consideration
            if (rangeDST.IsContain(*left)) {
                InsertNode(*left, action, isEquivalentCheck);
            }

        }
        if(right != nullptr)
        {
            // only take new rule into consideration
            if (rangeDST.IsContain(*right)) {
                InsertNode(*right, action, isEquivalentCheck);
            }
        }
        //equivalent check
        if (isEquivalentCheck && !hasChecked) {
            if (action != this->isAllow) {
                srcRanges.push_back(IPRange(curSrcNode->range.start, curSrcNode->range.end));
                dstRanges.push_back(IPRange(mid->start, mid->end));
                diffActions.push_back(action);
            }
            hasChecked = true;
        }
    }
}
DestNode::~DestNode(){
    if(this->left != nullptr)
        delete this->left;
    if(this->right != nullptr)
        delete this->right;
}


