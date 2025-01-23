# Non-blocking TCP Server

[![Build and Test TCP Server](https://github.com/progstorage/libev_TCP_server/actions/workflows/build.yml/badge.svg)](https://github.com/progstorage/libev_TCP_server/actions/workflows/build.yml)

A simple non-blocking TCP server implemented in **C++** using **libev**. The server listens for client connections on port `5000`, echoes back any received data, and logs the connections (timestamp and received data). A Python-based client is provided to test the server.

## Features

- Non-blocking TCP server using **libev**.
- Listens for connections on port `5000`.
- Echoes received data back to the client.
- Logs client connections with timestamp and received data.
- Includes a Python client (`client.py`) for testing.

## Project Structure

- **server.cpp**: The C++ implementation of the non-blocking TCP server.
- **client.py**: A Python script to test the server functionality.
- **CMakeLists.txt**: CMake configuration file for building the project.
- **.github/workflows/build.yml**: GitHub Actions configuration for CI/CD.

## Requirements

- Linux-based system
- **CMake** (version 3.10 or higher)
- **GCC** or **Clang**
- **libev**
- **Python 3** (for testing)

## Build and Test Instructions

1) Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-name>

2) Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make

4) Run and test the server:
- Start the server:
   ```bash
   ./server
- In a separate terminal, run the Python client:
   ```bash
   python3 client.py
- The client will send a message to the server and display the echoed response.

## Continuous Integration (CI)

This project includes a GitHub Actions workflow (.github/workflows/build.yml) to automate the following tasks:

- Build the project using CMake.
- Test the server functionality with client.py.
