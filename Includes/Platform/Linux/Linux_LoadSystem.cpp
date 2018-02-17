ISystem* PlatformManager::LoadSystem(ESystemType SystemType, IWindow* Window)
{
    ISystem* Result = nullptr;

#define LOAD_SYSTEM(x, y) \
    void* hndl_##x = dlopen(y, RTLD_LAZY); \
    fp_##x* x = (fp_##x*) dlsym(hndl_##x, #x);

    switch(SystemType)
    {
        case ESystemType::AI:
        {
            LOAD_SYSTEM(CreateAISystem, "AI.so");
            Result = CreateAISystem(MemoryManager::Get());            
        } break;

        
        case ESystemType::COLLISION:
        {
            LOAD_SYSTEM(CreateCollisionSystem, "Collision.so");
            Result = CreateCollisionSystem(MemoryManager::Get());
        } break;

        
        case ESystemType::GRAPHICS:
        {
            LOAD_SYSTEM(CreateGraphicsSystem, "Graphics.so");
            Result = CreateGraphicsSystem(MemoryManager::Get(),
                                          PlatformManager::Get(),
                                          Window);
        } break;

        
        case ESystemType::INPUT:
        {
            LOAD_SYSTEM(CreateInputSystem, "Input.so");
            Result = CreateInputSystem(MemoryManager::Get());
        } break;
        
        case ESystemType::PHYSICS:
        {
            LOAD_SYSTEM(CreatePhysicsSystem, "Physics.so");
            Result = CreatePhysicsSystem(MemoryManager::Get());
        } break;
        
        case ESystemType::SOUND:
        {
            LOAD_SYSTEM(CreateSoundSystem, "Sound.so");
            Result = CreateSoundSystem(MemoryManager::Get());
        } break;
        
        case ESystemType::TRANSFORM:
        {
            LOAD_SYSTEM(CreateTransformSystem, "Transform.so");
            Result = CreateTransformSystem(MemoryManager::Get());
        } break;
        
        case ESystemType::WIDGET:
        {
            LOAD_SYSTEM(CreateWidgetSystem, "Widget.so");
            Result = CreateWidgetSystem(MemoryManager::Get());
        } break;

        
        default:
        {
            ASSERT(!"", "Not a valid system");
        } break;
    }

    return Result;
}

void PlatformManager::UnloadSystem(ISystem** System)
{

    if((*System))
    {
        switch((*System)->GetType())
        {
            case ESystemType::AI:
            {
                LOAD_SYSTEM(DestroyAISystem, "AI.so");
                DestroyAISystem((IAI**)System);            
            } break;
            
            case ESystemType::COLLISION:
            {
                LOAD_SYSTEM(DestroyCollisionSystem, "Collision.so");
                DestroyCollisionSystem((ICollision**)System);
            } break;
            
            case ESystemType::GRAPHICS:
            {
                LOAD_SYSTEM(DestroyGraphicsSystem, "Graphics.so");
                DestroyGraphicsSystem((IGraphics**)System);
            } break;
            
            case ESystemType::INPUT:
            {
                LOAD_SYSTEM(DestroyInputSystem, "Input.so");
                DestroyInputSystem((IInput**)System);
            } break;
        
            case ESystemType::PHYSICS:
            {
                LOAD_SYSTEM(DestroyPhysicsSystem, "Physics.so");
                DestroyPhysicsSystem((IPhysics**)System);
            } break;
        
            case ESystemType::SOUND:
            {
                LOAD_SYSTEM(DestroySoundSystem, "Sound.so");
                DestroySoundSystem((ISound**)System);
            } break;
        
            case ESystemType::TRANSFORM:
            {
                LOAD_SYSTEM(DestroyTransformSystem, "Transform.so");
                DestroyTransformSystem((ITransform**)System);
            } break;
        
            case ESystemType::WIDGET:
            {
                LOAD_SYSTEM(DestroyWidgetSystem, "Widget.so");
                DestroyWidgetSystem((IWidget**)System);
            } break;

            default:
            {
                ASSERT(!"", "Not a valid system");
            } break;
        }
    }
}
