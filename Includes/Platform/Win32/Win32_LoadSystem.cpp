/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

ISystem* PlatformManager::LoadSystem(ESystemType SystemType)
{
    ISystem* Result = nullptr;

#define LOAD_SYSTEM(x, y)     fp_##x* x = (fp_##x*)GetProcAddress(LoadLibrary(y), #x)
            
    
    switch(SystemType)
    {
        case ESystemType::AI:
        {
            LOAD_SYSTEM(CreateAISystem, "AI.dll");
            Result = CreateAISystem();
            
        } break;

        /*
        case ESystemType::COLLISION:
        {
            LOAD_SYSTEM(CreateCollisionSystem, "Collision.dll");
            Result = CreateCollisionSystem();
        } break;
        
        case ESystemType::GRAPHICS:
        {
            LOAD_SYSTEM(CreateGraphicsSystem, "Graphics.dll");
            Result = CreateGraphicsSystem();
        } break;
        
        case ESystemType::INPUT:
        {
            LOAD_SYSTEM(CreateInputSystem, "Input.dll");
            Result = CreateInputSystem();
        } break;
        
        case ESystemType::PHYSICS:
        {
            LOAD_SYSTEM(CreatePhysicsSystem, "Physics.dll");
            Result = CreatePhysicsSystem();
        } break;
        
        case ESystemType::SOUND:
        {
            LOAD_SYSTEM(CreateSoundSystem, "Sound.dll");
            Result = CreateSoundSystem();
        } break;
        
        case ESystemType::TRANSFORM:
        {
            LOAD_SYSTEM(CreateTransformSystem, "Transform.dll");
            Result = CreateTransformSystem();
        } break;
        
        case ESystemType::WIDGET:
        {
            LOAD_SYSTEM(CreateWidgetSystem, "Widget.dll");
            Result = CreateWidgetSystem();
        } break;

        */
        default:
        {
            ASSERT(!"", "Not a valid system");
        } break;
    }

    return nullptr;
}

void PlatformManager::UnloadSystem(ISystem** System)
{

    if((*System))
    {
        switch((*System)->GetType())
        {
            case ESystemType::AI:
            {
                LOAD_SYSTEM(DestroyAISystem, "AI.dll");
                DestroyAISystem((IAI**)System);
            
            } break;

            /*
              case ESystemType::COLLISION:
              {
              LOAD_SYSTEM(DestroyCollisionSystem, "Collision.dll");
              DestroyCollisionSystem((ICollision**)System);
              } break;
        
              case ESystemType::GRAPHICS:
              {
              LOAD_SYSTEM(DestroyGraphicsSystem, "Graphics.dll");
              DestroyGraphicsSystem((IGraphics**)System);
              } break;
        
              case ESystemType::INPUT:
              {
              LOAD_SYSTEM(DestroyInputSystem, "Input.dll");
              DestroyInputSystem((IInput**)System);
              } break;
        
              case ESystemType::PHYSICS:
              {
              LOAD_SYSTEM(DestroyPhysicsSystem, "Physics.dll");
              DestroyPhysicsSystem((IPhysics**)System);
              } break;
        
              case ESystemType::SOUND:
              {
              LOAD_SYSTEM(DestroySoundSystem, "Sound.dll");
              DestroySoundSystem((ISound**)System);
              } break;
        
              case ESystemType::TRANSFORM:
              {
              LOAD_SYSTEM(DestroyTransformSystem, "Transform.dll");
              DestroyTransformSystem((ITransform**)System);
              } break;
        
              case ESystemType::WIDGET:
              {
              LOAD_SYSTEM(DestroyWidgetSystem, "Widget.dll");
              DestroyWidgetSystem((IWidget**)System);
              } break;

            */
            default:
            {
                ASSERT(!"", "Not a valid system");
            } break;
        }
    }
}
