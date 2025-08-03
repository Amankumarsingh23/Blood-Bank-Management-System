# Blood Bank Management System

## Project Overview
This is a C++ console application that simulates a simple Blood Bank Management System. It allows a user (an administrator) to manage donors, hospitals, and blood packets. The system provides robust data persistence, ensuring all records are saved between sessions.

This project was built to demonstrate an understanding of Object-Oriented Programming (OOP) principles, including:
- Classes and objects (`Donor`, `Hospital`, `BloodBank`).
- Data encapsulation and member functions.
- Constructors.
- File I/O for data persistence using binary files.
- Basic input validation and error handling.

## Features
- **Administrator Authentication**: Secure login with a hardcoded username and password.
- **Donor Management**:
    - Add new donors with details like name, contact, blood type, and fitness status.
    - Update a donor's contact or fitness status.
- **Hospital Management**:
    - Register new hospitals with a unique ID and contact number.
- **Blood Inventory**:
    - Donors can donate blood, which adds a new packet to the inventory.
    - Hospitals can request blood packets, which are removed from the inventory upon successful payment.
    - The inventory tracks blood type, Rh factor, and expiry year.
- **Data Persistence**: All donor, hospital, and inventory data is saved to a binary file (`bloodbank_data.dat`) and loaded on startup, ensuring no data is lost.

## How to Compile and Run
### Prerequisites
- A C++ compiler (e.g., g++, MinGW, Visual C++).
- A C++ IDE like VS Code, Visual Studio, or an online compiler.

### Steps
1. Save the code as `main.cpp` (or any other filename you prefer).
2. Compile the code using a C++ compiler. For example, in the terminal:
   ```bash
   g++ main.cpp -o bloodbank
