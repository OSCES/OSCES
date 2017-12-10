module TopModule
(
   input              EXT_CLK      ,
   //input              EXT_RESET    ,
   //input              EXT_OE       ,

   // ----------- TO MEMORY --------------
   inout  wire  [7:0] EXT_MEM_DATA ,
   output wire [18:0] EXT_MEM_ADDR ,
   output wire        EXT_MEM_WE   ,
   output wire        EXT_MEM_OE   ,
   output wire        EXT_MEM_CE   ,
   // ------------------------------------

   // ------------ TO MCU ----------------
   inout  wire  [7:0] EXT_MCU_DATA ,
   input  wire [18:0] EXT_MCU_ADDR ,
   input  wire        EXT_MCU_CE   ,
   input  wire        EXT_MCU_WE   ,
   input  wire        EXT_MCU_OE   ,
   // ------------------------------------

   // -------------- TO VGA --------------
   output wire  [4:0] EXT_VGA_R     , // Выходная шина составляющей красного цвета
   output wire  [4:0] EXT_VGA_G     , // Выходная шина составляющей зеленого цвета
   output wire  [4:0] EXT_VGA_B     , // Выходная шина составляющей синего цвета	
   output wire        EXT_VGA_HS    , // Сигнал горизонтальной синхронизации
   output wire        EXT_VGA_VS      // Сигнал вертикальной синхронизации
   // ------------------------------------
);

wire [10:0] INT_VGA_POS_X; 
wire  [9:0] INT_VGA_POS_Y;
wire        INT_VGA_ENABLE;


wire [ 7:0] INT_PORTB_DATA;
wire [18:0] INT_PORTB_ADDR;
wire        INT_PORTB_WE  ;
wire        INT_PORTB_OE  ;
wire        INT_PORTB_CE  ;
wire        INT_SELECT_BUFF;
wire        INT_CLEAR;

//wire  [9:0] INT_CONTROL_MOUSE_POS_X;
//wire  [9:0] INT_CONTROL_MOUSE_POS_Y;


VgaSyncGenerator VgaSyncGeneratorInst
(
   .CLK       ( EXT_CLK       ), //Сигнал тактирования
   .VGA_HS    ( EXT_VGA_HS    ), //Сигнал горизонтальной синхронизации
   .VGA_VS    ( EXT_VGA_VS    ), //Сигнал вертикальной синхронизации
   .VGA_POS_X ( INT_VGA_POS_X ),
   .VGA_POS_Y ( INT_VGA_POS_Y ),
   .VGA_ENABLE( INT_VGA_ENABLE )
 );


 
VgaRenderer VgaRendererInst
(
   .RENDERER_CLK     ( EXT_CLK         ),
   .RENDERER_POS_X   ( INT_VGA_POS_X   ),
   .RENDERER_POS_Y   ( INT_VGA_POS_Y   ),	
   .RENDERER_SEL_BUFF( INT_SELECT_BUFF ),
	
//	.RENDERER_MOUSE_POS_X( INT_CONTROL_MOUSE_POS_X ),
//   .RENDERER_MOUSE_POS_Y( INT_CONTROL_MOUSE_POS_Y ),

	

// --------------- TO MEMORY -----------------
   .RENDERER_ENABLE  ( INT_VGA_ENABLE  ),
   .RENDERER_DATA    ( INT_PORTB_DATA ),
   .RENDERER_ADDR    ( INT_PORTB_ADDR ),
   .RENDERER_WE      ( INT_PORTB_WE   ),
   .RENDERER_OE      ( INT_PORTB_OE   ),
   .RENDERER_CE      ( INT_PORTB_CE   ),
// -------------------------------------------

// ---------------- TO VGA -------------------
   .RENDERER_RED     ( EXT_VGA_R      ),
   .RENDERER_GREEN   ( EXT_VGA_G      ),
   .RENDERER_BLUE    ( EXT_VGA_B      )
// -------------------------------------------
);


MemMux MemMuxInst
(
   .MEM_MUX_CLK( EXT_CLK        ),

   .PORTA_DATA ( EXT_MCU_DATA   ),
   .PORTA_ADDR ( EXT_MCU_ADDR   ),
   .PORTA_WE   ( EXT_MCU_WE     ),
   .PORTA_OE   ( EXT_MCU_OE     ),
   .PORTA_CE   ( EXT_MCU_CE     ),

   .PORTB_DATA ( INT_PORTB_DATA ),
   .PORTB_ADDR ( INT_PORTB_ADDR ),
   .PORTB_WE   ( INT_PORTB_WE   ),
   .PORTB_OE   ( INT_PORTB_OE   ),
   .PORTB_CE   ( INT_PORTB_CE   ),

   .MEMORY_DATA( EXT_MEM_DATA   ),
   .MEMORY_ADDR( EXT_MEM_ADDR   ),
   .MEMORY_WE  ( EXT_MEM_WE     ),
   .MEMORY_OE  ( EXT_MEM_OE     ),
   .MEMORY_CE  ( EXT_MEM_CE     )
);

ControlBlock ControlBlockInst
(
	.CLK                ( EXT_CLK         ),
	.CONTROL_DATA       ( EXT_MCU_DATA    ),
	.CONTROL_ADDR       ( EXT_MCU_ADDR    ),
	//.CONTROL_MOUSE_POS_X( INT_CONTROL_MOUSE_POS_X ),
   //.CONTROL_MOUSE_POS_Y( INT_CONTROL_MOUSE_POS_Y ),
   //.CONTROL_CLEAR      ( INT_CLEAR ),
	
	.CONTROL_SEL_BUFF   ( INT_SELECT_BUFF )
);

/*
SramModule SramModuleInst
(
	//.SRAM_CLK    ( EXT_CLK      ),
	.SRAM_DATA   ( INT_MEM_DATA ),
	.SRAM_ADDR   ( INT_MEM_ADDR ),
	.SRAM_CE     ( INT_MEM_CE   ),
	.SRAM_WE     ( INT_MEM_WE   ),
	.SRAM_OE     ( INT_MEM_OE   )
);
*/


endmodule