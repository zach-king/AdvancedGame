//#include "MemoryPool.h"
//
//#include <memory>
//
//bool MemoryPool::GrowMemoryArray(void)
//{
//	// Allocate a new array
//	size_t allocationSize = sizeof(unsigned char*) * (m_memArraySize + 1);
//	unsigned char** ppNewMemArray = (unsigned char**)malloc(allocationSize);
//
//	// Make sure the allocation succeeded
//	if (!ppNewMemArray)
//		return false;
//
//	// Copy any existing memory pointers over
//	for (unsigned int i = 0; i < m_memArraySize; ++i)
//	{
//		ppNewMemArray[i] = m_ppRawMemoryArray[i];
//	}
//
//	// Allocate a new block of memory. Indexing m_memArraySize here is 
//	// safe because we haven't incremented it yet to reflect the new size
//	ppNewMemArray[m_memArraySize] = AllocateNewMemoryBlock();
//
//	// Attach the block to the end of the current memory list
//	if (m_pHead)
//	{
//		unsigned char* pCurr = m_pHead;
//		unsigned char* pNext = GetNext(m_pHead);
//		while (pNext)
//		{
//			pCurr = pNext;
//			pNext = GetNext(pNext);
//		}
//		SetNext(pCurr, ppNewMemArray[m_memArraySize]);
//	}
//	else
//	{
//		m_pHead = ppNewMemArray[m_memArraySize];
//	}
//
//	// Destroy the old memory array
//	if (m_ppRawMemoryArray)
//		free(m_ppRawMemoryArray);
//
//	// Assign the new memory array and increment the size count
//	m_ppRawMemoryArray = ppNewMemArray;
//	++m_memArraySize;
//
//	return true;
//}
//
//unsigned char* MemoryPool::AllocateNewMemoryBlock(void)
//{
//	// Calculate the size of each block and the size of the 
//	// actual memory allocation
//	size_t blockSize = m_chunkSize + CHUNK_HEADER_SIZE; // chunk + linked list
//	// Overhead
//	size_t trueSize = blockSize * m_numChunks;
//
//	// Allocate the memory
//	unsigned char* pNewMem = (unsigned char*)malloc(trueSize);
//	if (!pNewMem)
//		return NULL;
//
//	// Turn the memory into a linked list of chunks
//	unsigned char* pEnd = pNewMem + trueSize;
//	unsigned char* pCurr = pNewMem;
//	while (pCurr < pEnd)
//	{
//		// Calculate the next pointer position
//		unsigned char* pNext = pCurr + blockSize;
//
//		// Set the next pointer
//		unsigned char** ppChunkHeader = (unsigned char**)pCurr;
//		ppChunkHeader[0] = (pNext < pEnd ? pNext : NULL);
//
//		// Move to the next block
//		pCurr += blockSize;
//	}
//
//	return pNewMem;
//}
//
//void* MemoryPool::Alloc(void)
//{
//	// If we're out of memory chunks, grow the pool. This is very expensive.
//	if (!m_pHead)
//	{
//		// If we don't allow resizes return NULL
//		if (!m_toAllowResize)
//			return NULL;
//
//		// Attempt to grow the pool
//		if (!GrowMemoryArray())
//			return NULL; // couldn't allocate anymore memory
//	}
//
//	// Grab the first chunk from the list and move to the next chunks
//	unsigned char* pRet = m_pHead;
//	m_pHead = GetNext(m_pHead);
//	return (pRet + CHUNK_HEADER_SIZE); // make sure we return a pointer to 
//										// the data section only
//}
//
//void MemoryPool::Free(void* pMem)
//{
//	// Calling Free() on a NULL pointer is perfectly valid C++ so
//	// we have to check for it. 
//	if (pMem != NULL)
//	{
//		// The pointer we get back is just to the data section of 
//		// the chunk. This gets us the full chunk.
//		unsigned char* pBlock = ((unsigned char*)pMem) - CHUNK_HEADER_SIZE;
//
//		// Push the chunk to the front of the list
//		SetNext(pBlock, m_pHead);
//		m_pHead = pBlock;
//	}
//}