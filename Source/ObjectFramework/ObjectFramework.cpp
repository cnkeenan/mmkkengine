/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>

static IMemoryManager* gMemoryManager;

#include "UScene.cpp"
#include "UWorld.cpp"
#include "ObjectConstructor.cpp"
#include "UObject.cpp"
#include "UEntity.cpp"
#include "UController.cpp"
#include "UWidget.cpp"
#include "UAIController.cpp"
#include "UPlayerController.cpp"
#include "UActor.cpp"
#include "UPawn.cpp"

//NOTE(EVERYONE): if the framework needs anything from the engine (like the managers) pass it in this
//function
void InitializeFramework(IMemoryManager* MemoryManager)
{
    gMemoryManager = MemoryManager;
}

void* operator new(ptr_size Size)
{
    return gMemoryManager->Allocate(Size);
}

void* operator new[](ptr_size Size)
{
    return gMemoryManager->Allocate(Size);
}

void operator delete(void* Pointer)
{
    gMemoryManager->Free(Pointer);
}

void operator delete[](void* Pointer)
{
    gMemoryManager->Free(Pointer);
}
