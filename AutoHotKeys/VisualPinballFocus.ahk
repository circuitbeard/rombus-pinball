#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

; Keep dmd on to
if WinExist("ahk_class MAME")
  WinSet, AlwaysOnTop, ON, ahk_class MAME

; Activate playing field
if WinExist("Visual Pinball Player")
  WinActivate