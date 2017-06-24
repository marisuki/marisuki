`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/06/20 22:50:10
// Design Name: 
// Module Name: homework_v2
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


module homework_v2(
    input A,
    input B,
    input C,
    input D,
    input enlock,
    input encmp,
    input clk,
    output [7:0] wrer0,
    output [7:0] timer1,
    output alert,
    output open,
    output locked
    );
    wire [3:0]key,key_n;
    wire open=1;
    reg [3:0]wrtimes=5,timer=9;
    reg [10:0] counttime0=0,counttime1=0,counttime2=0;
    reg newlock=0;
    JK JK0(A,~A,enlock,key[0],key_n[0]);
    JK JK1(B,~B,enlock,key[1],key_n[1]);
    JK JK2(C,~C,enlock,key[2],key_n[2]);
    JK JK3(D,~D,enlock,key[3],key_n[3]);
    digit dig0(wrtimes[3],wrtimes[2],wrtimes[1],wrtimes[0],wrer0[0],wrer0[1],wrer0[2],wrer0[3],wrer0[4],wrer0[5],wrer0[6],wrer0[7]);
    digit dig1(timer[3],timer[2],timer[1],timer[0],timer1[0],timer1[1],timer1[2],timer1[3],timer1[4],timer1[5],timer1[6],timer1[7]);
    assign open=((key[0]&A)|((~key[0])&(~A)))&((key[1]&B)|((~key[1])&(~B)))&((key[2]&C)|((~key[2])&(~C)))&((key[3]&D)|((~key[3])&(~D)))&encmp&(~alert);
    assign alert=(wrtimes==0|timer==0)? 1:0;
    assign locked=~open;
    always@(posedge encmp)
    begin
        #20 if(open==0&alert==0)
        begin
            wrtimes=wrtimes-1;
        end
    end
    always@(posedge clk)
    begin
        counttime0=counttime0+1;
        if(timer==0||open==1||newlock==1)
        begin
            counttime0=counttime0-1;
        end
        if(counttime0==1000)
        begin
            counttime0=0;
            counttime1=counttime1+1;
        end
        if(counttime1==1000)
        begin
            counttime2=counttime2+1;
            counttime1=0;
        end
        if(counttime2==100)
        begin
            counttime2=0;
            timer=timer-1;
        end
        if(enlock==1)
        begin
             timer=9;
        end
    end
    
endmodule
