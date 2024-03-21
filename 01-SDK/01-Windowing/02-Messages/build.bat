cls

cl.exe /c /EHsc  Window.cpp

link.exe  Window.obj Msimg32.lib User32.lib GDI32.lib  /SUBSYSTEM:WINDOWS

Window.exe