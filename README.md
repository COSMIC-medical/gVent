### The Gravity Ventilator (gVent) 
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

#### __What stage is this ventilator at?__

The ventilator prototype was built with assistance at  Iron Mountain Welding Ltd., where in-house designers helped create the CAD drawings and the v3 prototype in collaboration with the UBC SOS eVent group. With the integration of a simple microcontroller, the system can sense pressure and volume. Hence the system can, on patient triggering, deliver pressure control and volume control ventilation. Additional modes of ventilation yet to be implemented include a pressure support system.
