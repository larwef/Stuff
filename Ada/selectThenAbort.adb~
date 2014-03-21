with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure selectThenAbort is
i		: Integer := 0;
begin
   select
      delay 3.0;
      Put_Line("test");
      Put("i became: "); Put(i);
   then abort
      -- This will be abandoned upon terminal interrupt
      loop
         i := i + 1;
         delay 0.001;
      end loop;
   end select;
   
end selectThenAbort;
