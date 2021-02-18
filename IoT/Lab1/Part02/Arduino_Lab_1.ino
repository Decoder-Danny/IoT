#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }
}

// Initialize variables
float temperaturesum = 0;
float humiditysum = 0;
float pressuresum = 0;
    
// Initialize arrays
float temperatureArray[10] = {0};
float humidityArray[10] = {0};
float pressureArray[10] = {0};

// Initiliaze a boolean value to check if there are more than 10 readings
bool haveyoupasttenyet = false;

// Initialize a counter to determine how many readings had been taken
int count = 0;
  
void loop() {
  // Initialize variables
  float avgtemperature = 0;
  float avghumidity = 0;
  float avgpressure = 0;

  // read all the sensor values
  float temperature = HTS.readTemperature();
  float humidity = HTS.readHumidity();
  float pressure = BARO.readPressure();

  // Update arrays with current readings
  for (int i = 0; i < 9; i++){
    temperatureArray[i] = temperatureArray[i+1];
    humidityArray[i] = humidityArray[i+1];
    pressureArray[i] = pressureArray[i+1];
  }
  temperatureArray[9] = temperature;
  humidityArray[9] = humidity;
  pressureArray[9] = pressure;

  // Increments counter
  count++;

  // Checks if 10 samples has past
  if (count >= 10){
    haveyoupasttenyet = true;
  }

  // Calculates average of past 10 readings
  if(haveyoupasttenyet){
    temperaturesum = 0;
    humiditysum = 0;
    pressuresum = 0;
    avgtemperature = 0;
    avghumidity = 0;
    avgpressure = 0;
    
    for (int i = 0; i < 10; i++){
      temperaturesum += temperatureArray[i];
      humiditysum += humidityArray[i];
      pressuresum += pressureArray[i];
    }

    avgtemperature = temperaturesum/10;
    avghumidity = humiditysum/10;
    avgpressure = pressuresum/10;
  }
  
  // print each of the sensor values
  Serial.println("Current Readings");
  Serial.println("-----------------------------------");
  
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" kPa");

  // print an empty line
  Serial.println();
  
  Serial.println("Average Readings of Past 10 Samples");
  Serial.println("-----------------------------------");
  
  if(haveyoupasttenyet){
    Serial.print("Average Temperature = ");
    Serial.print(avgtemperature);
    Serial.println(" °C");
    
    Serial.print("Average Humidity = ");
    Serial.print(avghumidity);
    Serial.println(" %");

    Serial.print("Average Pressure = ");
    Serial.print(avgpressure);
    Serial.println(" kPa");
  } else{
    Serial.println("Not enough data for average, please standby until 10 seconds...");
  }
  
  // print 2 empty lines
  Serial.println();
  Serial.println();

  // wait 1 second to print again
  delay(1000);
}
