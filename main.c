#include <bslug.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "oslink.h"

BSLUG_MODULE_GAME("RVYE");
BSLUG_MODULE_NAME("wawiihook");
BSLUG_MODULE_VERSION("v1.0");
BSLUG_MODULE_AUTHOR("InvoxiPlayGames");

bool in_mp = false;

char *UI_SafeTranslateString(char *stringName);
char *UI_SafeTranslateStringHook(char *stringName) {
    // Nintendo WFC label at top of MP main menu
    if (strcmp(stringName, "PLATFORM_PLAY_ONLINE") == 0)
        return "^6Hooked MP!";
    // Sign-in indicator in top right of SP main menu
    if (strcmp(stringName, "XBOXLIVE_SIGNEDINAS") == 0 || strcmp(stringName, "XBOXLIVE_NOTSIGNEDIN") == 0)
        return "^6Hooked SP!";
    return UI_SafeTranslateString(stringName);
}

void HookFunction(unsigned int OriginalAddress, void *StubFunction, void *NewFunction);

bool OSLinkHook(OSModuleHeader *header, void *bss, int fixed) {
    bool r = OSLink(header, bss, fixed);
    if (r == true) {
        uint32_t safeTranslateOffset = 0;
        // Detect which gamemode is being loaded based on module ID
        if (header->id == 2) {
            printf("Linked MP\n");
            in_mp = true;
            safeTranslateOffset = 0x00191f1c;
        } else if (header->id == 1) {
            printf("Linked SP\n");
            in_mp = false;
            safeTranslateOffset = 0x001b8170;
        }
        OSSectionInfo *sectionInfo = (OSSectionInfo *)header->sectionInfoOffset;
        // As per REL (File Format) @ Wiiki
        // "The least significant bit of this value is 1 if the section is executable and 0 otherwise, but the OS always zeroes out that bit for the offset calculation."
        uint32_t section1address = sectionInfo[1].sectionOffset & 0xFFFFFFFE;
        printf("Section 1 address: 0x%08x\n", section1address);
        HookFunction(section1address + safeTranslateOffset, UI_SafeTranslateString, UI_SafeTranslateStringHook);
    }
    return r;
}

BSLUG_MUST_REPLACE(OSLink, OSLinkHook);
