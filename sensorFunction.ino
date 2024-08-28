void getWeatherData()
{
  float RAW_TEMPERATURE = 0;
  float RAW_HUMIDITY = 0;

  for (int i = 0; i < READ_SAMPLE; i++)
  {
    sensors_event_t humidity, temp;
    AHT_SENSOR.getEvent(&humidity, &temp);
    RAW_TEMPERATURE = RAW_TEMPERATURE + temp.temperature;
    RAW_HUMIDITY = RAW_HUMIDITY + humidity.relative_humidity;

    delay(25);
  }

  TEMPERATURE = RAW_TEMPERATURE / READ_SAMPLE;
  HUMIDITY = RAW_HUMIDITY / READ_SAMPLE;

  Serial.print("Temperature : ");
  Serial.print(TEMPERATURE);
  Serial.print(" *C | Humidity : ");
  Serial.print(HUMIDITY);
  Serial.println(" %");
}