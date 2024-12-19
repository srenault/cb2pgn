# Dockerfile
FROM --platform=linux/amd64 rust:1.50

# Install system dependencies
RUN apt-get update && \
    apt-get install -y build-essential default-jdk

# Create workspace directory
WORKDIR /workspace

# Copy the source code
COPY . .

# Set environment variables for legacy compatibility
ENV RUSTFLAGS="-C target-feature=-crt-static"

# Build the project
CMD ["./docker-build.sh"]