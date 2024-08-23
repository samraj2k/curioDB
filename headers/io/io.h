//
// Created by Sameer Raj on 02/08/24.
//

#ifndef IO_H
#define IO_H
#include "storage/page.h"
#include "storage/block.h"

namespace io {
    Page loadPageFromDisk(BlockNumber blockNumber, ID relationId);
    void writePageToDisk(Page page, BlockNumber blockNumber, ID file);
    BlockNumber getLastBlockForFile(ID file);
}
#endif //IO_H
