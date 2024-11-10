# ENGR10301H Dorm Lock Project

Firmware for Robert Nies's ENGR10301 project.

App code available: https://github.com/RobertJN64/Kotlin_NFC_EV

[src/main.cpp](src/main.cpp) contains overall program logic.

[src/lock.cpp](src/lock.cpp) contains code for the stepper mode which spins the winch to unlock and lock the door.

[src/reader.cpp](src/reader.cpp) contains code for the NFC reader chip.

[src/db.cpp](src/db.cpp) contains code for storing and updating valid keys using saved .json.