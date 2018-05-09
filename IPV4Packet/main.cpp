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
#include <sstream>
#include <string>
#include <vector>

#include "IPRange.hpp"
#include "IPRangeNode.hpp"


using namespace std;




void verifyData(SourceNode* tree){
    string testCaseItem;
    ifstream dataFile;
    dataFile.open("./Res/packetfile.txt");
    ofstream resultFile;
    resultFile.open ("./Res/result_redundant.txt");
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
                unsigned int srcPacketInt = IPRange::ip_to_int(srcStr);
                unsigned int dstPacketInt = IPRange::ip_to_int(dstStr);
                if (tree->IsPacketAllow(srcPacketInt, dstPacketInt)) {
                    resultFile << "ALLOW\n";
                }else{
                    resultFile << "DENY\n";
                }
            }
        }
    }
    dataFile.close();
    resultFile.close();
}

SourceNode *createTree(string fileName){
    SourceNode * root = nullptr;
    string ruleItem;
    ifstream dataFile;
    dataFile.open(fileName);
    int redundantCount = 0;
    if (dataFile.is_open()) {
        while(getline(dataFile,ruleItem)) {
            istringstream ss(ruleItem);
            string srcStr, dstStr, actionStr;
            if (getline( ss, srcStr, ',' )&&
                getline( ss, dstStr, ',' )&&
                getline( ss, actionStr)){
                IPRange rangeSRC(srcStr);
                IPRange rangeDST(dstStr);
                bool action = actionStr=="ALLOW" ? true:false;
                if (root == nullptr) {
                    root = new SourceNode(rangeSRC, rangeDST, action);
                }else{
                    root->InsertNode(rangeSRC, rangeDST, action);
                    if (isRedudant) {
                        redundantCount += 1;
                    }else{
                        isRedudant = true;
                    }
                }
            }
        }
    }
    dataFile.close();
//    verifyData(root);
    cout<<"redundantCount: "<<redundantCount<<endl;
    return root;
}
int isRuleSetAllRedundant(SourceNode *root, string fileName){
    string ruleItem;
    ifstream dataFile;
    dataFile.open(fileName);
    int redundantCount = 0;
    if (dataFile.is_open()) {
        while(getline(dataFile,ruleItem)) {
            istringstream ss(ruleItem);
            string srcStr, dstStr, actionStr;
            if (getline( ss, srcStr, ',' )&&
                getline( ss, dstStr, ',' )&&
                getline( ss, actionStr)){
                IPRange rangeSRC(srcStr);
                IPRange rangeDST(dstStr);
                bool action = actionStr=="ALLOW" ? true:false;
                if (root == nullptr) {
                    root = new SourceNode(rangeSRC, rangeDST, action);
                }else{
                    root->InsertNode(rangeSRC, rangeDST, action);
                    if (isRedudant) {
                        redundantCount += 1;
                    }else{
                        isRedudant = true;
                    }
                }
            }
        }
    }
    dataFile.close();
//    verifyData(root);
    cout<<"Ruleset redundantCount: "<<redundantCount<<endl;
    return redundantCount;
}



int main(int argc, const char * argv[]) {
    string ruleSetAPath =  "./Res/RuleSetA.txt";
    string ruleSetBPath =  "./Res/RuleSetB.txt";
    SourceNode* rootA = createTree(ruleSetAPath);
    SourceNode* rootB = createTree(ruleSetBPath);
    isRuleSetAllRedundant(rootA, ruleSetBPath);
    isRuleSetAllRedundant(rootB, ruleSetAPath);
}

#endif

