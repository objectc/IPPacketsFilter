//
//  Rule.cpp
//  cs600_fianl
//
//  Created by Xue Kaiyun on 2018/4/18.
//  Copyright © 2018年 Xue Kaiyun. All rights reserved.
//

#include "Rule.hpp"
Rule::Rule(IPRange dest, IPRange source, bool action)
{
    dst = dest;
    src = source;
    this->allow = action;
}
Rule::Rule(std::string inputStr)
{
    std::string ruleValues[11];
    int ii = 0;
    for(int i = 0; i < inputStr.size(); i++)
    {
        if(inputStr[i] == '.' || inputStr[i] == '/' || inputStr[i] == ',')
        {
            ii++;
            continue;
        }
        ruleValues[ii]+=inputStr[i];
    }
    src = IPRange(ruleValues[0], ruleValues[1], ruleValues[2], ruleValues[3], ruleValues[4]);
    dst = IPRange(ruleValues[5], ruleValues[6], ruleValues[7], ruleValues[8], ruleValues[9]);
    if(ruleValues[10] == "ALLOW")
        allow = true;
    else
        allow = false;
}
void Rule::Print()
{
    cout<<"SourceIP:";
    src.Print();
    cout<<"DestIP:";
    dst.Print();
    cout<<"Action:"<<allow<<endl<<endl;
}


