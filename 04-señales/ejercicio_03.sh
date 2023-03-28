#!/bin/env sh

gcc -o sig_02 sig_02.c
./sig_02

# Observaremos que el proceso se pausa,
# ya que al igual que SIGKILL, SIGSTOP no se puede ignorar
