`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/06/16 19:46:40
// Design Name: 
// Module Name: digit
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


module digit(
    input A,
    input B,
    input C,
    input D,
    output a,
    output b,
    output c,
    output d,
    output e,
    output f,
    output g,
    output enable
    );
    assign a=(A | C | ( B & D ) | ( ( ~B ) & ( ~D ) ) );
    assign b=(~B | ( C & D ) | ( ( ~C ) & ( ~D ) ) );
    assign c=( B | (~C) | D );
    assign d=(A | ( C & ( ~D ) ) | ( ( ~B ) & C ) | ( ( ~B ) & ( ~D ) ) | ( B & (~C) & D ) );
    assign e=( ( C & ( ~D ) ) | ( ( ~B ) & ( ~D ) ) );
    assign f=(A | ( ( ~C ) & ( ~D ) ) | ( B & ( ~C ) ) | ( B & ( ~D ) ) );
    assign g=(A | ( C & ( ~D ) ) | ( ( ~B ) & C ) | ( B & ( ~C ) ) );
    assign enable=1;
endmodule