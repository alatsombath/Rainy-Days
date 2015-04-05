-- RainyDays v1.1
-- LICENSE: Creative Commons Attribution-Non-Commercial-Share Alike 3.0

local HeightLookup,PositionY,Measure,Meter={},{},{},{}
function Initialize()
	RainSpeed,RainConstant,RainCover=SKIN:ParseFormula(SKIN:ReplaceVariables("#RainSpeed#")),SKIN:ParseFormula(SKIN:ReplaceVariables("#RainConstant#")),SKIN:ParseFormula(SKIN:ReplaceVariables("#RainCover#"))
	Sub,Index,Limit=SELF:GetOption("Sub"),SKIN:ParseFormula(SELF:GetOption("Index")),SKIN:ParseFormula(SELF:GetOption("Limit"))
	
	RainDivider,BarHeight=(RainCover*0.5)-(RainCover*0.5)%1,SKIN:ParseFormula(SKIN:ReplaceVariables("#BarHeight#"))
	for i=Index,RainDivider do HeightLookup[i]=BarHeight*(i/RainDivider) end
	
	local MeasureName,MeterName,gsub=SKIN:ReplaceVariables("#MeasureName#"),SKIN:ReplaceVariables("#MeterName#"),string.gsub
	for i=Index,Limit do PositionY[i],Measure[i],Meter[i]=0,SKIN:GetMeasure((gsub(MeasureName,Sub,i))),(gsub(MeterName,Sub,i)) end end
	
function Update()
	for i=Index,Limit do
		PositionY[i]=(PositionY[i]+RainSpeed*Measure[i]:GetValue()+RainConstant)%RainCover+1
		local PositionY=PositionY[i]-PositionY[i]%1
		
		if PositionY<=RainDivider then SKIN:Bang("!SetOption",Meter[i],"H",HeightLookup[PositionY])
		else SKIN:Bang("!SetOption",Meter[i],"H",BarHeight-HeightLookup[PositionY-RainDivider]) end

		SKIN:Bang("!SetOption",Meter[i],"Y",PositionY)
	end
end