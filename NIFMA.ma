[top]
components : account@Account
components : refresh@Refresh
components : datageneration@Datageneration
components : Dataprocessing

out : display_out 
in : account_setting 
in : refresh_setting 
in : plus_in
in : minus_in 
in : choice_in

Link : account_setting account_setting@account
Link : plus_in plus_in@account
Link : minus_in minus_in@account
Link : refresh_setting refresh_setting@refresh
Link : plus_in plus_in@refresh
Link : minus_in minus_in@refresh
Link : choice_in choice_in@Dataprocessing     
Link : accountNO_out@account accountNO_in@datageneration
Link : refresh_out@refresh LT_in@datageneration
Link : data1_out@datageneration bit1_in@Dataprocessing
Link : data2_out@datageneration bit2_in@Dataprocessing
Link : data3_out@datageneration bit3_in@Dataprocessing
Link : data4_out@datageneration bit4_in@Dataprocessing
Link : display_out@Dataprocessing display_out  

[account]
preparation : 00:00:10:000
timeout : 00:00:20:000 

[refresh]
preparation : 00:00:10:000
timeout : 00:00:20:000 

[datageneration]
preparation : 00:00:10:000 
timeout : 00:00:20:000

[Dataprocessing]
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
