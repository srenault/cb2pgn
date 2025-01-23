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

# Build
RUN mkdir -p build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release \
          ../cb2pgnlib && \
    make -j$(nproc)

# Copy the built library
CMD ["cp", "build/libcb2pgn.so", "/output/"]