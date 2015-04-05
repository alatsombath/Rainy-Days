-- RainyDays v1.2
-- LICENSE: Creative Commons Attribution-Non-Commercial-Share Alike 3.0

local HeightLookup,PositionY,Measure,Meter={},{},{},{}

function Initialize()

	RainSpeed,RainConstant=SKIN:ParseFormula(SKIN:ReplaceVariables("#RainSpeed#")),SKIN:ParseFormula(SKIN:ReplaceVariables("#RainConstant#"))
	
	-- Iteration control variables
	Sub,Index,Limit=SELF:GetOption("Sub"),SKIN:ParseFormula(SELF:GetNumberOption("Index")),SKIN:ParseFormula(SELF:GetOption("Limit"))
	
	-- Rainfall height (rounded for indexing)
	RainCover=SKIN:ParseFormula(SKIN:ReplaceVariables("#RainCover#"))
	
	-- Raindrop height
	BarHeight=SKIN:ParseFormula(SKIN:ReplaceVariables("#BarHeight#"))
	
	-- Establish halfway point as half the skin height (rounded for indexing)
	RainDivider=math.ceil(RainCover*0.5)
	
	-- Generate height lookup table
	for i=Index,RainDivider do HeightLookup[i]=BarHeight*(i/RainDivider) end
	
	-- Retrieve measures and meter names, store in tables
	local MeasureName,MeterName,gsub=SELF:GetOption("MeasureName"),SELF:GetOption("MeterName"),string.gsub
	for i=Index,Limit do
		PositionY[i],Measure[i],Meter[i]=0,SKIN:GetMeasure((gsub(MeasureName,Sub,i))),(gsub(MeterName,Sub,i))
	end

end

function Update()

	-- For each raindrop
	for i=Index,Limit do
		
		-- Increase the Y position of the raindrop based on the measure value and control variables
		-- Reset when it reaches the bottom of the skin
		PositionY[i]=(PositionY[i]+RainSpeed*Measure[i]:GetValue()+RainConstant)%RainCover
		
		-- Cache the Y position (rounded for indexing)
		local PositionY=PositionY[i]-PositionY[i]%1
		
		-- Check for invalid index
		if PositionY==0 then PositionY=1 end
		
		-- Set the raindrop height based on whether it has crossed the halfway point
		if PositionY<=RainDivider then
			SKIN:Bang("!SetOption",Meter[i],"H",HeightLookup[PositionY])
		else
			SKIN:Bang("!SetOption",Meter[i],"H",BarHeight-HeightLookup[PositionY-RainDivider])
		end

		-- Move the Y position of the meter
		SKIN:Bang("!SetOption",Meter[i],"Y",PositionY)
		
	end
	
end