#ifndef TRAVELTIMEWIDGET_H
#define TRAVELTIMEWIDGET_H

#include "Widget.h"
#include <HTTPClient.h>

class TravelTimeWidget : public Widget {
public:
    TravelTimeWidget(ScreenManager &manager);
    ~TravelTimeWidget() override;
    void setup() override;
    void update(bool force = false) override;
    void draw(bool force = false) override;
    void buttonPressed(uint8_t buttonId, ButtonState state) override;
    String getName() override;

private:
    String getTravelTime();
    void displayTravelTime(const String &travelTime);
    void configureColors();

    String m_travelTime;
    uint16_t m_foregroundColor;
    uint16_t m_backgroundColor;
    ScreenMode m_screenMode = Dark;

    String m_startLocation;
    String m_endLocation;
    String m_apiKey;
};

#endif // TRAVELTIMEWIDGET_H
