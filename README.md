# Icethetics

It will interpret the encoded data from an ice core to reconstruct climatic records into an unique artistic representation. A visitor explores the encoded past using a primitive slider with a printing machine by positioning the arrow at the layer of interest and activating the printing. The printed receipt will provide a physical souvenir representing the fingerprint of certain Earth's age.

```
CART 411
Computation Arts
Concordia University
```

# Setup

## Wires

### Legend

    A Arduino
    R Raspberry
    P Printer
    L Leds
    P Power
    M "rotational magnet" TODO fix name
    
    A analog
    D diginal
    
    g ground
    p positive
    s serial

### Logic

    A_D3 <-> ?
    A_Dg <-> L_g <-> P_g
    A_Ag <-> M_g
    A_A0 <->
    A_A1 <->
    
    R_g <-> P_g
    R_? <-> RX
    R_? <-> Tx
    
    L_p <-> P_p (max=1mA)
    L_g <-> P_g
    L_s <-> 
