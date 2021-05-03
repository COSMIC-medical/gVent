# System Outputs

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