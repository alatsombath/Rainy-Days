[Variables]

Bands=35
; Number of raindrops - Activate Rainy Days\GenerateBands.ini skin after changing this value

Color=128,160,255
; (Do not add an alpha value)

BarWidth=2
; Raindrop width

BarHeight=81
; Maximum raindrop height

BarGap=56
; Spacing between the raindrops

RainSpeed=50

RainConstant=1
; Falling speed when no sound is playing

RainCover=#WORKAREAHEIGHT#
; Rainfall height

AverageSize=0
; Average sound levels over time to provide continuity

LoudnessEqualization=1
; Increases visibility for quiet audio sources when applicable

FFTSize=1024
FFTOverlap="(#FFTSize#-512)"
FFTAttack=0
FFTDecay=0
FreqMin=30
FreqMax=10000
Sensitivity=24
; http://docs.rainmeter.net/manual-beta/plugins/audiolevel

MusicPlayer=None
; Music player process name, such as "VLC" (not "VLC.exe")

FirstBandIndex=1
; "0" band should be skipped for aesthetic purpose

IdleAudioTimeout=1
; How long before hiding the visualizer when no sound is playing

; Environment variables for settings window
SkinGroup=RainyDays
Config=Rainy Days
ConfigPath=#ROOTCONFIGPATH##Config#.ini
WriteVariable=Color
Slant=None
Invert=0
Channel=Avg
Port=Output
ID=
