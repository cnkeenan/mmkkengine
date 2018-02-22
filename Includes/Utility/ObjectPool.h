#if !defined(OBJECTPOOL_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
template <typename T>
class TObjectPool
{
private:    
    const static uint32 NULL_PTR = UINT_MAX;
    const static uint32 NULL_PTR_2 = (0 << 16) | (NULL_PTR & 0xFFFF);
    uint32 m_MaxSize;
    uint32 m_NextKey;
    uint32 m_FreeHead;
    uint32 m_HighestIndex;
    uint32 m_Size;

    struct FItem
    {
        T Item = T();
        uint32 ID = NULL_PTR_2;
    };
        
    FItem* m_Items = nullptr;

    FItem* GetHead()
    {
        if(m_Size == 0)
            return nullptr;
        else
        {
            FItem* Front = m_Items;
            while((Front->ID & 0xFFFF0000) == 0)                            
                Front++;
            
            return Front;
        }        
    }


    FItem* GetTail()
    {
        if(m_Size == 0)
            return nullptr;
        else
        {
            return m_Items + (m_HighestIndex-1);
        }
    }

    
    inline FItem* Next(FItem* Item)
    {
        FItem* ItemContainer = Item;
        FItem* Tail = GetTail();
        if(Tail == nullptr)
            return nullptr;
        ItemContainer++;
        while((ItemContainer->ID & 0xFFFF0000) == 0)
        {
            if(ItemContainer == (Tail+1))
            {
                return nullptr;
            }
            ItemContainer++;
        }

        if(ItemContainer == (Tail+1))
        {
            return nullptr;
        }
        else
        {
            return ItemContainer;
        }        
    }

    
public:

    TObjectPool() : m_Items(nullptr), m_MaxSize(NULL_PTR), m_NextKey(NULL_PTR), m_FreeHead(NULL_PTR),
                    m_HighestIndex(NULL_PTR), m_Size(NULL_PTR)
    {}

    void Initialize(uint32 Count)
    {
        m_Items = new FItem[Count];        
        m_MaxSize = Count;
        m_NextKey = 1;
        m_FreeHead = NULL_PTR;
        m_HighestIndex = 0;
        m_Size = 0;
        Clear();
    }

    void Destroy()
    {
        if(m_Items)
        {
            Clear();
            delete[] m_Items;
            m_Items = nullptr;
        }
    }
    
    void Clear()
    {
        for(uint32 ObjectIndex = 0; ObjectIndex < m_MaxSize; ObjectIndex++)
        {
            m_Items[ObjectIndex] = FItem{T(), NULL_PTR_2};
        }        
    }

    T* Create()
    {
        uint32 Index = 0;
        if(m_FreeHead != NULL_PTR)
        {
            Index = m_FreeHead;
        }
        else
            Index = m_HighestIndex++;
        FItem* Item = m_Items + Index;
        
        if(Item->ID != NULL_PTR_2)
            m_FreeHead = (Item->ID & 0xFFFF);

        Item->ID = (m_NextKey++ << 16) | Index;
        m_Size++;
        return &Item->Item;
    }    

    void Free(T* Item)
    {
        uint32* ID = (uint32*)(Item+1);
        FItem* ItemContainer = m_Items + (*ID & 0xFFFF);
        ItemContainer->Item = T();
        
        *ID &= 0xFFFF;
        if(m_FreeHead != NULL_PTR)
        {
            uint32 Head = m_FreeHead;
            m_FreeHead = (*ID & 0xFFFF);
            *ID = 0 | Head;
        }
        else
        {
            m_FreeHead = (*ID & 0xFFFF);
            *ID = NULL_PTR_2;
        }
        m_Size--;        
    }

    inline uint32 GetID(T* Item)
    {
        return *(uint32*)(Item+1);
    }

    inline T* Get(const uint32 ID)
    {
        FItem* Item = m_Items + (ID & 0xFFFF);
        if(Item->ID == NULL_PTR_2)
        {
            return nullptr;
        }
        else
        {
            return &Item->Item;
        }
    }

    inline uint32 Size()
    {
        return m_Size;
    }

    inline T* Next(T* Item)
    {
        FItem* ItemContainer = m_Items + (GetID(Item) & 0xFFFF);
        return &Next(ItemContainer)->Item; 
    }

    inline T* Head()
    {
        return &GetHead()->Item;
    }
    
    inline T* Tail()
    {
        return &GetTail()->Item;
    }

    class FIterator
    {
    private:
        FItem* m_Item;
        TObjectPool<T>* m_ObjectPool;
    public:
        FIterator(TObjectPool<T>* ObjectPool, FItem* Item) : m_ObjectPool(ObjectPool),
                                                             m_Item(Item)
        {}

        bool operator!=(const FIterator& Iterator) const
        {
            if(m_Item)                
                return m_Item->ID != Iterator.m_Item->ID;
            else
                return false;
                
        }

        T& operator*() const
        {
            return m_Item->Item;
        }

        const FIterator& operator++()
        {
            m_Item = m_ObjectPool->Next(m_Item);
            return *this;
        }
    };
    
    FIterator begin()
    {
        return FIterator(this, GetHead());
    }

    FIterator end() 
    {
        return FIterator(this, GetTail()+1);
    }    
};

#define OBJECTPOOL_H
#endif
