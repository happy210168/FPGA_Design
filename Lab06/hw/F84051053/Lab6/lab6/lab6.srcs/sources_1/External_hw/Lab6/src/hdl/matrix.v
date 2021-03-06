`timescale 1ns / 1ps
 module matrix(
    input [2:0] cmd,
    input [31:0] data1, // one use 7:0 , and one use 15:8   
    input [31:0] data2,
    output [31:0] dataout
 );
    reg [31:0] d_out;
    reg [31:0] temp;
    always@(*)
    begin
        case(cmd)
        3'd0: //乘法
        begin
            d_out = data1[7:0]*data2[7:0] + data1[15:8]*data2[15:8];
        end
        3'd1: //加法
        begin
            d_out[15:0] = data1[7:0] + data2[7:0];
            d_out[31:16] = data1[15:8] + data2[15:8];
        end
        3'd2: //減法
        begin
            d_out[15:0] = data1[7:0] - data2[7:0];
            d_out[31:16] = data1[15:8] - data2[15:8];
        end
        3'd3: //轉置
        begin
            d_out[7:0] = data1[7:0];
            d_out[15:8] = data2[7:0];
            d_out[23:16] = data1[15:8];
            d_out[31:24] = data2[15:8];
        end
        3'd4: //行列式
        begin
                d_out[31:0] = data1[7:0]*data2[15:8] - data1[15:8]*data2[7:0];
        end
        default:
            d_out = 32'd0;
        endcase
    end
    assign dataout = d_out;
 endmodule