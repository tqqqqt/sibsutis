#ifndef ALL_H
#define ALL_H

struct players_in_loby{
        int clientSocket;
        int curentState;
        char *nickName;
        struct players_in_loby *next;
};

struct players_in_game{
        int socketWhoInvite, readyFlagWhoInvite;
        char *nickWhoInvite;
        int socketWhoGetInvite, readyFlagWhoGetInvite;
        char *nickWhoGetInvite;
        int curentGameState, checkTimes;
        char *gameName;
        pid_t childPid;
        struct players_in_game *next;
};

#endif
