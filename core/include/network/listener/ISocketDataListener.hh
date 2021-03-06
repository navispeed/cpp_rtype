//
// Created by drouar_b on 11/13/16.
//

#ifndef CPP_RTYPE_ISOCKETDATALISTENER_HH
#define CPP_RTYPE_ISOCKETDATALISTENER_HH

#include <vector>

namespace network {
    namespace listener {
        class ISocketDataListener {
        public:
            virtual ~ISocketDataListener() { };

            virtual void notify(unsigned long fd, const std::vector<uint8_t> &data) = 0;
        };
    }
}

#endif //CPP_RTYPE_ISOCKETDATALISTENER_HH
