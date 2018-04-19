//
//  IPParser.cpp
//  IPV4Packet
//
//  Created by tab on 4/18/18.
//  Copyright © 2018 tab. All rights reserved.
//

#include "IPParser.hpp"
#include <sstream>
    
IPParser::IPParser() {
    parseData();
}
    
IPParser::~IPParser() {
}
    
void IPParser::parseData() {
    string ruleItem;
    ifstream dataFile;
    dataFile.open("rules.txt");
    if (dataFile.is_open()) {
        while(getline(dataFile,ruleItem)) {
            istringstream ss(ruleItem);
            string srcStr, dstStr, action;
            if (getline( ss, srcStr, ',' )&&
                getline( ss, dstStr, ',' )&&
                getline( ss, action)){
                IP src(srcStr);
                IP dst(dstStr);
                bool allow = action == "ALLOW" ? true:false;
                Rule rule(src, dst, allow);
                ruleList.push_back(rule);
            }
//            classifyIP(ip_address);
        }
    }
    dataFile.close();
}

void IPParser::verifyData(){
    string testCaseItem;
    ifstream dataFile;
    dataFile.open("packets.txt");
    ofstream resultFile;
    resultFile.open ("result.txt");
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

    
void IPParser::printIP() {
    
//    int i,j;
//    cout << endl;
//    
//    for(i = 0; i < 33; i++) {
//        if (map[i].size() == 0) {
//            continue;
//        }
//        else {
//            cout << "IPs with CIDR = " << i << endl;
//            
//            for (j = 0; j < map[i].size(); j++)
//                cout << map[i][j] << endl;
//        }
//        cout << endl << endl;
//    }
}
