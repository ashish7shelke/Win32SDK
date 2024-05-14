cls

cl.exe /c /EHsc  Window.cpp

rc.exe Window.rc

link.exe  Window.obj Window.res Msimg32.lib User32.lib GDI32.lib  /SUBSYSTEM:WINDOWS

Window.exe