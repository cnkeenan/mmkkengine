/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
template <typename T>
T* FObjectConstructor::Construct()
{
    return nullptr;
}

void FObjectConstructor::Destruct(IObject** Object)
{
    switch((*Object)->GetType())
    {
    }

    (*Object) = nullptr;
}
