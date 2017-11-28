module ControlBlock
(
   input               CLK               ,
  
   input  wire  [ 7:0] CONTROL_DATA      ,
   input  wire  [18:0] CONTROL_ADDR      ,
   output wire         CONTROL_SEL_BUFF
);

assign CONTROL_SEL_BUFF    = Ctrl[ 0 ];


reg [7:0]Ctrl = 0;


always@ ( posedge CLK )
begin

	if( 'h7FFFF == CONTROL_ADDR )
	begin
		 Ctrl <= CONTROL_DATA;
	end
	
end

endmodule
