`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/06/19 18:32:14
// Design Name: 
// Module Name: JK
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


module JK(
    input J,
    input K,
    input CLK,
    output Q,
    output Q_n
    );
    reg Q,Q_n;
    always@(posedge CLK)
    begin
        Q<=J&&(~Q)||(~K)&&Q;
        Q_n<=~Q;
    end
endmodule
