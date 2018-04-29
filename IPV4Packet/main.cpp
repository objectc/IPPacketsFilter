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


using namespace std;

unsigned int ip_to_int (const std::string &ip){
    /* The return value. */
    unsigned v = 0;
    /* The count of the number of bytes processed. */
    int i;
    /* A pointer to the next digit to process. */
    const char * start;
    
    start = ip.c_str();
    for (i = 0; i < 4; i++) {
        /* The digit being processed. */
        char c;
        /* The value of this byte. */
        int n = 0;
        while (1) {
            c = * start;
            start++;
            if (c >= '0' && c <= '9') {
                n *= 10;
                n += c - '0';
            }
            /* We insist on stopping at "." if we are still parsing
             the first, second, or third numbers. If we have reached
             the end of the numbers, we will allow any character. */
            else if ((i < 3 && c == '.') || i == 3) {
                break;
            }
            else {
                std::cout << "Incorrent IP address: " << ip << std::endl;
                return 0;
            }
        }
        if (n >= 256) {
            std::cout << "Incorrent IP address: " << ip << std::endl;
            return 0;
        }
        v *= 256;
        v += n;
    }
    return v;
}

/*
void verifyData(SrcTree* tree){
    string testCaseItem;
    ifstream dataFile;
    dataFile.open("./Res/packetfile.txt");
    ofstream resultFile;
    resultFile.open ("./Res/result_1D.txt");
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
                if (tree->Search1Dim(srcPacketInt, tree->root)) {
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
*/

int main(int argc, const char * argv[]) {
    cout<<"true is "<<true<<endl;
    // insert code here...
    cout << "Hello, World!\n";
    fstream f_stream;
    string s;
    f_stream.open("./Res/ruleset 2.txt", ios::in);
//    SrcTree tree = SrcTree();
    int loopTime = 0;
    while (!f_stream.eof()) {
        //cout<<"IP info"<<endl;
        f_stream>>s;
//        Rule rule(s);
//        cout<<"--------------------------"<<endl;
//        cout<<"DO:-------->"<<endl;
//        tree.InsertNode(rule, tree.root);
//        cout<<endl<<"[[[[-----tree--------]]]]"<<endl;
//        tree.Print(tree.root);
        
//        cout<<endl<<"---loop---"<<loropTime<<endl<<endl;
        loopTime++;
    }
//    cout<<"Main----->"<<tree.root<<endl;
    f_stream.close();
//    cout<<loopTime;
//    tree.Print(tree.root);
//    verifyData(&tree);
}

#endif

