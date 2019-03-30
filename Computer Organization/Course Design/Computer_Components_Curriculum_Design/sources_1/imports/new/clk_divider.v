`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/15 13:31:43
// Design Name: 
// Module Name: clk_divider
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


/*
 * ʱ�ӷ�Ƶ��ģ�飬 ��Ƶ�ȣ�1/delay
 * input params:
 *      clk: ʱ������
 *      change_scale: �ı��Ƶ���ź�����
 * output params:
 *      clk_divd: ��Ƶ���ʱ���ź�
 */
module clk_divider(
    input clk,
    input change_scale,
    input[31:0] delay_1,
    output reg clk_divd,
    output reg[2:0] speed
    );
    
    reg [31:0]count;
    reg [31:0]delay;
//    parameter delay_1 = 100_000_000;
    initial begin
        speed = 0;
        count = 0;
        clk_divd = 0;
        delay = delay_1;
    end
    
    always@ (posedge clk) begin
        if (count >= delay / 2) begin
            count = 0;
            clk_divd = ~clk_divd;
        end
        count = count + 1;
    end
    
    always@ (posedge change_scale) begin
        speed = speed + 1;
        if (delay <= 1) begin
            delay = delay_1;
            speed = 0;
        end
        else begin
            delay = delay / 10;
        end
    end
    
endmodule
