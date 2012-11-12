#!/bin/bash

xmodmap -e "keycode 16 = 7 underscore 7 slash braceleft NoSymbol braceleft"
xmodmap -e "keycode 61 = slash minus underscore endash dead_belowcomma endash"
xmodmap -e 'keycode 35 = quotedbl asciicircum quotedbl asciicircum asciitilde dead_macron dead_tilde dead_macron'
xmodmap -e 'keycode 21 = underscore acute underscore acute grave equal grave equal'
