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

void verifyData(SrcTree* tree){
    string testCaseItem;
    ifstream dataFile;
    dataFile.open("packetfile.txt");
    ofstream resultFile;
    resultFile.open ("result1.txt");
    if (dataFile.is_open()) {
        while(getline(dataFile,testCaseItem)) {
            istringstream ss(testCaseItem);
            string srcStr, dstStr, skip1;
            if (getline( ss, srcStr, ',' )&&
                getline( ss, dstStr)){
                std::string delimiter = ",";
                size_t pos = 0;
                string ip;
                pos = srcStr.find(delimiter);
                string firstPart = srcStr.substr(0, pos);
                //              No incoming packet with a=1 should be allowed
                if (firstPart == "1") {
                    resultFile<<"DENY\n";
                    continue;
                }
                unsigned int srcPacketInt = ip_to_int(srcStr);
                unsigned int dstPacketInt = ip_to_int(dstStr);
                bool founded = false;
                for (vector<Rule>::iterator iter = ruleList.begin(); iter!=ruleList.end(); ++iter) {
                    if (iter->isContain(srcPacketInt, dstPacketInt)){
                        if (iter->isAllow(srcPacketInt, dstPacketInt)) {
                            //                            cout<<"src"<<iter->src.intIP<<endl;
                            //                            cout<<iter->src.cidr;
                            resultFile << "ALLOW\n";
                            founded = true;
                            break;
                        }else{
                            break;
                        }
                    }
                }
                if (!founded) {
                    resultFile<<"DENY\n";
                }
            }
            //            classifyIP(ip_address);
        }
    }
    dataFile.close();
    resultFile.close();
}

int main(int argc, const char * argv[]) {
    cout<<"true is "<<true<<endl;
    // insert code here...
    cout << "Hello, World!\n";
    fstream f_stream;
    string s;
    f_stream.open("./IPV4Packet/rules.txt", ios::in);
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
        tree.Print(tree.root);
        
        cout<<endl<<"---loop---"<<loopTime<<endl<<endl;
        loopTime++;
    }
//    cout<<"Main----->"<<tree.root<<endl;
    f_stream.close();
//    cout<<loopTime;
    tree.Print(tree.root);
}

#endif

