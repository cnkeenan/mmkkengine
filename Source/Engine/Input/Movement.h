#if !defined(MOVEMENT_H)

#include "Input.h"

// NOTE(EVERYONE): This for execute can be modified in the Input header if we decide to alter how we
//                 go about developing the input. If the character controls its own movement
//                 then we need to adjust the way the values are passed (pass a reference to the character)
//                 See the example of the command pattern: http://gameprogrammingpatterns.com/command.html
//                 to understand what I mean

class Movement : public Input
{
  public:
    virtual void execute(){};
};

#define MOVEMENT_H

#endif