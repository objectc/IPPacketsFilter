//
//  IPRangeNode.cpp
//  RangeTree
//
//  Created by tab on 4/29/18.
//  Copyright © 2018 tab. All rights reserved.
//

#include "IPRangeNode.hpp"


bool SourceNode::IsPacketAllow(unsigned int packetSRC, unsigned int packetDST, IPRangeNode *currentNode){
    SourceNode *srcRes = Search(packetSRC, currentNode);
    DestNode *dstRes = srcRes->dstChild->Search(packetDST);
    return dstRes->isAllow;
};




