#include "FSM.h"
#include "MotorControl.h"
#include "Bluetooth.h"

FSM::FSM() {
    currentState = INIT;
    directionChangeCount = 0;
    startTime = millis();
}

void FSM::handleEvent(Event event) {
    switch (currentState) {
        case INIT:
            if (event == SENSOR_DETECTED) {
                // MotorControl::rotateClockwise();
                // Bluetooth::sendMessage("Motor rotating clockwise");
                transitionTo(FORWARD);
            }
            break;

        case FORWARD:
            if (event == SENSOR_DETECTED) {
                directionChangeCount++;
                // MotorControl::rotateCounterClockwise();
                // Bluetooth::sendMessage("Motor rotating counterclockwise");
                transitionTo(BACKWARD);
            } else if (millis() - startTime > 30000 || directionChangeCount >= 5) {
                // MotorControl::stop();
                // Bluetooth::sendMessage("Motor stopped");
                transitionTo(FINAL);
            }
            break;

        case BACKWARD:
            if (event == SENSOR_DETECTED) {
                directionChangeCount++;
                // MotorControl::rotateClockwise();
                // Bluetooth::sendMessage("Motor rotating clockwise");
                transitionTo(FORWARD);
            } else if (millis() - startTime > 30000 || directionChangeCount >= 5) {
                transitionTo(FINAL);
            }
            break;

        case FINAL:
                // MotorControl::stop();
                // Bluetooth::sendMessage("Motor stopped");
            // No transitions; system must reboot to reactivate.
            break;
    }
}

State FSM::getState() {
    return currentState;
}

void FSM::transitionTo(State newState) {
    currentState = newState;
}
