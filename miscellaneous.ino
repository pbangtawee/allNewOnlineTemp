void blink(const int _pin, unsigned long _storeTime, unsigned long _onTime, unsigned long _offTime)
{
    if (digitalRead(_pin) == HIGH)
    {
        if (millis() - _storeTime >= _onTime)
        {
            _storeTime = millis();
            digitalWrite(_pin, LOW);
        }
    }
    else if (digitalRead(_pin) == LOW)
    {
        if (millis() - _storeTime >= _offTime)
        {
            _storeTime = millis();
            digitalWrite(_pin, HIGH);
        }
    }
}