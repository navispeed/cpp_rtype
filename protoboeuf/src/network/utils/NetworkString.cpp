//
// Created by drouar_b on 10/25/16.
//

#include <cstring>
#include <stdexcept>
#include "network/utils/NetworkString.hh"

network::utils::NetworkString::~NetworkString() {

}

uint16_t network::utils::NetworkString::getSize() const {
    return this->size() + 2;
}

void network::utils::NetworkString::serialize(t_rawdata *data) const {
    unsigned short *len;

    data->resize(data->size() + this->getSize(), 0);
    len = reinterpret_cast<unsigned short *>(&data->back() - this->getSize() + 1);
    *len = static_cast<unsigned short>(this->size());
    memcpy(&data->back() - this->size() + 1, this->c_str(), this->size());
}

t_rawdata::iterator network::utils::NetworkString::deserialize(t_rawdata *data, t_rawdata::iterator it) {
    unsigned short *len;

    if (data->end() - it < 2)
        throw std::out_of_range("Can't read size of NetworkString");
    len = reinterpret_cast<unsigned short *>(&(*it));
    if (data->end() - it < *len + 2)
        throw std::out_of_range("Can't read string of NetworkString");
    this->resize(*len);
    std::memcpy(const_cast<char *>(this->c_str()), &(*it) + 2, *len);
    return it + this->getSize();
}

t_rawdata::iterator network::utils::NetworkString::deserialize(t_rawdata *data) {
    return this->deserialize(data, data->begin());
}

network::utils::INetworkUtil *network::utils::NetworkString::clone() {
    return new NetworkString;
}


