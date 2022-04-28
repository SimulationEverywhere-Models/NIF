[top]
components : write@Write


out : write_out 
in : choice_in

Link : choice_in choice_in@write
Link : write_out@write write_out 

[write]
preparation : 00:00:10:000

