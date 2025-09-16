# Philosophers

# 🧠 Philosophers

This project is a simulation of the classic **Dining Philosophers** problem, focused on exploring **threads**, **mutexes**, **concurrency**, and **resource synchronization** in C using POSIX threads.

## 💡 About

Five philosophers sit around a circular table. Each philosopher alternates between **thinking**, **eating**, and **sleeping**. To eat, a philosopher needs **two forks**—one on their left and one on their right. The challenge is to simulate this behavior correctly while avoiding **deadlocks** and **race conditions**.

The main goal of this project is to implement a solution that handles:

- Accurate timing of actions  
- Safe concurrent access to shared resources (forks)  
- Proper thread lifecycle management  
- Synchronized and readable logging output  

## 🧵 Concepts Used

- Threads (`pthread_create`, `pthread_join`)
- Mutexes (`pthread_mutex_t`)
- Time measurement (`gettimeofday`, `usleep`)
- Synchronization
- Shared memory and resource handling

## 🚧 Status

🔧 **DONE** — Evaluated with grade 100%

## Illustration

<img width="225" height="225" alt="image" src="https://github.com/user-attachments/assets/80612021-6b7b-4fa3-b659-c2b51910897c" />
