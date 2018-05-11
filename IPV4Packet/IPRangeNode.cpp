//
//  IPRangeNode.cpp
//  RangeTree
//
//  Created by tab on 4/29/18.
//  Copyright © 2018 tab. All rights reserved.
//

#include "IPRangeNode.hpp"

IPRangeNode* IPRangeNode::root = nullptr;
stack<IPRangeNode *> SourceNode::trackStackSrc;
stack<IPRangeNode *> DestNode::trackStackDst;

static IPRangeNode* tem = nullptr;

int updateHeight(IPRangeNode *node){
    if(!node)
    return -1;
    else{
        int newLeftH = updateHeight(node->getLeft());
        int newRightH = updateHeight(node->getRight());
        return max(newLeftH, newRightH)+1;
    }
}

//TODO:Memory Leak
void SourceNode::InsertNode(const IPRange &rangeSRC, const IPRange &rangeDST, bool action){
    DestNode::root = this->dstChild;
    if (rangeSRC.start>this->range.end) {
        if (this->right == nullptr) {
            this->right = new SourceNode(rangeSRC, rangeDST, action);
            trackStackSrc.push(this->right);
            root->high = updateHeight(root);
            //rotate
            while(trackStackSrc.size() != 0){
                    if(hight(trackStackSrc.top()->left) - hight(trackStackSrc.top()->right) == 2){
                        if(rangeSRC.end  < trackStackSrc.top()->left->range.start){
                            tem = single_rotate_left(trackStackSrc.top());
                        }
                        else if(rangeSRC.start  < trackStackSrc.top()->left->range.end){
                            tem = double_rotate_left(trackStackSrc.top());
                        }
                    }else if(hight(trackStackSrc.top()->right) - hight(trackStackSrc.top()->left) == 2){
                        if(rangeSRC.start > trackStackSrc.top()->right->range.end){
                            tem = single_rotate_right(trackStackSrc.top());
                        }
                        else if(rangeSRC.end  < trackStackSrc.top()->right->range.start){
                            tem = double_rotate_right(trackStackSrc.top());
                        }
                    }
                trackStackSrc.pop();
            }
            
            root->high = updateHeight(root);

        }else{
            trackStackSrc.push(this);
            this->right->InsertNode(rangeSRC, rangeDST, action);
        }
    }else if (rangeSRC.end<this->range.start){
        if (this->left == nullptr) {
            this->left = new SourceNode(rangeSRC, rangeDST, action);
            trackStackSrc.push(this->left);
            root->high = updateHeight(root);
            //rotate
            while(trackStackSrc.size() != 0){
                if(hight(trackStackSrc.top()->left) - hight(trackStackSrc.top()->right) == 2){
                    if(rangeSRC.end  < trackStackSrc.top()->left->range.start){
                        tem = single_rotate_left(trackStackSrc.top());
                    }
                    else if(rangeSRC.start  < trackStackSrc.top()->left->range.end){
                        tem = double_rotate_left(trackStackSrc.top());
                    }
                }else if(hight(trackStackSrc.top()->right) - hight(trackStackSrc.top()->left) == 2){
                    if(rangeSRC.start > trackStackSrc.top()->right->range.end){
                        tem = single_rotate_right(trackStackSrc.top());
                    }
                    else if(rangeSRC.end  < trackStackSrc.top()->right->range.start){
                        tem = double_rotate_right(trackStackSrc.top());
                    }
                }
                trackStackSrc.pop();
            }
            
            root->high = updateHeight(root);
        }else{
            trackStackSrc.push(this);
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
    //change the high of each srcNode.
    this->dstChild = dynamic_cast<DestNode *>(DestNode::root);
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
            trackStackDst.push(this->right);
            root->high = updateHeight(root);
            while (trackStackDst.size() != 0) {
                    //rotate
                    if(hight(trackStackDst.top()->left) - hight(trackStackDst.top()->right) == 2){
                        if(rangeDST.end < trackStackDst.top()->left->range.start){
                            tem = single_rotate_left(trackStackDst.top());
                        }
                        else if(rangeDST.start > trackStackDst.top()->left->range.end){
                            tem = double_rotate_left(trackStackDst.top());
                        }
                    } else if(hight(trackStackDst.top()->right) - hight(trackStackDst.top()->left) == 2){
                        if(rangeDST.start > trackStackDst.top()->right->range.end){
                            tem = single_rotate_right(trackStackDst.top());
                        }
                        else if(rangeDST.end < trackStackDst.top()->right->range.start){
                            tem = double_rotate_right(trackStackDst.top());
                        }
                    }
                trackStackDst.pop();
            }
            root->high = updateHeight(root);
        }else{
            //push current node into stack
            trackStackDst.push(this);
            this->right->InsertNode(rangeDST, action);
        }
        
    }else if (rangeDST.end<range.start){
        if (this->left == nullptr) {
            this->left = new DestNode(rangeDST, action);
            trackStackDst.push(this->left);
            root->high = updateHeight(root);
            while (trackStackDst.size() != 0) {
                //rotate
                if(hight(trackStackDst.top()->left) - hight(trackStackDst.top()->right) == 2){
                    if(rangeDST.end < trackStackDst.top()->left->range.start){
                        tem = single_rotate_left(trackStackDst.top());
                    }
                    else if(rangeDST.start > trackStackDst.top()->left->range.end){
                        tem = double_rotate_left(trackStackDst.top());
                    }
                } else if(hight(trackStackDst.top()->right) - hight(trackStackDst.top()->left) == 2){
                    if(rangeDST.start > trackStackDst.top()->right->range.end){
                        tem = single_rotate_right(trackStackDst.top());
                    }
                    else if(rangeDST.end < trackStackDst.top()->right->range.start){
                        tem = double_rotate_right(trackStackDst.top());
                    }
                }
                trackStackDst.pop();
            }
            root->high = updateHeight(root);
        }else{
            //push current node into stack
            trackStackDst.push(this);
            this->left->InsertNode(rangeDST, action);
        }
        
//        //rotate
//        if(hight(this->left) - hight(this->right) == 2){
//            if(rangeDST.end > this->left->range.start){
//                tem = single_rotate_left(this);
//            }
//            else if(rangeDST.start > this->left->range.end){
//                tem = double_rotate_left(this);
//            }
//        }
        
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
            
//            //rotate
//                if(hight(this->right) - hight(this->left) == 2){
//                    if(rangeDST.start > this->right->range.end){
//                        tem = single_rotate_right(this);
//                    }
//                    else if(rangeDST.end < this->right->range.start){
//                        tem = double_rotate_right(this);
//                    }
//                }
        }
    }
    
    //chage high of each dstNode
//    this->high = max(hight(this->left), hight(this->right)) + 1;
}

//get the high of each node
int IPRangeNode::hight(IPRangeNode * node){
    if(!node)
        return -1;
    else
        return node->high;
}

//rotate left
IPRangeNode* IPRangeNode::single_rotate_left(IPRangeNode *node){
    IPRangeNode * tmp = node->getLeft();
    node->setLeft(tmp->getRight());
    tmp->setRight(node);
    
    //when finished rotate, change the node's height
    node->high = max(hight(node->getLeft()), hight(node->getRight())) + 1;
    tmp->high = max(hight(tmp->getLeft()), hight(tmp->getRight())) + 1;
    //return the new tree root node.
    if(node == root){
        root = tmp;
    }
    return tmp;
}

//rotate right
IPRangeNode* IPRangeNode::single_rotate_right(IPRangeNode * node){
    IPRangeNode * tmp = node->getRight();
    node->setRight(tmp->getLeft());
    tmp->setLeft(node);
    node->high = max(hight(node->getLeft()), hight(node->getRight())) + 1;
    tmp->high = max(hight(tmp->getLeft()), hight(tmp->getRight())) + 1;
    if(node == root){
        root = tmp;
    }
    return tmp;
}

//rotate right then left.
IPRangeNode* IPRangeNode::double_rotate_left(IPRangeNode * node){
    //first rotate right child tree.
//    node->left = single_rotate_right(node->getLeft());
    IPRangeNode * newLeft = single_rotate_right(node->getLeft());
    node->setLeft(newLeft);
    
    //then rotate the whole tree.
    return single_rotate_left(node);
}

//rotate left then right.
IPRangeNode* IPRangeNode::double_rotate_right(IPRangeNode * node){
    //first rotate left child tree.
//    node->right = single_rotate_left(node->getRight());
    IPRangeNode * newRight = single_rotate_left(node->getRight());
    node->setRight(newRight);
    //then roate the whole tree.
    return single_rotate_right(node);
}


