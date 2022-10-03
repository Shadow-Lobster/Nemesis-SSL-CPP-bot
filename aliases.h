#include <iostream>

class alias
{
    public:
        /*** config values ***/
        const char *hostname ="irc.evilcorp.ga";
        const int portnum = 6697;
        std::string nick = "Nemesis";
        std::string user = "Nemesis 0 * cppbot";
        std::string password = "";
        std::string channels = "#shadowcave,#cult,#bots"; //seperate channels by comma(,)
        std::string owner = "Man.With.Claws"; //owner of the bots, host name if set by services is preferable along with nick.
        std::string usermodes = "+B";
        std::string quit_msg = "your worst enemy will be back";

        /*** Aliases string format ***/
        std::string nick_alias = "NICK " + nick + "\r\n"; //NICK raw
        std::string user_alias = "USER " + user + "\r\n"; //USER raw
        std::string join_alias = "JOIN " + channels + "\r\n"; //JOIN channel raw
        std::string usermodes_alias = "MODE " + nick + " " + usermodes + "\r\n";
        std::string quit_alias = "QUIT " + quit_msg + "\r\n";
        std::string identify_alias = "PRIVMSG NickServ :identify " + nick + " " + password + "\r\n";

        /*** Aliases char* format ***/
        const char *nick_raw = nick_alias.c_str();
        const char *user_raw = user_alias.c_str();
        const char *join_raw = join_alias.c_str();
        const char *usermodes_raw = usermodes_alias.c_str();
        const char *quit_raw = quit_alias.c_str();
        const char *identify_raw = identify_alias.c_str();
};
