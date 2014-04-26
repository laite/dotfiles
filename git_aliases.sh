#!/bin/bash
git config alias.st 'status -sb'
git config alias.hi 'log --pretty=format:"%C(yellow)%h%x09%Creset%ad %C(blue)%an%Creset %s" --date=short --decorate --graph'
