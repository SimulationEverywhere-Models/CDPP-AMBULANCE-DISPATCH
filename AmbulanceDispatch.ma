[top]
components : CallHandler Dispatcher Response@Response
in : in
out :  response_out 
Link : in callin@CallHandler
Link : lout@CallHandler lin@Dispatcher
Link : pout@CallHandler pin@Dispatcher
Link : pout@CallHandler priority_in@Response
Link : time_out@Dispatcher time_in@Response
Link : response_out@Response response_out


[CallHandler]
components : CallerQueue CallerINFO@CallerINFO
in : callin
out : lout pout
Link : callin callin@CallerQueue
Link : callout@CallerQueue callin@CallerINFO
Link : lout@CallerINFO lout
Link : pout@CallerINFO pout

[Dispatcher]
components : Dispatch@Dispatch 
in : lin pin 
out : ambulance_out time_out 
Link : lin lin@Dispatch
Link : pin pin@Dispatch
Link : ambulance_out@Dispatch ambulance_out
Link : time_out@Dispatch time_out


[Response]
preparation : 00:00:00:00

[Dispatch]
preparation : 00:00:00:000

[CallerINFO]
preparation : 00:00:00:00

[CallerQueue]
components : CallLength@Generator CallQueue@Queue 
out : callout 
in : callin 
Link : callin in@CallQueue
Link : out@CallQueue callout
Link : out@CallLength done@CallQueue

[CallLength]
distribution : Normal
mean : 30
deviation : 15

[CallQueue]
preparation : 00:00:00:00
