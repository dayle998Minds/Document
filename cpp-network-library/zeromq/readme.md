# zeroMQ install

```

# Download zeromq
# Ref http://zeromq.org/intro:get-the-software
wget https://github.com/zeromq/libzmq/releases/download/v4.2.2/zeromq-4.2.2.tar.gz

# Unpack tarball package
tar xvzf zeromq-4.2.2.tar.gz

# Install dependency
sudo apt-get update && \
sudo apt-get install -y libtool pkg-config build-essential autoconf automake uuid-dev

# Create make file
cd zeromq-4.2.2
./configure

# Build and install(root permission only)
sudo make install

# Install zeromq driver on linux
sudo ldconfig

# Check installed
ldconfig -p | grep zmq

# check
ll /usr/local/lib/libzmq*

# Expected
############################################################
# libzmq.so.5 (libc6,x86-64) => /usr/local/lib/libzmq.so.5
# libzmq.so (libc6,x86-64) => /usr/local/lib/libzmq.so
############################################################
```
# zeroMQ github install
```
git clone https://github.com/zeromq/libzmq
cd libzmq/
git checkout v4.2.2
mkdir cmake-build && cd cmake-build
cmake .. && make -j 4
sudo make install
```
## 참조
<https://gist.github.com/katopz/8b766a5cb0ca96c816658e9407e83d00>
 