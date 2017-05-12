/*
 * @file    RDM6300.h
 * @author  Arliones Hoeller Jr.
 * @license MIT (see LICENSE)
 * 
 */

#ifndef __RDM6300_H__
#define __RDM6300_H__

template<typename SerialT>
class RDM6300 {
private:
    RDM6300() :
            _serial(0), _current_id(0), _received_checksum(0), _id_is_valid(
                    false) {
    }

public:

    RDM6300(SerialT * serial) :
            _serial(serial), _current_id(0), _received_checksum(0), _id_is_valid(
                    false) {
    }

    ~RDM6300() {
    }

    unsigned long long read() {
        while (!_id_is_valid) {
            while (_serial->has_data()) {
                parse(_serial->get());
            }
        }
        _id_is_valid = false;
        return _current_id;
    }

private:
    int get_val(char c) {
        static const char ascii_diff = 48;
        c -= ascii_diff;
        if (c > 9)
            c -= 7;
        return c;
    }

    int get_checksum(unsigned long long data) {
        union {
            unsigned char uc[8];
            unsigned long long ul;
        } tmp;
        tmp.ul = data;
        return tmp.uc[0] ^ tmp.uc[1] ^ tmp.uc[2] ^ tmp.uc[3] ^ tmp.uc[4];
    }

    bool parse(char d) {
        static int state = 0;

        unsigned long long val = 0;
        unsigned long long desl = 0;

        _id_is_valid = false;

        switch (state) {
        case 0:
            if (d == 0x02) {
                _current_id = 0;
                _received_checksum = 0;
                state = 1;
            }
            // else => garbage!
            break;
        case 11: //1st byte of checksum
            val = get_val(d);
            _received_checksum = val << 4;
            state++;
            break;
        case 12: //2nd byte of checksum
            val = get_val(d);
            _received_checksum |= val;
            state++;
            break;
        case 13:
            if (d == 0x03 && _received_checksum == get_checksum(_current_id)) {
                _id_is_valid = true;
            }
            state = 0;
            break;
        default:
            val = get_val(d);
            desl = (10 - state) * 4;
            _current_id |= val << desl;
            state++;
            break;
        }

        return _id_is_valid;
    }

    SerialT * _serial;
    unsigned long long _current_id;
    unsigned char _received_checksum;
    bool _id_is_valid;
};

#endif /* __RDM6300_H__ */

