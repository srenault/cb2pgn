# System Architecture

0. Web Interface
   - Web page provides user interface for chess base file uploads
   - Users can directly upload chess base files through the browser
   - Provides immediate feedback on upload status

1. Storage
   - Chess base files are stored in Amazon S3

2. API Layer
   - An HTTP API serves as the interface for chess base to PGN conversion
   - The API acts as a proxy, forwarding requests to AWS Lambda
   - The Lambda Runtime function will be either a Go or Java function

3. Processing
   - AWS Lambda function handles the conversion process
   - Converts chess base files to PGN format
   - Returns the converted PGN data to the client

## Platform Compatibility

The core C++ library must be built in an environment matching AWS Lambda's runtime:

- **Build Environment**: Amazon Linux 2 Docker container
  - Ensures binary compatibility with AWS Lambda runtime
  - Matches system libraries and versions available in Lambda
  - Maintains ABI (Application Binary Interface) compatibility
  - Handles platform-specific dependencies correctly

This is critical because the C++ shared library (`libcb2pgn.so`) needs to:
- Link against compatible system libraries
- Match the target platform's CPU architecture
- Use consistent compiler toolchain and runtime libraries

Building in a different environment (like macOS or Ubuntu) would result in incompatible binaries that wouldn't run in the Lambda environment.

### Test Program Compatibility

The Java test program must also run inside the Docker container for the same reasons:
- It needs to load and interact with the compiled `libcb2pgn.so` library
- JNI (Java Native Interface) bindings require binary compatibility
- System library versions and paths must match
- The test environment should mirror the production Lambda environment as closely as possible

This ensures that passing tests in the development environment translate to working functionality in AWS Lambda. 