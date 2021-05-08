zi-dwm
============================
Patched version of DWM, with slight adjustment.

Keybinds
--------
TIPS: Switching between tiling mode or key that affecting tiles will always use MODKEY+Shift!

`mod` = Windows/Super/(Command?) Key

|-------------|-----------------------|
|key|description|
|-------------|-----------------------|
|`mod`+`space`|Spawn dmenu            |
|`mod`+`enter`|Spawn terminal (set to `kitty` by default)|
|`mod`+`b`    |Toggle bar             |
|`mod`+`shift`+`h`|Decrement gaps by 5|
|`mod`+`shift`+`l`|Increment gaps by 5|
|`mod`+`h`|Derement master window by 1|
|`mod`+`l`|Increment master window by 1|
|`mod`+`alt`+`shift`+`+`|Set gaps to 0|
|`mod`+`j` or `k`|Switch focus        |
|`mod`+`shift`+`j` or `k`|Switch focused window position|


`DWM's README`
-------------

```
Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
```
