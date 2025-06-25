---
title: "CableChecker"
author: "Joshua Wolfson"
description: "A portable tool for techies to check XLR cables."
created_at: "2025-06-22"
---

# June 23rd: Initial conception and part sourcing.

Initial conception of the idea: an easy way for theatre techs to check whether xlr cables work.

After a bit of brainstorming, heres the BOM I arrived at:

| Item                         | Model          | Qty | Price        | Shipping      | Link                                                                 |
|------------------------------|----------------|-----|--------------|---------------|----------------------------------------------------------------------|
| Audio Codec                  | ES8388         | 1   | $26.99       | $12.40        | [ES8388 Module](https://pcbartists.com/product/es8388-module/)      |
| Audio Transformer            | ED8            | 2   | $2.92        | $2.50         | [ED8 Transformer](https://www.aliexpress.com/i/1005002450695711.html) |
| XLR3 Male                    | NC3MAAV        | 1   | $1.74        | $3.98         |                                                                      |
| XLR3 Female                  | NC3FAAV        | 1   | $1.74        |               |                                                                      |
| Microcontroller              | ESP32-S3       | 1   | $9.30        | Free          | [ESP32-S3 Mini](https://core-electronics.com.au/esp32-s3-mini-development-board-retired.html) |
| Rotary Encoder w/ Button     | EC11           | 1   | $5.25        | Free          | [EC11 Encoder Module](https://core-electronics.com.au/ec11-rotary-encoder-module.html) |
| LED Bar Graph                | HDSP-4836      | 1   | $8.50        | Free          | [12-LED Bargraph](https://core-electronics.com.au/bi-color-red-green-12-led-bargraph-pack-of-2.html) |

**Total:** $56.44  
**Total (inc. Shipping):** $75.32

Yes, I know the ES8388 is expensive, I'm going to do some more digging over the next few days for some alternatives.

Anyway, this is my first time doing anything to do with pcb's and the like, I normally code my way out of problems. So we'll see how it goes.

With that being said, I'm onto wiring and modelling tomorrow.

Thanks for following along,

Josh

**Total time spent: 2h**

# June 25th: Finalising BOM and starting Wiring/Modelling

This is my updated parts list:

| Part                     | SKU       | Model    | Quantity | Price   | Shipping | Link                                                                                  |
|--------------------------|-----------|----------|----------|---------|----------|---------------------------------------------------------------------------------------|
| Audio Module             | PCBA2103  | ES8388   | 1        | $26.99  | $12.40   | [Link](https://pcbartists.com/product/es8388-module/)                                 |
| Audio Transformer        |           | ED8      | 2        | $5.84   | $2.50    | [Link](https://www.aliexpress.com/i/1005002450695711.html)                            |
| XLR3 Male                | NC3MAAV   | XLR3     | 1        | $1.74   | $3.98    | [Link](https://www.aliexpress.com/item/1005003251181647.html)                         |
| XLR3 Female              | NC3FAAV   | XLR3     | 1        | $1.74   | ''       | [Link](https://www.aliexpress.com/item/1005003251181647.html)                         |
| Microcontroller          | WS-25081  | ESP32-S3 | 1        | $9.30   | Free     | [Link](https://core-electronics.com.au/esp32-s3-mini-development-board-retired.html)  |
| Rotary Encoder w/ Button | ADA377    | PEC11    | 1        | $9.95   | ''       | [Link](https://core-electronics.com.au/rotary-encoder-extras.html)                    |
| LED Bar Graph            | ADA1719   | KWL-R1230XDUGB | 2  | $8.50   | ''       | [Link](https://core-electronics.com.au/bi-color-red-green-12-led-bargraph-pack-of-2.html) |

**Total:** $64.06 (AUD)
**Total (inc. Shipping):** $82.94 (AUD)

I found a rotary encoder with a lower profile. I think, unfortunately, that I'm going to have to shell out for the PCB artists ES8388.

On another note, I've started wiring and modelling the body using KiCad and Fusion360.

Thanks for following along,

Josh

**Total time spent: 5h**
