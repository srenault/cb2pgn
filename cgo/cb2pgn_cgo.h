#ifndef CB2PGN_CGO_H
#define CB2PGN_CGO_H

#ifdef __cplusplus
extern "C" {
#endif

// Convert a CBH file to PGN format
// Returns the number of games converted, or -1 on error
int ConvertToPgn(const char* cbhFilePath, const char* outputDir);

// Set a callback function for progress updates (0-100)
typedef void (*ProgressCallback)(int progress);
void SetProgressCallback(ProgressCallback callback);

#ifdef __cplusplus
}
#endif

#endif // CB2PGN_CGO_H 