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
    RelationCache relCache;
};


using Relation = RelationData*;

namespace relation {
    inline BlockNumber getLastUsedBlock(Relation relation) {
        if(relation == NULL or relation -> relCache == NULL or relation -> relCache->targetBlock == NULL) {
            return NULL;
        }
        return relation -> relCache -> targetBlock;
    }
}
#endif //RELATION_H
