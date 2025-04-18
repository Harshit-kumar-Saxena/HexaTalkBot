HexaTalkBot

Overview

HexaTalkBot is a six-legged robotic system designed for talk-back functionality, manual control, and autonomous movement. Built using ESP32 for interactive and efficient mobility.

Features

Talk-Back System – Responds to voice commands for interactive communication.

Manual Mode – Can be controlled via remote or mobile app.

Autonomous Navigation – Uses sensors to detect obstacles and move independently.

Grid Polygon Movement – We use a grid polygon system for movement.

Requirements

Hardware

ESP32 microcontroller

Servo motors (12x for hexapod movement)

Ultrasonic or other sensors for obstacle detection

Battery pack for power supply

SD card for storing general talks in MP3 files

Software & Libraries

Arduino IDE
ESP32 Board Support Package
Servo library
Wi-Fi library

Installation

1️⃣ Set Up ESP32 in Arduino IDE

Ensure you have the required board and libraries installed:

Install ESP32 Board Manager in Arduino IDE
Add necessary libraries (Servo, Wi-Fi, etc.)

2️⃣ Upload the Firmware

Upload HexaTalkBot.ino to the ESP32.

3️⃣ Run the Robot

Power the hexapod.

Use the remote app for manual control or activate autonomous mode.

⚙️ How It Works

Manual Mode: Commands from a mobile app control the hexapod's movement.

Talk-Back System: The bot processes voice inputs and responds accordingly.

Autonomous Mode: Sensors detect obstacles and navigate accordingly.

🎮 Usage

Use the remote control app for manual operation.

Activate autonomous mode for independent navigation.

Experiment with the talk-back feature for interactive responses.

🔧 Potential Improvements

Implement AI-based speech recognition for improved interaction.

Enhance path planning algorithms for smoother movement.

📜 License

This project is open-source and available for modifications.

