#add_subdirectory(headless)

target_sources(Proteus PRIVATE
	myLookAndFeel.cpp
	myLookAndFeel.h
	PluginEditor.cpp
	PluginEditor.h
	PluginProcessor.cpp
	PluginProcessor.h
      ResampledRNN.cpp
      ResampledRNN.h
      SampleLSTM.h
      SampleLSTM.tpp

)

#target_precompile_headers(Proteus PRIVATE pch.h)
