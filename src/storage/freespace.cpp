//
// Created by Sameer Raj on 16/08/24.
//

#include "storage/freespace.h"

#include <assert.h>
#include <map>

#include "io/io.h"
#include "storage/buffer.h"
#include "utils/relation.h"

static std::mutex mtx;
static std::map<ID, std::map<BlockNumber, ObjectSize>> freeSpaceMap;

namespace freespace {
    void initFreeSpaceMap(Relation relation) {
        std::unique_lock lck(mtx);
        const BlockNumber lastBlock = io::getLastBlockForFile(relation->relationId);
        const BufferId bufferId = buffer::readBuffer(relation, lastBlock);
        Page page = buffer::getPage(bufferId);
        const ObjectSize emptySpace = page::getEmptySpace(page);
        freeSpaceMap[relation->relationId][io::getLastBlockForFile(relation->relationId)] = emptySpace;
        buffer::releaseBuffer(bufferId);
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

    BlockNumber recordFreeSpaceAndGetPage(Relation relation,
                                            const BlockNumber blockNumber,
                                            const ObjectSize oldSpace,
                                            const ObjectSize requiredSize) {
        std::unique_lock lck(mtx);
        assert(freeSpaceMap.contains(relation->relationId));
        auto relFreeSpaceMap = freeSpaceMap[relation->relationId];
        if(relFreeSpaceMap.contains(blockNumber)) {
            relFreeSpaceMap[blockNumber] = std::min(relFreeSpaceMap[blockNumber], oldSpace);
        }
        lck.unlock();
        return getFreeBlock(relation, requiredSize);
    }

    BufferId addBlockInRelation(Relation relation) {
        std::unique_lock lck(mtx);
        assert(freeSpaceMap.contains(relation->relationId));


    }
}





