with Ada.Text_IO; use Ada.Text_IO;
with Ada.Float_Text_IO; use Ada.Float_Text_IO;

procedure calculator is
	Number1 	: Float;
	Operator 	: Character;
	Number2 	: Float;
	Result		: Float;
begin
	Put_Line("Enter your math problem: ");
	-- Examlple: 1+2, 1.2+3 etc.
	Get(Number1);
	Get(Operator);
	Get(Number2);
	
	if Operator = '+' then
		Result := Number1 + Number2;
	elsif Operator = '-' then
		Result := Number1 - Number2;
	elsif Operator = '*' then
		Result := Number1 * Number2;
	elsif Operator = '/' then
		Result := Number1 / Number2;
	else
		Result := 0.0;
		Put_Line("Invalid input");
	end if;
	
	Put_Line("Result" & Float'Image(Result));
	
end calculator;
