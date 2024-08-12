//
// Created by Sameer Raj on 12/07/24.
//

#ifndef ITEM_H
#define ITEM_H

#include "curio.h"
#include "block.h"

using Item = char*;
using ItemSize = std::uint16_t;

struct ItemPointerData {
    BlockNumber blockNumber;
    Offset position;
};

struct ItemIdData {
    Offset dataOffset;;  // offset to tuple (from start of page)
    ItemSize dataLength;  // byte length of tuple
};

#endif //ITEM_H
