// https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

#include <stdio.h>
#include <windows.h>
#include <process.h>

volatile int thread_quit = 0;
volatile int main_quit   = 0;

struct tag_key_list
{
    const int       key;
    const char      key_name[16];
    volatile int    key_times;
    volatile int    key_state;
};

static struct tag_key_list key_list[] = {
    { VK_LBUTTON,        "LBUTTON"          , 0, 0 },   // 0x01
    { VK_RBUTTON,        "RBUTTON"          , 0, 0 },
    { VK_CANCEL,         "CANCEL"           , 0, 0 },
    { VK_MBUTTON,        "MBUTTON"          , 0, 0 },
    { VK_BACK,           "BACK"             , 0, 0 },
    { VK_TAB,            "TAB"              , 0, 0 },
    { VK_RETURN,         "RETURN"           , 0, 0 },

    { VK_PAUSE,          "PAUSE"            , 0, 0 },   // 0x13
    { VK_CAPITAL,        "CAPITAL"          , 0, 0 },
    { VK_ESCAPE,         "ESCAPE"           , 0, 0 },

    { VK_SPACE,          "SPACE"            , 0, 0 },   // 0x20
    { VK_PRIOR,          "PRIOR"            , 0, 0 },
    { VK_NEXT,           "NEXT"             , 0, 0 },
    { VK_END,            "END"              , 0, 0 },
    { VK_HOME,           "HOME"             , 0, 0 },
    { VK_LEFT,           "LEFT"             , 0, 0 },
    { VK_UP,             "UP"               , 0, 0 },
    { VK_RIGHT,          "RIGHT"            , 0, 0 },
    { VK_DOWN,           "DOWN"             , 0, 0 },
    { VK_SELECT,         "SELECT"           , 0, 0 },
    { VK_PRINT,          "PRINT"            , 0, 0 },
    { VK_EXECUTE,        "EXECUTE"          , 0, 0 },
    { VK_SNAPSHOT,       "SNAPSHOT"         , 0, 0 },
    { VK_INSERT,         "INSERT"           , 0, 0 },
    { VK_DELETE,         "DELETE"           , 0, 0 },
    { VK_HELP,           "HELP"             , 0, 0 },

    { '0',               "0"                , 0, 0 },   // 0x30
    { '1',               "1"                , 0, 0 },
    { '2',               "2"                , 0, 0 },
    { '3',               "3"                , 0, 0 },
    { '4',               "4"                , 0, 0 },
    { '5',               "5"                , 0, 0 },
    { '6',               "6"                , 0, 0 },
    { '7',               "7"                , 0, 0 },
    { '8',               "8"                , 0, 0 },
    { '9',               "9"                , 0, 0 },

    { 'A',               "A"                , 0, 0 },   // 0x41
    { 'B',               "B"                , 0, 0 },
    { 'C',               "C"                , 0, 0 },
    { 'D',               "D"                , 0, 0 },
    { 'E',               "E"                , 0, 0 },
    { 'F',               "F"                , 0, 0 },
    { 'G',               "G"                , 0, 0 },
    { 'H',               "H"                , 0, 0 },
    { 'I',               "I"                , 0, 0 },
    { 'J',               "J"                , 0, 0 },
    { 'K',               "K"                , 0, 0 },
    { 'L',               "L"                , 0, 0 },
    { 'M',               "M"                , 0, 0 },
    { 'N',               "N"                , 0, 0 },
    { 'O',               "O"                , 0, 0 },
    { 'P',               "P"                , 0, 0 },
    { 'Q',               "Q"                , 0, 0 },
    { 'R',               "R"                , 0, 0 },
    { 'S',               "S"                , 0, 0 },
    { 'T',               "T"                , 0, 0 },
    { 'U',               "U"                , 0, 0 },
    { 'V',               "V"                , 0, 0 },
    { 'W',               "W"                , 0, 0 },
    { 'X',               "X"                , 0, 0 },
    { 'Y',               "Y"                , 0, 0 },
    { 'Z',               "Z"                , 0, 0 },

    { VK_LWIN,           "LWIN"             , 0, 0 },   // 0x5B
    { VK_RWIN,           "RWIN"             , 0, 0 },
    { VK_APPS,           "APPS"             , 0, 0 },
    //{ VK_SLEEP,            "SLEEP"            , 0, 0 },

    { VK_NUMPAD0,        "NUMPAD0"          , 0, 0 },   // 0x60
    { VK_NUMPAD1,        "NUMPAD1"          , 0, 0 },
    { VK_NUMPAD2,        "NUMPAD2"          , 0, 0 },
    { VK_NUMPAD3,        "NUMPAD3"          , 0, 0 },
    { VK_NUMPAD4,        "NUMPAD4"          , 0, 0 },
    { VK_NUMPAD5,        "NUMPAD5"          , 0, 0 },
    { VK_NUMPAD6,        "NUMPAD6"          , 0, 0 },
    { VK_NUMPAD7,        "NUMPAD7"          , 0, 0 },
    { VK_NUMPAD8,        "NUMPAD8"          , 0, 0 },
    { VK_NUMPAD9,        "NUMPAD9"          , 0, 0 },
    { VK_MULTIPLY,       "MULTIPLY"         , 0, 0 },
    { VK_ADD,            "ADD"              , 0, 0 },
    { VK_SEPARATOR,      "SEPARATOR"        , 0, 0 },
    { VK_SUBTRACT,       "SUBTRACT"         , 0, 0 },
    { VK_DECIMAL,        "DECIMAL"          , 0, 0 },
    { VK_DIVIDE,         "DIVIDE"           , 0, 0 },

    { VK_F1,             "F1"               , 0, 0 },   // 0x70
    { VK_F2,             "F2"               , 0, 0 },
    { VK_F3,             "F3"               , 0, 0 },
    { VK_F4,             "F4"               , 0, 0 },
    { VK_F5,             "F5"               , 0, 0 },
    { VK_F6,             "F6"               , 0, 0 },
    { VK_F7,             "F7"               , 0, 0 },
    { VK_F8,             "F8"               , 0, 0 },
    { VK_F9,             "F9"               , 0, 0 },
    { VK_F10,            "F10"              , 0, 0 },
    { VK_F11,            "F11"              , 0, 0 },
    { VK_F12,            "F12"              , 0, 0 },
    { VK_F13,            "F13"              , 0, 0 },
    { VK_F14,            "F14"              , 0, 0 },
    { VK_F15,            "F15"              , 0, 0 },
    { VK_F16,            "F16"              , 0, 0 },
    { VK_F17,            "F17"              , 0, 0 },
    { VK_F18,            "F18"              , 0, 0 },
    { VK_F19,            "F19"              , 0, 0 },
    { VK_F20,            "F20"              , 0, 0 },
    { VK_F21,            "F21"              , 0, 0 },
    { VK_F22,            "F22"              , 0, 0 },
    { VK_F23,            "F23"              , 0, 0 },
    { VK_F24,            "F24"              , 0, 0 },

    { VK_NUMLOCK,        "NUMLOCK"          , 0, 0 },   // 0x90
    { VK_SCROLL,         "SCROLL"           , 0, 0 },
    { VK_OEM_FJ_JISHO,   "OEM_FJ_JISHO"     , 0, 0 },
    { VK_OEM_FJ_MASSHOU, "OEM_FJ_MASSHOVK"  , 0, 0 },
    { VK_OEM_FJ_TOUROKU, "OEM_FJ_TOUROKVK"  , 0, 0 },
    { VK_OEM_FJ_LOYA,    "OEM_FJ_LOYA"      , 0, 0 },
    { VK_OEM_FJ_ROYA,    "OEM_FJ_ROYA"      , 0, 0 },

    { VK_LSHIFT,         "LSHIFT"           , 0, 0 },   // 0xA0
    { VK_RSHIFT,         "RSHIFT"           , 0, 0 },
    { VK_LCONTROL,       "LCONTROL"         , 0, 0 },
    { VK_RCONTROL,       "RCONTROL"         , 0, 0 },
    { VK_LMENU,          "LMENU"            , 0, 0 },
    { VK_RMENU,          "RMENU"            , 0, 0 },

    { 0xc0,              "`~"               , 0, 0 },   // 0thers
    { 0xbd,              "-_"               , 0, 0 },
    { 0xbb,              "=+"               , 0, 0 },
    { 0xdb,              "[{"               , 0, 0 },
    { 0xdd,              "]}"               , 0, 0 },
    { 0xdc,              "\'|"              , 0, 0 },
    { 0xba,              ";:"               , 0, 0 },
    { 0xde,              "'\""              , 0, 0 },
    { 0xbc,              ",<"               , 0, 0 },
    { 0xbe,              ".>"               , 0, 0 },
    { 0xbf,              "/?"               , 0, 0 },
};

unsigned __stdcall thread_keypress(void* args)
{
    int i, key_state;
    while (! thread_quit)
    {
        for (i = 0; i < sizeof(key_list) / sizeof(key_list[0]); ++i)
        {
            key_state = !!GetAsyncKeyState(key_list[i].key);
            key_list[i].key_times += (key_state != 0 && key_list[i].key_state == 0);
            key_list[i].key_state = key_state;
        }
        Sleep(10);
    }

    // save
    for (i = 0; i < sizeof(key_list) / sizeof(key_list[0]); ++i)
    {
        if (key_list[i].key_times > 0)
        {
            char name[128]  = {0};
            char value[128] = {0};
            int key_times = GetPrivateProfileInt("Key", ltoa(key_list[i].key, name, 10), 0, ".\\KeyPressStatistics.ini");
            WritePrivateProfileString("Key", name, ltoa(key_list[i].key_times + key_times, value, 10), ".\\KeyPressStatistics.ini");
        }
    }

    return 0;
}

int compare_key_times(const void * a, const void * b)
{
    const struct tag_key_list* aa = a;
    const struct tag_key_list* bb = b;
    return (bb->key_times - aa->key_times);
}

void print_result()
{
    int i;
    struct tag_key_list sort_list[256];
    memcpy(sort_list, key_list, sizeof(key_list));
    qsort (sort_list, sizeof(key_list) / sizeof(key_list[0]), sizeof(key_list[0]), compare_key_times);

    printf("-------------------------------\n");
    for (i = 0; i < sizeof(key_list) / sizeof(key_list[0]); ++i)
    {
        if (sort_list[i].key_times > 0)
            printf("%6d  =  %s (%d)\n", sort_list[i].key_times, sort_list[i].key_name, sort_list[i].key);
    }
}

void input_process(const char* _cmd)
{
    if (strcmp(_cmd, "q") == 0)             { main_quit = thread_quit = 1;  }
    else if (strcmp(_cmd, "cls") == 0)      { system("cls");    }
    else if (strcmp(_cmd, "print") == 0)    { print_result();   }
}

int main()
{
    HANDLE handle;
    handle = (HANDLE)_beginthreadex(0, 0, thread_keypress, 0, 0, 0);

    while (! main_quit)
    {
        char buf[256] = {0};
        printf("=>");
        gets(buf);      //scanf("%s", buf);

        input_process(buf);
    }

    WaitForSingleObject(handle, INFINITE);
    CloseHandle(handle);

    return 0;
}
