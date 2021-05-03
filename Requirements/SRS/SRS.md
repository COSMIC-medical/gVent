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