This compressed folder includes:
1) modifications to the platform architecture
2) addition of .h an an example for the platform specification
3) addition of code 

The platform architecture has been modified so that the headers that should be 
used by the platform only are now postfixed with the keyword "private".
This was done to separate the functionalities provided by the platform to an
application developer to the ones of the platform. 

The platform specification is the headers Inc/platform/xxx.h files. 
This specification is not complete and right now can be seen as an example.