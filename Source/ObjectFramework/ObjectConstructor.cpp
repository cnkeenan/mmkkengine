/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
template <typename T>
T* FObjectConstructor::Construct()
{
    return nullptr;
}

template <>
IAIObject* FObjectConstructor::Construct()
{
    return m_AIScene->CreateObject();
}

template <>
IWidgetObject* FObjectConstructor::Construct()
{
    return m_WidgetScene->CreateObject();
}

template <>
ICollisionObject* FObjectConstructor::Construct()
{
    return m_CollisionScene->CreateObject();
}

template <>
IGraphicsObject* FObjectConstructor::Construct()
{
    return m_GraphicsScene->CreateObject();
}

template <>
IInputObject* FObjectConstructor::Construct()
{
    return m_InputScene->CreateObject();
}

template <>
IPhysicsObject* FObjectConstructor::Construct()
{
    return m_PhysicsScene->CreateObject();
}

template <>
ISoundObject* FObjectConstructor::Construct()
{
    return m_SoundScene->CreateObject();
}

template <>
ITransformObject* FObjectConstructor::Construct()
{
    return m_TransformScene->CreateObject();
}

void FObjectConstructor::Destruct(IObject* Object)
{
    if(Object && Object->IsInitialized())
    {
        switch(Object->GetType())
        {
            case ESystemType::AI:
            {
                m_AIScene->DestroyObject((IAIObject*)Object);
            } break;

            case ESystemType::COLLISION:
            {
                m_CollisionScene->DestroyObject((ICollisionObject*)Object);
            } break;

            case ESystemType::GRAPHICS:
            {
                m_GraphicsScene->DestroyObject((IGraphicsObject*)Object);
            } break;

            case ESystemType::INPUT:
            {
                m_InputScene->DestroyObject((IInputObject*)Object);
            } break;

            case ESystemType::PHYSICS:
            {
                m_PhysicsScene->DestroyObject((IPhysicsObject*)Object);
            } break;

            case ESystemType::SOUND:
            {
                m_SoundScene->DestroyObject((ISoundObject*)Object);
            } break;

            case ESystemType::TRANSFORM:
            {
                m_TransformScene->DestroyObject((ITransformObject*)Object);
            } break;

            case ESystemType::WIDGET:
            {
                m_WidgetScene->DestroyObject((IWidgetObject*)Object);
            } break;

            default:
            {
            } break;
        }

    }
}
