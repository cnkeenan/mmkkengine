/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#define RAW_X_AXIS 48
#define RAW_Y_AXIS 49
#define RAW_Z_AXIS 50
#define RAW_X_ROTATION 51
#define RAW_Y_ROTATION 52
#define RAW_Z_ROTATION 53
#define RAW_HAT 57

struct Win32_Window : public IWindow
{
    HWND m_Window;
    HDC m_DeviceContext;
    HGLRC m_RenderingContext;

    virtual void Initialize(const int Width, const int Height, const char* WindowName) final;
    virtual void ProcessOSWindowMessages() final;
    virtual void SwapOpenGLBuffers() final;
};

static RAWINPUTDEVICE Win32_CreateRawInputDevice(USHORT UsagePage, USHORT Usage, HWND Window)
{
    RAWINPUTDEVICE Result;
    Result.usUsagePage = UsagePage;
    Result.usUsage = Usage;
    Result.dwFlags = 0;
    Result.hwndTarget = Window;
    return Result;
}

static LRESULT CALLBACK Win32_WindowProcedure(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
    LRESULT Result = 0;

    switch(Message)
    {
        case WM_CREATE:
        {
            RAWINPUTDEVICE RawInputDevices[4];

            //NOTE(EVERYONE): All information related to UsagePages and Usage
            //found here http://www.usb.org/developers/hidpage/Hut1_12v2.pdf
            //UsagePage = 1 is for generic desktop controls            
            const USHORT MouseUsage = 2;
            const USHORT JoystickUsage = 4;
            const USHORT GamepadUsage = 5;
            const USHORT KeyboardUsage = 6;
            RawInputDevices[0] = Win32_CreateRawInputDevice(1, MouseUsage, Window);
            RawInputDevices[1] = Win32_CreateRawInputDevice(1, JoystickUsage, Window);
            RawInputDevices[2] = Win32_CreateRawInputDevice(1, GamepadUsage, Window);
            RawInputDevices[3] = Win32_CreateRawInputDevice(1, KeyboardUsage, Window);
            RegisterRawInputDevices(RawInputDevices, ARRAYCOUNT(RawInputDevices), sizeof(RAWINPUTDEVICE));
        } break;
        
        case WM_CLOSE:
        {
            PostQuitMessage(0);
        } break;

        default:
        {
            Result = DefWindowProc(Window, Message, WParam, LParam);
        } break;
    }
    
    return Result;
}

//NOTE(EVERYONE): We want the width and height to be the size of the client area not the window resolution.
//That is just a little bit bigger because of the padding.
void Win32_Window::Initialize(const int Width, const int Height, const char* WindowName)
{
    WNDCLASSEX WindowClass = {};
    WindowClass.cbSize = sizeof(WNDCLASSEX);
    WindowClass.hInstance = GetModuleHandle(0);
    WindowClass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    WindowClass.lpszClassName = WindowName;
    WindowClass.lpfnWndProc = Win32_WindowProcedure;

    if(RegisterClassEx(&WindowClass))
    {        
        RECT ClientRect{0, 0, Width, Height};
        DWORD Style = WS_OVERLAPPEDWINDOW;
        BOOL Result = AdjustWindowRectEx(&ClientRect, Style, FALSE, 0);
        if(Result)
        {
            m_Window = CreateWindow(WindowName, WindowName, Style, CW_USEDEFAULT, CW_USEDEFAULT,
                                    ClientRect.right-ClientRect.left, ClientRect.bottom-ClientRect.top,
                                    0, 0, WindowClass.hInstance, 0);
            if(m_Window)
            {
                ShowWindow(m_Window, SW_SHOW);
            }
            else
            {
                //TODO(JJ): Logging
            }
        }
        else
        {
            //TODO(JJ): Logging 
        }
    }
    else
    {
        //TODO(JJ): Logging
    }
}

void Win32_Window::ProcessOSWindowMessages()
{        
    MSG Message;
    while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
    {
        switch(Message.message)
        {
            case WM_INPUT:
            {
                //NOTE(EVERYONE): Using the platform to allocate memory. Generally more
                //light-weight than using new
                HANDLE Heap = GetProcessHeap();
                UINT BufferSize;
                GetRawInputData((HRAWINPUT)Message.lParam, RID_INPUT, nullptr, &BufferSize,
                                sizeof(RAWINPUTHEADER));

                RAWINPUT* RawInput = new RAWINPUT[BufferSize];                

                GetRawInputData((HRAWINPUT)Message.lParam, RID_INPUT, RawInput, &BufferSize,
                                sizeof(RAWINPUTHEADER));

                switch(RawInput->header.dwType)
                {
                    case RIM_TYPEKEYBOARD:
                    {
                        RAWKEYBOARD* Keyboard = &RawInput->data.keyboard;
                        LOG(INFO, "Make Code: %d", (int)Keyboard->MakeCode);
                        LOG(INFO, "Flags: %d", (int)Keyboard->Flags);
                        LOG(INFO, "Reserved: %d", (int)Keyboard->Reserved);
                        LOG(INFO, "VKey: %d", (int)Keyboard->VKey);
                        LOG(INFO, "Message: %d", Keyboard->Message);
                        LOG(INFO, "Extra Information: %l", Keyboard->ExtraInformation);
                        
                        
                    } break;

                    case RIM_TYPEMOUSE:
                    {
                        RAWMOUSE* Mouse = &RawInput->data.mouse;                        
                    } break;

                    //NOTE(EVERYONE): Joystick and gamepad since we don't check for any other device
                    case RIM_TYPEHID:
                    {
                        //TODO(JJ): Error checking and logging
                        GetRawInputDeviceInfo(RawInput->header.hDevice, RIDI_PREPARSEDDATA,
                                              nullptr, &BufferSize);
                        _HIDP_PREPARSED_DATA* PreparsedData = (_HIDP_PREPARSED_DATA*)operator new(BufferSize);                        
                        GetRawInputDeviceInfo(RawInput->header.hDevice, RIDI_PREPARSEDDATA,
                                              PreparsedData, &BufferSize);

                        HIDP_CAPS HIDCapabilities;
                        HidP_GetCaps(PreparsedData, &HIDCapabilities);

                        USHORT CapabilitiesSize = HIDCapabilities.NumberInputButtonCaps;
                        
                        HIDP_BUTTON_CAPS* ButtonCapabilities = new HIDP_BUTTON_CAPS[CapabilitiesSize];                        

                        HidP_GetButtonCaps(HidP_Input, ButtonCapabilities, &CapabilitiesSize,
                                           PreparsedData);

                        USHORT NumberOfButtons = ButtonCapabilities->Range.UsageMax -
                            ButtonCapabilities->Range.UsageMin+1;

                        CapabilitiesSize = HIDCapabilities.NumberInputValueCaps;
                        HIDP_VALUE_CAPS* ValueCapabilities = new HIDP_VALUE_CAPS[CapabilitiesSize];
                        
                        HidP_GetValueCaps(HidP_Input, ValueCapabilities, &CapabilitiesSize,
                                          PreparsedData);

                        ULONG UsageLength = NumberOfButtons;
                        USAGE* Usage = new USAGE[UsageLength];                        
                        HidP_GetUsages(HidP_Input, ButtonCapabilities->UsagePage, 0, Usage,
                                       &UsageLength, PreparsedData, (PCHAR)RawInput->data.hid.bRawData,
                                       RawInput->data.hid.dwSizeHid);

                        //NOTE(EVERYONE): Joystick buttons (aka gamepad)
                        for(ULONG ButtonIndex = 0; ButtonIndex < UsageLength; ButtonIndex++)
                        {
                            switch(Usage[ButtonIndex])
                            {
                                case 1:
                                {
                                    LOG(INFO, "Square");
                                } break;

                                case 2:
                                {
                                } break;

                                case 3:
                                {
                                } break;

                                case 4:
                                {
                                } break;

                                case 5:
                                {
                                } break;

                                case 6:
                                {
                                } break;

                                case 7:
                                {
                                } break;

                                case 8:
                                {
                                } break;

                                case 9:
                                {
                                } break;

                                case 10:
                                {
                                } break;

                                case 11:
                                {
                                } break;

                                case 12:
                                {
                                } break;                                
                            }
                        }

                        
                        //NOTE(EVERYONE): Joysticks
                        for(ULONG ValueIndex = 0; ValueIndex < HIDCapabilities.NumberInputValueCaps;
                            ValueIndex++)
                        {
                            ULONG Value;
                            HidP_GetUsageValue(HidP_Input, ValueCapabilities[ValueIndex].UsagePage, 0,
                                               ValueCapabilities[ValueIndex].Range.UsageMin, &Value,
                                               PreparsedData, (PCHAR)RawInput->data.hid.bRawData,
                                               RawInput->data.hid.dwSizeHid);

                            switch(ValueCapabilities[ValueIndex].Range.UsageMin)
                            {
                                case RAW_X_AXIS:
                                {
                                } break;

                                case RAW_Y_AXIS:
                                {
                                } break;

                                case RAW_Z_AXIS:
                                {
                                } break;

                                case RAW_X_ROTATION:
                                {
                                } break;

                                case RAW_Y_ROTATION:
                                {
                                } break;

                                case RAW_Z_ROTATION:
                                {
                                } break;

                                case RAW_HAT:
                                {
                                } break;
                            }
                        }

                        delete[] Usage;
                        delete[] ValueCapabilities;
                        delete[] ButtonCapabilities;
                        operator delete(PreparsedData);

                        
                    } break;
                }

                delete[] RawInput;                
            } break;

            case WM_MOUSEMOVE:
            {
            } break;
            
            case WM_QUIT:
            {
                EnvironmentManager::Get()->ExecutionState(EExecutionState::EXIT);
            } break;

            default:
            {
                TranslateMessage(&Message);
                DispatchMessage(&Message);
            } break;
        }
    }
}

void Win32_Window::SwapOpenGLBuffers()
{
    if(m_DeviceContext)
        SwapBuffers(m_DeviceContext);
}

#undef CreateWindow
IWindow* PlatformManager::CreateWindow(const int Width, const int Height, const char* WindowName)
{
    IWindow* Result = new Win32_Window;
    Result->Initialize(Width, Height, WindowName);
    return Result;
}
