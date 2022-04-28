[top]
components : filter@Filter


out : bit_out 
in : choice_in
in : bit1_in 
in : bit2_in
in : bit3_in
in : bit4_in

Link : bit1_in bit1_in@filter 
Link : bit2_in bit2_in@filter 
Link : bit3_in bit3_in@filter 
Link : bit4_in bit4_in@filter 
Link : choice_in choice_in@filter 
Link : bit_out@filter bit_out 

[filter]
preparation : 00:00:10:000
timeout : 00:00:20:000 
