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
    P Power (max 5v 1Ma)
    E Rotational encoded
    
    A analog
    D diginal
    
    g ground
    p positive
    s serial

### Logic

    A_s         R_USB
    A_D3        L_s
    A_Dg        L_g     P_g
    A_Ag        E_g
    A_A0        E_B
    A_A1        E_A
    
    R_s         A_USB
    R_g         P_g
    R_8_tx      P_rx
    R_10_rx     P_tx
    
    L_p         P_p
    L_g         P_g     A_Dg
    L_s         A_D3
