#pragma once

#include "SampleLSTM.h"

template <int hiddenSize>
class ResampledRNN
{
public:
    ResampledRNN() = default;
    ResampledRNN (ResampledRNN&&) noexcept = default;
    ResampledRNN& operator= (ResampledRNN&&) noexcept = default;

    int input_size =  1;

    void initialise (const std::string& filename, double modelSampleRate);

    void prepare (double sampleRate);

    template <bool useRedisuals = false>
    void process (float* x, int numSamples)
    {
        if constexpr (useRedisuals)
        {
            for (int i = 0; i < numSamples; ++i)
                x[i] += model.forward (&x[i]);
        }
        else
        {
            for (int i = 0; i < numSamples; ++i)
                x[i] = model.forward (&x[i]);
        }
    }

private:
    using RecurrentLayerType = SampleLSTM<float, 1, hiddenSize>;
    using DenseLayerType = RTNeural::DenseT<float, hiddenSize, 1>;
    RTNeural::ModelT<float, 1, 1, RecurrentLayerType, DenseLayerType> model;

    double targetSampleRate = 44100.0;
    bool needsResampling = true;
};
