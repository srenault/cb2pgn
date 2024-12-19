package org.chess.cb;

public class Cb2Pgn {
    static {
        System.loadLibrary("cb2pgn");
    }

    /**
     * Extract a ChessBase file to the specified output directory.
     * @param inputPath Path to the ChessBase file
     * @param outputDir Directory where extracted files should be placed
     * @return Status message indicating success or failure
     */
    public native String extractCbv(String inputPath, String outputDir);
} 