//
// Created by Sameer Raj on 16/08/24.
//

#include "storage/freespace.h"

#include <map>
#include <mutex>

#include "io/io.h"
#include "utils/relation.h"

static std::mutex mtx;
static std::map<ID, std::map<BlockNumber, ObjectSize>> freeSpaceMap;


void initFreeSpaceMap(Relation relation) {
    std::unique_lock lck(mtx);

    Page lastBlockPage = io::loadPageFromDisk(io::getLastBlockForFile(relation->relationId), relation->relationId);
    ObjectSize emptySpace = page::getEmptySpace(lastBlockPage);
    freeSpaceMap[relation->relationId][io::getLastBlockForFile(relation->relationId)] = emptySpace;
}

BlockNumber getFreeBlock(Relation relation, ObjectSize size) {
    std::unique_lock lck(mtx);
    if(!freeSpaceMap.contains(relation->relationId)) {
        initFreeSpaceMap(relation);
    }
    auto relFreeSpaceMap = freeSpaceMap[relation->relationId];

    for(auto to: relFreeSpaceMap) {
        if(to.second >= size) {
            return to.first;
        }
    }
    return -1;

}



