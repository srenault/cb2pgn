package org.chess.cb;

import java.io.File;
import java.io.IOException;

public class Cbh2PgnTask {
    static {
        try {
            System.out.println("Loading native library cb2pgn...");
            System.loadLibrary("cb2pgn");
            System.out.println("Successfully loaded native library");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Failed to load native library: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }

    private native int convertToPgn(String fileName, String outputDir);

    // Optional callback methods that might be called from native code
    public void setNOGames(int games) {
        System.out.println("Total number of games: " + games);
    }

    public void setPgnFileName(String name) {
        System.out.println("Output PGN file: " + name);
    }

    public void progress(int value) {
        System.out.println("Progress: " + value);
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java Cbh2PgnTask <input.cbh> <output_dir>");
            System.exit(1);
        }

        String inputFile = args[0];
        String outputDir = args[1];

        System.out.println("Input file: " + inputFile);
        System.out.println("Output directory: " + outputDir);

        // Check input file extension
        if (!inputFile.toLowerCase().endsWith(".cbh")) {
            System.err.println("Error: Input file must have .cbh extension");
            System.err.println("Current file extension: " + inputFile.substring(inputFile.lastIndexOf('.')));
            System.exit(1);
        }

        // Check input file
        File cbhFile = new File(inputFile);
        if (!cbhFile.exists()) {
            System.err.println("Error: Input file does not exist: " + inputFile);
            System.exit(1);
        }
        if (!cbhFile.isFile()) {
            System.err.println("Error: Input path is not a file: " + inputFile);
            System.exit(1);
        }
        if (!cbhFile.canRead()) {
            System.err.println("Error: Cannot read input file: " + inputFile);
            System.exit(1);
        }
        System.out.println("Input file exists and is readable");
        System.out.println("Input file size: " + cbhFile.length() + " bytes");

        // Check for related ChessBase files
        String basePath = inputFile.substring(0, inputFile.lastIndexOf('.'));
        String[] relatedExtensions = {".cba", ".cbj", ".cit"};
        for (String ext : relatedExtensions) {
            File relatedFile = new File(basePath + ext);
            if (relatedFile.exists()) {
                System.out.println("Found related file: " + relatedFile.getName() + " (" + relatedFile.length() + " bytes)");
            }
        }

        // Check output directory
        File outDirFile = new File(outputDir);
        if (!outDirFile.exists()) {
            System.out.println("Creating output directory: " + outputDir);
            if (!outDirFile.mkdirs()) {
                System.err.println("Error: Failed to create output directory: " + outputDir);
                System.exit(1);
            }
        }
        if (!outDirFile.isDirectory()) {
            System.err.println("Error: Output path is not a directory: " + outputDir);
            System.exit(1);
        }
        if (!outDirFile.canWrite()) {
            System.err.println("Error: Cannot write to output directory: " + outputDir);
            System.exit(1);
        }
        System.out.println("Output directory exists and is writable");

        try {
            System.out.println("Input file canonical path: " + cbhFile.getCanonicalPath());
            System.out.println("Output directory canonical path: " + outDirFile.getCanonicalPath());
        } catch (IOException e) {
            System.err.println("Error resolving paths: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }

        Cbh2PgnTask converter = new Cbh2PgnTask();
        try {
            System.out.println("Starting conversion...");
            int result = converter.convertToPgn(inputFile, outputDir);
            System.out.println("Conversion completed with result: " + result);
            if (result > 0) {
                System.out.println("Successfully converted " + result + " games");
            } else {
                System.out.println("Conversion failed with error code: " + result);
                System.out.println("Error codes:");
                System.out.println("  -1: Failed to open CBH file");
                System.out.println("  -2: Failed to read file header");
                System.out.println("  -3: Exception during database initialization");
                System.out.println("  -4: Unknown exception during database initialization");
                System.out.println("  -5: Exception during initialization");
                System.out.println("  -6: Unknown exception during initialization");
            }
        } catch (Exception e) {
            System.err.println("Error during conversion: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }
} 