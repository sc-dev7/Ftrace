# SCHOOL - Project

## DESCRIPTION  
The **Ftrace** project consists of creating a tool similar to `strace`, but focused on function calls. Instead of tracing system calls, **Ftrace** traces function calls made by a binary during its execution, including those from shared libraries.

---

## FEATURES  
- **Function call tracing:**  
  - Intercept and display function calls made by the program.  
- **Symbol resolution:**  
  - Display the names of functions using `nm` and `elf` symbol parsing.  
- **Shared library support:**  
  - Track calls to functions from dynamic libraries (e.g., `libc`).  
- **Arguments and return values (optional):**  
  - Display arguments passed to functions and their return values.  

---

## FUNCTIONS ALLOWED  
- System calls:  
  - `ptrace`, `execve`, `waitpid`, `kill`.  
- Library functions:  
  - `malloc`, `free`, `write`, `read`.  
  - ELF parsing utilities (e.g., `dlopen`, `dlsym`, `nm`).

---

## USAGE  
### Syntax:  
```bash
./ftrace [program] [args...]
