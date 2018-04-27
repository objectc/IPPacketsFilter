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

using namespace std;

class IPRange
{
public:
    // minIP <= ip < maxIP
    unsigned int intIP;
    unsigned int IPEnd;
    
    IPRange();
    IPRange(unsigned int minIP, unsigned int maxIP);
    IPRange(int a, int b, int c, int d, int k);
    IPRange(string a,string b,string c,string d,string k);
    bool IsContain(IPRange b);
    void Print();
    static void Split(IPRange a, IPRange b, IPRange*& left, IPRange*& mid, IPRange*& right)
    {
        if(!a.IsContain(b) && !b.IsContain(a))
        {
            throw "a and b is not a contain relationship";
        }
            
//        cout<<"----Start SPLIT:"<<endl;
//        a.Print();
//        b.Print();
        if(a.intIP > b.intIP)
        {
            IPRange *l = new IPRange(b.intIP, a.intIP - 1);
            left = l;
//            cout<< "left:";
//            l->Print();
            if(a.IPEnd < b.IPEnd)
            {
                IPRange* r = new IPRange(a.IPEnd + 1, b.IPEnd);
                right = r;
//                cout<<"rignt: ";
//                r->Print();
            }
//            cout<<"middle:";
            IPRange* m = new IPRange(a.intIP, a.IPEnd);
            mid = m;
//            mid->Print();
        }
        else if(a.intIP < b.intIP)
        {
            IPRange* l = new IPRange(a.intIP, b.intIP - 1);
            left = l;
//            cout<< "left:";
//            l->Print();
            if(b.IPEnd < a.IPEnd)
            {
                IPRange* r = new IPRange(b.IPEnd + 1, a.IPEnd);
                right = r;
//                cout<<"rignt:";
//                r->Print();
            }
//            cout<<"middle:";
            IPRange* m = new IPRange(b.intIP, b.IPEnd);
            mid = m;
//            mid->Print();
        }
        else
        {
            if(a.IPEnd > b.IPEnd)
            {
                IPRange* r = new IPRange(b.IPEnd + 1, a.IPEnd);
                IPRange* m = new IPRange(a.intIP, b.IPEnd);
                right = r;
                mid = m;
//                cout<<"rignt: ";
//                right->Print();
//                cout<<"middle: ";
//                mid->Print();
            }
            else if(b.IPEnd > a.IPEnd)
            {
                IPRange* r = new IPRange(a.IPEnd + 1, b.IPEnd);
                IPRange* m = new IPRange(b.intIP, a.IPEnd);
                right = r;
                mid = m;
//               cout<<"rignt: ";
//                right->Print();
//                cout<<"middle: ";
//                mid->Print();
                
            }
            else
            {
                IPRange* m = new IPRange(a.intIP, a.IPEnd);
                mid = m;
//                cout<<"middle: ";
//                m->Print();
            }
        }
//        cout<<endl<<"____SPLIT END____"<<endl<<endl;
    }
    
private:
    int a;
    int b;
    int c;
    int d;
    int k;
    void TransformIP();
};


#endif /* IPAddress_hpp */
