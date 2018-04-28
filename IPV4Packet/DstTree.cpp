//
//  DstTree.cpp
//  cs600
//
//  Created by Xue Kaiyun on 2018/4/27.
//  Copyright © 2018年 xbai9. All rights reserved.
//

#include "DstTree.hpp"
#include "RangeNode.hpp"

DstTree::DstTree()
{
    root = nullptr;
}

RangeNode* DstTree::SearchPos(IPRange ip, RangeNode* searchRoot)
{
    if(searchRoot == nullptr)
    {
        //        cout<<"ROOT FIND!"<<endl;
        return searchRoot;
    }
    else if(searchRoot->dstIP.IsContain(ip))
    {
        //        cout<<"be Contained"<<endl;
        return searchRoot;
    }
    else if(ip.IsContain(searchRoot->dstIP))
    {
        //        cout<<"Countains"<<endl;
        return searchRoot;
    }
    else if(ip.intIP > searchRoot->dstIP.intIP)
    {
        if(searchRoot->right == nullptr)
        {
            //            cout<<"find! on the right"<<endl;
            return searchRoot;
        }
        else
        {
            //            cout<<"right"<<endl;
            return SearchPos(ip, searchRoot->right);
        }
    }
    else
    {
        if(searchRoot->left == nullptr)
        {
            //            cout<<"find! on the left"<<endl;
            return searchRoot;
        }
        else
        {
            //            cout<<"left"<<endl;
            return SearchPos(ip, searchRoot->left);
        }
    }
}
int DstTree::hight(RangeNode * root)
{
    if(!root)
        return -1;
    else
        return root->high;
}
int DstTree::max(int l, int r)
{
    return (l > r ? l : r);
}

RangeNode* DstTree::single_rotate_left(RangeNode *root)
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

RangeNode* DstTree::single_rotate_right(RangeNode * root)
{
    RangeNode * tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    root->high = max(hight(root->left), hight(root->right)) + 1;
    tmp->high = max(hight(tmp->left), hight(tmp->right)) + 1;
    return tmp;
}

RangeNode* DstTree::double_rotate_left(RangeNode * root)
{
    //first rotate right child tree.
    root->left = single_rotate_right(root->left);
    
    //then rotate the whole tree.
    return single_rotate_left(root);
}

RangeNode* DstTree::double_rotate_right(RangeNode * root)
{
    //first rotate left child tree.
    root->right = single_rotate_left(root->right);
    //then roate the whole tree.
    return single_rotate_right(root);
}
RangeNode* DstTree:: InsertNode( Rule rule, RangeNode* searchRoot)
{
    //    cout<<"searchRoot:";
    //    searchRoot->ip.Print();
    //    cout<<"rule: ";
    //    rule.Print();
    IPRange newIP;
    newIP = rule.dst;
    newNode = new RangeNode(rule);
    newNode->action = rule.allow;
    
    if(searchRoot == nullptr)
    {
        return newNode;
    }
    else if(searchRoot->dstIP.IsContain(newIP) || newIP.IsContain(searchRoot->dstIP))
    {
        // cout<<"contain"<<endl;
        IPRange *left = nullptr, *right = nullptr, *mid = nullptr;
        IPRange::Split(newIP, searchRoot->dstIP, left, mid, right);
        searchRoot->dstIP = *mid;
        if(left != nullptr)
        {
            // cout<<"Recursion Start!"<<endl<<endl;
            Rule* leftRule = new Rule(rule.dst,*left, rule.allow);
            root = InsertNode(*leftRule, root);
            //            cout<<"Recursion End!"<<endl;
            //            cout<<"Back To:";
            //  searchRoot->ip.Print();
        }
        if(right != nullptr)
        {
            // cout<<"Recursion Start!"<<endl<<endl;
            Rule* rightRule = new Rule(rule.dst,*right, rule.allow);
            root =  InsertNode(*rightRule, root);
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
    else if(newIP.intIP > searchRoot->dstIP.IPEnd)
    {
        // cout<<"right"<<endl<<endl;
        RangeNode *tmp;
        //        searchRoot->right = InsertNode(rule, searchRoot->right);
        tmp = InsertNode(rule, searchRoot->right);
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
            if(searchRoot->right->dstIP.IPEnd < newNode->dstIP.intIP)
            {
                searchRoot = single_rotate_right(searchRoot);
            }
            else if (searchRoot->right->dstIP.intIP > newNode->dstIP.IPEnd)
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
    else if(newIP.IPEnd < searchRoot->dstIP.intIP)
    {
        //cout<<"left"<<endl<<endl;
        //        searchRoot->left = InsertNode(rule, searchRoot->left);
        RangeNode *tmp;
        tmp = InsertNode(rule, searchRoot->left);
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
            if(searchRoot->left->dstIP.intIP > newNode->dstIP.IPEnd)
            {
                //cout<<"single_rotate_left"<<endl;
                searchRoot = single_rotate_left(searchRoot);
            }
            else if(searchRoot->left->dstIP.IPEnd < newNode->dstIP.intIP)
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
    
    searchRoot->high = max(hight(searchRoot->left), hight(searchRoot->right)) + 1;
    return searchRoot;
}
void DstTree::Print(RangeNode *root)
{
    if(!root)
        return ;
    if(root){
        cout<<"["<< root->dstIP.intIP<<","<<root->dstIP.IPEnd << "]   height:" << root->high << endl;
        if(root->left != nullptr)
        {
            cout<<"left:"<<endl;
            Print(root->left);
            cout<<"back to"<<"["<< root->dstIP.intIP<<","<<root->dstIP.IPEnd << "]"<<endl;
        }
        if(root->right != nullptr)
        {
            cout<<"right:"<<endl;
            Print(root->right);
            cout<<"back to"<<"["<< root->dstIP.intIP<<","<<root->dstIP.IPEnd << "]"<<endl;
        }
    }
}
DstTree* DstTree::CpySelf()
{
    DstTree* newTree = new DstTree();
    CpyNode(root, newTree->root);
    return newTree;
}
void DstTree:: CpyNode(RangeNode* node, RangeNode*& newN)
{
    if(node == nullptr)
        return;
    newN = new RangeNode(node->srcIP, node->dstIP, node->action, node->high);
    CpyNode(node->left, newN->left);
    CpyNode(node->right, newN->right);
}



