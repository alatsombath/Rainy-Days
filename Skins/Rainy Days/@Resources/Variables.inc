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

RainSpeed=40

RainConstant=2
; Falling speed when no sound is playing

RainCover=#WORKAREAHEIGHT#
; Rainfall height

AverageSize=0
; Average sound levels over time to provide continuity

LoudnessEqualization=1
; Increases visibility for quiet audio sources when applicable

FFTSize=10240
FFTOverlap="(#FFTSize#-256)"
FFTAttack=0
FFTDecay=0
FreqMin=20
FreqMax=20000
Sensitivity=17
; http://docs.rainmeter.net/manual-beta/plugins/audiolevel

MusicPlayer=None
; Music player process name

FirstBandIndex=1

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
