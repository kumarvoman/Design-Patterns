#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

/*
This implementation includes:

Key Components:
Observer Interface: Abstract base class with update() method
Subject Class: Manages observers and notifications
WeatherStation: Concrete subject that holds weather data
Display Classes: Three concrete observers that display different information

Features:
Attach/Detach: Dynamically add/remove observers
Automatic Notification: All observers are notified when data changes
Type Safety: Uses dynamic_cast for safe downcasting
Memory Management: Proper destructors and RAII principles
Extensibility: Easy to add new observer types

┌─────────────────────────────────────────────────────────────────────────────┐
│                            <<interface>>                                    │
│                             Observer                                        │
├─────────────────────────────────────────────────────────────────────────────┤
│ + ~Observer() = default                                                     │
│ + update(subject: Subject*): void = 0                                       │
│ + getName(): string = 0                                                     │
└─────────────────────────────────────────────────────────────────────────────┘
                                        △
                                        │
                                        │ implements
                    ┌───────────────────┼───────────────────┐
                    │                   │                   │
┌───────────────────▼─────────────┐ ┌───▼──────────────┐ ┌──▼─────────────────┐
│   CurrentConditionsDisplay      │ │ StatisticsDisplay│ │   ForecastDisplay  │
├─────────────────────────────────┤ ├──────────────────┤ ├────────────────────┤
│ - temperature: float            │ │ - temperatures:  │ │ - currentPressure: │
│ - humidity: float               │ │   vector<float>  │ │   float            │
│ - name: string                  │ │ - name: string   │ │ - lastPressure:    │
├─────────────────────────────────┤ ├──────────────────┤ │   float            │
│ + CurrentConditionsDisplay(     │ │ + StatisticsDisp-│ │ - name: string     │
│   displayName: string)          │ │   lay(displayName│ ├────────────────────┤
│ + update(subject: Subject*):    │ │   : string)      │ │ + ForecastDisplay( │
│   void                          │ │ + update(subject:│ │   displayName:     │
│ + display(): void               │ │   Subject*): void│ │   string)          │
│ + getName(): string             │ │ + display(): void│ │ + update(subject:  │
└─────────────────────────────────┘ │ + getName():     │ │   Subject*): void  │
                                    │   string         │ │ + display(): void  │
                                    └──────────────────┘ │ + getName(): string│
                                                         └────────────────────┘


┌─────────────────────────────────────────────────────────────────────────────┐
│                                Subject                                      │
├─────────────────────────────────────────────────────────────────────────────┤
│ - observers: vector<Observer*>                                              │
├─────────────────────────────────────────────────────────────────────────────┤
│ + ~Subject() = default                                                      │
│ + attach(observer: Observer*): void                                         │
│ + detach(observer: Observer*): void                                         │
│ + notify(): void                                                            │
│ + getState(): string = 0                                                    │
└─────────────────────────────────────────────────────────────────────────────┘
                                        △
                                        │
                                        │ extends
                                        │
┌───────────────────────────────────────▼─────────────────────────────────────┐
│                            WeatherStation                                   │
├─────────────────────────────────────────────────────────────────────────────┤
│ - temperature: float                                                        │
│ - humidity: float                                                           │
│ - pressure: float                                                           │
├─────────────────────────────────────────────────────────────────────────────┤
│ + WeatherStation()                                                          │
│ + setMeasurements(temp: float, hum: float, press: float): void              │
│ + measurementsChanged(): void                                               │
│ + getTemperature(): float                                                   │
│ + getHumidity(): float                                                      │
│ + getPressure(): float                                                      │
│ + getState(): string                                                        │
└─────────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────────┐
│                            Relationships                                    │
├─────────────────────────────────────────────────────────────────────────────┤
│ Subject ────────────────► Observer                                          │
│        1              0..*                                                  │
│        (composition/aggregation)                                            │
│                                                                             │
│ Observer ────────────────► Subject                                          │
│         (dependency - used in update method)                                │
└─────────────────────────────────────────────────────────────────────────────┘
*/
/*
Where to use Observer Pattern

1. GUI Event Handling
Button clicks, mouse events, keyboard input
Model-View-Controller (MVC) architecture
React/Vue.js state management

2. Model-View Architectures
Database changes updating multiple UI components
Spreadsheet applications (Excel)
Document editors

3. Real-time Data Feeds
Stock market tickers
Sports scoreboards
News feeds
IoT sensor data

4. Messaging and Notifications
Social media notifications
Email systems
Chat applications
Push notifications

5. Game Development
Achievement systems
Player state changes
Event systems

6. Logging and Monitoring
System monitoring dashboards
Error tracking
Performance metrics
Audit trails

7. Configuration Management
Settings changes
Theme switching
Language localization

8. E-commerce Applications
Inventory updates
Price changes
Order status tracking

9. Financial Systems
Trading platforms
Risk management
Portfolio tracking

10. Enterprise Applications
Workflow management
Business process automation
Integration between systems

Key Benefits:

Loose Coupling: Subject doesn't need to know observer details
Dynamic Relationships: Add/remove observers at runtime
Broadcast Communication: One-to-many notifications
Open/Closed Principle: Easy to add new observers without modifying existing code

When NOT to use:

Simple one-to-one relationships
Performance-critical code with many observers
When notification order matters
Tight coupling is acceptable/preferred
*/
 

// Forward declaration
class Subject;

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(Subject* subject) = 0;
    virtual std::string getName() const = 0;
};

// Subject interface
class Subject {
private:
    std::vector<Observer*> observers;

public:
    virtual ~Subject() = default;

    void attach(Observer* observer) {
        observers.push_back(observer);
        std::cout << "Observer " << observer->getName() << " attached." << std::endl;
    }

    void detach(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
            std::cout << "Observer " << observer->getName() << " detached." << std::endl;
        }
    }

    void notify() {
        std::cout << "Notifying all observers..." << std::endl;
        for (Observer* observer : observers) {
            observer->update(this);
        }
    }

    virtual std::string getState() const = 0;
};

// Concrete Subject - WeatherStation
class WeatherStation : public Subject {
private:
    float temperature;
    float humidity;
    float pressure;

public:
    WeatherStation() : temperature(0.0f), humidity(0.0f), pressure(0.0f) {}

    void setMeasurements(float temp, float hum, float press) {
        std::cout << "\nWeatherStation: New measurements received." << std::endl;
        temperature = temp;
        humidity = hum;
        pressure = press;
        measurementsChanged();
    }

    void measurementsChanged() {
        notify();
    }

    float getTemperature() const { return temperature; }
    float getHumidity() const { return humidity; }
    float getPressure() const { return pressure; }

    std::string getState() const override {
        return "Temperature: " + std::to_string(temperature) + 
               "°C, Humidity: " + std::to_string(humidity) + 
               "%, Pressure: " + std::to_string(pressure) + " hPa";
    }
};

// Concrete Observer - CurrentConditionsDisplay
class CurrentConditionsDisplay : public Observer {
private:
    float temperature;
    float humidity;
    std::string name;

public:
    CurrentConditionsDisplay(const std::string& displayName) : name(displayName) {}

    void update(Subject* subject) override {
        if (WeatherStation* weatherStation = dynamic_cast<WeatherStation*>(subject)) {
            temperature = weatherStation->getTemperature();
            humidity = weatherStation->getHumidity();
            display();
        }
    }

    void display() {
        std::cout << "[" << name << "] Current conditions: " 
                  << temperature << "°C and " << humidity << "% humidity" << std::endl;
    }

    std::string getName() const override {
        return name;
    }
};

// Concrete Observer - StatisticsDisplay
class StatisticsDisplay : public Observer {
private:
    std::vector<float> temperatures;
    std::string name;

public:
    StatisticsDisplay(const std::string& displayName) : name(displayName) {}

    void update(Subject* subject) override {
        if (WeatherStation* weatherStation = dynamic_cast<WeatherStation*>(subject)) {
            temperatures.push_back(weatherStation->getTemperature());
            display();
        }
    }

    void display() {
        if (temperatures.empty()) return;

        float sum = 0;
        float min = temperatures[0];
        float max = temperatures[0];

        for (float temp : temperatures) {
            sum += temp;
            if (temp < min) min = temp;
            if (temp > max) max = temp;
        }

        float avg = sum / temperatures.size();
        std::cout << "[" << name << "] Avg/Max/Min temperature: " 
                  << avg << "/" << max << "/" << min << "°C" << std::endl;
    }

    std::string getName() const override {
        return name;
    }
};

// Concrete Observer - ForecastDisplay
class ForecastDisplay : public Observer {
private:
    float currentPressure;
    float lastPressure;
    std::string name;

public:
    ForecastDisplay(const std::string& displayName) 
        : currentPressure(29.92f), lastPressure(29.92f), name(displayName) {}

    void update(Subject* subject) override {
        if (WeatherStation* weatherStation = dynamic_cast<WeatherStation*>(subject)) {
            lastPressure = currentPressure;
            currentPressure = weatherStation->getPressure();
            display();
        }
    }

    void display() {
        std::cout << "[" << name << "] Forecast: ";
        if (currentPressure > lastPressure) {
            std::cout << "Improving weather on the way!" << std::endl;
        } else if (currentPressure == lastPressure) {
            std::cout << "More of the same" << std::endl;
        } else {
            std::cout << "Watch out for cooler, rainy weather" << std::endl;
        }
    }

    std::string getName() const override {
        return name;
    }
};

int observerMain() {
    std::cout << "=== Observer Pattern Implementation ===" << std::endl;
    std::cout << "Weather Station Example\n" << std::endl;

    // Create the subject (weather station)
    WeatherStation weatherStation;

    // Create observers (displays)
    CurrentConditionsDisplay currentDisplay("Current Conditions Display");
    StatisticsDisplay statsDisplay("Statistics Display");
    ForecastDisplay forecastDisplay("Forecast Display");

    // Register observers with the subject
    weatherStation.attach(&currentDisplay);
    weatherStation.attach(&statsDisplay);
    weatherStation.attach(&forecastDisplay);

    std::cout << "\n--- First set of measurements ---" << std::endl;
    weatherStation.setMeasurements(25.0f, 65.0f, 30.4f);

    std::cout << "\n--- Second set of measurements ---" << std::endl;
    weatherStation.setMeasurements(27.0f, 70.0f, 29.2f);

    std::cout << "\n--- Third set of measurements ---" << std::endl;
    weatherStation.setMeasurements(22.0f, 90.0f, 29.2f);

    // Detach one observer
    std::cout << "\n--- Detaching Current Conditions Display ---" << std::endl;
    weatherStation.detach(&currentDisplay);

    std::cout << "\n--- Fourth set of measurements (after detaching) ---" << std::endl;
    weatherStation.setMeasurements(28.0f, 60.0f, 30.8f);

    return 0;
}

int ObserverMain() {
    observerMain();
    return 0;
}
