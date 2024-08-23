//
// Created by Sameer Raj on 10/08/24.
//

#ifndef RELATION_H
#define RELATION_H
#include "curio.h"


struct RelationCacheData {
    BlockNumber targetBlock;
};

using RelationCache = RelationCacheData*;

struct RelationData {
    ID relationId;
};


using Relation = RelationData*;

#endif //RELATION_H
