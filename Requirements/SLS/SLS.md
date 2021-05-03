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