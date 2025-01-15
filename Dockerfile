# Dockerfile
FROM --platform=linux/amd64 ubuntu:20.04

# Avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    curl \
    default-jdk \
    pkg-config \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Install Rust
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

# Create workspace directory
WORKDIR /workspace

# Copy the source code
COPY . .

# Set environment variables for legacy compatibility
ENV RUSTFLAGS="-C target-feature=-crt-static"

# Build the project
CMD ["./docker-build.sh"]