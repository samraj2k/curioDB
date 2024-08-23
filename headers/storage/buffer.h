//
// Created by Sameer Raj on 13/07/24.
//

#ifndef BUFFER_H
#define BUFFER_H

#include <atomic>
#include <unordered_map>

#include "configs/constants.h"
#include "block.h"
#include "page.h"
#include "lock/lock.h"
#include "utils/relation.h"

using BufferId = unsigned int;
// 128 MB for 8KB buffer

struct BufferTag {
    BlockNumber blockNumber;
    ID relationId;

    bool operator==(const BufferTag& other) const {
        return blockNumber == other.blockNumber && relationId == other.relationId;
    }

    struct Hash {
        std::size_t operator()(const BufferTag& tag) const {
            std::string combined = std::to_string(tag.blockNumber) + "#" + std::to_string(tag.relationId);
            return std::hash<std::string>{}(combined);
        }
    };
};

struct BufferDescriptor {
    BufferDescriptor(const BufferTag &tag, const BufferId id)
        : tag(tag),
          id(id) {
    }

    BufferTag tag;
    BufferId id;
    std::atomic<unsigned int> pinCount;
    std::atomic<unsigned int> usageCount;
    std::atomic<bool> isDirty;
    ReadWriteLock contentLock;
};

using BufferMap = std::unordered_map<BufferTag, BufferId, BufferTag::Hash>;
using BufferDescriptors = std::vector<BufferDescriptor*>;

namespace buffer {

    void initBuffer();
    BufferId readBuffer(Relation relation, BlockNumber blockNumber);
    BufferId readBuffer(const BufferTag &tag);
    void releaseBuffer(BufferId bufferId);
    void lockBuffer(BufferId bufferId, LockMode lockMode);
    void unlockBuffer(BufferId bufferId, LockMode lockMode);
    Page getPage(BufferId buffer);

    inline void pin(BufferDescriptor* bufferDesc) {
        bufferDesc->pinCount.store(bufferDesc->pinCount.load() + 1, std::memory_order_relaxed);
        bufferDesc->usageCount.store(bufferDesc->usageCount.load() + 1, std::memory_order_relaxed);
    }

    inline void unpin(BufferDescriptor* bufferDesc) {
        bufferDesc->pinCount.store(bufferDesc->pinCount.load() - 1, std::memory_order_relaxed);
    }

    inline bool isValidBuffer(BufferId bufferId) {
        if(bufferId >= BUFFER_SLOTS) {
            return false;
        }
        return true;
    }
}
#endif //BUFFER_H
