#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#define STUB_FUNCTION(x)                   \
    void x()                           \
    {                                  \
        asm("li 0, " LINE_STRING ";"); \
    }

STUB_FUNCTION(UI_SafeTranslateString)
