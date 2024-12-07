#include "appTemperature.h"

double temperature, humidity;

bool trunkLightState = false;
bool mainLightState = false;

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void appTemperature()
{
    // Read temperature and humidity from the HTU21DF sensor
    double temp = read_temperature(TEMP_SENSOR_ADDRESS);
    double hum = read_humidity(TEMP_SENSOR_ADDRESS);

    lcd.clear();
    // Display the sensor data on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Hauptlicht: ");
    if (mainLightState)
    {
        lcd.print("AN");
    }
    else
    {
        lcd.print("AUS");
    }

    lcd.setCursor(0, 1);
    lcd.print("Heckklappe: ");
    if (trunkLightState)
    {
        lcd.print("AN");
    }
    else
    {
        lcd.print("AUS");
    }

    lcd.setCursor(0, 2);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print(" C");

    lcd.setCursor(0, 3);
    lcd.print("Feuchte: ");
    lcd.print(hum);
    lcd.print(" %");
}
void sensor_init()
{
    Wire.begin();
    delay(100);
    lcd.init();
    lcd.backlight();
    Wire.beginTransmission(TEMP_SENSOR_ADDRESS);
    Wire.endTransmission();
}
void turnOffBacklight()
{
    lcd.noBacklight();
}
void turnOnBacklight()
{
    lcd.backlight();
}
void setTrunkLightState(bool state)
{
    trunkLightState = state;
}
void setMainLightState(bool state)
{
    mainLightState = state;
}

double read_temperature(const int addr)
{
    double temperature;
    int low_byte, high_byte, raw_data;
    /**Send command of initiating temperature measurement**/
    Wire.beginTransmission(addr);
    Wire.write(0xE3);
    Wire.endTransmission();
    /**Read data of temperature**/
    Wire.requestFrom(addr, 2);
    if (Wire.available() <= 2)
    {
        high_byte = Wire.read();
        low_byte = Wire.read();
        high_byte = high_byte << 8;
        raw_data = high_byte + low_byte;
    }
    temperature = (175.72 * raw_data) / 65536;
    temperature = temperature - 46.85;
    return temperature;
}

double read_humidity(const int addr)
{
    double humidity, raw_data_1, raw_data_2;
    int low_byte, high_byte, container;
    /**Send command of initiating relative humidity measurement**/
    Wire.beginTransmission(addr);
    Wire.write(0xE5);
    Wire.endTransmission();
    /**Read data of relative humidity**/
    Wire.requestFrom(addr, 2);
    if (Wire.available() <= 2)
    {
        high_byte = Wire.read();
        container = high_byte / 100;
        high_byte = high_byte % 100;
        low_byte = Wire.read();
        raw_data_1 = container * 25600;
        raw_data_2 = high_byte * 256 + low_byte;
    }
    raw_data_1 = (125 * raw_data_1) / 65536;
    raw_data_2 = (125 * raw_data_2) / 65536;
    humidity = raw_data_1 + raw_data_2;
    humidity = humidity - 6;
    return humidity;
}