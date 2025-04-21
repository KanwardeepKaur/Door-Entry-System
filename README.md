DOOR ENTRY CONTROLLER SYSTEM

This project simulates a secure two-door building entry system using QNX Neutrino IPC (Inter-Process Communication). It is based on concurrent programming and embedded system design.

🛡️ Purpose

This system enhances building security by controlling and monitoring entry/exit through two doors. It helps prevent:
* Unauthorized access (e.g., tailgating)
* Theft, by verifying that the person’s weight remains the same before and after entry

Key safety features:
* Weight check after ID scan to detect anomalies
* Manual door unlock by guards for added control
* One-person-at-a-time enforcement using a state machine

Ideal for secure areas like data centers, labs, or warehouses.


The system is split into three processes:
* controller – Central logic using a finite state machine
* input – Simulates inputs like card scans, weight measurements, and guard actions
* display – Outputs system status updates based on messages from the controller

🧠 How It Works
* A person scans their ID to request entry/exit.
* A guard manually unlocks doors via input commands.
* A scale validates the person by weight.
* The controller transitions between states and broadcasts updates.
* The display listens and prints user-friendly messages about the system state.

🏗️ Components
1. controller
*Implements a state machine (des-mva.h) to manage entry/exit flow
*Receives and handles messages from input
*Sends state updates to display

2. input
* Simulates the following actions:
* Scanning ID at left/right doors
* Unlocking/locking doors
* Weight input
* Sends messages to controller via QNX MsgSend

3. display
* Attaches to a channel using name_attach
* Receives messages from controller
* Prints updates based on state transitions
* Uses outMessage[] from des-mva.h to show output like:
    "Person scanned entering with ID: 12345"
    "Weight is 72 kg"
    "Guard unlocked left door"
    "System is idle"

⚙️ Technologies Used
* Language: C
* Platform: QNX Neutrino RTOS
* IPC: QNX Native Messaging (MsgSend, MsgReceive, name_attach, name_open)

🧪 How to Run (on QNX)

1. Add content to the /tmp directory and navigate to tmp: cd /tmp
  
2. Start the display process:
  ./display &

3. Start the controller process:
  ./controller <display_pid> &

4. Start the input process and follow prompts:
  ./input <controller_pid>

5. Follow the sequence of commands written in the exitLeftDoor file to test the door exit flow.
     
Make sure all executables are compiled and running in the same QNX environment so they can communicate using the OS's IPC.
