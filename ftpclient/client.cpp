#include "client.h"
#include <vector>

client::client()
{

}

int client::Send(const char *server, const char *file, const char *user, const char *pwd)
{
    std::vector<Command> commands;
    commands.push_back({"USER", "sportspip"});  // login
    commands.push_back({"PORT", ""}  );         // announce port for data connection, args added below.
    commands.push_back({"CWD", "videos"}  );    // change directory
    commands.push_back({"STOR", file} );        // send a file
    commands.push_back({"QUIT", ""} );          // quit


}

int client::Receive(const char *server, const char *file, const char *user, const char *pwd)
{

}
