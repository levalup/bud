//
// Created by kier on 15-11-17.
//

#ifndef BUD_NOTIFIER_H
#define BUD_NOTIFIER_H

#include <string>

namespace bud {

    enum class MESSAGEBOX_TYPE {
        ERROR,
        WARNING,
        INFORMATION
    };

    class Notifier {
    public:
        static const std::string version();

        static const std::string meta_version();

        static void log(const std::string &msg);

        static void err(const std::string &msg);

        static void message(MESSAGEBOX_TYPE type, const std::string &title, const std::string &msg);

        static void message(const std::string &title, const std::string &msg);
    };

}


#endif //BUD_NOTIFIER_H
