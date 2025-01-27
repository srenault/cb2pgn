# Dockerfile
FROM amazonlinux:2

# Install build dependencies
RUN yum update -y && \
    yum groupinstall -y "Development Tools" && \
    yum install -y cmake3 lzo-devel liblzo2-devel expat-devel java-1.8.0-openjdk-devel && \
    ln -s /usr/bin/cmake3 /usr/bin/cmake

# Set up build directory
WORKDIR /build

# Copy source files
COPY . .

# Build all libraries
RUN mkdir -p build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release \
          .. && \
    make -j$(nproc)

# Copy libraries to output
CMD cp build/cb2pgnlib/libcb2pgnlib.so \
       build/jni/libopenchessbase_jni.so \
       build/cgo/libopenchessbase_cgo.so \
       /output/