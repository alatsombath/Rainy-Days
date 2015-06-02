function Update()
	
	-- Parse these values only once to be easily read on every update cycle
	local BarWidth=SKIN:ParseFormula(SKIN:ReplaceVariables("#BarWidth#"))
	local BarGap=SKIN:ParseFormula(SKIN:ReplaceVariables("#BarGap#"))
	local Offset=BarWidth+BarGap
	
	local Color=SKIN:ReplaceVariables("#Color#")
	local Slant=SKIN:ReplaceVariables("#Slant#")
	
	local Limit=SKIN:ParseFormula(SKIN:ReplaceVariables("#Bands#")-1)
	
	local Meter={}
	local gsub,Sub,MeterName=string.gsub,SELF:GetOption("Sub"),SELF:GetOption("MeterName")
	for i=1,Limit do
		Meter[i]=(gsub(MeterName,Sub,i))
		SKIN:Bang("!SetOption",Meter[i],"Group","Bars")
		SKIN:Bang("!UpdateMeter",Meter[i])
	end
	
	SKIN:Bang("!SetOptionGroup","Bars","W",BarWidth)
		
	-- First bar is offset by the gap value
	SKIN:Bang("!SetOption","MeterBar1","X",BarGap)
	for i=2,Limit do
		SKIN:Bang("!SetOption",Meter[i],"X",BarGap+Offset*(i-1))
	end	
	
	-- If the rainfall is slanted
	if Slant~="None" then
		if Slant=="Left" then
			-- SKIN:Bang("!SetOptionGroup","Bars","TransformationMatrix","(Cos(-5*PI/180));(-Sin(-5*PI/180));(Sin(-5*PI/180));(Cos(-5*PI/180));0;(-Sin(5*PI/180)*((#Bands#-1)*(#BarWidth#+#BarGap#)))")
			SKIN:Bang("!SetOptionGroup","Bars","TransformationMatrix","(Cos(-5*PI/180));(-Sin(-5*PI/180));(Sin(-5*PI/180));(Cos(-5*PI/180));0;0")
		else
			-- SKIN:Bang("!SetOptionGroup","Bars","TransformationMatrix","(Cos(5*PI/180));(-Sin(5*PI/180));(Sin(5*PI/180));(Cos(5*PI/180));0;(-Sin(5*PI/180)*((#Bands#-1)*(#BarWidth#+#BarGap#)))")
			SKIN:Bang("!SetOptionGroup","Bars","TransformationMatrix","(Cos(5*PI/180));(-Sin(5*PI/180));(Sin(5*PI/180));(Cos(5*PI/180));0;0")
		end
		
		-- SKIN:Bang("!SetVariable","RainCover","(#WORKAREAHEIGHT#+(Sin(5*PI/180)*((#Bands#-1)*(#BarWidth#+#BarGap#))))")
		-- SKIN:Bang("!CommandMeasure","ScriptRainyDays","Initialize()")
		
		SKIN:Bang("!SetOptionGroup","Bars","AntiAlias",1)
		SKIN:Bang("!UpdateMeterGroup","Bars")
		
		-- Unset the matrix after the meters have been transformed
		SKIN:Bang("!SetOptionGroup","Bars","TransformationMatrix","")
		
	end
	
	SKIN:Bang("!SetOptionGroup","Bars","BarColor","255,0,0,0")
	SKIN:Bang("!SetOptionGroup","Bars","GradientAngle",90)
	
	-- If it's an RGB color
	if Color:find(",") then
	
		SKIN:Bang("!SetOptionGroup","Bars","SolidColor","#Color#,0")
		SKIN:Bang("!SetOptionGroup","Bars","SolidColor2","#Color#,255")
		
	-- If it's a HEX color
	else
		
		SKIN:Bang("!SetOptionGroup","Bars","SolidColor","#Color#00")
		SKIN:Bang("!SetOptionGroup","Bars","SolidColor2","#Color#FF")
		
	end
	
	SKIN:Bang("!SetOptionGroup","Bars","UpdateDivider",1)
	SKIN:Bang("!UpdateMeterGroup","Bars")
	
end