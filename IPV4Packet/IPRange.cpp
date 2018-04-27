//
//  IPAddress.cpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#include "IPRange.hpp"
IPRange::IPRange()
{
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    k = 0;
    IPEnd = 0;
    intIP = 0;
}
IPRange::IPRange(unsigned int min, unsigned int max)
{
    if(min > max)
        {
//            cout<<"min:"<<min<<" , ";
//            cout<<"max:"<<max<<","<<endl;
            throw "min > max";
        }
    this->IPEnd = max;
    this->intIP = min;
}
IPRange::IPRange(int a, int b, int c, int d, int k)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->k = k;
    TransformIP();
}
IPRange::IPRange(std::string a,std::string b,std::string c,std::string d,std::string k)
{
    this->a = atoi(a.c_str());
    this->b = atoi(b.c_str());
    this->c = atoi(c.c_str());
    this->d = atoi(d.c_str());
    this->k = atoi(k.c_str());
    TransformIP();
}
void IPRange::Print()
{
    if(this != nullptr)
        cout<<intIP<<" to "<< IPEnd<<endl;
    else
    cout<<"null"<<endl;
}
void IPRange::TransformIP()
{
    intIP = a * pow(256, 3) + b * pow(256, 2) + c * 256 + d;
    //cout<<"min"<<minIP<<endl;
    unsigned int _m = pow(2, k) - 1;
    IPEnd =intIP | _m;
    //cout<<"max"<<maxIP<<endl;
}
bool IPRange::IsContain(IPRange b)
{
    if(IPEnd >= b.IPEnd && intIP <= b.intIP)
        return true;
    else
        return  false;
}

