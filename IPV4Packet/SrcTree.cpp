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
    if(src > searchRoot->srcIP.IPEnd)
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
    else if(src < searchRoot->srcIP.intIP)
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
RangeNode* SrcTree:: InsertNode(Rule rule, RangeNode *searchRoot)
{
    RangeNode *node = new RangeNode(rule);
    return InsertNode(node, searchRoot);
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
//    else if(rule.src.intIP == searchRoot->ip.IPEnd)
//    {
//       // cout<<"connect"<<endl;
//        IPRange left = IPRange(searchRoot->ip.intIP, searchRoot->ip.IPEnd - 1);
//        IPRange mid = IPRange(searchRoot->ip.IPEnd, rule.src.intIP); // signle point
//        IPRange right = IPRange(rule.src.intIP + 1, rule.src.IPEnd);
//        searchRoot->ip = mid;
//        Rule* leftRule = new Rule(rule.dst,left, rule.allow);
//        searchRoot = InsertNode(*leftRule, searchRoot);
//        Rule* rightRule = new Rule(rule.dst,right, rule.allow);
//        searchRoot =  InsertNode(*rightRule, searchRoot);
//    }
//    else if(rule.src.IPEnd == searchRoot->ip.intIP)
//    {
//       // cout<<"connect"<<endl;
//        IPRange left = IPRange(rule.src.intIP, rule.src.IPEnd - 1);
//        IPRange mid = IPRange(searchRoot->ip.IPEnd, rule.src.intIP); // signle point
//        IPRange right = IPRange(searchRoot->ip.intIP + 1, searchRoot->ip.IPEnd);
//        searchRoot->ip = mid;
//        Rule* leftRule = new Rule(rule.dst,left, rule.allow);
//        searchRoot = InsertNode(*leftRule, searchRoot);
//        Rule* rightRule = new Rule(rule.dst,right, rule.allow);
//        searchRoot =  InsertNode(*rightRule, searchRoot);
//    }
    else if(newIP.intIP > searchRoot->srcIP.IPEnd)
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
            if(searchRoot->right->srcIP.IPEnd < newNode->srcIP.intIP)
            {
                searchRoot = single_rotate_right(searchRoot);
            }
            else if (searchRoot->right->srcIP.intIP > newNode->srcIP.IPEnd)
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
    else if(newIP.IPEnd < searchRoot->srcIP.intIP)
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
            if(searchRoot->left->srcIP.intIP > newNode->srcIP.IPEnd)
            {
                //cout<<"single_rotate_left"<<endl;
                searchRoot = single_rotate_left(searchRoot);
            }
            else if(searchRoot->left->srcIP.IPEnd < newNode->srcIP.intIP)
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
        cout<<"bengle"<<endl;
        
    }
    
    searchRoot->high = max(hight(searchRoot->left), hight(searchRoot->right)) + 1;
    return searchRoot;
}
void SrcTree::Print(RangeNode *root)
{
    if(!root)
        return ;
    if(root){
        cout<<"["<< root->srcIP.intIP<<","<<root->srcIP.IPEnd << "]   height:" << root->high << endl;
        cout<<"----------SUBTREE----------"<<endl;
        root->childTree->Print(root->childTree->root);
        cout<<"----------SUBTREE END----------"<<endl;
        if(root->left != nullptr)
        {
            cout<<"left:"<<endl;
            Print(root->left);
            cout<<"back to"<<"["<< root->srcIP.intIP<<","<<root->srcIP.IPEnd << "]"<<endl;
        }
        if(root->right != nullptr)
        {
            cout<<"right:"<<endl;
            Print(root->right);
            cout<<"back to"<<"["<< root->srcIP.intIP<<","<<root->srcIP.IPEnd << "]"<<endl;
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


