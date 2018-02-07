#if !defined(INPUTDELEGATION_H)

#include "Input.h"

// NOTE(EVERYONE): The actual private section of this class is a set of pointers to Input, each one representing
//                 the different input available, (arrows, etc). Since this is platform dependent, I left this
//                 intentionally blank to be revisited at a different or later date.

class InputDelegation
{
  public:
    void HandleInput();

  private:
    /* Here we would add pointers to Input regarding the types of input
       We allow. This is platform dependent, so we will revisit
    */
};

#define INPUTDELEGATION_H

#endif