/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

FPool* MemoryManager::GetPool(ESystemType Type)
{
    switch(Type)
    {
        case ESystemType::AI:
        {
            return &m_AIPool;
        } break;

        case ESystemType::COLLISION:
        {
            return &m_CollisionPool;
        } break;

        case ESystemType::GRAPHICS:
        {
            return &m_GraphicsPool;
        } break;

        case ESystemType::INPUT:
        {
            return &m_InputPool;
        } break;

        case ESystemType::PHYSICS:
        {
            return &m_PhysicsPool;
        } break;

        case ESystemType::SOUND:
        {
            return &m_SoundPool;
        } break;

        case ESystemType::TRANSFORM:
        {
            return &m_TransformPool;
        } break;

        case ESystemType::WIDGET:
        {
            return &m_WidgetPool;
        } break;
    }

    return nullptr;
}
