#include <stdbool.h>
#include <stdint.h>

// Documentation from https://wiki.tockdom.com/wiki/REL_(File_Format)

typedef struct _OSModuleHeader_t {
    uint32_t id; // 0x0
    uint32_t next; // 0x4
    uint32_t prev; // 0x8
    uint32_t numSections; // 0xC
    uint32_t sectionInfoOffset; // 0x10
    uint32_t nameOffset; // 0x14
    uint32_t nameSize; // 0x18
    uint32_t version; // 0x1C
    uint32_t bssSize; // 0x20
    uint32_t relOffset; // 0x24
    uint32_t impOffset; // 0x28
    uint32_t impSize; // 0x2c
    uint8_t prologSection; // 0x30
    uint8_t epilogSection; // 0x31
    uint8_t unresolvedSection; // 0x32
    uint8_t bssSection; // 0x33
    uint32_t prolog; // 0x34
    uint32_t epilog; // 0x38
    uint32_t unresolved; // 0x3c
    uint32_t align; // 0x40
    uint32_t bssAlign; // 0x44
    uint32_t fixSize; // 0x48
} OSModuleHeader;

typedef struct _OSSectionInfo {
    uint32_t sectionOffset;
    uint32_t sectionSize;
} OSSectionInfo;

int j = sizeof(OSModuleHeader);

// Technically we are hooking "Link", not OSLink
bool OSLink(OSModuleHeader *header, void *bss, int fixed);
