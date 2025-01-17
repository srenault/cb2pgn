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

    # Create a specific directory for our library
    mkdir -p /usr/local/lib/cb2pgn
    cp /libs/libcb2pgn.so /usr/local/lib/cb2pgn/
    chmod 755 /usr/local/lib/cb2pgn/libcb2pgn.so
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
    strace -f -e trace=file,read,write,open,stat java -verbose:jni -cp build org.chess.cb.Cbh2PgnTask /test/test.cbh /test/output
'