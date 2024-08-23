//
// Created by Sameer Raj on 16/08/24.
//

#ifndef FREESPACE_H
#define FREESPACE_H
#include "block.h"
#include "configs/constants.h"
#include "utils/relation.h"

namespace freespace {
    BlockNumber getFreeBlock(Relation relation, ObjectSize size);
    BlockNumber recordFreeSpaceAndGetPage(Relation relation,
                                            BlockNumber blockNumber,
                                            ObjectSize oldSpace,
                                            ObjectSize requiredSize);
}
#endif //FREESPACE_H
