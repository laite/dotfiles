#!/bin/bash
sleep 3
# key definitions for 1337 keyboard usage
# "original" (finnish) meanings of keys abbreviated in comments

# Note - requires xcape!
setxkbmap -option 'caps:ctrl_modifier'
xcape -e 'Caps_Lock=Escape'
# 16 = number 7
xmodmap -e 'keycode 16 = 7 underscore 7 slash braceleft NoSymbol braceleft'
# key 21 = left to backspace
xmodmap -e 'keycode 21 = asciitilde dead_tilde asciitilde dead_tilde grave equal grave equal'

# key 30 = u
xmodmap -e 'keycode 30 = u U u U udiaeresis Udiaeresis udiaeresis Udiaeresis'
# key 34 = swedish 'o'
xmodmap -e 'keycode 34 = bracketleft braceleft bracketleft braceleft parenleft dead_abovering parenright dead_abovering'
# key 35 = dead_circum/dead_tilde
xmodmap -e 'keycode 35 = bracketright braceright bracketright braceright parenright dead_abovering parenright dead_abovering'

# key 38 = a
xmodmap -e 'keycode 38 = a A a A dead_abovering SCHWA dead_abovering SCHWA'

# key 49 = section/half
xmodmap -e 'keycode 49 = asciicircum dollar asciicircum dollar dead_acute NoSymbol dead_acute NoSymbol'
# key 51 = apostrophe/asterisk
xmodmap -e 'keycode 51 = apostrophe asterisk apostrophe asterisk quotedbl dead_caron quotedbl dead_breve'

# key 61 = (line)
xmodmap -e 'keycode 61 = slash minus underscore slash underscore dead_belowcomma underscore dead_belowcomma'

# change caps lock to escape (great in vim)
# xmodmap -e 'clear Lock' -e 'keycode 0x42 = Control_L' -e 'add Control = Control_L'

