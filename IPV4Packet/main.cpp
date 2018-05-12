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

void destMerge(vector<IPRange> &src, vector<IPRange> &dest, vector<bool> &act, int searchID = 0){
    vector<IPRange>::iterator srcItrator = src.begin() + searchID;
    vector<IPRange>::iterator destIterator = dest.begin() + searchID;
    vector<bool>::iterator actionIterator = act.begin() + searchID;
    
    IPRange &mrgSrc = *srcItrator;
    IPRange &mrgDest = *destIterator;
    bool mrgAction = *actionIterator;
    
    if(src.size() == searchID + 1)
        return;
    
    for(int i = searchID + 1; i < src.size(); i++)
    {
        srcItrator = src.begin() + i;
        destIterator = dest.begin() + i;
        actionIterator = act.begin() + i;
        if(*srcItrator == mrgSrc && *actionIterator == mrgAction)
        {
            //compare if the dst ip could be merged
            if(destIterator->start == mrgDest.end + 1)
            {
                mrgDest.end = destIterator->end;
                dest.erase(destIterator);
                src.erase(srcItrator);
                act.erase(actionIterator);
                //recursion
                destMerge(src, dest, act, searchID);
                return;
            }
            else if(destIterator->end + 1 == mrgDest.start)
            {
                mrgDest.start = destIterator->start;
                dest.erase(destIterator);
                src.erase(srcItrator);
                act.erase(actionIterator);
                //recursion
                destMerge(src, dest, act, searchID);
                return;
            }
        }
    }
    searchID++;
    destMerge(src, dest, act, searchID);
}

void merge_result(vector<IPRange> &src, vector<IPRange> &dest, vector<bool> act){
    vector<IPRange> newSrc;
    vector<IPRange> newDest;
    vector<bool> newAction;
    
    //Dest Merge
    
    //Src Merge
    
    src = newSrc;
    dest = newDest;
    act = newAction;
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

SourceNode *createTree(string fileName){
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
                bool action = actionStr=="ALLOW" ? true:false;
                if (root == nullptr) {
                    root = new SourceNode(rangeSRC, rangeDST, action);

                }else{
                    root->InsertNode(rangeSRC, rangeDST, action);
                    if (isRedudant) {
                        redundantCount += 1;
                        
                    }else{
                        //cout<<"lines: "<<lines<<endl;
                        string fileNameToWrite = fileName+"output";
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
                bool action = actionStr=="ALLOW" ? true:false;
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
    srand(time(0));
    for (int i=0; i<10000000; ++i) {
        unsigned int srcIP,dstIP;
        bool shouldEquivalent = (rand()%2 == 1);
        bool testAction = false;
        int randomIndex = 0;
        if (shouldEquivalent) {
            randomIndex = rand()%srcRanges.size();
            int diffSrc = (srcRanges[randomIndex].end-srcRanges[randomIndex].start);
            srcIP = diffSrc == 0 ? srcRanges[randomIndex].start : srcRanges[randomIndex].start+rand()%diffSrc;
            int diffDst = (dstRanges[randomIndex].end-dstRanges[randomIndex].start);
            dstIP = diffDst == 0 ? dstRanges[randomIndex].start : dstRanges[randomIndex].start+rand()%diffDst;
            testAction = diffActions[randomIndex];
        }else{
            char src [ 19 ] ;  // Longest possible IP address is 20 bytes)
            sprintf ( src, "%d.%d.%d.%d", rand() & 0xFF, rand() & 0xFF,
                     rand() & 0xFF, rand() & 0xFF ) ;
            char dst [19];
            sprintf(dst, "1.%d.%d.%d", rand() & 0xFF,
                    rand() & 0xFF, rand() & 0xFF);
    
            srcIP =  IPRange::ip_to_int(src);
            dstIP =  IPRange::ip_to_int(dst);
        }
        bool resA = rootA->IsPacketAllow(srcIP, dstIP);
        bool resB = rootB->IsPacketAllow(srcIP, dstIP);
        bool isInDiff = false;
        for (int i = 0; i<srcRanges.size(); ++i) {
            IPRange srcRange = srcRanges[i];
            if (srcRange.IsContain(srcIP)){
                IPRange dstRange = dstRanges[i];
                if (dstRange.IsContain(dstIP)){
                    isInDiff = true;
                    diffCnt++;
                    if (resB != testAction) {
                        cout<<"action error"<<endl;
                    }
                    if (resB == resA){
                        cout<<"diff error"<<endl;
                        errorcnt++;
                    }
                    break;
                }
            }
        }
        if (!isInDiff) {
            if (resB!=resA){
                cout<<"equivalent error"<<endl;
                errorcnt++;
                break;
            }
        }
        
    }
    cout<<"diffcnt "<<diffCnt<<" errorcnt "<<errorcnt<<endl;
}


int main(int argc, const char * argv[]) {
//    string ruleSetAPath =  "./Res/ruleset 2.txt";
    string ruleSetAPath =  "./Res/A.txt";
//    string ruleSetBPath =  "./Res/RuleTestB.txt";
    string ruleSetBPath =  "./Res/B.txt";
    SourceNode* rootA = createTree(ruleSetAPath);
    SourceNode* rootB = createTree(ruleSetBPath);
//    isRuleSetAllRedundant(rootA, ruleSetBPath);
//    isRuleSetAllRedundant(rootB, ruleSetAPath);
    equivalentCheck(rootA, ruleSetBPath);
//    equivalentCheck(rootB, ruleSetAPath);
    for(int i = 0; i < srcRanges.size(); i++)
    {
        cout<<"OLD("<<srcRanges[i].start<<","<<srcRanges[i].end<<"),("<<dstRanges[i].start<<","<<dstRanges[i].end<<")  "<<diffActions[i]<<endl;
    }
    destMerge(dstRanges,srcRanges,diffActions);
    destMerge(srcRanges,dstRanges,diffActions);
    destMerge(dstRanges,srcRanges,diffActions);
    destMerge(srcRanges,dstRanges,diffActions);
    destMerge(dstRanges,srcRanges,diffActions);
    destMerge(srcRanges,dstRanges,diffActions);
    for(int i = 0; i < srcRanges.size(); i++)
    {
        cout<<"NEW("<<srcRanges[i].start<<","<<srcRanges[i].end<<"),("<<dstRanges[i].start<<","<<dstRanges[i].end<<")  "<<diffActions[i]<<endl;
    }
    cout<<dstRanges.size();
    test(rootA,rootB);
}

#endif

