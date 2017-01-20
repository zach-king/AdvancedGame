//#pragma once
//
///*
//	Memory Pool class written by Mike McShaffry, the co-author 
//	of Game Coding Complete, where this code was taken from.
//*/
//#ifndef MEMORYPOOL_H
//#define MEMORYPOOL_H
//
//class MemoryPool
//{
//	unsigned char** m_ppRawMemoryArray;	// an array of memory blocks, each
//										// split up into chunks
//	unsigned char* m_pHead;	// the front of the memory chunk linked list
//	unsigned int m_chunkSize, m_numChunks; // the size of each chunk and 
//											// the number of chunks per array
//	unsigned int m_memArraySize; // the number elements in the memory array
//	bool m_toAllowResize; // true if we resize the memory pool when it fills
//
//	const static size_t CHUNK_HEADER_SIZE = (sizeof(unsigned char*));
//
//public:
//	// Construction
//	MemoryPool(void);
//	~MemoryPool(void);
//	bool Init(unsigned int chunkSize, unsigned int numChunks);
//	void Destroy(void);
//
//	// Allocation functions
//	void* Alloc(void);
//	void Free(void* pMem);
//	unsigned int GetChunkSize(void) const { return m_chunkSize; }
//	
//	// Settings
//	void SetAllowResize(bool toAllowResize)
//	{
//		m_toAllowResize = toAllowResize;
//	}
//
//private:
//	// Resets internal vars
//	void Reset(void);
//
//	// Internal memory allocation helpers
//	bool GrowMemoryArray(void);
//	unsigned char* AllocateNewMemoryBlock(void);
//
//	// Internal linked list management
//	unsigned char* GetNext(unsigned char* pBlock);
//	void SetNext(unsigned char* pBlockToChange, unsigned char* pNewNext);
//
//	// Don't allow copy constructor
//	MemoryPool(const MemoryPool &memPool) {}
//};
//
//#endif