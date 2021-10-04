# Door-Locker
Door Locker system

Simulation on Proteus Professional of a door locking/unlocking system using an Arduino Uno.
The user is asked to insert a code (we have chosen a 4-digit code but this can be modified by program). The user has 3 attempts.
If the code is correct, a green LED lights up, meaning that the door is open. After 10 seconds, the door locks automatically.
If the code is not correct after 3 attempts, the door remains locked, and an alarm sounds for 10 seconds. The user will have to wait for the end of the alarm before trying again (this time can be extended).
