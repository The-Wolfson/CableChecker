# Cable Checker
A handheld device to check XLR3 cables faster.

## Basic Operation
This device has 3 testing modes:
- input (tests incoming signal)
- output (tests outgoing signal)
- both (tests both incoming and outgoing signals)

These are controlled by the slide switch ion the side.

To start a test, hold the rotary encoder down for 3 seconds. The test will run for 5 seconds, afterwards the LEDs will show the results and input levels.

There is also a headphone jack, the knob can be used for volume.

When in output mode, the knob is used for volume.

## BOM

| Item | Model | Qty | Price (USD) | Shipping | Link |
|-|--|-|-|-|-|
| Audio Codec | ES8388 | 1 | $2.51 | $9.34 | [Link](https://lcsc.com/product-detail/ADCs-DACs-Special-Purpose_Everest-semi-Everest-Semiconductor-ES8388_C365736.html) |
| Audio Transformer | HR610660 | 2 | $1.03 | '' | [Link](https://lcsc.com/product-detail/Audio-Transformers_HANRUN-Zhongshan-HanRun-Elec-HR610660_C48357.html) |
| XLR3 Male | NC3MAAH | 1 | $1.57 | '' | [Link](https://lcsc.com/product-detail/XLR-Cannon-Connectors_Neutrik-NC3MAAH_C368463.html) |
| XLR3 Female | NC3FAAH | 1 | $1.43 | '' | [Link](https://lcsc.com/product-detail/XLR-Cannon-Connectors_Neutrik-NC3FAAH_C368521.html) |
| Audio Jack | PJ-306M | 1 | $1.14 | '' | [Link](https://lcsc.com/product-detail/Audio-Connectors_HOOYA-PJ-306M_C2939172.html) |
| Slide Switch (SP3T) | SK13D07VG5 | 1 | $0.66 | '' | [Link](https://lcsc.com/product-detail/Slide-Switches_SHOU-HAN-SK13D07VG5_C393948.html) |
| Microcontroller | ESP32-S3-Zero | 1 | $6.10 | Free | [Link](https://core-electronics.com.au/esp32-s3-mini-development-board-retired.html) |
| Rotary Encoder w/ Button | PEC11-4215F-S24 | 1 | $6.53 | '' | [Link](https://core-electronics.com.au/rotary-encoder-extras.html) |
| LED Bar Graph | WS2812B | 1 | $3.22 | '' | [Link](https://core-electronics.com.au/glowbit-stick-1x8.html) |
| PCB (JLCPCB) | - | 1 | $2.92 | $16.59 | [Link](Link) |
| Case (JLC3DP) | - | 1 | $2.92 | '' | [Link](Link) |

**AUD Total:** $76.21

**USD Total:** $50.01

## Background
I run sound at my school, and we have a legacy system, set up who knows how many years ago. As part of that, there are lots of XLR3 cables lying around that nobody knows if they work, or not.

The solution to my problem, a small portable device that tests if the XLR cable is functioning properly. THis exists... for around $350 AUD. 

So, when I heard about Hackclub's *Highway* YSWS, my mind immediately jumped to this.
