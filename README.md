# TLC5941
TLC5941 is a high-level object-oriented Arduino library for driving large numbers of LEDs using the Texas Instruments TLC5941 and TLC5940 LED drivers. The library allows for daisy-chaining large numbers of TLC594x chips, allowing control of potentially hundred of individual LEDs (depending on RAM available).

## Structure
The library is broken into four main classes: The Controller class, which handles all the hardware related stuff, the TLC5941 class, which acts a proxy for each actual TLC5941 (and will be extended to cover TLC5940's shortly), the Light class, which acts as a proxy for each actual string of LEDs attached to the TLC5941's, and the FX class, which is a base class for deriving new effects (e.g., for implementing Cylon/KITT style flashers, or POV renderers).

## Caveats
This is one of my earlier efforts at writing low-level embedded code. As such, there are some aspects which may raise some eyebrows. Rather than hacking the SPI interface, which would only make a certain amount of sense given the TLC594x's idiosyncratic serial interface, this code relies on brute force bit-banging to achieve results. That said, results are indeed achieved. Second, by relying on a somewhat abstract polymorphism results in large vtables, and hence uses up more memory than a more streamlined C library might achieve. But the result is a usable and flexible interface, which was my primary aim.
