#ifndef BROADCAST_H
#define BROADCAST_H
#include <cstring>
/*
[0]     : server id
[1]     : message type
[2-3]   : timestamp
[4-31]  : message

*/

class Broadcast
{
    char chr[62] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};
    char unq[3844][2] = {};

    struct broadcast_t
    {
        char id[1];
        char type[1];
        char timestamp[2];
        char message[28];
    };
    broadcast_t broadcast;
    void populate()
    {
        int count = 0;
        for (int i = 0; i < 62; i++) //[48-57], [65-90], [97-122]
        {
            for (int p = 0; p < 62; p++)
            {
                char *c = unq[count];
                c[0] = chr[i];
                c[1] = chr[p];
                // c[2] = {};
                count += 1;
            }
        }
    }
    Broadcast() : broadcast{}
    {
        populate();
    }

    static Broadcast s_broadcast;

public:
    void Create(char *id, char *type, char *timestamp, char *message)
    {
        memcpy(broadcast.id, id, 1);
        memcpy(broadcast.type, type, 1);
        memcpy(broadcast.timestamp, timestamp, 2);
        memcpy(broadcast.message, message, 28);
    }
    static Broadcast *Instance()
    {
        return &s_broadcast;
    }
    enum Type
    {
        SRV_ADD = 0
    };
    char *data()
    {
        return &broadcast.id[0];
    }
};

#endif //BROADCAST_H