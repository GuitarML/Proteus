/*
  ==============================================================================
  CabSim
  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"

#pragma once

//==============================================================================
class CabSim
{
public:
    //==============================================================================
    CabSim() = default;

    //==============================================================================
    void prepare (const juce::dsp::ProcessSpec& spec)
    {
        processorChain.prepare(spec);
    }

    //==============================================================================
    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept
    {
        processorChain.process(context);
    }

    //==============================================================================
    void reset() noexcept 
    {
        processorChain.reset();
    }

    void load(const void* sourceData, size_t sourceDataSize) noexcept
    {
        auto& convolution = processorChain.template get<convolutionIndex>();
        //loadImpulseResponse(const void* sourceData, size_t sourceDataSize, Stereo isStereo, Trim requiresTrimming, size_t size, Normalise requiresNormalisation = Normalise::yes)
        convolution.loadImpulseResponse(sourceData, sourceDataSize,
            juce::dsp::Convolution::Stereo::yes,
            juce::dsp::Convolution::Trim::no,
            0);
       //convolution.loadImpulseResponse(irFile,
       //   juce::dsp::Convolution::Stereo::yes,
       //   juce::dsp::Convolution::Trim::no,
       //   0); // Set to 0 to use the full size of IR with no trimming
    }

private:
    enum
    {
        convolutionIndex
    };

    juce::dsp::ProcessorChain<juce::dsp::Convolution> processorChain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CabSim)
};