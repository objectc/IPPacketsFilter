//
//  main.cpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue /Users/xuekaiyun/Documents/cs600_fianl/ruleset.txtaiyun. All rights reserved.
//
#ifndef MAIN
#define MAIN
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "IPRange.hpp"
#include "IPRangeNode.hpp"


using namespace std;

void writeToFile(IPRange src, IPRange dest, bool action,string fileName){
    ofstream dataFile;
    dataFile.open(fileName,ios::app);
    if(dataFile.is_open()){
        dataFile<<src.start<<","<<src.end<<","<<dest.start<<","<<dest.end<<","<<action<<endl;
    }
    dataFile.close();
}

void merge_result(const vector<IPRange> &src, const vector<IPRange> &dest, const vector<bool> act){
    vector<IPRange> newSrc = src;
    vector<IPRange> newDest = dest;
    vector<bool> newAct = act;
    cout<<"src size" << src.size() << "   newSrc size"<< newSrc.size()<<endl;
    
    for(int i = 0; i < newSrc.size()-1; i++){
        IPRange obj(newDest[i].start, newDest[i].end);
        for(int j = 1; j < newSrc.size(); j++){
            if(newSrc[i].start == newSrc[j].start && newSrc[i].end == newSrc[j].end && newAct[i] == newAct[j]){
                if(dest[i].start == dest[j].end+1){
                    obj.start = dest[j].start;
                    newAct.erase(newAct.begin()+i);
                    newAct.erase(newAct.begin()+j);
                    newSrc.erase(newSrc.begin()+i);
                    newSrc.erase(newSrc.begin()+j);
                    newDest.erase(newDest.begin()+i);
                    newDest.erase(newDest.begin()+j);
                    newAct.push_back(newAct[i]);
                    newSrc.push_back(newSrc[i]);
                    newDest.push_back(obj);
                    i--;
                    break;
                    
                }else if(dest[j].start == dest[i].end+1){
                    obj.start = dest[i].start;
                    newAct.erase(newAct.begin()+i);
                    newAct.erase(newAct.begin()+j);
                    newSrc.erase(newSrc.begin()+i);
                    newSrc.erase(newSrc.begin()+j);
                    newDest.erase(newDest.begin()+i);
                    newDest.erase(newDest.begin()+j);
                    newAct.push_back(newAct[i]);
                    newSrc.push_back(newSrc[i]);
                    newDest.push_back(obj);
                    i--;
                    break;
                }
            }
        }
    }
    vector<IPRange> realSrc = newSrc;
    vector<IPRange> realDest = newDest;
    vector<bool> realAct = newAct;
    for(int i = 0; i < realSrc.size()-1; i++){
        IPRange obj(realDest[i].start, realDest[i].end);
        for(int j = 1; j < realSrc.size(); j++){
            if(realDest[i].start == realDest[j].start && realDest[i].end == realDest[j].end && realAct[i] == realAct[j]){
                if(realSrc[i].start == realSrc[j].end+1){
                    obj.start = dest[j].start;
                    realAct.erase(realAct.begin()+i);
                    realAct.erase(realAct.begin()+j);
                    realSrc.erase(realSrc.begin()+i);
                    realSrc.erase(realSrc.begin()+j);
                    realDest.erase(realDest.begin()+i);
                    realDest.erase(realDest.begin()+j);
                    realAct.push_back(realAct[i]);
                    realDest.push_back(realDest[i]);
                    realSrc.push_back(obj);
                    i--;
                    break;
                    
                }else if(realSrc[j].start == realSrc[i].end+1){
                    obj.start = dest[i].start;
                    realAct.erase(realAct.begin()+i);
                    realAct.erase(realAct.begin()+j);
                    realSrc.erase(realSrc.begin()+i);
                    realSrc.erase(realSrc.begin()+j);
                    realDest.erase(realDest.begin()+i);
                    realDest.erase(realDest.begin()+j);
                    realAct.push_back(realAct[i]);
                    realDest.push_back(realDest[i]);
                    realSrc.push_back(obj);
                    i--;
                    break;
                }
            }
        }
    }
    cout<<"size :"<<realSrc.size()<<endl;
    for(int i = 0; i < realSrc.size(); i++){
        
        writeToFile(realSrc[i], realDest[i], realAct[i], "./Res/a.txt");
    }
    
}



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

SourceNode *createTree(string fileName,string fileNameToWrite){
    SourceNode * root = nullptr;
    string ruleItem;
    ifstream dataFile;
    dataFile.open(fileName);
    int redundantCount = 0;
    int lines = 0;
    if (dataFile.is_open()) {
        while(getline(dataFile,ruleItem)) {
            lines++;
            istringstream ss(ruleItem);
            string srcStr, dstStr, actionStr;
            if (getline( ss, srcStr, ',' )&&
                getline( ss, dstStr, ',' )&&
                getline( ss, actionStr)){
                IPRange rangeSRC(srcStr);
                IPRange rangeDST(dstStr);
                bool action = actionStr=="ALLOW\r" ? true:false;
                if (root == nullptr) {
                    root = new SourceNode(rangeSRC, rangeDST, action);

                }else{
                    root->InsertNode(rangeSRC, rangeDST, action);
                    if (isRedudant) {
                        redundantCount += 1;
                        
                    }else{
                        cout<<"lines: "<<lines<<endl;
                         writeToFile(rangeSRC, rangeDST, action, fileNameToWrite);
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
                bool action = actionStr=="ALLOW\r" ? true:false;
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


void equivalentCheck(SourceNode *root, string fileName){
    string ruleItem;
    ifstream dataFile;
    dataFile.open(fileName);
    if (dataFile.is_open()) {
        while(getline(dataFile,ruleItem)) {
            istringstream ss(ruleItem);
            string srcStr, dstStr, actionStr;
            if (getline( ss, srcStr, ',' )&&
                getline( ss, dstStr, ',' )&&
                getline( ss, actionStr)){
                IPRange rangeSRC(srcStr);
                IPRange rangeDST(dstStr);
                bool action = actionStr=="ALLOW\r" ? true:false;
                root->InsertNode(rangeSRC, rangeDST, action, true);
            }
        }
    }
    dataFile.close();
    cout<<diffActions.size()<<endl;
}

void test(SourceNode* rootA, SourceNode* rootB){
    int errorcnt = 0;
    int diffCnt = 0;
    for (int i=0; i<100000; ++i) {
        srand(time(0));
        char src [ 19 ] ;  // Longest possible IP address is 20 bytes)
        sprintf ( src, "%d.%d.%d.%d", rand() & 0xFF, rand() & 0xFF,
                 rand() & 0xFF, rand() & 0xFF ) ;
        char dst [19];
        sprintf(dst, "1.%d.%d.%d", rand() & 0xFF,
                rand() & 0xFF, rand() & 0xFF);
        
        unsigned int srcIP =  IPRange::ip_to_int(src);
        unsigned int dstIP =  IPRange::ip_to_int(dst);
//        dstIP = 84281887;
//        dstIP = 16777216 + rand()%(20971519-16777216);
        bool resA = rootA->IsPacketAllow(srcIP, dstIP);
        bool resB = rootB->IsPacketAllow(srcIP, dstIP);
        for (int i = 0; i<srcRanges.size(); ++i) {
            IPRange srcRange = srcRanges[i];
            if (srcRange.IsContain(srcIP)){
                IPRange dstRange = dstRanges[i];
                if (dstRange.IsContain(dstIP)){
                    diffCnt++;
                    if (resB == resA){
                        cout<<"diff error"<<endl;
                        errorcnt++;
                        break;
                    }
                }
            }
            if (resB!=resA){
                cout<<"equivalent error"<<endl;
                errorcnt++;
                break;
            }
        }
        
    }
    cout<<"diffcnt "<<diffCnt<<"errorcnt "<<errorcnt<<endl;
}


int main(int argc, const char * argv[]) {
    string ruleSetAPath =  "./Res/RuleSetA.txt";
    string ruleSetBPath =  "./Res/RuleSetB.txt";
    SourceNode* rootA = createTree(ruleSetAPath,"./Res/newRuleSetA.txt");
    SourceNode* rootB = createTree(ruleSetBPath,"./Res/newRuleSetB.txt");
//    isRuleSetAllRedundant(rootA, ruleSetBPath);
//    isRuleSetAllRedundant(rootB, ruleSetAPath);
    equivalentCheck(rootA, ruleSetBPath);
//    equivalentCheck(rootB, ruleSetAPath);
    merge_result(srcRanges,dstRanges,diffActions);
    test(rootA,rootB);
}

#endif

