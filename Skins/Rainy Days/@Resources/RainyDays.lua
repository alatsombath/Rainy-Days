-- RainyDays v1.3
-- LICENSE: Creative Commons Attribution-Non-Commercial-Share Alike 3.0

local HeightLookup,PositionY,Measure,Meter={},{},{},{}

function Initialize()

	RainSpeed,RainConstant=SKIN:ParseFormula(SKIN:ReplaceVariables("#RainSpeed#")),SKIN:ParseFormula(SKIN:ReplaceVariables("#RainConstant#"))
	
	-- Iteration control variables
	Sub,Index,Limit=SELF:GetOption("Sub"),SKIN:ParseFormula(SELF:GetNumberOption("Index")),SKIN:ParseFormula(SELF:GetOption("Limit"))
	
	-- Rainfall height (rounded for indexing)
	RainCover=math.floor(SKIN:ParseFormula(SKIN:ReplaceVariables("#RainCover#"))+0.5)

	-- Raindrop height
	BarHeight=SKIN:ParseFormula(SKIN:ReplaceVariables("#BarHeight#"))
	
	-- Establish halfway point as half the skin height (rounded for indexing)
	RainDivider=math.floor((RainCover*0.5)+0.5)
	
	-- Generate height lookup table
	for i=Index,RainDivider do HeightLookup[i]=BarHeight*(i/RainDivider) end
	
	-- Retrieve measures and meters, store in tables
	local MeasureName,MeterName,gsub=SELF:GetOption("MeasureName"),SELF:GetOption("MeterName"),string.gsub
	for i=Index,Limit do
		PositionY[i],Measure[i],Meter[i]=0,SKIN:GetMeasure((gsub(MeasureName,Sub,i))),SKIN:GetMeter((gsub(MeterName,Sub,i)))
	end

end

function Update()
	
	local RainDivider,HeightLookup,BarHeight,Meter=RainDivider,HeightLookup,BarHeight,Meter
	
	-- For each raindrop
	for i=Index,Limit do
		
		-- Increase the Y position of the raindrop based on the measure value and control variables
		-- Reset when it reaches the bottom of the skin
		PositionY[i]=(PositionY[i]+RainSpeed*Measure[i]:GetValue()+RainConstant+0.5)%RainCover
		
		-- Cache the Y position (rounded for indexing)
		local PositionY=PositionY[i]-PositionY[i]%1
		
		-- Check for invalid index
		if PositionY==0 then PositionY=1 end
		
		-- Set the raindrop height based on whether it has crossed the halfway point
		if PositionY<=RainDivider then
			Meter[i]:SetH(HeightLookup[PositionY])
		else
			Meter[i]:SetH(BarHeight-HeightLookup[PositionY-RainDivider])
		end

		-- Move the Y position of the meter
		Meter[i]:SetY(PositionY)
		
	end
	
end