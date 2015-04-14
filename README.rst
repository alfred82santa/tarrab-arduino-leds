===================
tarrab-arduino-leds
===================

Arduino code to control NeoPixels from computer

-------------------
Protocol definition
-------------------

+=========+=========================+
| Command | Command data            |
+=========+=========================+
| 1 Byte  | n bytes of message data |
+---------+-------------------------+

--------
Commands
--------

ACTION_SET_PIXEL
================

    **Command:** 0x01

    **Command data length:** 7 bytes (+ 1 byte for command)

    +---------+----------------------+--------+--------+--------+
    | Command | Pixel position       | Red    | Green  | Blue   | 
    +=========+===========+==========+========+========+========+
    | 0x01    | high byte | low byte | 1 byte | 1 byte | 1 byte |
    +---------+-----------+----------+--------+--------+--------+

ACTION_SET_SECTOR
================= 

    **Command:** 0x02

    **Command data length:** 7 bytes (+ 1 byte for command)

    +---------+----------------------+----------------------+--------+--------+--------+
    | Command | First pixel position | Sector length        | Red    | Green  | Blue   | 
    +=========+===========+==========+===========+==========+========+========+========+
    | 0x02    | high byte | low byte | high byte | low byte | 1 byte | 1 byte | 1 byte |
    +---------+-----------+----------+-----------+----------+--------+--------+--------+

ACTION_SHOW
===========

    **Command:** 0x03

    **Command data length:** 0 bytes (+ 1 byte for command)

    +---------+
    | Command |
    +=========+
    | 0x03    |
    +---------+

ACTION_CONFIG_STRIP
===================

    **Command:** 0x04

    **Command data length:** 2 bytes (+ 1 byte for command)

    +---------+----------------------+
    | Command | Strip length         | 
    +=========+===========+==========+
    | 0x04    | high byte | low byte |
    +---------+-----------+----------+

ACTION_SET_8_PIXELS
===================

    **Command:** 0x05

    **Command data length:** 27 bytes (+ 1 byte for command)

    +---------+----------------------+--------+---------+--------+--------+---------+--------+--------+---------+--------+--------+---------+--------+--------+---------+--------+--------+---------+--------+--------+---------+--------+--------+---------+--------+
    | Command | First pixel position | 1 Red  | 1 Green | 1 Blue | 2 Red  | 2 Green | 2 Blue | 3 Red  | 3 Green | 3 Blue | 4 Red  | 4 Green | 4 Blue | 5 Red  | 5 Green | 5 Blue | 6 Red  | 6 Green | 6 Blue | 7 Red  | 7 Green | 7 Blue | 8 Red  | 8 Green | 8 Blue | 
    +=========+===========+==========+========+=========+========+========+=========+========+========+=========+========+========+=========+========+========+=========+========+========+=========+========+========+=========+========+========+=========+========+
    | 0x05    | high byte | low byte | 1 byte | 1 byte  | 1 byte | 1 byte | 1 byte  | 1 byte | 1 byte | 1 byte  | 1 byte | 1 byte | 1 byte  | 1 byte | 1 byte | 1 byte  | 1 byte | 1 byte | 1 byte  | 1 byte | 1 byte | 1 byte  | 1 byte | 1 byte | 1 byte  | 1 byte |
    +---------+-----------+----------+--------+---------+--------+--------+---------+--------+--------+---------+--------+--------+---------+--------+--------+---------+--------+--------+---------+--------+--------+---------+--------+--------+---------+--------+
