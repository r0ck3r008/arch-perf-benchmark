FROM ubuntu

#update upgrade
RUN apt-get update -y; apt-get upgrade -y

#install essentials
RUN apt-get install autoconf automake autotools-dev curl \
	libmpc-dev libmpfr-dev libgmp-dev gawk build-essential \
	bison flex texinfo gperf libtool patchutils bc zlib1g-dev \
	git tmux vim -y

#make dir for repos
RUN mkdir -p /rv8/toolchain /rv8/rv8

#fetch repos
RUN git clone https://github.com/riscv/riscv-gnu-toolchain.git /rv8/toolchain
RUN git clone https://github.com/rv8-io/rv8.git /rv8/rv8

#install toolchain
RUN cd /rv8/toolchain; git submodule update --init --recursive
RUN cd /rv8/toolchain; ./configure --prefix=/opt/riscv/toolchain
RUN cd /rv8/toolchain; make -j10

#install rv8
RUN cd /rv8/rv8; git submodule update --init --recursive
RUN cd /rv8/rv8; make -j10
RUN cd /rv8/rv8; make install
