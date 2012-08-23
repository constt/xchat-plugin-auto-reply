Xchat Plugin: auto reply
========================

Simple and almost useless auto reply plugin for xchat.

Usage:
-------
    # Auto Reply Plugin; Usage: AUTOREPLY [TRIGGERING_WORD] [AUTO_ANSWER]
    # Pass no parameters to disable auto reply
    
    /AUTOREPLY windows "tu doch mal lieber den linux!"
    
    # Auto Reply with trigger windows and answer tu doch mal lieber den linux!
    # enabled (on channel #trollbox)

Dependencies:
--------------
  * /usr/include/xchat/xchat-plugin.h

Compilation:
-------------
    g++ -Wl,--export-dynamic -Wconversion -Wsign-conversion -Wextra -Werror \
        -pedantic -Wall -Wextra -Wcast-align -Wcast-qual \
        -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op \
        -Wmissing-include-dirs -Wredundant-decls -Wstrict-overflow=5 \
        -Wswitch-default -Wundef -Wno-unused \
        -O1 -shared -fPIC \
        auto_reply.cpp -o auto_reply.so


