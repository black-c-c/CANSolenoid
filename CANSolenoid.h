#ifndef _CANSolenoid_H_
#define _CANSolenoid_H_

#include "mbed.h"

class CANSolenoid
{
public:

    enum PinDef {
        OFF,
        ON,
        A1,
        A2,
        A3,
        A4,
        A5,
        A6,
        B1,
        B2,
        B3,
        B4,
        B5,
        B6,
        C1,
        C2,
        C3,
        C4,
        C5
    };
    CANSolenoid(PinName rd, PinName td, int dip);
 
    CANSolenoid(CAN &can_obj, int dip);
 
    ~CANSolenoid();
    
    void send();
    void write(int get_data, int switching);
    
private:

    CAN *_can_p;
    CAN &_can;
    CANMessage _msg;

    int a[6];
    int b[6];
    int c[5];
    int i;
};
#endif