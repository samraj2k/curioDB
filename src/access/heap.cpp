//
// Created by Sameer Raj on 13/08/24.
//

#include "access/heap.h"

#include "storage/buffer.h"
#include "storage/page.h"
#include "utils/relation.h"


BufferId relationGetBufferForTuple(Relation relation, HeapTuple heapTuple) {
    BufferId bufferId = NULL;
    BlockNumber targetBlock = NULL;
    const ObjectSize spaceRequiredInBuffer = page::sizeOfItemIdData()
                                                + sizeof(HeapTupleHeaderData)
                                                + heapTuple->dataLength;
    if(spaceRequiredInBuffer + page::sizeOfHeader() > PAGE_SIZE) {
        // throw error here
    }
    targetBlock = relation::getLastUsedBlock(relation);
    if(targetBlock == NULL) {
        // need to fetch from disk
        // for now hardcoding it
    }

    bufferId = buffer::readBuffer(relation, targetBlock);
    buffer::lockBuffer(bufferId, LockMode::WRITE);
    // again check, if it does not fullfull
    if(buffer::getEmptySpace(bufferId) < spaceRequiredInBuffer) {
        // someone else took the lock and made the changes
        buffer::unlockBuffer(bufferId, LockMode::WRITE);
        buffer::releaseBuffer(bufferId);
    }
    return bufferId;
}

void heap_insert(Relation relation, HeapTuple heapTuple) {


    BufferId bufferToInsert = relationGetBufferForTuple(relation, heapTuple);


}

