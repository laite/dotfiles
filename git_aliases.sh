#!/bin/bash
git config --global alias.st 'status -sb'
git config --global alias.hi 'log --pretty=format:"%C(yellow)%h%x09%Creset%ad %C(blue)%an%Creset %s%C(yellow)%d%Creset" --date=short --decorate --graph'
