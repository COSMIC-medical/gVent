# The Gravity Ventilator (gVent)

### A COSMIC Medical Project

This repository contains all the design files necessary to assemble a gravity ventilator. Please read license.pdf before using any of the files to understanad the liabilities and limitations you are responsible for by using this repository.

### DISCLAIMER OF WARRANTIES

You acknowledge that the Content is in research phase and all outcomes from use of the Content are not known. YOUR USE OF THE SITE AND THE CONTENT LOCATED ON THIS SITE AND ANY LINKED SITE, INCLUDING THE DESIGN SPECIFICATIONS, IS AT YOUR OWN RISK. THE SITE AND ITS CONTENT, INCLUDING THE DESIGN SPECIFICATIONS LOCATED ON THE SITE OR ANY LINKED SITE, ARE PROVIDED ON AN “AS IS” AND “AS AVAILABLE” BASIS.



COSMIC MEDICAL MAKES NO REPRESENTATIONS, WARRANTIES OR COVENANTS, WHETHER STATUTORY, EXPRESS, IMPLIED, BY COURSE OF COMMUNICATION OR DEALING, OR OTHERWISE WITH RESPECT TO THE CONTENT, INCLUDING THE DESIGN SPECIFICATIONS, AND ANY RESULTING DEVICE. COSMIC MEDICAL SPECIFICALLY DISCLAIMS ANY WARRANTY WITH REGARD TO FITNESS FOR ANY PARTICULAR PURPOSE, MERCHANTABILITY OR NON-INFRINGEMENT. 



WITHOUT LIMITING THE GENERALITY OF THE FOREGOING, COSMIC MEDICAL MAKES NO WARRANTY OF ANY KIND THAT THE CONTENT, INCLUDING THE DESIGN SPECIFICATIONS, AND ANY RESULTING DEVICE OR THE RESULTS OF THE USE OF SUCH DEVICE WILL MEET YOUR OR ANY THIRD PARTY’S REQUIREMENTS, OR ACHIEVE ANY INTENDED RESULT OR THAT THE USE OF THE DESIGN SPECIFICATIONS TO MAKE A DEVICE WILL COMPLY WITH INTERNATIONAL, FEDERAL, STATE OR MUNICIPAL LAWS AND REGULATIONS REGARDING MEDICAL DEVICES OR MEDICAL USES. YOU EXPRESSLY ACKNOWLEDGE AND AGREE THAT COSMIC MEDICAL IS NOT RESPONSIBLE FOR ANY HEALTH PROBLEMS, INJURIES OR DEATH THAT MAY RESULT FROM YOUR OR ANY THIRD PARTY’S USE OF ANY DEVICE RESULTING FROM YOUR USE OF THE CONTENT, INCLUDING THE DESIGN SPECIFICATIONS. IT IS UNDERSTOOD THAT COSMIC MEDICAL DOES NOT PROVIDE MEDICAL OR OTHER HEALTH-RELATED ADVICE.



COSMIC MEDICAL DISCLAIMS ANY RESPONSIBILITY FOR OR ASSURANCES REGARDING THE QUALITY, FUNCTIONALITY, OR SAFETY OF ANY DEVICE RESULTING FROM YOUR USE OF THE CONTENT, INCLUDING THE DESIGN SPECIFICATIONS, OR ANY DEFECT, ERRORS OR MALFUNCTION IN CONNECTION THEREWITH. FURTHER, COSMIC MEDICAL DISCLAIMS ANY RESPONSIBILITY FOR OR ASSURANCES REGARDING ANY COMMENTS, FEEDBACK, INFORMATION OR OTHER KNOW-HOW UPLOADED TO THIS SITE OR ANY LINKED SITE BY ANY USER. YOU RELY ON USER COMMENTS, FEEDBACK, INFORMATION AND/OR KNOW-HOW SOLELY AT YOUR OWN RISK.



YOU UNDERSTAND AND ACKNOWLEDGE THAT: YOU ARE A LEARNED INDIVIDUAL THAT HAS HAD THE OPPORTUNITY TO OBTAIN ANY AND ALL INFORMATION RELEVANT TO THE USE OF ANY DEVICE RESULTING FROM YOUR USE OF THE

CONTENT, INCLUDING THE DESIGN SPECIFICATIONS; YOU HAVE NO OBLIGATION TO USE THE CONTENT, THE DESIGN SPECIFICATIONS OR ANY DEVICE RESULTING THEREFROM AND YOU DO SO IN YOUR SOLE DISCRETION; YOU ARE RESPONSIBLE FOR DETERMINING THE DEGREE OF MONITORING OR OVERSIGHT THAT IS APPROPRIATE IN CONNECTION WITH PATIENT CARE AND THE USE OF ANY DEVICE RESULTING FROM YOUR USE OF THE CONTENT, INCLUDING THE DESIGN SPECIFICATIONS; YOU HAVE ACCEPTED ALL RESPONSIBILITY AND COSMIC MEDICAL RETAINS NO RESPONSIBILITY FOR YOUR USE OF ANY RESULTING DEVICE; AND YOU WILL COMPLY WITH ALL LAWS AND GOVERNMENTAL RULES, REGULATIONS AND GUIDELINES, INCLUDING ANY SAFETY PRECAUTIONS, THAT ARE APPLICABLE TO THE DEVICE OR THE USE THEREOF.

## The Idea

In February 2020 amidst the CoVid-19 pandemic, concerns about a global shortage of ventilators began to surface and these discussions rapidly became a reality. We sought out to find a local solution to the rapidly evolving crisis, working alongside the hundreds of open-source projects worldwide, aimed at tackling the same problem. 

We believe that we add a novel solution to a landscape dominated by automated bag-valve mask compression devices. Built using readily-available materials and utilizing resources routinely found at a patient’s bedside, our aims were to produce a device capable of being produced at a sub-$100 price point for low-resource settings, as well as a more robust model, both founded using the same principles.

NOTE: At this point, this device is NOT medically approved for human use, and as such, improper use can result in harm or death of the patient. It is still in its development stages and any use in the clinical setting should be under the strict consultation and supervision of qualified healthcare experts and/or engineers.


## The Design

Modern commercial ventilators are complex machines with specialized components. According to the Department of Health and Social Care guidance statement on Rapidly Manufactured Ventilator System Specification (20/03/2020), ventilators must meet certain criteria to be considered “clinically acceptable”.

RMVS-compatible ventilators must be capable of providing one of two modes of ventilation. The first is mandatory ventilation, wherein the patient is completely sedated, and all work of breathing must be done by the ventilator, according to preset criteria (e.g. tidal volume, respiratory rate, E/I ratio). Supportive ventilation, on the other hand, is used when the patient can do some work on their own. The machine must be able to sense when the patient is attempting to inhale (and provide inspiratory support), and when the patient is exhaling (and provide expiratory support).


#### __How does it work?__

The basis of the gVent system is gravity, water, and two cylindrical vessels fitted together to create a pressurized system. This pressure can then be used to ventilate a sick patient. The two vessels are each sealed at one end. The larger vessel is filled with water; the smaller vessel is placed inside the larger vessel.

Air is then introduced into the system from the hospital's O<sub>2</sub> outlet. A clinician can thus control the FiO<sub>2</sub> by titrating the amount of hospital air to the amount of delivered O<sub>2</sub>. As this pressurized gas builds up in the system, the top cylinder is displaced upwards from its resting position, commensurate to the weight of the top cylinder (which can have weight added to adjust the pressure).

To deliver air, a valve is opened, releasing the pressurized air/O<sub>2</sub> mixture through to the intubated patient. And with the valve controlled on an electronic circuit, the operator has the ability to control important respiratory parameters, including respiratory rate, I:E ratio, and the volume of air delivered to the patient.

##  Installation Instructions

1. The Assembly Instructions document for the gVent can be found at [The COSMIC Medical Website](https://cosmicmedical.ca/gvent-722-warnings-disclaimers).
2. In order to view the code and upload it to the Arduino, download and install the [Arduino IDE](https://www.arduino.cc/en/Main/Software).

## Contributing
See the [CONTRIBUTOR.md](./CONTIBUTOR.md) file in the root of the repository for guidelines and additional instructions.