[Variables]

; Refresh the skin after updating these settings!


; DISPLAY
; =======

Bands=64
; Number of raindrops

Color=128,160,255

BarWidth=1
; Raindrop width

BarHeight=(#WORKAREAHEIGHT#/8)
; Maximum raindrop height
; "#WORKAREAHEIGHT#" is generally your monitor's height
; http://docs.rainmeter.net/manual-beta/variables/built-in-variables#WORKAREAXYWH

BarGap=24
; Gap between the raindrops


; MECHANICS
; =========

RainSpeed=100
; Rainfall speed

RainConstant=1
; Rainfall speed when no sound is playing

RainCover=#WORKAREAHEIGHT#
; Rainfall height


; AUDIO
; =====

Sensitivity=42
; Increase this if the spectrum is not visible enough

FFTAttack=350
FFTDecay=350
; Decrease for faster response, increase for slower response
; http://docs.rainmeter.net/manual-beta/plugins/audiolevel#FFTAttack

FFTSize=2048
FFTOverlap=(#FFTSize#/2)
FreqMin=40
FreqMax=16000
Port=Output
; Additional audio settings
; http://docs.rainmeter.net/manual-beta/plugins/audiolevel#FFTOptions
