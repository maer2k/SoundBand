#ifndef CONFIG_H
#define CONFIG_H

// LIB VERSION
#define MAJOR_VERSION               0
#define MINOR_VERSION               1
#define REVISION_VERSION            0

// sqlite config
#define DATABASE_NAME               "songdata.dat"
#define DATATABLE_NAME              "songs"

// network config
#define DEFAULT_ADRESS              "DEFAULT_ADRESS"
#define DEFAULT_NRTWORK             0         // the network number from which the address will be taken.
#define LOCAL_HOST                  "127.0.0.1"
#define DEFAULT_PORT                1994
#define MAX_SYNC_TIME               20 * 1000 // 10 sec on millisec
#define SYNC_TIME                   5 * 1000  // 5 sec on millisec
#define DEEP_SCANER_INTERVAL        10000     // 10 sec

// sync
#define MIN_DIFFERENCE              100       // millisec

#endif // CONFIG_H
