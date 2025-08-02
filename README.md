# 📡 miniTalk

[![42 School Project](https://img.shields.io/badge/42-School_Project-000000?style=flat-square&logo=42)](https://github.com/s4nxez/minitalk)
[![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat-square&logo=linux&logoColor=black)](https://www.linux.org/)

**An inter-process communication system using UNIX signals to transfer text messages bit by bit.**

---

## 📋 Table of Contents

1. [Project Description](#-project-description)
2. [System Architecture](#-system-architecture)
3. [Main Components](#-main-components)
   - [Server](#server)
   - [Client](#client)
   - [Utils](#utils)
4. [Compilation and Installation](#-compilation-and-installation)
5. [Usage](#-usage)
6. [Communication Protocol](#-communication-protocol)
7. [Error Handling](#-error-handling)
8. [File Structure](#-file-structure)

---

## 🎯 Project Description

**miniTalk** is a 42 school project that implements an inter-process communication system using only the UNIX signals `SIGUSR1` and `SIGUSR2`. The system allows a client to send text messages to a server, transmitting each character bit by bit using these two signals.

### Main Features:
- ✅ **Asynchronous communication** between client and server
- ✅ **Bit-by-bit transmission** using only two UNIX signals
- ✅ **Acknowledgment system** to confirm reception
- ✅ **Robust error handling**
- ✅ **Unicode character support**
- ✅ **No data loss**

---

## 🏗️ System Architecture

```
┌─────────────┐    SIGUSR1/SIGUSR2    ┌─────────────┐
│   CLIENT    │ ────────────────────► │   SERVER    │
│             │                       │             │
│ • Sends bits│ ◄───────────────────  │ • Receives  │
│ • Waits ACK │    ACK (SIGUSR1)      │ • Rebuilds  │
└─────────────┘    END (SIGUSR2)      └─────────────┘
```

The system uses a communication protocol based on:
- **SIGUSR1**: Represents bit `1` (client → server) / ACK (server → client)
- **SIGUSR2**: Represents bit `0` (client → server) / END (server → client)

---

## 🔧 Main Components

### Server

**File**: [`src/server.c`](src/server.c)

The server is the receiver process that:

1. **Displays its PID** on startup so the client can connect
2. **Registers signal handlers** for `SIGUSR1` and `SIGUSR2`
3. **Reconstructs characters** bit by bit from received signals
4. **Sends acknowledgments** to the client after each bit
5. **Prints the received message** when it detects the null character (`\0`)

```c
// Main signal handler function
void handler(int signo, siginfo_t *info, void *more_info)
```

**Technical features:**
- Uses `siginfo_t` to get the sender client's PID
- Handles static state to rebuild characters
- Implements bit-shifting logic to recompose bytes

### Client

**File**: [`src/client.c`](src/client.c)

The client is the sender process that:

1. **Validates arguments** (server PID and message)
2. **Converts each character** into an 8-bit sequence
3. **Sends each bit** as a signal to the server
4. **Waits for acknowledgment** before sending the next bit
5. **Terminates transmission** by sending a null character

```c
// Function to send a complete character
void send_char(char c, pid_t server)
```

**Technical features:**
- Volatile global variable `g_server` for synchronization
- Separate handlers for ACK and termination
- Uses `usleep(42)` to avoid system saturation

### Utils

**File**: [`src/utils.c`](src/utils.c)

Contains shared utility functions:

#### `ft_signal()`
```c
void ft_signal(int signo, void *handler, bool use_siginfo)
```
- **Purpose**: Configure signal handlers safely
- **Parameters**:
  - `signo`: Signal to configure
  - `handler`: Handler function
  - `use_siginfo`: Whether to use `SA_SIGINFO` to get sender info

#### `ft_kill()`
```c
void ft_kill(pid_t pid, int signo)
```
- **Purpose**: Send signals with error handling
- **Parameters**:
  - `pid`: Target process PID
  - `signo`: Signal to send

---

## 🛠️ Compilation and Installation

### Prerequisites
- Linux/Unix operating system
- GCC compiler
- Make

### Compilation

```bash
# Clone the repository
git clone https://github.com/s4nxez/minitalk.git
cd minitalk

# Compile both programs
make

# Or compile individually
make server    # Server only
make client    # Client only
```

### Cleanup

```bash
make clean     # Remove object files
make fclean    # Complete cleanup
make re        # Recompile from scratch
```

---

## 🚀 Usage

### 1. Start the Server

```bash
./server
```

The server will display its PID:
```
PID: 12345
```

### 2. Send Message from Client

```bash
./client <SERVER_PID> "Your message here"
```

**Complete example:**
```bash
# Terminal 1: Start server
./server
PID: 12345

# Terminal 2: Send message
./client 12345 "Hello world! 🌍"
200

# Terminal 1: Server output
Hello world! 🌍
```

### Use Cases

```bash
# Simple message
./client 12345 "Hello World"

# Message with spaces
./client 12345 "This is a long message with spaces"

# Special characters
./client 12345 "Symbols: @#$%^&*()"

# Empty message
./client 12345 ""
```

---

## 📡 Communication Protocol

### Transmission Flow

```
1. Client decomposes character into 8 bits
2. For each bit:
   ├─ Sends SIGUSR1 (bit=1) or SIGUSR2 (bit=0)
   ├─ Waits for server ACK (SIGUSR1)
   └─ Continues with next bit
3. At message end, sends '\0'
4. Server responds with SIGUSR2 (termination)
5. Client exits with code 200
```

### Binary Representation

```
Character 'A' (ASCII 65):
┌─────────────────────────────────────┐
│ Bits: 0 1 0 0 0 0 0 1               │
│ Signals: USR2 USR1 USR2 USR2 USR2 USR2 USR2 USR1 │
└─────────────────────────────────────┘
```

### System States

- **READY**: Server ready to receive next bit
- **BUSY**: Server processing current bit
- **ACK**: Acknowledgment sent to client
- **END**: Transmission completed

---

## ⚠️ Error Handling

### Client Validations
- **Number of arguments**: Must be exactly 3
- **Valid PID**: Numeric verification of server PID
- **Failed signals**: Error control in `kill()`

### Server Protections
- **Signal configuration**: Verification of `sigaction()`
- **Signal masks**: Signal blocking during processing
- **Robust recovery**: Consistent state upon interruptions

### Exit Codes
- **0**: Successful execution
- **1**: Error in arguments or execution
- **200**: Message sent correctly (client)

---

## 📁 File Structure

```
minitalk/
├── 📄 README.md                    # This documentation
├── 📄 LICENSE                      # Project license
├── 📄 Makefile                     # Build system
├── 📁 include/                     # Header files
│   ├── 📄 minitalk.h              # Main definitions
│   └── 📁 ft_printf/              # Custom printf library
│       ├── 📄 Makefile
│       ├── 📁 include/
│       │   └── 📄 ft_printf.h
│       └── 📁 src/
│           ├── 📄 ft_printf.c
│           ├── 📄 ft_putchar.c
│           ├── 📄 ft_puthex.c
│           ├── 📄 ft_putnbr.c
│           ├── 📄 ft_putstr.c
│           └── 📄 ft_putunbr.c
└── 📁 src/                        # Source code
    ├── 📄 server.c                # [Server] - Receiver process
    ├── 📄 client.c                # [Client] - Sender process
    └── 📄 utils.c                 # [Utilities] - Helper functions
```

---

<div align="center">

**Developed with ❤️ by [s4nxez](https://github.com/s4nxez)**

*42 Madrid School Project*

</div>
