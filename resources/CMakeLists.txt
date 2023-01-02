juce_add_binary_data(BinaryData SOURCES
    footswitch_down.png
    footswitch_up.png
    knob_hex.png
    background_on.jpg
    background_on_blue.jpg
    background_off.jpg
    default_ir.wav
    cab_switch_off.png
    cab_switch_on.png
    big_knob.png
    small_knob.png

)

# Need to build BinaryData with -fPIC flag on Linux
set_target_properties(BinaryData PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE)
