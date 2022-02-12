#include "EnergySensor.h"

EnergySensor::EnergySensor(ApplicationSettings *settings): _settings(settings)
{
}

EnergySensor::~EnergySensor()
{
    for(auto it : _sensors)
    {
        delete it;
    }

}
