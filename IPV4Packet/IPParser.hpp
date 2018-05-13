//
//  IPParser.hpp
//  IPV4Packet
//
//  Created by tab on 4/18/18.
//  Copyright © 2018 tab. All rights reserved.
//

#ifndef IPParser_hpp
#define IPParser_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Rule.hpp"

using namespace std;
const int CIDR_MAX = 33;

static void generateRuleAndTestCase(){
    ofstream ruleFile;
    ruleFile.open ("rules.txt");
    for (int i=0; i<10000; ++i) {
        char src [ 19 ] ;  // Longest possible IP address is 20 bytes)
        sprintf ( src, "%d.%d.%d.%d/%d", rand() & 0xFF, rand() & 0xFF,
                 rand() & 0xFF, rand() & 0xFF,rand()%32+1 ) ;
        char dst [19];
        sprintf(dst, "1.%d.%d.%d/%d", rand() & 0xFF,
                rand() & 0xFF, rand() & 0xFF,rand()%24+1);
        string action = rand()%2 == 1? "ALLOW":"DENY";
        ruleFile<<src<<","<<dst<<","<<action<<endl;
    }
    ruleFile<<"1.1.1.1/32,1.1.1.1/32,DENY";
    ruleFile.close();
    
    ofstream testcaseFile;
    testcaseFile.open("packets.txt");
    for (int i=0; i<10000; ++i) {
        char src [ 19 ] ;  // Longest possible IP address is 20 bytes)
        sprintf ( src, "%d.%d.%d.%d", rand() & 0xFF, rand() & 0xFF,
                 rand() & 0xFF, rand() & 0xFF ) ;
        char dst [19];
        sprintf(dst, "1.%d.%d.%d", rand() & 0xFF,
                rand() & 0xFF, rand() & 0xFF);
        testcaseFile<<src<<","<<dst<<endl;
    }
    testcaseFile.close();
    
}

class IPParser {
    
private:
//    array<vector<string>,CIDR_MAX> map;
//    vector<>
    vector<Rule> ruleList;
    
public:
    
    IPParser();
    IPParser(string fileName);
    
    ~IPParser();
    
    void parseData(string fileName);
    
    void verifyData();
    
    void printIP();
    
    bool isAllow(unsigned int srcPacketInt, unsigned int dstPacketInt);
};


#endif /* IPParser_hpp */
