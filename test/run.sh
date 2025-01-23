#!/bin/bash

# Create build directory
mkdir -p build
mkdir -p output

# List of all ChessBase file extensions
CB_EXTENSIONS="cbh cba cbj cit cbc cbg cbp cbt cbs cbe cbm cbl cbtt cbv ini"

# Check for all required ChessBase files
echo "=== Checking ChessBase files ==="
for ext in $CB_EXTENSIONS; do
    if [ -f "test.$ext" ]; then
        echo "Found test.$ext:"
        ls -la "test.$ext"
    else
        echo "Warning: test.$ext not found"
    fi
done

# Run test in Docker container
docker compose run --rm test bash -c '
    # Install Java and LZO
    yum update -y
    yum install -y java-1.8.0-openjdk-devel lzo strace

    # Create directories and copy all ChessBase files
    mkdir -p /test/output
    for ext in cbh cba cbj cit cbc cbg cbp cbt cbs cbe cbm cbl cbtt cbv ini; do
        if [ -f "test.$ext" ]; then
            echo "Copying test.$ext to /test/"
            cp -v "test.$ext" "/test/"
            chmod 644 "/test/test.$ext"
        fi
    done

    echo "=== Directory contents ==="
    ls -la /test
    ls -la /libs

    # Create directories for our libraries
    mkdir -p /usr/local/lib/cb2pgn

    # Copy libraries from the mounted volumes
    cp /libs/libcb2pgnlib.so /usr/local/lib/cb2pgn/
    cp /libs/libopenchessbase_jni.so /usr/local/lib/cb2pgn/

    chmod 755 /usr/local/lib/cb2pgn/libcb2pgnlib.so
    chmod 755 /usr/local/lib/cb2pgn/libopenchessbase_jni.so
    ldconfig /usr/local/lib/cb2pgn

    # Compile Java code
    javac -d build org/chess/cb/Cbh2PgnTask.java

    # Set library path and run test with debug output
    export LD_LIBRARY_PATH="/usr/local/lib/cb2pgn:$LD_LIBRARY_PATH"
    echo "=== ChessBase files in container ==="
    for ext in cbh cba cbj cit cbc cbg cbp cbt cbs cbe cbm cbl cbtt cbv ini; do
        if [ -f "/test/test.$ext" ]; then
            echo "Found /test/test.$ext:"
            ls -la "/test/test.$ext"
            echo "First 32 bytes:"
            dd if="/test/test.$ext" bs=1 count=32 2>/dev/null | hexdump -C
        fi
    done

    echo "=== Starting Java program ==="
    java -Djava.library.path=/usr/local/lib/cb2pgn -verbose:jni -cp build org.chess.cb.Cbh2PgnTask /test/test.cbh /test/output
'