# Color-Based Pill Sorting System

This repository contains the code and documentation for the Color-Based Pill Sorting System project. The system utilizes a microcontroller 8051, a color sensor, a servo motor, and a treadmill to accurately count and organize pills based on their color. This innovative solution streamlines the pill sorting process, making it ideal for pharmaceutical companies, hospitals, and pharmacies.

## Hardware Components

* 8051 Microcontroller: The central processing unit responsible for controlling and coordinating the system components.
* Color Sensor: Detects the color of pills by capturing their optical properties and converting them into electrical signals.
* Servo Motor: Controls the orientation of the pill chute, ensuring pills of a specific color are directed to the correct output container.
* Treadmill: Provides controlled movement for the pills, allowing them to pass under the color sensor one at a time.

## Working Principle

1. Initialization: The microcontroller sets up the system and configures the color sensor, servo motor, and treadmill.
2. Pill Placement: Pills are placed on the treadmill to pass in front of the color sensor individually.
3. Color Detection: The color sensor converts the optical properties of each pill into electrical signals, which the microcontroller processes to determine its color.
4. Sorting Mechanism: The microcontroller adjusts the pill chute using the servo motor to direct pills to the appropriate output container based on their color.
5. Pill Counting: The microcontroller keeps track of the number of pills sorted by color.
Output Display: A display interface connected to the microcontroller provides real-time feedback on the pill count for each color.

## Benefits and Applications

* Efficient Pill Sorting: Automates the process and reduces manual effort and human error.
* Accurate Color Detection: Precise identification of pill colors eliminates misclassification.
* Increased Productivity: Rapid and accurate sorting improves overall productivity.
* Pharmaceutical Industry: Enables efficient sorting during manufacturing or quality control processes.
* Hospitals and Pharmacies: Organizes and dispenses pills accurately, reducing medication errors.

## Installation

To set up the Color-Based Pill Sorting System, follow these steps:

1. Clone this repository: git clone https://github.com/your-username/repository.git
2. Connect the hardware components as described in the documentation.
3. Upload the microcontroller code to the 8051 microcontroller.
4. Run the system and monitor the output on the connected display interface.

## Documentation

For detailed instructions and documentation, please refer to the documentation folder.

## License

This project is licensed under the MIT License. Feel free to modify and distribute it as per the terms of the license.
