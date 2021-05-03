# Dictionary

The names of configurable System Parameters are in all-uppercase, e.g., `VALVE_CLOSING_TIME_CSP`.
The names of inputs are enclosed within matching angle brackets, e.g., <selected respiratory rate>.
The names of the defined values are enclosed within braces, e.g., {circuit pressure}.

**Pressure Control** – A form of controlled ventilation, where the clinician sets a specific pressure that the ventilator delivers to the patient. The amount of volume delivered at that set patient varies based on patient factors (eg the ability of the lungs to expand (compliance)).

**Peak Inspiratory Pressure (PIP)** – The highest level of pressure that is applied to the lungs during inhalation.

**Standard Liter Per Minute (SLPM)** - Flow rate unit of measurement.

**\<selected /respiratory rate>** – Minimum number of breaths per minute.

**\<selected /inspiration time>** - The duration of an inspiration as selected by the clinician.

**\<selected I:E ratio>** – the ratio of inspiration/expiration in one breath cycle. 

**\<selected tidal volume>** – The lung volume or the volume of air displaced between inhalation and exhalation.

**\<measured expiratory pressure>** – The measured pressure in cmH2O at the inspiratory valve.

**\<measured inspiratory pressure>** – The measured pressure in cmH2O at the inspiratory valve.

**\<acceptable/set low PEEP value>** - The value for lowest acceptable PEEP value as set by the clinician into the machine. 

**\<acceptable breaths per minute>** - The value for the acceptable number of 
breaths per minute as set by the clinician.  This is an average rate for 
30 seconds.

**\<measured exhaled tidal volume>** - The exhaled tidal volume measured by the system.

**\<measured minute volume>** - The sum of the tidal volume over the last minute. 

**\<acceptable exhaled tidal volume value>** - The acceptable exhaled tidal volume value as inputted and specified by the clinician on the device. 

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
