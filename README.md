# Proteus

Capture your own amps/pedals/plugins with Proteus. Can capture a drive/tone knob, or snapshot of the sound at a specific setting. Use the Proteus Capture Utility to quickly train models in the cloud with Colab. Effective for Amps/PreAmps, Distortion/Overdrive/Boost pedals (non-time based, no Reverb/Delay/Flange/Phaser). You can also capture a "rig", or combination of pedals/amp.

- Checkout the video tutorials for creating your own models for the Proteus plugin.
  - [Amp Capture](https://youtu.be/2vs4WKYgZUs)
  - [Pedal Capture](https://youtu.be/86oQuYHjpy0)
  - [Plugin Capture](https://youtu.be/vwsSYpqRqyM)
  
- Visit the GuitarML [ToneLibrary Website](https://guitarml.com/tonelibrary/tonelib-pro.html) to download Proteus compatible models.
- Download the [Proteus Capture Utility](https://github.com/GuitarML/Releases/releases/download/v1.0.0/Proteus_Capture_Utility.zip), which includes the input audio file and Colab script to train models for Proteus.

![app](https://github.com/GuitarML/Proteus/blob/master/resources/app_pic.png)

Proteus uses a LSTM neural network to emulate guitar amplifiers/preamps and distortion/overdrive/boost pedals. You can capture the sound of an amplifier either by recording with a microphone, or direct out from a load box. When running "Direct Out" models, you will need to use an Impulse Response plugin to accurately model the amp speaker/cabinet. 

You can create your own models using the [Automated-GuitarAmpModelling](https://github.com/GuitarML/Automated-GuitarAmpModelling) repository directly (LSTM with hidden size 40), or by using the Capture Utility files (available for download at [GuitarML.com](https://guitarml.com/)) with Google Colab (recommended).

To share your best models, email the json files to smartguitarml@gmail.com and they may be included in the ToneLibrary.

## Installing the plugin

1. Download the appropriate plugin installer (Windows, Mac, Linux) from the [Releases](https://github.com/GuitarML/Releases/releases) page.
2. Run the installer and follow the instructions. May need to reboot to allow your DAW to recognize the new plugin.
3. Download the Proteus Capture Utility from [GuitarML.com](https://guitarml.com/#products) to create your own amp/pedal/plugin captures.

### Loading models
Download available models from the [Proteus ToneLibrary](https://guitarml.com/tonelibrary/tonelib-pro.html). Use the Load Model button to select a folder containing Proteus json models. Note that models for NeuralPi and SmartPedal use a different model architecture and will not be compatible.

## Capturing an Amp/Pedal/Plugin (recommended to follow along with the video tutorials listed above)
1. Download the [Proteus_Capture_Utility.zip](https://github.com/GuitarML/Releases/releases/download/v1.0.0/Proteus_Capture_Utility.zip)
2. Play the ProteusCapture.wav from your DAW / Audio Device and input to your amp/pedal/plugin, and record the output. Recommended to use a Reamp for impedence matching, and a Load Box for direct amp captures. 

### Troubleshooting Captures
1. The model training is very sensitive to any latency in your output recording. Audio timing mismatch will result in stalled training, where it never goes below 0.75 loss value. May be required to manually line up your audio files before exporting, using the initial click (approx. 1 second into the ProteusCapture.wav) as guide.
2. You can capture amps using a microphone, which will result in the capture of the mic/cab/speaker. These captures may be less accurate than direct amp captures from a load box. Direct amp captures are also more flexible for adding Impluse Responses after the Proteus plugin.
3. Recommended to test a snapshot capture of your device before attempting a Knob capture. Snapshot captures are much quicker, less prone to error, and can be more accurate.
4. When exporting your audio recording, it needs to be WAV format, PCM16 (FP32 also acceptable), 44100 samplerate, Mono. 
5. In Colab, the different devices listed for Step 4a,b,c are just guidelines. They start from a pre-trained model. You may be able to get better results by trying a different options for step 4. 
6. You may use your own input audio for training, either by using your own or modifying the ProteusCapture.wav. If you do this, modify the training line in Colab step 4 in the following way (using your custom file for "YourNewInput.wav"):
`!python prep_wav.py $model -s ../YourNewInput.wav ../out.wav --normalize true`

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

### Special Thanks
Special thanks to John Stutts and Stefan Schmidt for the graphics used in Proteus. 
