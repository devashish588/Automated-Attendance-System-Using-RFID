
# RFID Attendance System with Arduino

This is a simple **RFID-based time attendance system** using Arduino, MFRC522 RFID module, DS3231 RTC, and OLED display.

## 📦 Features

- Records attendance with real-time timestamps
- Displays user status on OLED
- Prints logs to Serial (can be extended to SD card or server)

## 🛠️ Hardware Required

- Arduino UNO / Nano
- MFRC522 RFID Module
- DS3231 RTC Module
- OLED Display (0.96", I2C)
- Breadboard & Wires
- RFID Key Tags

## 🔌 Circuit Diagram

See [`docs/circuit_diagram.png`](docs/circuit_diagram.png)

## 🧠 How it Works

1. When an RFID tag is tapped, the UID is read.
2. The UID is compared against a list of authorized users.
3. If matched:
   - OLED shows name & timestamp.
   - Serial monitor logs the time.
4. If unmatched:
   - OLED displays "Access Denied".

## 📝 Future Improvements

- Save logs to SD card or upload to server
- Integrate with Google Sheets or Firebase
- Add buzzer or LED for visual feedback
- Web dashboard to view attendance

## 📄 License

MIT License
