#ifndef DEVICES_DEVICE_H
#define DEVICES_DEVICE_H

#include <Arduino.h>
#include <stdint.h>

namespace Devices {

class Device {
public:
    Device(const char* id, const char* name, const char* type);
    virtual ~Device();

    // Inicialización obligatoria para cada dispositivo concreto
    virtual bool initialize() = 0;

    // Reinicia el estado general del dispositivo
    virtual void reset();

    bool isConnected() const;
    bool isEnabled() const;

    void setConnected(bool connected);
    void setEnabled(bool enabled);

    const char* getId() const;
    const char* getName() const;
    const char* getType() const;

    uint32_t getLastUpdateTime() const;
    void updateTimestamp();

protected:
    const char* _id;
    const char* _name;
    const char* _type;
    bool _enabled;
    bool _connected;
    uint32_t _lastUpdateTime;
};

} // namespace Devices

#endif // DEVICES_DEVICE_H
