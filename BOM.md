# Bill of materials (BOM)

Structured as a pipe table: one row per line item, stable column order (header row defines fields for scripts and importers).

| Item | Qty | Description | Supplier | Unit price (est.) | Notes | Wokwi | Part / link |
| ---: | :-: | --- | --- | --- | --- | --- | --- |
| 1 | 1 | ELEGOO Mega R3 ATmega2560 Board + USB Cable | Amazon | ~$18 | Main controller; 54 I/O; 6 interrupt pins | Yes | [B091DSB8HY](https://www.amazon.com/dp/B091DSB8HY) |
| 2 | 1 | Electronics-Salon Screw Terminal Shield (Mega kit) | Amazon | ~$15 | Hardened field wiring; requires soldering | No | [B00UT13YXA](https://www.amazon.com/dp/B00UT13YXA) |
| 3 | 1 | Diymore 2.42 inch OLED 128x64 SSD1309 I2C/SPI | Amazon | ~$19 | Biggest practical OLED; use I2C (4-pin) mode | Yes (custom chip) | [B07XRFFPCT](https://www.amazon.com/dp/B07XRFFPCT) |
| 4 | 1 | STEPPERONLINE NEMA 34 closed-loop stepper + driver (24–80 VDC step/dir) | Amazon | Owned | Already purchased; closed-loop driver bundled with motor | Yes (stepper only) | [B0C7QH7K1T](https://www.amazon.com/dp/B0C7QH7K1T) |
| 5 | 1 | KY-040 rotary encoder module 8-pack (PCB + detent + push + knob caps) | Amazon | ~$13 pack | Use **3** for force + interval + spare; integrated PCB (no Bourns/encoder PCB); wire CLK/DT/SW to terminal shield | Yes | [B07B68H6R8](https://www.amazon.com/dp/B07B68H6R8) |
| 6 | 1 | APIELE PBS-33B momentary pushbutton, waterproof, pre-wired leads | Amazon | ~$10–15 pack | ZERO / set hit position → Mega pin 11; wired leads to terminal shield (no lug soldering); confirm panel cutout on listing | Yes | [B09V2L98NH](https://www.amazon.com/dp/B09V2L98NH) |
| 7 | 1 | APIELE KCD2-102N illuminated rocker, pre-wired (multicolor) | Amazon | ~$12–20 pack | HIT mode on/off → Mega pin 10; **12 V** lamp + switch poles per listing diagram; rectangular panel cutout—verify on Amazon page | Yes | [B08YWH3TLB](https://www.amazon.com/dp/B08YWH3TLB) |
| 8 | 1 | IEC 320 C14 panel inlet with integrated on/off switch | Amazon | ~$15 est. | **120 V** mains in → AC–DC switching supply; **250 V** label = max rating (OK at 120 V); wire hot through switch; panel cutout per listing | No | [B09X1VZ852](https://www.amazon.com/dp/B09X1VZ852) |
| 9 | 1 | ALITOVE regulated AC–DC switching power supply | Amazon | ~$20–80 est. | **Confirm V & A on listing.** Item 4 stepper/driver needs **24–80 V DC**—a **12 V** unit is for **12 V loads + 5 V buck**, **not** the NEMA 34 bus unless you pick a **24–48 V** (etc.) variant sized to the motor | No | [B06XJVYDDW](https://www.amazon.com/dp/B06XJVYDDW) |
| 10 | 1 | 2-pack 15 ft IEC power cord (C13 to wall plug) | Amazon | ~$15–25 est. | Wall → item **8** C14 inlet; **use 1** cord, spare in pack; confirm plug type (**NEMA 5-15**) for your region on listing | No | [B0CV8XX9WK](https://www.amazon.com/dp/B0CV8XX9WK) |
| 11 | 1 | Shaft coupling / coupler fittings (e.g. 14 mm flanged style) | Amazon | ~$15–40 est. | **Mechanical:** motor shaft → hammer arm; **verify bore & screw pattern** vs item **4** motor shaft and arm hub on listing | No | [B0C16XR5QZ](https://www.amazon.com/dp/B0C16XR5QZ) |
| 12 | 1 | PCB Piezotronics 086C02 Modally Tuned® impulse hammer (ICP®, BNC) | PCB | Quote | **±100 lbf** pk, **50 mV/lbf**; **BNC** output; **ICP** needs **2–20 mA** / **20–30 V** excitation from **DAQ or conditioner**—not the Mega 5 V rail; mount tips/arm per PCB docs | No | [086C02](https://www.pcb.com/products?m=086c02) |
