[top]
components : refresh@Refresh

out : refresh_out 
in : refresh_setting 
in : plus_in 
in : minus_in

Link : refresh_setting refresh_setting@refresh
Link : plus_in plus_in@refresh
Link : minus_in minus_in@refresh
Link : refresh_out@refresh refresh_out 

[refresh]
preparation : 00:00:10:000
timeout : 00:00:20:000