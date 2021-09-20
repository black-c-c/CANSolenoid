#include "mbed.h"
#include "CANSolenoid.h"

CANSolenoid::CANSolenoid(PinName rd, PinName td, int dip)
    : _can_p(new CAN(rd, td)), _can(*_can_p)
{
    _msg.id = (dip * 3) + 1500;
    _msg.len = 3;
    for(i=0; i<6; i++){
        a[i] = 0;
        b[i] = 0;
        if(i<5){
            c[i] = 0;
        }
    }
}

CANSolenoid::CANSolenoid(CAN &can_obj, int dip)
    : _can_p(NULL), _can(can_obj)
{
    _msg.id = (dip * 3) + 1500;
    _msg.len = 3;
    for(i=0; i<6; i++){
        a[i] = 0;
        b[i] = 0;
        if(i<5){
            c[i] = 0;
        }
    }
}
 
CANSolenoid::~CANSolenoid()
{
    delete _can_p;
}
 
void CANSolenoid::write(int get_data, int switching)
{
    if(switching) {
        switch(get_data) {
            case A1:
                a[0] = 1;
                _msg.data[0] |= 0b10000000;
                break;
            case A2:
                a[1] = 1;
                _msg.data[0] |= 0b01000000;
                break;
            case A3:
                a[2] = 1;
                _msg.data[0] |= 0b00100000;
                break;
            case A4:
                a[3] = 1;
                _msg.data[0] |= 0b00010000;
                break;
            case A5:
                a[4] = 1;
                _msg.data[0] |= 0b00001000;
                break;
            case A6:
                a[5] = 1;
                _msg.data[0] |= 0b00000100;
                break;
            case B1:
                b[0] = 1;
                _msg.data[0] |= 0b00000010;
                break;
            case B2:
                b[1] = 1;
                _msg.data[0] |= 0b00000001;
                break;
            case B3:
                b[2] = 1;
                _msg.data[1] |= 0b10000000;
                break;
            case B4:
                b[3] = 1;
                _msg.data[1] |= 0b01000000;
                break;
            case B5:
                b[4] = 1;
                _msg.data[1] |= 0b00100000;
                break;
            case B6:
                b[5] = 1;
                _msg.data[1] |= 0b00010000;
                break;
            case C1:
                c[0] = 1;
                _msg.data[1] |= 0b00001000;
                break;
            case C2:
                c[1] = 1;
                _msg.data[1] |= 0b00000100;
                break;
            case C3:
                c[2] = 1;
                _msg.data[1] |= 0b10000010;
                break;
            case C4:
                c[3] = 1;
                _msg.data[1] |= 0b00000001;
                break;
            case C5:
                c[4] = 1;
                _msg.data[2] |= 0b10000000;
                break;
        }
    } else {
        switch(get_data) {
            case A1:
                if(a[0]){
                    _msg.data[0] -= 0b10000000;
                    a[0] = 0;
                }
                break;
            case A2:
                if(a[1]){
                    _msg.data[0] -= 0b01000000;
                    a[1] = 0;
                }
                break;
            case A3:
                if(a[2]){
                    _msg.data[0] -= 0b00100000;
                    a[2] = 0;
                }
                break;
            case A4:
                if(a[3]){
                    _msg.data[0] -= 0b00010000;
                    a[3] = 0;
                }
                break;
            case A5:
                if(a[4]){
                    _msg.data[0] -= 0b00001000;
                    a[4] = 0;
                }
                break;
            case A6:
                if(a[5]){
                    _msg.data[0] -= 0b00000100;
                    a[5] = 0;
                }
                break;
            case B1:
                if(b[0]){
                    _msg.data[0] -= 0b00000010;
                    b[0] = 0;
                }
                break;
            case B2:
                if(b[1]){
                    _msg.data[0] -= 0b00000001;
                    b[1] = 0;
                }
                break;
            case B3:
                if(b[2]){
                    _msg.data[1] -= 0b10000000;
                    b[2] = 0;
                }
                break;
            case B4:
                if(b[3]){
                    _msg.data[1] -= 0b01000000;
                    b[3] = 0;
                }
                break;
            case B5:
                if(b[4]){
                    _msg.data[1] -= 0b00100000;
                    b[4] = 0;
                }
                break;
            case B6:
                if(b[5]){
                    _msg.data[1] -= 0b00010000;
                    b[5] = 0;
                }
                break;
            case C1:
                if(c[0]){
                    _msg.data[1] -= 0b00001000;
                    c[0] = 0;
                }
                break;
            case C2:
                if(c[1]){
                    _msg.data[1] -= 0b00000100;
                    c[1] = 0;
                }
                break;
            case C3:
                if(c[2]){
                    _msg.data[1] -= 0b00000010;
                    c[2] = 0;
                }
                break;
            case C4:
                if(c[3]){
                    _msg.data[1] -= 0b00000001;
                    c[3] = 0;
                }
                break;
            case C5:
                if(c[4]){
                    _msg.data[2] -= 0b10000000;
                    c[4] = 0;
                }
                break;
        }
    }
}

void CANSolenoid::send()
{
    _can.write(_msg);
}