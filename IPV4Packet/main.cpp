//
//  main.cpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue /Users/xuekaiyun/Documents/cs600_fianl/ruleset.txtaiyun. All rights reserved.
//
#ifndef MAIN
#define MAIN
#include "Rule.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "SrcTree.hpp"
#include "RangeNode.hpp"


using namespace std;

static void preorder_traversal(RangeNode *root);
int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    fstream f_stream;
    string s;
    f_stream.open("./rules.txt", ios::in);
    SrcTree tree = SrcTree();
    int loopTime = 0;
    while (!f_stream.eof()) {
        //cout<<"IP info"<<endl;
        f_stream>>s;
        Rule rule(s);
//        cout<<"--------------------------"<<endl;
//        cout<<"DO:-------->"<<endl;
        tree.root = tree.InsertNode(rule, tree.root);
//        cout<<endl<<"[[[[-----tree--------]]]]"<<endl;
//        preorder_traversal(tree.root);
        
//        cout<<endl<<"---loop---"<<loopTime<<endl<<endl;
        loopTime++;
    }
//    cout<<"Main----->"<<tree.root<<endl;
    f_stream.close();
//    cout<<loopTime;
    preorder_traversal(tree.root);
}

static void preorder_traversal(RangeNode *root)
{
    if(!root)
        return ;
    if(root){
        cout<<"["<< root->ip.intIP<<","<<root->ip.IPEnd << "]   height:" << root->high << endl;
        if(root->left != nullptr)
        {
            cout<<"left:"<<endl;
            preorder_traversal(root->left);
            cout<<"back to"<<"["<< root->ip.intIP<<","<<root->ip.IPEnd << "]"<<endl;
        }
        if(root->right != nullptr)
        {
            cout<<"right:"<<endl;
            preorder_traversal(root->right);
            cout<<"back to"<<"["<< root->ip.intIP<<","<<root->ip.IPEnd << "]"<<endl;
        }
    }
}

#endif

