#ifndef PAGE_H
#define PAGE_H

#include <cstdint>
#include "curio.h"
#include "item.h"
#include "configs/constants.h"

// A page is a block of memory that is used to store data
// Suppose it is 8 KB, so a char pointer having 1024 * 8 bytes
using Page = char*;

/**
Using slotted page structure

+----------------+---------------------------------+
| PageHeaderData | itemId0 itemId1 itemId2 ...     |
+-----------+----+---------------------------------+
| ... itemIdN |                                    |
+-----------+--------------------------------------+
|		     ^ freeSpaceStart                      |
|                                                  |
|			 v freeSpaceEnd                        |
+-------------+------------------------------------+
|			 | ItemN ...                           |
+-------------+------------------+-----------------+
|	   ... Item2 Item1 Item0 | specialDataSpace    |
+--------------------------------+-----------------+
ItemIds are also part of header
Item are essentially tuples, either: HeapTuple, BtreeTuple or any index
Essentially they are item (Pointer), but Buffer does not care about this.
In they access layer, Item pointer will be parsed as per the index/heap tuple
**/

struct PageHeaderData {
    Offset freeSpaceStart;
    Offset freeSpaceEnd;
    Offset specialDataSpace;
    ItemIdData itemIds[];
};
using PageHeader = PageHeaderData*;

namespace page {

    inline ObjectSize sizeOfHeader() {
        return sizeof(PageHeaderData);
    }

    inline ObjectSize sizeOfItemIdData() {
        return sizeof(ItemIdData);
    }

    inline uint16_t numOfItems(Page page) {
        auto header = (PageHeader)page;
        return (header->freeSpaceStart - sizeOfHeader()) / sizeof(ItemIdData);
    }

    inline uint16_t getEmptySpace(Page page) {
        auto header = (PageHeader)page;
        return header->freeSpaceEnd - header->freeSpaceStart;
    }

    inline bool isAddable(Page page, size_t sizeOfItem) {
        return getEmptySpace(page) + sizeof(ItemIdData) >= sizeOfItem;
    }

    Page initPage(ObjectSize specialDataLength);
    void addItem(Page page, ItemSize sizeOfItem, Item item);

}

#endif //PAGE_H
