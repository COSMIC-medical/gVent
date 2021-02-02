# gVent - Software Requirement Specification

## Introduction

This Software Requirements Specification (SRS) specifies the required
functionality of the gVent software. It is a refinement and elaboration
of that portion of the system level behaviour allocated to software.
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

## Purpose

Present the software requirements in a not so low level of abstraction
for software developers to start implementation. These requirements are
 used to drive requirements-based testing of the gVENT software.

The first draft of this document will only contain a partially worked
example of how a single system level requirement at the SLS level
can be refined and elaborated into software requirements specified in
the SRS, and then into source code for the gVent Platform. The requirements
shown below are draft requirements only.  In this example, the specification
of a single system requirement, SLS-0070, is shown below.  This is followed
by a set of software requirements, SRS-XXXX.  

## Scope

The requirements described in this document descend directly from the SLS.
Only software requirements. Some other requirements for the non software element
of the system would be written elsewhere. The requirements for the platform
where the software will run will be documented in a Platform Specification (PS)
link here and in a Hardware Abstraction Specification(HAS) link here. The
requirements in this specification should be expressed at a level of abstraction
“just above” the platform implemented by an RTOS or cyclic executive on top
of bare hardware, i.e., these requirements use a purely functional (“blackbox”)
view of the platform as a basis for specifying requirements at this level.

## Background

### GVent

The gravity Ventilator (gVent) intends to provide mechanical ventilation
to patients. The gravity Ventilator aims to deliver constant pressure
ventilation to patients, which appears to be the most useful ventilatory
mode with COVID ARDS patients, as high pressures can easily lead to barotrauma.

### SRS

While the SLS level of specification is expressed at a level of abstraction
suitable for a clinician.  The SRS level of specification is a “black box”
view of the software functionality. In the SRS, references to inputs and
outputs are clearly identified, but referenced only in terms of an abstract
view of the software/hardware interface. These shall statements are
accompanied by additional sentences (inter-woven with the shall statements)
and graphics that clarify these shall statements.

All project-specific terminology (words and phrases) are defined in the 
glossary,including, but not limited to inputs/outputs, state variables and
system parameters.

### Notation

Each software requirement present in the SRS is clearly identified by a
unique identifier or the form SRS-XXXX where XXXX is unique within the
set of requirements defined in the SRS. A requirement in the SRS is a
“shall statement”, i.e., a sentence that uses the modal verb “shall” to
mark these sentences as a “formal requirement”.  

 In general, every functional requirement is an instance of one of the 
 following:

- A requirement that specifies an “effect” in response to a stimulus.
- A requirement that defines a condition.

Additionally, the requirements in this document follow the following rules:

- Use one shall for each requirement.
- Write concise and complete requirements. A requirement should fully define
a functionality.
- Write testable requirements. Avoid negative requirements, since they are
difficult to verify. Use the active voice.
- Write requirements at an appropriate and consistent level of granularity.
- Build robustness into the requirements by thinking through how the software
will respond to abnormal inputs.
- Include rationale and background for requirements to clear the requirement
meaning or how it is related to a SLS.
- Avoid ambiguous requirements. Avoid using and/or or using the slash (/)
symbol to separate two words. Use adverbs ending in -ly cautiously (e.g.,
reasonably, quickly, significantly, and occasionally). Use pronouns cautiously
 (e.g., it or they). It is typically better to repeat the noun. Avoid words
 that sound alike or similar.
- Minimize or avoid the use of words that indicate multiple requirements,
such as unless or except.

### Document Structure

[Section 2](#system-description) of this document describes the software with
its inputs and outputs.
The rest of the document contains the software requirements, while in
[Section 4](#dictionary) the terms used in this document are defined.

## System Description

### System inputs
The inputs of the system are either the measured values or values entered by
a clinician in the system.

| Name            | Data type | Units | Validity Criteria   | Failsafe Value |
| ------------------------- | --------- | ----- | ------------------- |------|
| selected respiratory rate | int       | bpm   | [4, 50]             | 15   |
| selected I:E ratio        | int       |       | [1, 5]              | 1    |
| measured inspiratory pressure | int   |       | [-5, 40]            |      |
| measured inspiratory flow | int       | cmH2O | [-250, 250]         |      |
| measured expiratory pressure | int    | SPLM  | [-5, 40]            |      |
| measured expiratory flow  | int       | cmH2O | [-250, 250]         |      |
| selected input for modification | enum| NA    | {RR, TV, I:E ratio} | None |
| Acceptable low PEEP value | int       | cmH2O | [0, 30]             | 4    |
| Acceptable breath per minute | int    | bpm   | [10, 100]           | 30   |
| Acceptable exhaled tidal volume | int | mL    | [150, 600]          | 300  |
| Ventilation mode          | enum      | NA    | {triggered, timed}  | timed|

### Defined values
*Defined values* are values that are calculated or obtained in some non-trivial
manner.

| Name          | Data type | Units | Validity Criteria | Failsafe Value | Computation|
| ---------------------- | --- | ---- | --------- | -- | ----------- |
| breath cycle duration  | int | ms   |           |    | 60 000 / RR |
| circuit pressure       | int | cmH2O| [10, 40]  |    | mean(measured inspiratory pressure, measured expiratory pressure)|
| measured tidal volume  | int | mL   | [20, 1500]|    |             |

### System outputs

| Name            | Data type | Units | Validity Criteria   | Failsafe Value |
| ------------------------- | --------- | ----- | ----------- |-------|
| Power led (green led)     | enum| NA  | {on, off}           | off   |
| Power led (yellow led)    | enum| NA  | {on, off}           | off   |
| Alarm led (red led)       | enum| NA  | {on, off}           | on    |
| inspiratory valve         | enum| NA  | {open, close}       | open  |
| expiratory valve          | enum| NA  | {open, close}       | open  |
| tank valve                | enum| NA  | {open, close}       | close |
| buzzer                    | enum| NA  | {on, off}           | on    |

since the following are also displayed to the clinician. They should be part of
this table.
- measured exhaled Tidal volume (expired).
- selected I:E ratio.
- selected RR.
- computed Inspiration times.
- computed expiration times.
- minute volume.
- measured PIP.
- mean inspiratory pressure (average over one inspiration).
- selected ventilation mode.
- measured leak percentage. 


## Requirements

### SRS-0000:  Start ventilation
Upon system power-on, gVent **shall** default to timed-mode pressure-control ventilation (PCV).
This requirement might not reflect the final behaviour of the system. 

### SRS-0001:  computation of breath cycle duration
Related to: [SLS-0055.](SLS.md#SLS-0055)  
The {duration of a breath cycle} **shall** be determined between breaths (i.e., just before starting a new inspiration) according to the \<selected respiratory rate>.  
This means that gVent will compute the length of the next breath cycle before starting this breath cycle.
The {duration of a breath cycle} is given in ms.  
The computation is as follows:  60 000 / <selected respiratory rate>. The {duration of a breath cycle} is in ms. The division is an integer division. Utilisation of an integer division is acceptable in this case since the RR is given in breath per minute the  error introduced by this division is not significant. 
The {duration of a breath cycle} is an input to the ventilation SRS requirements SRS-0010 and SRS-0025.



### SRS-0002:  computation of circuit pressure
The {circuit pressure} **shall** be determined as the mean of the \<measured inspiratory pressure> and the \<measured expiratory pressure>. The computation is as follows: (\<measured inspiratory pressure> + \<measured expiratory pressure>) / 2. The division is an integer division. This is acceptable since a +/- cmH20 error in the circuit pressure is acceptable.  
The {circuit pressure} is an input to the ventilation SRS requirements SRS-0010, SRS-0015, SRS-0020, and SRS-0025.  
  
### SRS-0003:  impossible computation of circuit pressure
Related to [SRS-0002.](SRS.md#SRS-0002)  
If either of the  \<measured inspiratory pressure> or the  \<measured expiratory pressure> necessary to compute the circuit pressure is not available, gVent **shall** transition to DSS in less than TIME_TO_TRANSITION_TO_DSS_CSP ms.   
A measured input such as the  \<measured inspiratory pressure> or the  \<measured expiratory pressure>  is not available when the platform returns the unavailable value. This could be caused by the sensor not sending any values or the value sensed being outside of the valid bounds. 

### SRS-0004 : RR default failsafe value
If the \<selected respiratory rate> is not available the RR **shall** be set equal to the default failsafe value (see table for value).  
The value for respiratory rate selected by the clinician is not available when the platform returns the unavailable value. This could be caused by the clinician never setting this value or setting this value outside the validity bound for this value, or any other error in the hardware leading the platform to read a value out of the validity bounds.

### SRS-0010: PC timed mode start inspiration
Related to: [SLS-0055.](SLS.md#SLS-0055)  
While in ‘timed mode’, at the start of the current breath cycle, if the {circuit pressure} *is less than or equal to* MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP cmH2O gVENT **shall** command the inspiratory valve to open. 

### SRS-0011: PC timed mode start inspiration pressure to high
Related to [SRS-0010](SLS.md#SLS-0010), [SLS-0055.](SLS.md#SLS-0055)  
While in ‘timed mode’, at the start of the current breath cycle, the {circuit pressure} is greater than MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP cmH2O, gVent **shall** transition to DSS in less than TIME_TO_TRANSITION_TO_DSS_CSP ms. 

### SRS-0012: PC timed mode start inspiration closes expiratory valve
Related to: [SLS-0055.](SLS.md#SLS-0055)  
While in ‘timed mode’, at the start of the current breath cycle, if the {circuit pressure} is less than or equal to MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP cmH2O gVENT **shall** command the expiratory valve to close. 

### SRS-0013: PC timed mode start inspiration closes tank valve
Related to: [SLS-0055.](SLS.md#SLS-0055)  
While in ‘timed mode’, at the start of the current breath cycle, if the {circuit pressure} is less than or equal to MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP cmH2O gVENT **shall** command the tank valve to close. 

### SRS-0015: PC timed mode end inspiration
Related to [SRS-0010](SLS.md#SLS-0010), [SLS-0055.](SLS.md#SLS-0055)   
While in ‘timed mode’, at the start of the current breath cycle, the {circuit pressure} is greater than MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP cmH2O, gVent **shall** transition to DSS in less than TIME_TO_TRANSITION_TO_DSS_CSP ms. 


### SRS-0020: PC timed mode start expiration
Related to: [SLS-0055.](SLS.md#SLS-0055)  
While in ‘timed’ mode,  \<selected inspiration time> ms after the start of  the current breath cycle, if the {circuit pressure} is less than MIN_CIRCUIT_PRESSMIN_CIRCUIT_PRESSURE_FOR_OPENING_EXP_VALVE_CSPURE_FOR_OPENING_EXP_VALVE_CSP cmH2O,  gVENT **shall** command the expiratory valve to open and tank valve to open.  
Note: VALVE_CLOSING_TIME_CSP is used to ensure under normal conditions that the inspiratory valve is closed before the expiratory valve opens.

### SRS-0021: PC timed mode start expiration
While in ‘timed mode’, VALVE_CLOSING_TIME_CSP milliseconds after the end of the inspiratory for the current breath cycle,  if the {circuit pressure} is greater or equal than the MIN_CIRCUIT_PRESSURE_FOR_OPENING_EXP_VALVE_CSP cmH2O, gVent **shall** transition to DSS.

### SRS-0025: PC timed mode end expiration
Related to: [SLS-0055.](SLS.md#SLS-0055)  
While in ‘timed’ mode, VALVE_CLOSING_TIME_CSP milliseconds (<1000) before the end current breath cycle, gVENT **shall** command the expiratory valve to close and tank valve to close.

### SRS-0030: Timed mode maximal pressure control

### SRS-0035: Timed mode PIP pressure control

### SRS-0040: Timed mode minimal pressure control

### SRS-0045: Timed mode PEEP pressure control

## Dictionary

The names of configurable System Parameters are in all-uppercase, e.g., `VALVE_CLOSING_TIME_CSP`.
The names of inputs are enclosed within matching angle brackets, e.g., <selected respiratory rate>.
The names of the defined values are enclosed within braces, e.g., {circuit pressure}.

**Pressure Control** – A form of controlled ventilation, where the clinician sets a specific pressure that the ventilator delivers to the patient. The amount of volume delivered at that set patient varies based on patient factors (eg the ability of the lungs to expand (compliance)).

**Peak Inspiratory Pressure (PIP)** – The highest level of pressure that is applied to the lungs during inhalation.

**Standard Liter Per Minute (SLPM)** - Flow rate unit of measurement.

**<selected /respiratory rate>** – Minimum number of breaths per minute.

**<selected /inspiration time>** - The duration of an inspiration as selected by the clinician.

**<selected I:E ratio>** – the ratio of inspiration/expiration in one breath cycle. 

**<selected tidal volume>** – The lung volume or the volume of air displaced between inhalation and exhalation.

**<measured expiratory pressure>** – The measured pressure in cmH2O at the inspiratory valve.

**<measured inspiratory pressure>** – The measured pressure in cmH2O at the inspiratory valve.

**<acceptable/set low PEEP value>** - The value for lowest acceptable PEEP value as set by the clinician into the machine. 

**<acceptable breaths per minute>** - The value for the acceptable number of 
breaths per minute as set by the clinician.  This is an average rate for 
30 seconds.

**<measured exhaled tidal volume>** - The exhaled tidal volume measured by the system.

**<measured minute volume>** - The sum of the tidal volume over the last minute. 

**<acceptable exhaled tidal volume value>** - The acceptable exhaled tidal volume value as inputted and specified by the clinician on the device. 

**{circuit pressure}** – The instantaneous pressure seen by the patient in cmH2O. The degree of precision for this is ???. 

**{number of breaths per minute averaged over 30 seconds}** - The measured Breaths Per Minute of the System averaged over 30 seconds.

`VALVE_CLOSING_TIME_CSP` – the normal amount of time in ms required for either valve to fully close upon command from the fully open position.

`MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP` – The maximum pressure in the circuit in cmH2O so that the inspiratory valve may be opened.
 
`MIN_CIRCUIT_PRESSURE_FOR_OPENING_EXP_VALVE_CSP` – The minimum pressure in the circuit in cmH2O so that the expiratory  valve may be opened.
 
`MAX_PRESSURE_CSP` – The maximum circuit pressure in cmH2O  that can be applied to the patient lungs. 

`MAX_PRESSURE_PERSISTANCE_CSP` – the maximum time in ms for which the pressure can be `MAX_PRESSURE_CSP` without endangering the patient.

`MIN_PRESSURE_CSP` – the minimum circuit pressure in cmH2O that can be applied to the patient lungs.

`MIN_PRESSURE_PERSITANCE_CSP` – the maximum time in ms for which the pressure can be `MIN_PRESSURE_CSP` without endangering the patient.

`MAX_TIME_BELOW_PEEP_CSP` – the maximum time in ms for which the pressure can be below <acceptable/set low PEEP value> before triggering the Low PEEP Alarm (ALA7B).

`BREATH_COUNT_TIME_CSP` - the number of ms that is used to compute the {running breath count}.

