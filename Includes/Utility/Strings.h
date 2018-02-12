#if !defined(STRINGS_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Utility/Libs.h>
/*NOTE(EVERYONE):
  @param String : A pointer to the string that is to be searched.
  @param StringToFind : The value of the string that we are searching for.
  @return : Returns the offset in the String pointer to the first found string sequence,
  or nullptr if the string cannot be found.
 */
inline const char* LocateString(const char* String, const char* StringToFind)
{    
    ptr_size StackSize = 0;

    //IMPORTANT: Do not include the null terminated value
    ptr_size LengthOfString = strlen(StringToFind);    

    char* At = (char*)String;
    while(*At)
    {
        if(*At == StringToFind[StackSize])
            StackSize++;
        else
            StackSize = 0;

        At++;
        if(StackSize == LengthOfString)
            return (const char*)(At-LengthOfString);
    }

    return nullptr;
}

#define STRINGS_H
#endif
