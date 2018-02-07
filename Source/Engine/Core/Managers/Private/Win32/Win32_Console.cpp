/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
void PlatformManager::ChangeConsoleColor(EConsoleColor BackgroundColor, EConsoleColor ForegroundColor)
{
    HANDLE Console = GetStdHandle(STD_ERROR_HANDLE);

    WORD Attributes = 0;

    switch(ForegroundColor)
    {
        case EConsoleColor::RED:
        {
            Attributes = FOREGROUND_RED;
        } break;

        case EConsoleColor::GREEN:
        {
            Attributes = FOREGROUND_GREEN;
        } break;

        case EConsoleColor::BLUE:
        {
            Attributes = FOREGROUND_BLUE;
        } break;

        case EConsoleColor::WHITE:
        {
            Attributes = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
        } break;
    }
    
    switch(BackgroundColor)
    {
        case EConsoleColor::RED:
        {
            Attributes |= BACKGROUND_RED;
        } break;

        case EConsoleColor::GREEN:
        {
            Attributes |= BACKGROUND_GREEN;
        } break;

        case EConsoleColor::BLUE:
        {
            Attributes |= BACKGROUND_BLUE;
        } break;

        case EConsoleColor::WHITE:
        {
            Attributes |= BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED;
        } break;
    }
    SetConsoleTextAttribute(Console, Attributes);

}
