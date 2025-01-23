# Create directories for our libraries
mkdir -p /usr/local/lib/cb2pgn

# Copy libraries from build directory
cp ../build/libcb2pgnlib.so /usr/local/lib/cb2pgn/
cp ../build/libcb2pgn_jni.so /usr/local/lib/cb2pgn/

# Set permissions
chmod 755 /usr/local/lib/cb2pgn/libcb2pgnlib.so
chmod 755 /usr/local/lib/cb2pgn/libcb2pgn_jni.so

# Run the Java program
java -Djava.library.path=/usr/local/lib/cb2pgn -verbose:jni -cp build org.chess.cb.Cbh2PgnTask /test/test.cbh /test/output 