# os_hmw
# Producer-Consumer Problem

The Producer-Consumer problem demonstrates synchronization in concurrent programming using semaphores and shared memory. In this implementation, a producer generates items and places them on a table, and a consumer picks up items from the table. The table can only hold a maximum of two items at a time.

## Table of Contents
- [Setup](#setup)
- [Usage](#usage)

## Setup
Ensure you have `gcc` installed:
gcc --version

gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer

## Usage
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
./producer & ./consumer &
