[top]
components : datageneration@Datageneration


out : data1_out 
out : data2_out
out : data3_out
out : data4_out
in : accountNO_in 
in : LT_in

Link : accountNO_in accountNO_in@datageneration
Link : LT_in LT_in@datageneration
Link : data1_out@datageneration data1_out 
Link : data2_out@datageneration data2_out
Link : data3_out@datageneration data3_out
Link : data4_out@datageneration data4_out

[datageneration]
preparation : 00:00:10:000
timeout : 00:00:20:000 
