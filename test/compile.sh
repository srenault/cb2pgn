#!/bin/bash

# Create build directory
mkdir -p build
mkdir -p output

# Run test in Docker container
docker compose run --rm test bash -c '
    # Install Java and LZO
    yum update -y
    yum install -y java-1.8.0-openjdk-devel lzo

    # Compile Java code
    javac -d build org/chess/cb/Cbh2PgnTask.java

    # Set library path and run test
    export LD_LIBRARY_PATH="/libs:$LD_LIBRARY_PATH"
    java -cp build org.chess.cb.Cbh2PgnTask test.cbh output
'