# minekit

C-based toolkit for spawning a revereshell userspace program through a kernel module trigger script
> ⚠️ **Disclaimer:** This code is intended for educational and lab use only.  
> Use it only on systems and networks you own or have explicit permission to test.



## Requirements

- A Linux environment
- `gcc` (or compatible C compiler)
- `make`
- (Optional) Linux kernel headers installed, if the project interacts closely with kernel modules

On a Debian/Ubuntu-like system, you can usually get these with:

```bash
sudo apt update
sudo apt install build-essential
````



## Building

To compile the project, run:

```bash
make
```

This will invoke the `Makefile` and produce the binaries (commonly named something like `rev` and `kmod_launcher` in the project directory).

To clean the build artifacts, run:

```bash
make clean
```

Refer to the `Makefile` to see the exact target names and any additional build options.



## Usage

### 1. Using the `launch` Script

The easiest way to run the project is through the provided `launch` script:

```bash
chmod +x launch
./launch
```

Depending on how the script is written, it may:

* Build the binaries if they don’t exist,
* Load or interact with the kernel module via `kmod_launcher`,
* Start the reverse helper (`rev`) with predefined arguments.

Check the script contents to adjust IP addresses, ports, or kernel module paths.

## Concepts used

### **1. System Calls**
The programs rely heavily on low-level Linux system calls:
- `socket()`, `connect()` – networking and IPC
- `dup2()` – file descriptor redirection
- `execve()` – process replacement
- `open()`, `read()`, `write()` (inside the launcher or kmod code)
These show how user-space interacts directly with the kernel.

### **2. File Descriptors**
The redirection logic demonstrates how:
- STDIN, STDOUT, STDERR (0,1,2)
- can be reassigned to sockets or devices  
This is a core OS abstraction used everywhere from shells to daemons.

### **3. Process Management**
The use of:
- `execve()` for launching a new program image
- The launcher preparing the environment for another process  
illustrates how processes are created, transformed, and managed by the OS.

### **4. Kernel–User Space Boundary**
`kmod_launcher.c` interacts with kernel modules, highlighting:
- User-space to kernel communication
- Device interfaces and system-level resource management
- The controlled transition across privilege boundaries

### **5. Memory & Structures**
Working with:
- `struct sockaddr_in`
- Stack-allocated buffers
shows how OS-level APIs require structured data layouts matching kernel expectations.

### **6. Networking (Sockets API)**
The project uses the BSD sockets interface, demonstrating:
- TCP client creation
- Address translation (`inet_aton/inet_addr`)
- Kernel-managed network I/O paths



