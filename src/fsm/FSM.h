#ifndef FSM_H
#define FSM_H

enum State {
    INIT,
    FORWARD,
    BACKWARD,
    FINAL
};

unsigned long millis(void);
enum Event {
    SENSOR_DETECTED,
    TIMEOUT,
    MAX_DIRECTION_CHANGE
};

class FSM {
public:
    FSM();
    void handleEvent(Event event);
    State getState();

private:
    State currentState;
    int directionChangeCount;
    unsigned long startTime;
    void transitionTo(State newState);
};

#endif
