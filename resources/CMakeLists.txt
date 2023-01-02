juce_add_binary_data(BinaryData SOURCES
    background_on.jpg
    background_on_blue.jpg
    default_ir.wav
    cab_switch_off.png
    cab_switch_on.png
    big_knob.png
    small_knob.png

)

# Need to build BinaryData with -fPIC flag on Linux
set_target_properties(BinaryData PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE)
