# V
Tiny vi-like text editor in only 100 lines of C++ code!

# Whi did I make it?
    I've been suffering from redundancy throughout my life.
    When it comes to text editors I really like vi-like ones,
    however there's a whole lot of issues with those existing out
    there. For instance VIM is perfect but needs time and effort
    for customization (mostly turning things off as I use only
    maybe 10% of what it's capable of). On the other hands VI is    
    another option but there's no such a version I loved - busybox VI
    is something I've been using on a daily basis but sometimes it's
    buggy (like when do multiple undos). So eventually I decided to make
    something on my own, something that would incorporate the most loved
    features from VI on the one hand meanwhile simplifying others to
    make them more accessible and intuitive.

# Features
    V is a modal editor like VI or VIM but unlikely the latter ones it
    only has 2 modes - command & insert dropping "ex" mode where user
    can type ":". Since the navigation is limited "w" is used to write
    bytes to the file and "q" allows to exit. There's no check for modified
    flag so "q" would exit forcingly. Also count behaves differently - it's
    only supported for yanking/deleting.

# Commands
    v file.txt          opens file, if no file specified it saves to "noname.txt"
                        if file doesn't exists it opens empty buffer but would
                        save the file using the specified file name

    ESC                 reset count, go to command mode

    h, j, k, l          works like in VI/VIM but without count (arrow keys are not supported)
    i, a, A, o, O       works like in VI/VIM
    x, r, R, G          works like in VI/VIM
    y, d, p             works like in VI/VIM but only linewise
    
    #                   equal to HOME
    $                   equal to END

    [count]             when count is specified it works like autoindent
    [count] SPACE       insert spaces into [count] lines 
    [count] BACKSPACE   remove chars from [count] lines
 
    w                   write current file to disk
    q                   force quit

# Video demonstration

