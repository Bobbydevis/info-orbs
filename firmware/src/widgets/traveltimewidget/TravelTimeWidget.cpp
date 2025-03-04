#include "TravelTimeWidget.h"
#include <ArduinoJson.h>

TravelTimeWidget::TravelTimeWidget(ScreenManager &manager) : Widget(manager) {
}

TravelTimeWidget::~TravelTimeWidget() {
}

void TravelTimeWidget::setup() {
    configureColors();
}

void TravelTimeWidget::update(bool force) {
    if (force || m_travelTime.isEmpty()) {
        m_travelTime = getTravelTime();
    }
}

void TravelTimeWidget::draw(bool force) {
    if (force || !m_travelTime.isEmpty()) {
        displayTravelTime(m_travelTime);
    }
}

void TravelTimeWidget::buttonPressed(uint8_t buttonId, ButtonState state) {
    // No button actions defined for this widget
}

String TravelTimeWidget::getName() {
    return "TravelTime";
}

String TravelTimeWidget::getTravelTime() {
    HTTPClient http;
    String travelTime;
    http.begin("https://maps.googleapis.com/maps/api/directions/json?origin=YOUR_ORIGIN&destination=YOUR_DESTINATION&key=YOUR_API_KEY");
    int httpCode = http.GET();
    if (httpCode > 0) {
        String payload = http.getString();
        DynamicJsonDocument doc(2048);
        DeserializationError error = deserializeJson(doc, payload);
        if (!error) {
            travelTime = doc["routes"][0]["legs"][0]["duration"]["text"].as<String>();
        }
    }
    http.end();
    return travelTime;
}

void TravelTimeWidget::displayTravelTime(const String &travelTime) {
    m_manager.selectScreen(2);
    m_manager.fillScreen(m_backgroundColor);
    m_manager.setFont(DEFAULT_FONT);
    m_manager.setFontColor(m_foregroundColor);
    m_manager.drawCentreString("Travel Time to Home", ScreenCenterX, ScreenCenterY - 20, 2);
    m_manager.drawCentreString(travelTime, ScreenCenterX, ScreenCenterY + 20, 4);
}

void TravelTimeWidget::configureColors() {
    m_foregroundColor = m_screenMode == Light ? TFT_BLACK : TFT_WHITE;
    m_backgroundColor = m_screenMode == Light ? TFT_WHITE : TFT_BLACK;
}
