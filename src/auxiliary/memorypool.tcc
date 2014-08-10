#ifndef ULMBLAS_SRC_AUXILIARY_MEMORYPOOL_TCC
#define ULMBLAS_SRC_AUXILIARY_MEMORYPOOL_TCC 1

#include <cassert>
#include <list>
#include <unordered_map>

#include <cstdio>

namespace ulmBLAS {

template <typename T>
T *
MemoryPool<T>::allocate(size_t n)
{
    _mutex.lock();

    BlockList &blockList = _free[n];
    T         *block;

    if (blockList.empty()) {
        block = new T[n];
        _allocated.push_back(block);
    } else {
        block = blockList.back();
        blockList.pop_back();
    }
    _used[block] = n;

    _mutex.unlock();
    return block;
}

template <typename T>
void
MemoryPool<T>::release(T *block)
{
    _mutex.lock();

    assert(_used.count(block)==1);
    size_t n = _used[block];
    _free[n].push_back(block);

    _mutex.unlock();
}

template <typename T>
MemoryPool<T>::~MemoryPool()
{
    for (auto it=_allocated.begin(); it!=_allocated.end(); ++it) {
        delete [] *it;
    }
}

} // namespace ulmBLAS

#endif // ULMBLAS_SRC_AUXILIARY_MEMORYPOOL_TCC
