//
//  IPAddress.hpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#ifndef IPAddress_hpp
#define IPAddress_hpp

#include <string>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class IPRange
{
public:
    // minIP <= ip < maxIP
    static unsigned int ip_to_int (const std::string &ip);
    unsigned int start;
    unsigned int end;
    IPRange(const unsigned int start, const unsigned int end);
    IPRange(const string &ruleStr);
    bool IsContain(IPRange b) const;
    bool IsContain(unsigned int ip);
    static void Split(IPRange a, IPRange b, IPRange*& left, IPRange*& mid, IPRange*& right)
    {
        std::vector<unsigned int> ipVec;
        ipVec.push_back(a.start);
        ipVec.push_back(a.end);
        ipVec.push_back(b.start);
        ipVec.push_back(b.end);
        std::sort(ipVec.begin(), ipVec.end());
        if (!(ipVec[1]-ipVec[0]<1)) {
            left = new IPRange(ipVec[0], ipVec[1]-1);
        }
        mid = new IPRange(ipVec[1], ipVec[2]);
        if (!(ipVec[3]-ipVec[2]<1)) {
            right = new IPRange(ipVec[2]+1, ipVec[3]);
        }
        return;
        
        
        //useless
        if(!a.IsContain(b) && !b.IsContain(a))
        {
            throw "a and b is not a contain relationship";
        }
            
//        cout<<"----Start SPLIT:"<<endl;
//        a.Print();
//        b.Print();
        if(a.start > b.start)
        {
            IPRange *l = new IPRange(b.start, a.start - 1);
            left = l;
//            cout<< "left:";
//            l->Print();
            if(a.end < b.end)
            {
                IPRange* r = new IPRange(a.end + 1, b.end);
                right = r;
//                cout<<"rignt: ";
//                r->Print();
            }
//            cout<<"middle:";
            IPRange* m = new IPRange(a.start, a.end);
            mid = m;
//            mid->Print();
        }
        else if(a.start < b.start)
        {
            IPRange* l = new IPRange(a.start, b.start - 1);
            left = l;
//            cout<< "left:";
//            l->Print();
            if(b.end < a.end)
            {
                IPRange* r = new IPRange(b.end + 1, a.end);
                right = r;
//                cout<<"rignt:";
//                r->Print();
            }
//            cout<<"middle:";
            IPRange* m = new IPRange(b.start, b.end);
            mid = m;
//            mid->Print();
        }
        else
        {
            if(a.end > b.end)
            {
                IPRange* r = new IPRange(b.end + 1, a.end);
                IPRange* m = new IPRange(a.start, b.end);
                right = r;
                mid = m;
//                cout<<"rignt: ";
//                right->Print();
//                cout<<"middle: ";
//                mid->Print();
            }
            else if(b.end > a.end)
            {
                IPRange* r = new IPRange(a.end + 1, b.end);
                IPRange* m = new IPRange(b.start, a.end);
                right = r;
                mid = m;
//               cout<<"rignt: ";
//                right->Print();
//                cout<<"middle: ";
//                mid->Print();
                
            }
            else
            {
                IPRange* m = new IPRange(a.start, a.end);
                mid = m;
//                cout<<"middle: ";
//                m->Print();
            }
        }
//        cout<<endl<<"____SPLIT END____"<<endl<<endl;
    }
};


#endif /* IPAddress_hpp */
