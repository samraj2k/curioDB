//
// Created by Sameer Raj on 12/08/24.
//

#ifndef HEAPTUPLE_H
#define HEAPTUPLE_H
#include "curio.h"
#include "storage/item.h"

/**
* CREATE TABLE example (
    id INT,
    name VARCHAR
);
INSERT INTO example VALUES (1, 'Alice');
Result:
[HeapTupleHeaderData][4 bytes for id][varlena for name]

struct varlena
{
    char vl_len_[4]; ----> 4 bytes for length
    char vl_dat[FLEXIBLE_ARRAY_MEMBER]; -> rest for data
};
Here currently solving for only key value pair, otherwise the fields would have added later after name.

The system catalogs (specifically pg_attribute) store information about each column's data type, constraints, etc.
When reading a tuple, PostgreSQL uses the table's metadata to know how many attributes to expect and their types.
If it's a fixed-length type (like INT, DATE), it reads the known number of bytes.
If it's variable-length (like VARCHAR, NUMERIC), it reads the length from the varlena header, then the data.

Postgres reference: https://github.com/postgres/postgres/blob/master/src/include/access/htup_details.h
Note HeapTupleHeaderData has fixed size, rest of the data is of size:
size(item) - size(HeapTupleHeaderData)
This struct is nothing but Pointer with this structure and also Item
**/

struct HeapTupleHeaderData {
    // which transaction inserted this tuple
    ID transactionId;

    // in the disk, where this heap tuple is, basically the ctid
    ItemPointerData itemPointerData;

    // Main data after this, ignored fields for null bitmap etc for reduced complexity in this project
};
#endif //HEAPTUPLE_H
