# Gravity Ventilator (gVent) – System Level Specification

***

| Document ID | CSL0133 |
| :-- | :-- |
| Status | DRAFT | 
| Prepared For | COSMIC |
| Project Name | gVent |
| Publish Date | 2020-09-28 |
| Version | 0.8 |

***

# Table of Contents
ii. Document History
1.	[Introduction](#introduction)	
- 1.1	Purpose and scope
- 1.2	Document Structure
- 1.3	Referenced Documents	
2.	System Identification	
- 2.1	System Overview	
- 2.2	Regulatory Environment	
3.	[General](#General)
4.	[Ventilation](#Ventilation)
5.	[Performance](#Performance)
6.	[Alarm](#Alarm)
7.	Major Failure Response
8.	[Reliability](#Reliability)	
9.	[Glossary](#Glossary)

# Document History
| Version | Date | Revision Summary |
| :-- | :-- | :-- |
| 0.1 | 2020-09-24 | First draft |
| 0.2 | 2020-09-25 | Addition of Background information |
| 0.3 | 2020-09-25 | Reformat according to CSL process |
| 0.4 | 2020-09-28 | Addressed internal comments |
| 0.5 | 2020-09-28 | Update requirements numbering to remove duplicates |
| 0.6 | 2020-10-16 | Reformat to GitHub Markdown |
| 0.7 | 2020-10-21 | Update Alarm section| 

# Introduction
This document is a system level specification of the gravity Ventilator (gVent) at a level of abstraction appropriate for clinicians, including respiratory therapists, anesthesiologists, and intensivists. gVent is a low-cost ventilator which provides a constant inspiratory pressure, hence reducing the risk of barotrauma which is inherent in many low-costs ventilator designs. 
### Purpose and scope
This document identifies all the functionalities provided by the gVent. This specification is a placeholder for the system’s requirements described at an appropriate level of abstraction that allows them to be understood by clinicians. The purpose of these functional systems requirements is to make sure that all stakeholders have a common understanding of the entire scope.  
These requirements are expressed at the system level, i.e., the function of the system that will be implemented by the combination of software, hardware, sensors, actuators, other electronics, mechanical and electrical components. Each requirement is a “shall statement”, i.e., a sentence that uses the modal verb “shall” to mark these sentences as a “formal requirement”.  These shall statements are accompanied by additional sentences (inter-woven with the shall statements) and graphics that clarify these shall statements. 
At this level of abstraction, the requirements can sometimes be intentional, e.g., it is acceptable to use a phrase such as “The system shall provide the user a means of adjusting the desired pressure …” without explicitly describing the details such as whether such adjustments are made using a knob or some other method. Although the level of abstraction for these requirements is “high”, this specification also incorporates whatever is currently known about the need to handle abnormal conditions through alarms or other means, e.g., transition to a safe state.

### Document Structure
Section 2 of this document gives an overview of the system, its business motivations and its regulatory environment. The next sections provide system requirements according to their scope, e.g., functional, performance.

### Referenced Documents
The following documents are referenced in this specification:
[1] UK Medicines & Healthcare products Regulatory Agency, Specification for Rapidly Manufactured Ventilator System (RMVS), 28 April 2020 [RMVS](https://assets.publishing.service.gov.uk/government/uploads/system/uploads/attachment_data/file/879382/RMVS001_v4.pdf)
[2] A brief for engineers, by a doctor, on hacking a ventilator for surge capacity in Covid19 patients. Vol 1: Ventilator Design Brief. Dr Erich Schulz, MBBS, FANZCA, Brisbane, Australia. [Brief_vol1](https://docs.google.com/document/d/1sdrKYQ0mDOu4bJum6Fx6piRutIJovo7UqFKYHHxUD5A/edit#heading=h.zfqx8qqil1g1)
[3] Brief, Vol 2: Hardware. Dr Erich Schulz, MBBS, FANZCA, Brisbane, Australia. [Brief_vol2](https://docs.google.com/document/d/1SBT8auegsJCKCVMBHFLWaVo8rKbs0zsJc3dDVAqeADE/edit#heading=h.sx9qnelsso49)
[4] Brief, Vol 3: Software. Dr Erich Schulz, MBBS, FANZCA, Brisbane, Australia. [Brief_vol3](https://docs.google.com/document/d/1-eV7ClGCTgaqPug7u9ovE_s-U6J5s8Hzc3XAalkEgVE/edit#heading=h.sx9qnelsso49)

# System Identification
## System Overview
The gravity Ventilator (gVent) intends to provide mechanical ventilation to patients. The gravity Ventilator aims to deliver controlled pressure ventilation to patients, which appears to be the most useful ventilatory mode with COVID ARDS patients, as high pressures can easily lead to barotrauma.

At minimum, the gVent is specified to operate for a few hours to a full day for patients in extremis as per rapidly manufactured ventilator system (RMVS, gov.uk Medicines and Healthcare Products Regulatory Agency)[1] specifications.  gVent will only rely on access to power and wall ports providing a supply of oxygen and filtered air.

## Regulatory Environment

# General 
#### SLS-0001 
gVent **shall** provide ventilation mechanisms to a patient through a system composed of an inspiratory limb and an expiratory limb. 

#### SLS-0005 
gVent **shall** be designed so that the expiratory block can be cleaned and sterilized.

#### SLS-0010
gVent **shall** accept power from 120V sources and 220V sources.

#### SLS-0015
In a power outage situation, gVent **shall**: turn on a visual and sound alarm, and transition seamlessly to external battery power. The external battery shall supply power for a minimum of 20 minutes.

# Ventilation
This section’s requirements focus primarily on providing ventilation. 
#### SLS-0020
gVent **shall** allow the clinician to set the FiO2 between [21%, 100%] in 10% increments. 
gVent relies on the supply of oxygen and filtered air commonly available through wall ports in a clinical environment. 
#### SLS-0025
gVent **shall** achieve ventilation using the filtered air source flow inputs in the range of [0, 40] liters per minutes (L/min) Other than valves, gVent does not intend to use mechanical parts to deliver the Pressure Controlled air flow.

*Note: this is about design, but it is also what makes gVent different from other ventilators. It might be beneficial to include such a requirement.*

Operator adjustable settings include ventilation control parameters such as Respiratory Rate as well as alarm thresholds.

#### SLS-0030
gVent **shall** provide a visual indication of operator adjustable settings and their corresponding values to the Clinician through an LCD display.

#### SLS-0035
gVent **shall** provide an interface for the clinician to modify operator adjustable settings.

#### SLS-0040
gVent **shall** provide a clinician interface to start and stop the ventilation.

*Note: a requirement may be needed to discuss emergency stop if it is different from normal stop.*
Mechanical ventilation is generally performed in either a Pressure Control mode or a Volume control mode while many other advanced modes also exist. The Gravity Ventilator will deliver constant pressure ventilation to patients to avoid the risk of high pressures which can lead to barotrauma.

#### SLS-0045
gVent **shall** deliver air flow to patient in Pressure Controlled mode for an inspiratory pressure range [10,40] centimeters of water (cm H2O).

*Note: Pressure Controlled mode includes two sub-modes of operations: the ‘timed’ and ‘triggered’ modes.*
Mechanical ventilation is generally performed in either a Pressure Control mode or a Volume control mode while many other advanced modes also exist. The Gravity Ventilator will deliver constant pressure ventilation to patients to avoid the risk of high pressures which can lead to barotrauma.
#### SLS-0045
gVent **shall** deliver air flow to patient in Pressure Controlled mode for an inspiratory pressure range [10,40] centimeters of water (cm H2O).

*Note: Pressure Controlled mode includes two sub-modes of operations: the ‘timed’ and ‘triggered’ modes.*

#### SLS-0050
gVent **shall** allow the clinician to select either the ‘timed’ or ‘triggered’ Pressure Controlled modes of operations

#### SLS-0055
In the ‘Timed’ mode of operation, gVent **shall** deliver pressure-controlled air flow based on the Respiratory Rate, the Inspiratory:Expiratory Ratio and the Inspiratory Pressure set by the clinician.

This is the situation where the patient is fully unconscious.

#### SLS-0060
In the ‘triggered’ mode of operation, gVent **shall** detect patient breath initiation and deliver pressure-controlled air flow for a set duration.
If gVent does not detect a breathing action within the period specified by the Respiratory Rate, gVent **shall** force the breathing actions.

This is the situation where the patient is semi-conscious. 

Positive End Expiratory Pressure maintains the patient's airway pressure above the atmospheric level by exerting pressure that opposes passive emptying of the lung. 
This is important for some patient lung medical conditions. 
This pressure is typically achieved by maintaining a positive pressure flow at the end of exhalation. This pressure is measured in centimeters of water, cmH2O.

#### SLS-0065
gVent ventilation modes **shall** achieve a defined Positive End Expiratory Pressure (PEEP) range between [0, 30] centimeters of water (cm H2O).

#### SLS-0070
gVent **shall** accommodate a Respiratory Rate between [1,60] breath per minute (bpm).


#### SLS-0075
gVent **shall** accommodate an Inspiratory:Expiratory ratio from 1:1 to 1:5.

Inspiratory:Expiratory ratio refers to the ratio of inspiratory time:expiratory time. In normal spontaneous breathing, the expiratory time is about twice as long as the inspiratory time

#### SLS-0140
gVent **shall** allow the clinician to change adjustable settings during ventilation.

While the clinician can change the adjustable settings during ventilation. This includes changing the mode of operation of the ventilator (time vs Trigerred).

# Performance
#### SLS-008
When a parameter exceeds a set alarm threshold, gVent **shall** trigger the alarm within 1/10 second.

#### SLS-0085
gVent **shall** provide real-time monitoring of parameters related to alarms. Each parameter shall be monitored every 1/10 second.

#### SLS-0090
gVent **shall** detect a Start action initiated by the clinician within 1/10 second and start the actual ventilation process within 5/10 second.

#### SLS-0095
gVent **shall** detect a Stop action initiated by the clinician within 1/10 second.

#### SLS-0100
In the ‘Triggered’ mode of operation gVent **shall** detect changing breath cycle every 2/10 second and adjust ventilation according to the sensed Respiratory Rate.

# Alarm
During the ventilation procedure gVent shall sound audible alarms when thresholds are exceeded for a given amount of time for a pre-defined set of alarm parameters. These parameters are described in a [notion](https://www.notion.so/Alarm-Documents-790364c4ae0842dabbaa4d9f6f67821b#a75de7f03972482d9c61786357f3d80f).

#### SLS-0120
gVent **shall** monitor a set of alarm conditions and generate alarms  based on corresponding alarm parameters:
- Inspiratory pressure: high and Low
- Positive End Expiratory Pressure (PEEP): high and low
- Tidal volume: high and low
- percentage of CO2 at expiration: high and low 
- Oxygen supply failure
- Airway occluded
- Patient disconnect
- Circuit Leak
- Power Failure
- Battery Failure
- Low Battery
- Pressure Sensor failure
- Flow sensor failure

#### SLS-0125
when an alarm condition is present for a predefined alarm time for this condition, gVent **shall** turn on a visual and auditory alarm and display the alarm level until the alarm condition is not present anymore. 

The alarm levels are info/notice, alert, warning, alarm, and critical. Each alarm condition is affected to a unique alarm level.

#### SLS-0130
gVent **shall** allow the clinician to mute a non-critical alarm for 60 seconds.

# Major Failure Response
This section addresses gVent response to abnormal situation that go beyond alarms and involve actuation. 

The safe state of gVent is an open circuit that supplies a high flow of oxygen. 

#### SLS-0135
In the event of a major failure gVent **shall** revert to the safe state.

# Reliability
#### SLS-0105
gVent **shall** run with no interruption and no performance degradation for a duration of at least 14 days.

*** 

## Glossary
| Term |  Abbreviation | Definition |
| :--- | :-- | :--- |
| Pressure Controlled Ventilation | PCV | A set pressure is delivered for the period of inspiration and the volume achieved is measured and displayed. Ideally PRVC, an adaptive mode where the tidal volume is set, and the lowest possible pressure is delivered to achieve this volume. PCV where the user has to provide the adaptive control to achieve tidal volume is only acceptable if the tidal volume delivered is clearly displayed and the user can set patient specific upper and lower tidal volume alarms to alert to the need to adjust the pressure [1].
| Volume Controlled Ventilation | VCV | The user sets a tidal volume and Respiratory Rate. The tidal volume is delivered during the inspiratory period. Acceptable only if additional pressure limiting controls are available, see Inspiratory Pressure section [1].
| Positive End Expiratory Pressure | PEEP | The pressure maintained in the breathing system during expiration[1].
| Respiratory Rate | RR | The number of breathing cycles every minute[1].
| Inspiratory: Expiratory ratio | I:E | The proportion of each breathing cycle that is spent breathing in compared to breathing out.
| FiO2 | |  inspired oxygen proportion.[1]
| Critical Systems Labs | CSL | Critical Systems Labs is a Canadian-owned engineering consultancy with expertise in the management of safety risk and security vulnerabilities associated with complex hardware/software intensive systems. CSL has partnered with COSMIC Medical to assist in the project development, software process, and risk analysis of the gVent design-build. 
| Centimeters of water | cmH2O | Unit of pressure used in clinical settings for ventilation systems.