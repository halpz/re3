#pragma once

// some windows shit
#ifdef MoveMemory
#undef MoveMemory
#endif

extern RwMemoryFunctions memFuncs;
void InitMemoryMgr(void);

template<typename T, uint32 N>
class CStack
{
public:
	T values[N];
	uint32 sp;

	CStack() : sp(0) {}
	void push(const T& val) { values[sp++] = val; }
	T& pop() { return values[sp--]; }
};


struct HeapBlockDesc
{
	uint32 m_size;
	int16 m_memId;
	int16 m_ptrListIndex;
	HeapBlockDesc *m_next;
	HeapBlockDesc *m_prev;

	HeapBlockDesc *GetNextConsecutive(void)
	{
		return (HeapBlockDesc*)((uintptr)this + sizeof(HeapBlockDesc) + m_size);
	}

	void *GetDataPointer(void)
	{
		return (void*)((uintptr)this + sizeof(HeapBlockDesc));
	}

	void RemoveHeapFreeBlock(void)
	{
		m_next->m_prev = m_prev;
		m_prev->m_next = m_next;
	}

	// after node
	void InsertHeapFreeBlock(HeapBlockDesc *node)
	{
		m_next = node->m_next;
		node->m_next->m_prev = this;
		m_prev = node;
		node->m_next = this;
	}

	HeapBlockDesc *FindSmallestFreeBlock(uint32 size)
	{
		HeapBlockDesc *b;
		for(b = m_next; b->m_size < size; b = b->m_next);
		return b;
	}
};

#ifdef USE_CUSTOM_ALLOCATOR
// TODO: figure something out for 64 bit pointers
static_assert(sizeof(HeapBlockDesc) == 0x10, "HeapBlockDesc must have 0x10 size otherwise most of assumptions don't make sense");
#endif

struct HeapBlockList
{
	HeapBlockDesc m_first;
	HeapBlockDesc m_last;

	void Init(void)
	{
		m_first.m_next = &m_last;
		m_last.m_prev = &m_first;
	}

	void Insert(HeapBlockDesc *node)
	{
		node->InsertHeapFreeBlock(&m_first);
	}
};

struct CommonSize
{
	HeapBlockList m_freeList;
	uint32 m_size;
	uint32 m_failed;
	uint32 m_remaining;

	void Init(uint32 size);
	void Free(HeapBlockDesc *node)
	{
		m_freeList.Insert(node);
		m_remaining++;
	}
	HeapBlockDesc *Malloc(void)
	{
		if(m_freeList.m_first.m_next == &m_freeList.m_last){
			m_failed++;
			return nil;
		}
		HeapBlockDesc *block = m_freeList.m_first.m_next;
		m_remaining--;
		block->RemoveHeapFreeBlock();
		block->m_ptrListIndex = -1;
		return block;
	}
};

enum {
	MEMID_FREE,
	// IDs from LCS:
	MEMID_ID1,	// "Game"
	MEMID_ID2,	// "World"
	MEMID_ID3,	// "Animation"
	MEMID_ID4,	// "Pools"
	MEMID_ID5,	// "Default Models"
	MEMID_ID6,	// "Streaming"
	MEMID_ID7,	// "Streamed Models"
	MEMID_ID8,	// "Streamed LODs"
	MEMID_ID9,	// "Streamed Textures"
	MEMID_ID10,	// "Streamed Collision"
	MEMID_ID11,	// "Streamed Animation"
	MEMID_ID12,	// "Textures"
	MEMID_ID13,	// "Collision"
	MEMID_ID14,	// "PreAlloc"
	MEMID_ID15,	// "Game Process"
	MEMID_ID16,	// "Script"
	MEMID_ID17,	// "Cars"
	MEMID_ID18,	// "Render"
	MEMID_ID19,	// "Ped Attr"

	NUM_MEMIDS,

	NUM_FIXED_MEMBLOCKS = 6
};

class CMemoryHeap
{
public:
	HeapBlockDesc *m_start;
	HeapBlockDesc *m_end;
	HeapBlockList m_freeList;
	CommonSize m_fixedSize[NUM_FIXED_MEMBLOCKS];
	uint32 m_totalMemUsed;
	CStack<int32, 16> m_idStack;
	uint32 m_currentMemID;
	uint32 *m_memUsed;
	uint32 m_totalBlocksUsed;
	uint32 *m_blocksUsed;
	uint32 m_unkMemId;

	CMemoryHeap(void) : m_start(nil) {}
	void Init(uint32 total);
	void RegisterMalloc(HeapBlockDesc *block);
	void RegisterFree(HeapBlockDesc *block);
	void *Malloc(uint32 size);
	void *Realloc(void *ptr, uint32 size);
	void Free(void *ptr);
	void FillInBlockData(HeapBlockDesc *block, HeapBlockDesc *end, uint32 size);
	uint32 CombineFreeBlocks(HeapBlockDesc *block);
	void *MoveMemory(void *ptr);
	HeapBlockDesc *WhereShouldMemoryMove(void *ptr);
	void *MoveHeapBlock(HeapBlockDesc *dst, HeapBlockDesc *src);
	void PopMemId(void);
	void PushMemId(int32 id);
	void RegisterMemPointer(void *ptr);
	void TidyHeap(void);
	uint32 GetMemoryUsed(int32 id);
	uint32 GetBlocksUsed(int32 id);

	void ParseHeap(void);

	HeapBlockDesc *GetDescFromHeapPointer(void *block)
	{
		return (HeapBlockDesc*)((uintptr)block - sizeof(HeapBlockDesc));
	}
	uint32 GetSizeBetweenBlocks(HeapBlockDesc *first, HeapBlockDesc *second)
	{
		return (uintptr)second - (uintptr)first - sizeof(HeapBlockDesc);
	}
	void FreeBlock(HeapBlockDesc *block){
		for(int i = 0; i < NUM_FIXED_MEMBLOCKS; i++){
			if(m_fixedSize[i].m_size == block->m_size){
				m_fixedSize[i].Free(block);
				return;
			}
		}
		HeapBlockDesc *b = m_freeList.m_first.FindSmallestFreeBlock(block->m_size);
		block->InsertHeapFreeBlock(b->m_prev);
	}
};
