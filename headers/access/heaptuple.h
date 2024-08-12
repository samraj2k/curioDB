//
// Created by Sameer Raj on 12/08/24.
//

#ifndef HEAPTUPLE_H
#define HEAPTUPLE_H
#include "curio.h"
#include "storage/item.h"

// Postgres reference: https://github.com/postgres/postgres/blob/master/src/include/access/htup_details.h
struct HeapTupleHeaderData {
    // which transaction inserted this tuple
    ID transactionId;
    // in the disk, where this heap tuple is, basically the ctid
    ItemPointerData itemPointerData;

    // Main data after this
    // Kept it simple, excluded number of attributes, null bits etc for KV impl
};
#endif //HEAPTUPLE_H
