//
//  IPRangeNode.cpp
//  RangeTree
//
//  Created by tab on 4/29/18.
//  Copyright © 2018 tab. All rights reserved.
//

#include "IPRangeNode.hpp"
//TODO:Memory Leak
void SourceNode::InsertNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action){
    if (rangeSRC.start>this->range.end) {
        if (this->right == nullptr) {
            this->right = new SourceNode(rangeSRC, rangeDST, action);
        }else{
            this->right->InsertNode(rangeSRC, rangeDST, action);
        }
        // rotate
        if(hight(this->right) - hight(this->left) == 2){
            if(rangeSRC.start > this->right->range.end){
                root = single_rotate_right(this);
            }
            else{
                root = double_rotate_right(this);
            }
        }
        
    }else if (rangeSRC.end<this->range.start){
        if (this->left == nullptr) {
            this->left = new SourceNode(rangeSRC, rangeDST, action);
        }else{
            this->left->InsertNode(rangeSRC, rangeDST, action);
        }
        // rotate
        if(hight(this->left) - hight(this->right) == 2){
            if(rangeSRC.start > this->left->range.end){
                root = single_rotate_left(this);
            }
            else{
                root = double_rotate_left(this);
            }
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
    //change the high of each srcNode.
    this->high = max(hight(this->left), hight(this->right)) + 1;
}
SourceNode::SourceNode(const IPRange &rangeSRC):IPRangeNode(rangeSRC){
    
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
        return this->right->Search(packetIP);
    }else if (packetIP<this->range.start) {
        return this->left->Search(packetIP);
    }else{
        return this;
    }
}

void DestNode::InsertNode(const IPRange &rangeDST, bool action){
    if (rangeDST.start>this->range.end) {
        if (this->right == nullptr) {
            this->right = new DestNode(rangeDST, action);
        }else{
            //push current node into stack
            trackStack.push(this);
            this->right->InsertNode(rangeDST, action);
        }
        
        //rotate
        if(hight(this->right) - hight(this->left) == 2){
            if(rangeDST.start > this->right->range.end){
                root = single_rotate_right(this);
            }
            else{
                root = double_rotate_right(this);
            }
        }
    }else if (rangeDST.end<range.start){
        if (this->left == nullptr) {
            this->left = new DestNode(rangeDST, action);
        }else{
            //push current node into stack
            trackStack.push(this);
            this->left->InsertNode(rangeDST, action);
        }
        
        //rotate
        if(hight(this->left) - hight(this->right) == 2){
            if(rangeDST.start > this->left->range.end){
                root = single_rotate_left(this);
            }
            else{
                root = double_rotate_left(this);
            }
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
            
            //rotate
            if(hight(trackStack.top()->left) - hight(trackStack.top()->right) == 2){
                if(rangeDST.start > trackStack.top()->left->range.end){
                    root = single_rotate_left(trackStack.top());
                }
                else{
                    root = double_rotate_left(trackStack.top());
                }
            }
        }
        if(right != nullptr)
        {
            // only take new rule into consideration
            if (rangeDST.IsContain(*right)) {
                InsertNode(*right, action);
            }
            
            //rotate
            if(hight(trackStack.top()->right) - hight(trackStack.top()->left) == 2){
                if(rangeDST.start > trackStack.top()->right->range.end){
                    root = single_rotate_right(trackStack.top());
                }
                else{
                    root = double_rotate_right(trackStack.top());
                }
            }
        }
    }
    
    trackStack.pop();
    
    //chage high of each dstNode
    this->high = max(hight(this->left), hight(this->right)) + 1;
}

//get the high of each node
int IPRangeNode::hight(IPRangeNode * root){
    if(!root)
    return -1;
    else
    return root->high;
}

//rotate left
IPRangeNode* IPRangeNode::single_rotate_left(IPRangeNode *root){
    IPRangeNode * tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    
    //when finished rotate, change the node's height
    root->high = max(hight(root->left), hight(root->right)) + 1;
    tmp->high = max(hight(tmp->left), hight(tmp->right)) + 1;
    //return the new tree root node.
    return tmp;
}

//rotate right
IPRangeNode* IPRangeNode::single_rotate_right(IPRangeNode * root){
    IPRangeNode * tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    root->high = max(hight(root->left), hight(root->right)) + 1;
    tmp->high = max(hight(tmp->left), hight(tmp->right)) + 1;
    return tmp;

}

//rotate right then left.
IPRangeNode* IPRangeNode::double_rotate_left(IPRangeNode * root){
    //first rotate right child tree.
    root->left = single_rotate_right(root->left);
    
    //then rotate the whole tree.
    return single_rotate_left(root);
}

//rotate left then right.
IPRangeNode* IPRangeNode::double_rotate_right(IPRangeNode * root){
    //first rotate left child tree.
    root->right = single_rotate_left(root->right);
    //then roate the whole tree.
    return single_rotate_right(root);
}


