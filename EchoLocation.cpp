#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <boost/asio.hpp>
#include <cmath>
#include <vector>
#include <array>
#include <type_traits>

template <typename T>
using const add_const_T = typename std::add_const<T>::type; // Trigger pin for the ultrasonic sensor
template <typename E>
using const add_const_E = typename std::add_const<E>::type; // Echo pin for the ultrasonic sensor

void clearScreen() 
{
    system("clear");
}

void oousetup() 
{
  Serial.begin(9600); // Initialize serial communication
  pinMode(trigPin, OUTPUT); // Set trigger pin as output
  pinMode(echoPin, INPUT); // Set echo pin as input
}

void loop() 
{
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Calculate distance from echo
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  
  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Wait for a short period before taking the next measurement
  delay(100);
}

int main()
{
    char x = " ";
    add_const_T<int> trigPin = 10; //initialize trigPin value
    add_const_E<int> trigPin = 11; //initialize trigPin value
    
    std::cout << "Welcome to EchoLocation 1.0" << std::endl;
    std::cout << "Start [Y/N]" << std::endl;
    std::cin >> x;
    
    if (x == "Y" || x == "y")
    {   
        clearScreen();
        std::cout << "initializing." << std::endl;
        while(true)
        {
            delay(100);
            try()
            {
                oousetup(); 
                loop();
            }
            catch(const std::runtime_error& e)
            {
                std::cerr << "Error: Check Device connection." << e.what() <<std::endl;
            }
        }
    }
    else if(x == "N" || x == "n")
    {
        std::cout << "Goodbye";
        delay(100);
        exit(0);
    }
    else
    {
        std::cerr << "invalid input. Goodbye." << std::endl;
        exit(1);
    }
    
    return 0;
}