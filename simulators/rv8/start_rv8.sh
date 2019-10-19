#!/bin/sh

docker run -v ${PWD}/src:/src -e RISCV=/opt/riscv/toolchain -it rv8 /bin/bash
