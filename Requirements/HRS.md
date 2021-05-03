# Hardware Requirements Specification

This Hardware Requirements Specification (HRS) specifies the required
functionality of the gVent hardware systesm, including both electronic, mechanical, pneumatic and all other physical or hardware sub-systems of the Gravity Ventilator (gVent) device. It is a refinement and elaboration
of that portion of the [system level](SLS.md) behaviour allocated to hardware.

The required software functionality is specified in terms of interactions
with the gVent Platform, which is an abstract view of the software/hardware
interface. The contents of this SRS are independent of board specific
details, i.e., porting gVent to a different target board should not
necessitate changes to this SRS.  In addition to “shall statements”,
this SRS includes a dictionary which also provides essential information
about the required functionality.  The requirements specified in this SRS
are used directly by software developers to develop the gVent source code.  
These requirements are also used directly for requirements-based testing
of the software. Every aspect of the system level behaviour, as specified
in the System Level Specification (SLS) should be traceable to one or
more requirements in this SRS unless the SLS requirement is entirely
unrelated to the software functionality.  Every requirement in this
SRS should be traceable to at least one SLS requirement unless the SRS
requirement is concerned with an internal software mechanism that
facilitates the implementation of other SRS requirements.