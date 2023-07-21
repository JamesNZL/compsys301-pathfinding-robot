# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\AKLbc\Desktop\301\psoc_code_base\CS301_Class.cydsn\CS301_Class.cyprj
# Date: Fri, 21 Jul 2023 01:22:47 GMT
#set_units -time ns
create_clock -name {ADC_IntClock(routed)} -period 983.33333333333314 -waveform {0 491.666666666667} [list [get_pins {ClockBlock/dclk_1}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 16.666666666666664 -waveform {0 8.33333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 16.666666666666664 -waveform {0 8.33333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {Clock_QENC} -source [get_pins {ClockBlock/clk_sync}] -edges {1 5 11} -nominal_period 83.333333333333314 [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {ADC_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 59 119} -nominal_period 983.33333333333314 [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {Clock_PWM} -source [get_pins {ClockBlock/clk_sync}] -edges {1 61 121} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {UART_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 131 261} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {Clock2} -source [get_pins {ClockBlock/clk_sync}] -edges {1 601 1201} [list [get_pins {ClockBlock/dclk_glb_4}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\AKLbc\Desktop\301\psoc_code_base\CS301_Class.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\AKLbc\Desktop\301\psoc_code_base\CS301_Class.cydsn\CS301_Class.cyprj
# Date: Fri, 21 Jul 2023 01:22:20 GMT
