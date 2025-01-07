#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG 0

#if (DEBUG == 1)
#define DEBUG_MESSAGE_TIME_MS 1000
#define SERIAL_BAUDRATE 9200
#endif

void debugInit(void);
void debugTask(void);

#endif