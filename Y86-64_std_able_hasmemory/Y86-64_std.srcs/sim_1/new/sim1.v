`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/01 20:58:26
// Design Name: 
// Module Name: sim1
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sim1();
reg clk;
reg [1:0]mode;
reg [63:0] uaddr;
reg [63:0] idata;
wire [63:0] odata;
wire [2:0] status;
reg [63:0] mem[127:0];

processor(.mode(mode),.udaddr(uaddr),.idata(idata),.odata(odata),.stat(status),.clock(clk));

initial begin
    mode = 2'b01;
    mem[0] = {4'h3,4'h0,56'h00000000000001};
    mem[1] = {8'h00,4'hC,4'h0,44'h0};
    mem[2] = {20'hb1,44'h0};
    mem[3] = {64'h0};
    clk=0;
    $display("core value for core1: irmovq $512, rax; iraddq $0xb1, rax; hlt");
    $monitor("f_icode, f_ifun, rax, f_pc, f_status = %h, %h, %h, %h, %d\n",core.f_icode,core.f_ifun,core.rax,core.f_pc, core.f_stat);
    #100000;
    mode = 2'b10;
    uaddr = 64'h0;
    idata = mem[0];
    #1000;
    mode = 2'b10;
    uaddr = 64'h8;
    idata = mem[1];
    #1000;
    mode = 2'b10;
    uaddr = 64'h10;
    idata = mem[3];
    #1000;
    mode = 2'b01;
    #100;
    mode = 2'b00;;
end
always #10 clk <= ~clk;
endmodule
