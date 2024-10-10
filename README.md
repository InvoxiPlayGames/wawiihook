# wawiihook

A demonstration of hooking OSLink on the Wii to hook functions when REL (relocatable modules) are loaded.

RVYE was chosen because it uses relocatable modules for each gamemode and comes with symbol maps for the RELs.

Uses Chadderz's brainslug-wii for code injection and hooking DOL functions: https://github.com/Chadderz121/brainslug-wii

Documentation on REL files: https://wiki.tockdom.com/wiki/REL_(File_Format)

Lazy symbol for RVYE:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<symbols>
    <!-- actually "Link" -->
    <symbol name="OSLink" size="0x2DC" offset="0x0">
        <data>
            94 21 ff e0 7c 08 02 a6 90 01 00 24 38 00 00 00
			93 e1 00 1c 7c bf 2b 78 93 c1 00 18 7c 9e 23 78
			93 a1 00 14
        </data>
    </symbol>
</symbols>
```
