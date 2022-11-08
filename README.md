# Proteus

Capture your own amps/pedals/plugins with Proteus. Can capture a drive/tone knob, or snapshot of the sound at a specific setting. Use the Proteus Capture Utility to quickly train models in the cloud with Colab.

- Checkout the video tutorials for creating your own models for the Proteus plugin.
  - [Amp Capture](https://youtu.be/2vs4WKYgZUs)
  - [Pedal Capture](https://youtu.be/86oQuYHjpy0)
  - [Plugin Capture](https://youtu.be/vwsSYpqRqyM)
  
- Visit the GuitarML [ToneLibrary Website](https://guitarml.com/tonelibrary/tonelib-pro.html) to download Proteus compatible models.

![app](https://github.com/GuitarML/Proteus/blob/master/resources/app_pic.png)

Proteus uses a LSTM neural network to emulate guitar amplifiers and distortion/overdrive/boost pedals. You can capture the sound of an amplifier either by recording with a microphone, or direct out from a load box. When running "Direct Out" models, you will need to use an Impulse Response plugin to accurately model the amp speaker/cabinet. 

You can create your own models using the [Automated-GuitarAmpModelling](https://github.com/GuitarML/Automated-GuitarAmpModelling) repository directly (LSTM with hidden size 40), or by using the Capture Utility files (available for download at [GuitarML.com](https://guitarml.com/)) with Google Colab (recommended).

To share your best models, email the json files to smartguitarml@gmail.com and they may be included in the ToneLibrary.

## Installing the plugin

1. Download the appropriate plugin installer (Windows, Mac, Linux) from the [Releases](https://github.com/GuitarML/Releases/releases) page.
2. Run the installer and follow the instructions. May need to reboot to allow your DAW to recognize the new plugin.
3. Download the Capture Utility from [GuitarML.com](https://guitarml.com/#products) to create your own amp/pedal/plugin captures.

## Build Instructions

### Build with Cmake

```bash
# Clone the repository
$ git clone https://github.com/GuitarML/Proteus.git
$ cd Proteus

# initialize and set up submodules
$ git submodule update --init --recursive

# build with CMake
$ cmake -Bbuild
$ cmake --build build --config Release
```
The binaries will be located in `Proteus/build/Proteus_artefacts/`

### Loading hardware models
Use the Load Model button to select a folder containing Proteus json models. Note that models for NeuralPi and SmartPedal use
a different model architecture and will not be compatible. 

### Special Thanks
Special thanks to John Stutts and Stefan Schmidt for the graphics used in Proteus. 
