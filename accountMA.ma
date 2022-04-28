[top]
components : account@Account

out : accountNO_out 
in : account_setting 
in : plus_in
in : minus_in

Link : account_setting account_setting@account
Link : plus_in plus_in@account
Link : minus_in minus_in@account
Link : accountNO_out@account accountNO_out 

[account]
preparation : 00:00:10:000
timeout : 00:00:20:000 
