#if !defined(POOL_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class FPool
{
private:
    uint32 m_BlockSize;
    uint32 m_BlockCount;
    uint32 m_NumberOfFreeBlocks;
    uint32 m_NumberOfInitBlocks;
    uint8* m_MemoryStart;
    uint8* m_Next;
public:

    void CreatePool(uint32 BlockSize, uint32 BlockCount) 
    {
        m_BlockSize = BlockSize;
        m_BlockCount = BlockCount;
        m_NumberOfFreeBlocks = BlockCount;
        m_NumberOfInitBlocks = 0;
        m_MemoryStart = new uint8[BlockSize*BlockCount];
        m_Next = m_MemoryStart;
    }

    void DestroyPool()
    {
        if(m_MemoryStart)
        {
            delete[] m_MemoryStart;
            m_MemoryStart = m_Next = nullptr;            
        }
    }

    inline void* Allocate()
    {
        if(m_NumberOfInitBlocks < m_BlockCount)
        {
            uint32* Address = (uint32*)AddressFromIndex(m_NumberOfInitBlocks);
            *Address = m_NumberOfInitBlocks+1;
            m_NumberOfInitBlocks++;
        }

        void* Result = nullptr;
        if(m_NumberOfFreeBlocks > 0)
        {
            Result = (void*)m_Next;
            --m_NumberOfFreeBlocks;
            if(m_NumberOfFreeBlocks != 0)
            {
                m_Next = AddressFromIndex(*((uint32*)m_Next));
            }
            else
            {
                m_Next = nullptr;
            }
        }

        return Result;
    }

    inline void Free(void* Address)
    {
        if(m_Next != nullptr)
        {
            (*(uint32*)Address) = IndexFromAddress(m_Next);
            m_Next = (uint8*)Address;
        }
        else
        {
            *((uint32*)Address) = m_BlockCount;
            m_Next = (uint8*)Address;
        }
        m_NumberOfFreeBlocks++;
    }

    
private:
    inline uint8* AddressFromIndex(uint32 Index) const
    {
        return m_MemoryStart + (Index * m_BlockSize);
    }

    inline uint32 IndexFromAddress(const uint8* Address) const
    {
        return (((uint32)(Address-m_MemoryStart))/m_BlockSize);
    }
};

#define POOL_H
#endif
