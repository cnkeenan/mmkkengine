#if !defined(OBJECTFRAMEWORK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

#include <Utility/PlatformDetection.h>

#ifdef FRAMEWORK_EXPORT
#define OBJECTFRAMEWORK_API EXPORT
#else
#define OBJECTFRAMEWORK_API IMPORT
#endif

#include <Utility/AtomicTypes.h>
#include <Utility/Macro.h>
#include <Utility/Libs.h>
#include <Utility/Pool.h>


#include <Interfaces/Systems/ISystem.h>

#include "UScene.h"
#include "ObjectConstructor.h"
#include "UWorld.h"
#include "UObject.h"
#include "UEntity.h"
#include "UController.h"
#include "UWidget.h"
#include "UAIController.h"
#include "UPlayerController.h"
#include "UActor.h"
#include "UPawn.h"

#include <Interfaces/Systems/IScene.h>
#include <Interfaces/Systems/IObject.h>
#include <Interfaces/Systems/ITask.h>
#include <Interfaces/Systems/AI/IAI.h>
#include <Interfaces/Systems/AI/IAIScene.h>
#include <Interfaces/Systems/AI/IAIObject.h>
#include <Interfaces/Systems/AI/IAITask.h>
#include <Interfaces/Systems/Collision/ICollision.h>
#include <Interfaces/Systems/Collision/ICollisionScene.h>
#include <Interfaces/Systems/Collision/ICollisionObject.h>
#include <Interfaces/Systems/Collision/ICollisionTask.h>
#include <Interfaces/Systems/Graphics/IGraphics.h>
#include <Interfaces/Systems/Graphics/IGraphicsScene.h>
#include <Interfaces/Systems/Graphics/IGraphicsObject.h>
#include <Interfaces/Systems/Graphics/IGraphicsTask.h>
#include <Interfaces/Systems/Input/IInput.h>
#include <Interfaces/Systems/Input/IInputScene.h>
#include <Interfaces/Systems/Input/IInputObject.h>
#include <Interfaces/Systems/Input/IInputTask.h>
#include <Interfaces/Systems/Physics/IPhysics.h>
#include <Interfaces/Systems/Physics/IPhysicsScene.h>
#include <Interfaces/Systems/Physics/IPhysicsObject.h>
#include <Interfaces/Systems/Physics/IPhysicsTask.h>
#include <Interfaces/Systems/Sound/ISound.h>
#include <Interfaces/Systems/Sound/ISoundScene.h>
#include <Interfaces/Systems/Sound/ISoundObject.h>
#include <Interfaces/Systems/Sound/ISoundTask.h>
#include <Interfaces/Systems/Transform/ITransform.h>
#include <Interfaces/Systems/Transform/ITransformScene.h>
#include <Interfaces/Systems/Transform/ITransformObject.h>
#include <Interfaces/Systems/Transform/ITransformTask.h>
#include <Interfaces/Systems/Widget/IWidget.h>
#include <Interfaces/Systems/Widget/IWidgetScene.h>
#include <Interfaces/Systems/Widget/IWidgetObject.h>
#include <Interfaces/Systems/Widget/IWidgetTask.h>


#define OBJECTFRAMEWORK_H
#endif
