[Rainmeter]
Update=32
DefaultUpdateDivider=-1
Group=RainyDays

ContextTitle="Change color..."
ContextAction=[!ActivateConfig "Rainy Days\InputSolidColor"]
ContextTitle2="Rain settings..."
ContextAction2=[!WriteKeyValue Variables Config "#CURRENTCONFIG#" "#@#Variables.inc"][!WriteKeyValue Variables ConfigPath "#CURRENTPATH##CURRENTFILE#" "#@#Variables.inc"][!ActivateConfig "Rainy Days\ContextMenus" "Rain.ini"]
ContextTitle3="Display settings..."
ContextAction3=[!WriteKeyValue Variables Config "#CURRENTCONFIG#" "#@#Variables.inc"][!WriteKeyValue Variables ConfigPath "#CURRENTPATH##CURRENTFILE#" "#@#Variables.inc"][!ActivateConfig "Rainy Days\ContextMenus" "Display.ini"]
ContextTitle4="Audio settings..."
ContextAction4=[!WriteKeyValue Variables Config "#CURRENTCONFIG#" "#@#Variables.inc"][!WriteKeyValue Variables ConfigPath "#CURRENTPATH##CURRENTFILE#" "#@#Variables.inc"][!ActivateConfig "Rainy Days\ContextMenus" "Audio.ini"]
ContextTitle5=---
ContextTitle6="Edit local settings..."
ContextAction6=["Notepad" "#CURRENTPATH##CURRENTFILE#"]
ContextTitle7="Edit global settings..."
ContextAction7=["Notepad" "#@#Variables.inc"]

[MeasureAudio]
Measure=Plugin
Group=Audio
Plugin=AudioLevel
Port=#Port#
ID=#ID#
FFTSize=#FFTSize#
FFTOverlap=#FFTOverlap#
FFTAttack=#FFTAttack#
FFTDecay=#FFTDecay#
Bands=#Bands#
FreqMin=#FreqMin#
FreqMax=#FreqMax#
Sensitivity=#Sensitivity#
UpdateDivider=1

; Hide meters and disable measures when idle
IfCondition=(MeasureAudio < 0.000000000000000001)
IfTrueAction=[!DisableMeasure MeasureAudio][!DisableMeasure ScriptRainyDays][!HideMeterGroup Bars][!HideMeter BoundingBox]

[Standby]
Measure=Plugin
Plugin=AudioLevel
Port=#Port#
ID=#ID#
UpdateDivider=1
IfConditionMode=1

; Show meters and enable measures when sound begins playing
IfCondition=(Standby > 0.000000000000000001)
IfTrueAction=[!EnableMeasure MeasureAudio][!EnableMeasure ScriptRainyDays][!ShowMeterGroup Bars][!ShowMeter BoundingBox]

; Include audio bands
@Include=#@#Bands.inc

[ScriptRainyDays]
Measure=Script
ScriptFile=#@#RainyDays.lua
Sub=Repeat
Index=1
Limit=(#Bands#-1)
MeasureName=MeasureAudioRepeat
MeterName=MeterBarRepeat
UpdateDivider=1

[SetMeasureOptions]
Measure=Calc
OnUpdateAction=[!SetOptionGroup Audio Channel #Channel#][!SetOptionGroup Audio AverageSize #AverageSize#][!SetOptionGroup Audio UpdateDivider 1][!UpdateMeasureGroup Audio]

[SetMeterOptions]
Measure=Script
ScriptFile=#@#SetMeterOptions.lua
Sub=Repeat
MeterName=MeterBarRepeat

[MeasureDummy]
Measure=Calc

; Invisible meter that prevents resizing the skin window
[BoundingBox]
Meter=Bar
H=#RainCover#
BarColor=255,255,255,0
MeasureName=MeasureDummy
UpdateDivider=-1