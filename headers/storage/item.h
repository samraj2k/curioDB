//
// Created by Sameer Raj on 12/07/24.
//

#ifndef ITEM_H
#define ITEM_H

#include "curio.h"
#include "block.h"

using Item = char*;
using ItemSize = std::uint16_t;


/**
 * Inside item, we will store this info
 * It will be for heapTuple
 * There is an item pointer in each tuple header and index
 * tuple header on disk.
 */
struct ItemPointerData {
    BlockNumber blockNumber;
    Offset position;
};

/**
 * Array of ItemIdData is there,
 * which points to item offset in the page, and its length
 */
struct ItemIdData {
    Offset dataOffset;;  // offset to tuple (from start of page)
    ItemSize dataLength;  // byte length of tuple
};

#endif //ITEM_H
