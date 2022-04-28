[top]
components : display@Display


out : display_out 
in : filter_in write_in

Link : filter_in filter_in@display
Link : write_in write_in@display 
Link : display_out@display display_out   

[display]
preparation : 00:00:10:000
timeout : 00:00:20:000 