[top]
components : filter@Filter
components : write@Write
components : display@Display

out : display_out 
in : bit1_in 
in : bit2_in 
in : bit3_in 
in : bit4_in 
in : choice_in

Link : bit1_in bit1_in@filter 
Link : bit2_in bit2_in@filter 
Link : bit3_in bit3_in@filter 
Link : bit4_in bit4_in@filter      
Link : choice_in choice_in@filter     
Link : choice_in choice_in@write      
Link : bit_out@filter  filter_in@display     
Link : write_out@write write_in@display      
Link : display_out@display display_out  

[filter]
preparation : 00:00:10:000
timeout : 00:00:20:000 

[display]
preparation : 00:00:10:000
timeout : 00:00:20:000 

[write]
preparation : 00:00:10:000 
timeout : 00:00:20:000 
