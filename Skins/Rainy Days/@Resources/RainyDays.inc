[Rainmeter]
Update=16
DefaultUpdateDivider=-1
Group=#SkinGroup#
OnCloseAction=[!RefreshGroup #SkinGroup#]

ContextTitle="Open settings window"
ContextAction=#OpenSettingsWindow#
ContextTitle2="Edit variables"
ContextAction2=["#@#Variables.inc"]

[Variables]

; Since each skin file has some specific settings, they should be written to the global Variables file for access
EnvSlant=[!WriteKeyValue Variables Slant #Slant# "#@#Variables.inc"]
EnvInvert=[!WriteKeyValue Variables Invert #Invert# "#@#Variables.inc"]
EnvChannel=[!WriteKeyValue Variables Channel #Channel# "#@#Variables.inc"]
EnvPort=[!WriteKeyValue Variables Port #Port# "#@#Variables.inc"]
EnvID=[!WriteKeyValue Variables ID "#ID#" "#@#Variables.inc"]
EnvConfig=[!WriteKeyValue Variables Config "#CURRENTCONFIG#" "#@#Variables.inc"]
EnvConfigPath=[!WriteKeyValue Variables ConfigPath "#CURRENTPATH##CURRENTFILE#" "#@#Variables.inc"]
EnvSettingsWindow=#EnvSlant##EnvInvert#EnvChannel##EnvPort##EnvID##EnvConfig##EnvConfigPath#
OpenSettingsWindow=#EnvSettingsWindow#[!ActivateConfig "#ROOTCONFIG#\SettingsWindow"][!Refresh "#ROOTCONFIG#\SettingsWindow"]

[MeasureAudio]
Measure=Plugin
Plugin=AudioLevel
Port=#Port#
ID=#ID#
RMSAttack=0
RMSDecay=0
RMSGain=1
PeakAttack=0
PeakDecay=0
PeakGain=1
FFTSize=#FFTSize#
FFTOverlap=#FFTOverlap#
FFTAttack=#FFTAttack#
FFTDecay=#FFTDecay#
Bands=#Bands#
FreqMin=#FreqMin#
FreqMax=#FreqMax#
Sensitivity=#Sensitivity#
UpdateDivider=1

[DisableProcessCheck]
Measure=String
String=#MusicPlayer#
IfMatch="None"
IfMatchAction=[!SetOption DisableProcessCheck String 1][!UpdateMeasure DisableProcessCheck]
IfNotMatchAction=[!SetOption MeasureProcess UpdateDivider 62.5]

[MeasureProcess]
Measure=Plugin
Plugin=Process
ProcessName=#MusicPlayer#.exe

[Standby]
Measure=Plugin
Plugin=AudioLevel
Port=#Port#
ID=#ID#
RMSAttack=0
RMSDecay=0
RMSGain=1
PeakAttack=0
PeakDecay=0
PeakGain=1
UpdateDivider=1

; Toggle measures/meters based on idle audio, music player running status, and constant rotation
IfCondition=((Standby > 0.00001) && ((DisableProcessCheck = 1) || (MeasureProcess = 1)) && (#RainConstant# = 0))
IfTrueAction=[!EnableMeasure ScriptRainyDays][!ShowMeterGroup Rotators][!ShowMeter BoundingBox]
IfFalseAction=[!DisableMeasure ScriptRainyDays][!HideMeterGroup Rotators][!SetOptionGroup Rotators Y 0][!HideMeter BoundingBox]
IfCondition2=(#RainConstant# <> 0)
IfTrueAction2=[!EnableMeasure ScriptRainyDays][!ShowMeterGroup Rotators][!ShowMeter BoundingBox]
IfCondition3=((Standby > 0.00001) && ((DisableProcessCheck = 1) || (MeasureProcess = 1)))
IfTrueAction3=[!EnableMeasureGroup Audio][!EnableMeasure MeasureAudio][!EnableMeasure DynamicSensitivity][!EnableMeasure DynamicFFTDecay]
IfFalseAction3=[!DisableMeasureGroup Audio][!DisableMeasure MeasureAudio][!DisableMeasure DynamicSensitivity][!DisableMeasure DynamicFFTDecay]

[DynamicSensitivity]
Measure=Calc
Formula=(#Sensitivity# - (MeasureAudio * 100 - #Sensitivity#))
IfCondition=((DynamicSensitivity > #Sensitivity#) && (#LoudnessEqualization# = 1))
IfTrueAction=[!SetOption MeasureAudio Sensitivity [DynamicSensitivity]]
IfConditionMode=1
UpdateDivider=1
; Average over the past 3 seconds to prevent stuttering
AverageSize=188

[DynamicFFTDecay]
Measure=Calc
Formula=(#FFTDecay# + (MeasureAudio * 100 - #Sensitivity#) * 10)
IfCondition=((DynamicSensitivity > #Sensitivity#) && (#LoudnessEqualization# = 1))
IfTrueAction=[!SetOption MeasureAudio FFTDecay [DynamicFFTDecay]]
IfConditionMode=1
UpdateDivider=1
AverageSize=188

@Include=#@#Bands.inc

[SetMeasureOptions]
Measure=Calc
OnUpdateAction=[!SetOptionGroup Audio Channel #Channel#][!SetOptionGroup Audio AverageSize #AverageSize#][!SetOptionGroup Audio UpdateDivider 1][!UpdateMeasureGroup Audio]

[SetMeterOptions]
Measure=Script
ScriptFile=#@#SetMeterOptions.lua

[ScriptRainyDays]
Measure=Script
ScriptFile=#@#RainyDays.lua
MeasureBaseName=MeasureAudio
MeterBaseName=MeterRotator
LowerLimit=#FirstBandIndex#
UpperLimit=(#Bands#-1)
Multiplier=#RainSpeed#
Constant=#RainConstant#
Cover=#RainCover#
MeterHeight=#BarHeight#
UpdateDivider=1
OnUpdateAction=[!Redraw]

; Reveal the transformation by expanding the skin window through an invisible meter
[BoundingBox]
Meter=Image
H=#RainCover#

[MeasureDummy]
Measure=Calc