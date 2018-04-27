////
////  IP.hpp
////  CS600
////
////  Created by Xue Kaiyun on 2018/4/21.
////  Copyright © 2018年 Xue Kaiyun. All rights reserved.
////
//
//#ifndef IP_hpp
//#define IP_hpp
//
//#include <stdio.h>
//#include <string>
//#include <iostream>
//
//class IP{
//public:
//    unsigned int intIP;
//    char cidr;
//    std::string ip;
//    IP(std::string const& ipStr);
//    IP();
//    //    ~IP();
//    
//    bool IsContain(IP ip);
//    
//    /*
//     1.a may contain b or b conatin a.
//     2. For the output result, there are 4 situations:
//        i.  outLeft is null but outMid and outRight are not.
//            e.g. a = 0-10, b = 0-5
//            result: left = null mid = 0-5 right = 5-10
//        ii. outRight is null but outMid and outLeft are not.
//            e.g. a = 0-10, b = 5-10
//            result: left = 0-5 mid = 5-10 right = null
//        iii. outLeft and outRight are null but outMid is not.
//            e.g. a = 0-10, b = 0-10
//            result: left = null mid = 0-10 right = null
//        iv. All are not null.
//            e.g. a = 0-10, b = 4-7
//            result: left = 0-4 mid = 4-7 right = 4-10
//     */
//    static void Split(const IP a, const IP b, IP* &outLeft, IP* &outMid, IP* &outRight)
//    {
//        //lll
//    };
//};
//
//#endif /* IP_hpp */

