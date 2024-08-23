//
// Created by Sameer Raj on 13/08/24.
//

#include "access/heap.h"

#include "storage/buffer.h"
#include "storage/freespace.h"
#include "storage/page.h"
#include "utils/relation.h"


BufferId relationGetBufferForTuple(Relation relation, HeapTuple heapTuple) {
    BufferId bufferId = NULL;
    BlockNumber targetBlock = NULL;
    Page page;
    const ObjectSize spaceRequiredInBuffer = page::sizeOfItemIdData()
                                                + sizeof(HeapTupleHeaderData)
                                                + heapTuple->dataLength;
    if(spaceRequiredInBuffer + page::sizeOfHeader() > PAGE_SIZE) {
        // throw error here
    }
    targetBlock = freespace::getFreeBlock(relation, spaceRequiredInBuffer);
    while(targetBlock != -1) {
        bufferId = buffer::readBuffer(relation, targetBlock);
        buffer::lockBuffer(bufferId, LockMode::WRITE);
        page = buffer::getPage(bufferId);
        ObjectSize emptySpace = page::getEmptySpace(page);
        if(emptySpace >= spaceRequiredInBuffer) {
            return bufferId;
        }
        buffer::unlockBuffer(bufferId, LockMode::WRITE);
        buffer::releaseBuffer(bufferId);
        targetBlock = freespace::recordFreeSpaceAndGetPage(relation,
            targetBlock,
            emptySpace,
            spaceRequiredInBuffer);

    }

    return bufferId;
}

void heap_insert(Relation relation, HeapTuple heapTuple) {


    BufferId bufferToInsert = relationGetBufferForTuple(relation, heapTuple);


}

