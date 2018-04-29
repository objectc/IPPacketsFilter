//
//  RangeTree.cpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/19.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#include "SrcTree.hpp"
//#include "Rule.hpp"
//#include "RangeNode.hpp"
SrcTree::SrcTree()
{
    root = nullptr;
}

bool SrcTree::SearchPos(int src, int dst, RangeNode* searchRoot)
{
    if(src > searchRoot->srcIP.end)
    {
        if(searchRoot->right == nullptr)
        {
            throw "out!!";
        }
        else
        {
            return SearchPos(src , dst , searchRoot->right);
        }
    }
    else if(src < searchRoot->srcIP.start)
    {
        if(searchRoot->left == nullptr)
        {
            throw "out!!";
        }
        else
        {
            return SearchPos(src, dst, searchRoot->left);
        }
    }
    else
    {
        return  searchRoot->childTree->SearchPos(dst, searchRoot->childTree->root);
    }
}
int SrcTree::hight(RangeNode * root)
{
    if(!root)
        return -1;
    else
        return root->high;
}
int SrcTree::max(int l, int r)
{
    return (l > r ? l : r);
}

RangeNode* SrcTree::single_rotate_left(RangeNode *root)
{
    RangeNode * tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    
    //when finished rotate, change the node's height
    root->high = max(hight(root->left), hight(root->right)) + 1;
    tmp->high = max(hight(tmp->left), hight(tmp->right)) + 1;
    //return the new tree root node.
    return tmp;
}

RangeNode* SrcTree::single_rotate_right(RangeNode * root)
{
    RangeNode * tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    root->high = max(hight(root->left), hight(root->right)) + 1;
    tmp->high = max(hight(tmp->left), hight(tmp->right)) + 1;
    return tmp;
}

RangeNode* SrcTree::double_rotate_left(RangeNode * root)
{
    //first rotate right child tree.
    root->left = single_rotate_right(root->left);
    
    //then rotate the whole tree.
    return single_rotate_left(root);
}

RangeNode* SrcTree::double_rotate_right(RangeNode * root)
{
    //first rotate left child tree.
    root->right = single_rotate_left(root->right);
    //then roate the whole tree.
    return single_rotate_right(root);
}
RangeNode* SrcTree:: InsertNode(Rule rule, RangeNode *&searchRoot)
{
    RangeNode *node = new RangeNode(rule);
//    return InsertNode(node, searchRoot);
    InsertSubNode(node, searchRoot);
    return nullptr;
}
RangeNode* SrcTree:: InsertNode( RangeNode* node , RangeNode* searchRoot)
{
    //    cout<<"searchRoot:";
    //    searchRoot->ip.Print();
    //    cout<<"rule: ";
    //    rule.Print();
    IPRange newIP;
    newIP = node->srcIP;
    newNode = node;
    
    if(searchRoot == nullptr)
    {
        // cout<<"find! Insert"<<endl;
        //dest:
        //SrcTree * newDestTree = new SrcTree();
        //newNode->childTree = newDestTree;
        DstTree *newDstTree = new DstTree();
        newNode->childTree = newDstTree;
        Rule rule = Rule(node->dstIP, node->srcIP, node->action);
        newDstTree->root = newDstTree->InsertNode(rule, newDstTree->root);
        return newNode;
    }
    else if(searchRoot->srcIP.IsContain(newIP))
    {
        // cout<<"contain"<<endl;
        IPRange *left = nullptr, *right = nullptr, *mid = nullptr;
        IPRange::Split(newIP, searchRoot->srcIP, left, mid, right);
        searchRoot->srcIP = *mid;
        Rule midR = Rule(node->dstIP, *mid, node->action);
        
        searchRoot->childTree->root = searchRoot->childTree->InsertNode(midR, searchRoot->childTree->root);
        if(left != nullptr)
        {
            // cout<<"Recursion Start!"<<endl<<endl;
            RangeNode* leftNode = searchRoot->CpyNode();
            leftNode->srcIP = *left;
            root = InsertNode(leftNode, root);
            //            cout<<"Recursion End!"<<endl;
            //            cout<<"Back To:";
            //  searchRoot->ip.Print();
        }
        if(right != nullptr)
        {
            // cout<<"Recursion Start!"<<endl<<endl;
            RangeNode* rightNode = searchRoot->CpyNode();
            rightNode->srcIP = *right;
            root = InsertNode(rightNode, root);
            
            //            cout<<"Recursion End!"<<endl;
            //            cout<<"Back To:";
            //  searchRoot->ip.Print();
        }
        return root;
    }
    else if(newIP.IsContain(searchRoot->srcIP))
    {
        // cout<<"contain"<<endl;
        IPRange *left = nullptr, *right = nullptr, *mid = nullptr;
        IPRange::Split(newIP, searchRoot->srcIP, left, mid, right);
        searchRoot->srcIP = *mid;
        Rule midR = Rule(node->dstIP, *mid, node->action);
        searchRoot->childTree->root = searchRoot->childTree->InsertNode(midR, searchRoot->childTree->root);
        if(left != nullptr)
        {
            // cout<<"Recursion Start!"<<endl<<endl;
            Rule leftRule = Rule(node->dstIP, *left, node->action);
            root = InsertNode(leftRule, root);
            //            cout<<"Recursion End!"<<endl;
            //            cout<<"Back To:";
            //  searchRoot->ip.Print();
        }
        if(right != nullptr)
        {
            // cout<<"Recursion Start!"<<endl<<endl;
            Rule rightRule = Rule(node->dstIP, *right, node->action);
            root = InsertNode(rightRule, root);
            //            cout<<"Recursion End!"<<endl;
            //            cout<<"Back To:";
            //  searchRoot->ip.Print();
        }
        return root;
    }
    //    else if(rule.src.start == searchRoot->ip.end)
    //    {
    //       // cout<<"connect"<<endl;
    //        IPRange left = IPRange(searchRoot->ip.start, searchRoot->ip.end - 1);
    //        IPRange mid = IPRange(searchRoot->ip.end, rule.src.start); // signle point
    //        IPRange right = IPRange(rule.src.start + 1, rule.src.end);
    //        searchRoot->ip = mid;
    //        Rule* leftRule = new Rule(rule.dst,left, rule.allow);
    //        searchRoot = InsertNode(*leftRule, searchRoot);
    //        Rule* rightRule = new Rule(rule.dst,right, rule.allow);
    //        searchRoot =  InsertNode(*rightRule, searchRoot);
    //    }
    //    else if(rule.src.end == searchRoot->ip.start)
    //    {
    //       // cout<<"connect"<<endl;
    //        IPRange left = IPRange(rule.src.start, rule.src.end - 1);
    //        IPRange mid = IPRange(searchRoot->ip.end, rule.src.start); // signle point
    //        IPRange right = IPRange(searchRoot->ip.start + 1, searchRoot->ip.end);
    //        searchRoot->ip = mid;
    //        Rule* leftRule = new Rule(rule.dst,left, rule.allow);
    //        searchRoot = InsertNode(*leftRule, searchRoot);
    //        Rule* rightRule = new Rule(rule.dst,right, rule.allow);
    //        searchRoot =  InsertNode(*rightRule, searchRoot);
    //    }
    else if(newIP.start > searchRoot->srcIP.end)
    {
        // cout<<"right"<<endl<<endl;
        RangeNode *tmp;
        //        searchRoot->right = InsertNode(rule, searchRoot->right);
        tmp = InsertNode(node, searchRoot->right);
        if(tmp == root)
            return root;
        searchRoot->right = tmp;
        // cout<<"back to"<<endl;
        //searchRoot->ip.Print();
        if((hight(searchRoot->right) - hight(searchRoot->left)) == 2){
            // cout<<"-----------ROTATE--------------"<<endl;
            //            if(searchRoot->right->left!=nullptr && searchRoot->right->right != nullptr && searchRoot ->right->high == 1)
            //            {
            //                return searchRoot;
            //            }
            if(searchRoot->right->srcIP.end < newNode->srcIP.start)
            {
                searchRoot = single_rotate_right(searchRoot);
            }
            else if (searchRoot->right->srcIP.start > newNode->srcIP.end)
            {
                searchRoot = double_rotate_right(searchRoot);
            }
            else
            {
                throw "dengyule";
            }
            //            cout<<"---SUBTREE---"<<endl;
            //            preorder_traversal(searchRoot);
            //            cout<<"subtree end //////"<<endl<<endl;
        }
    }
    else if(newIP.end < searchRoot->srcIP.start)
    {
        //cout<<"left"<<endl<<endl;
        //        searchRoot->left = InsertNode(rule, searchRoot->left);
        RangeNode *tmp;
        tmp = InsertNode(node, searchRoot->left);
        if(tmp == root)
            return root;
        searchRoot->left = tmp;
        //cout<<"back to"<<endl;
        //        searchRoot->ip.Print();
        if((hight(searchRoot->left) - hight(searchRoot->right)) == 2)
        {
            //            if(searchRoot->left->left!=nullptr && searchRoot->left->right != nullptr && searchRoot ->left->high == 1)
            //            {
            //                return searchRoot;
            //            }
            //            cout<<"-----------ROTATE--------------"<<endl;
            //            cout<<"search left ip:"; searchRoot->left->ip.Print();
            //            cout<<"new node:"; newNode->ip.Print();
            if(searchRoot->left->srcIP.start > newNode->srcIP.end)
            {
                //cout<<"single_rotate_left"<<endl;
                searchRoot = single_rotate_left(searchRoot);
            }
            else if(searchRoot->left->srcIP.end < newNode->srcIP.start)
            {
                //cout<<"double_rotate_left"<<endl;
                searchRoot = double_rotate_left(searchRoot);
            }
            else
            {
                throw "dengyule";
            }
            //            cout<<"---SUBTREE---"<<endl;
            //            preorder_traversal(searchRoot);
            //            cout<<"subtree end //////"<<endl<<endl;
            
        }
    }
    else
    {
        //        cout<<"bengle"<<endl;
        // cout<<"contain"<<endl;
        IPRange *left = nullptr, *right = nullptr, *mid = nullptr;
        IPRange::Split(newIP, searchRoot->srcIP, left, mid, right);
        Rule midR = Rule(node->dstIP, *mid, node->action);
        
        searchRoot->childTree->root = searchRoot->childTree->InsertNode(midR, searchRoot->childTree->root);
        if(left != nullptr)
        {
            // cout<<"Recursion Start!"<<endl<<endl;
            RangeNode* leftNode;
            if (searchRoot->srcIP.IsContain(*left)) {
                leftNode = searchRoot->CpyNode();
                leftNode->srcIP = *left;
            }else{
                leftNode = new RangeNode(*left, node->dstIP, node->action);
            }
            root = InsertNode(leftNode, root);
        }
        if(right != nullptr)
        {
            // cout<<"Recursion Start!"<<endl<<endl;
            RangeNode* rightNode;
            if (searchRoot->srcIP.IsContain(*right)) {
                rightNode = searchRoot->CpyNode();
                rightNode->srcIP = *right;
            }else{
                rightNode = new RangeNode(*right, node->dstIP, node->action);
            }
            root = InsertNode(rightNode, root);
        }
        searchRoot->srcIP = *mid;
        return root;
        
    }
    
    searchRoot->high = max(hight(searchRoot->left), hight(searchRoot->right)) + 1;
    return searchRoot;
}



void SrcTree::Print(RangeNode *root)
{
    if(!root)
        return ;
    if(root){
        cout<<"["<< root->srcIP.start<<","<<root->srcIP.end << "]   height:" << root->high << endl;
        cout<<"----------SUBTREE----------"<<endl;
        root->childTree->Print(root->childTree->root);
        cout<<"----------SUBTREE END----------"<<endl;
        if(root->left != nullptr)
        {
            cout<<"left:"<<endl;
            Print(root->left);
            cout<<"back to"<<"["<< root->srcIP.start<<","<<root->srcIP.end << "]"<<endl;
        }
        if(root->right != nullptr)
        {
            cout<<"right:"<<endl;
            Print(root->right);
            cout<<"back to"<<"["<< root->srcIP.start<<","<<root->srcIP.end << "]"<<endl;
        }
    }
}
SrcTree* SrcTree::CpySelf()
{
    SrcTree* newTree = new SrcTree();
    CpyNode(root, newTree->root);
    return newTree;
}
void SrcTree:: CpyNode(RangeNode* node, RangeNode*& newN)
{
    if(node == nullptr)
        return;
    newN = node->CpyNode();
    CpyNode(node->left, newN->left);
    CpyNode(node->right, newN->right);
}


void SrcTree::InsertSubNode(RangeNode *node, RangeNode* &searchRoot){
    IPRange newIP;
    newIP = node->srcIP;
    if(searchRoot == nullptr)
    {
        searchRoot = node;
    }
    else{
        if (newIP.start>searchRoot->srcIP.end){
            InsertSubNode(node, searchRoot->right);
        }
        else if (newIP.end<searchRoot->srcIP.start){
            InsertSubNode(node, searchRoot->left);
        }
        else{
            IPRange *left = nullptr, *right = nullptr, *mid = nullptr;
            IPRange::Split(newIP, searchRoot->srcIP, left, mid, right);
            
            if(left != nullptr)
            {
                RangeNode* leftNode = new RangeNode();
                leftNode->srcIP = *left;
                // if original contain, use original's action and dstTree
                if (searchRoot->srcIP.IsContain(*left)) {
                    leftNode->action = searchRoot->action;
                }else{
                    leftNode->action = node->action;
                }
                InsertSubNode(leftNode, searchRoot->left);
            }
            if(right != nullptr)
            {
                RangeNode* rightNode = new RangeNode();
                rightNode->srcIP = *right;
                if (searchRoot->srcIP.IsContain(*right)) {
                    rightNode->action = searchRoot->action;
                }else{
                    rightNode->action = node->action;
                }
                InsertSubNode(rightNode, searchRoot->right);
            }
            
            //        TODO:memory leak
            searchRoot->srcIP = *mid;
        }
    }
}

bool SrcTree::Search1Dim(int src, RangeNode* searchRoot){
    if(searchRoot == nullptr)
    {
        throw "Search1Dim No Rule Found!";
    }
    if(src > searchRoot->srcIP.end)
    {
        return Search1Dim(src , searchRoot->right);
    }
    else if(src < searchRoot->srcIP.start)
    {
        return Search1Dim(src, searchRoot->left);
    }else{
        return searchRoot->action;
    }
}
