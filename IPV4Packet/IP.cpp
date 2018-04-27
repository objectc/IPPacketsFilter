////
////  IP.cpp
////  CS600
////
////  Created by Xue Kaiyun on 2018/4/21.
////  Copyright © 2018年 Xue Kaiyun. All rights reserved.
////
//
//#include "IP.hpp"
//#include "Rule.hpp"
//IP::IP(std::string const& ipStr){
//    std::string delimiter = "/";
//    size_t pos = 0;
//    std::string ip;
//    pos = ipStr.find(delimiter);
//    ip = ipStr.substr(0, pos);
//    this->cidr = stoi(ipStr.substr(pos+1)) - '\0';
//    
//    // Storing the IP
//    if(cidr > 32 || cidr < 0) {
//        std::cout << "Incorrent IP address: " << ip << std::endl << std::endl;
//        return;
//    }
//    this->intIP = ip_to_int(ip);
//    this->ip = ipStr;
//}
//IP::IP(){
//    
//}
//
//bool IP::IsContain(IP ip)
//{
//    return true;
//}

