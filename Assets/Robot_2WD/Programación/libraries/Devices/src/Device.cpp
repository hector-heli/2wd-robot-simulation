#include "Devices/Device.h"

namespace Devices {

Device::Device(const char* id, const char* name, const char* type)
    : _id(id)
    , _name(name)
    , _type(type)
    , _enabled(false)
    , _connected(false)
    , _lastUpdateTime(0)
{
}

Device::~Device() {
}

void Device::reset() {
    _enabled = false;
    _connected = false;
    _lastUpdateTime = 0;
}

bool Device::isConnected() const {
    return _connected;
}

bool Device::isEnabled() const {
    return _enabled;
}

void Device::setConnected(bool connected) {
    _connected = connected;
    updateTimestamp();
}

void Device::setEnabled(bool enabled) {
    _enabled = enabled;
    updateTimestamp();
}

const char* Device::getId() const {
    return _id;
}

const char* Device::getName() const {
    return _name;
}

const char* Device::getType() const {
    return _type;
}

uint32_t Device::getLastUpdateTime() const {
    return _lastUpdateTime;
}

void Device::updateTimestamp() {
    _lastUpdateTime = millis();
}

} // namespace Devices
