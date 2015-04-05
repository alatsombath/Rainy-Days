-- RainyDays v1.0
-- LICENSE: Creative Commons Attribution-Non-Commercial-Share Alike 3.0

local Measure,Meter,PositionY={},{},{}
function Initialize()
	RainSpeed,RainCover=SKIN:ReplaceVariables("#RainSpeed#"),SKIN:ParseFormula(SKIN:ReplaceVariables("#RainCover#"))
	Sub,Index,Limit=SELF:GetOption("Sub"),SKIN:ParseFormula(SELF:GetOption("Index")),SKIN:ParseFormula(SELF:GetOption("Limit"))
	local MeasureName,MeterName,gsub=SKIN:ReplaceVariables("#MeasureName#"),SKIN:ReplaceVariables("#MeterName#"),string.gsub
	for i=Index,Limit do Measure[i]=SKIN:GetMeasure((gsub(MeasureName,Sub,i))) Meter[i]=(gsub(MeterName,Sub,i)) PositionY[i]=0 end end

function Update()
	for i=Index,Limit do 
		PositionY[i]=(PositionY[i]+RainSpeed*Measure[i]:GetValue()+SKIN:ReplaceVariables("#RainConstant#"))%RainCover
		
		local Height=PositionY[i]/(RainCover*0.5)
		if Height>1 then Height=(1/Height) end
		
		SKIN:Bang("!SetOption",Meter[i],"H",SKIN:ParseFormula(SKIN:ReplaceVariables("#BarHeight#"))*Height)
		SKIN:Bang("!SetOption",Meter[i],"Y",PositionY[i])
	end
end