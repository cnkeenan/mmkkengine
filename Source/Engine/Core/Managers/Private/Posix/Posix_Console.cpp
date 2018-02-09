void PlatformManager::ChangeConsoleColor(EConsoleColor BackgroundColor, EConsoleColor ForegroundColor)
{
    switch(ForegroundColor)
    {
        case EConsoleColor::RED:
        {
            system("tput setaf 1");
        } break;

        case EConsoleColor::GREEN:
        {
            system("tput setaf 2");
        } break;

        case EConsoleColor::BLUE:
        {
            system("tput setaf 4");
        } break;

        case EConsoleColor::WHITE:
        {
            system("tput setaf 7");
        } break;

        case EConsoleColor::BLACK:
        {
            system("tput setaf 0");
        } break;

    }
    
    switch(BackgroundColor)
    {
        case EConsoleColor::RED:
        {
            system("tput setab 1");
        } break;

        case EConsoleColor::GREEN:
        {
            system("tput setab 2");
        } break;

        case EConsoleColor::BLUE:
        {
            system("tput setab 4");
        } break;

        case EConsoleColor::WHITE:
        {
            system("tput setab 7");
        } break;
        case EConsoleColor::BLACK:
        {
            system("tput setab 0");
        } break;
    }
}
