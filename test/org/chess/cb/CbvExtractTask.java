package org.chess.cb;

import java.io.File;

public class CbvExtractTask {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java CbvExtractTask <input.cbv> <output_dir>");
            System.exit(1);
        }

        String inputFile = args[0];
        String outputDir = args[1];

        System.out.println("Input file: " + inputFile);
        System.out.println("Output directory: " + outputDir);

        // Check input file extension
        if (!inputFile.toLowerCase().endsWith(".cbv")) {
            System.err.println("Error: Input file must have .cbv extension");
            System.err.println("Current file extension: " + inputFile.substring(inputFile.lastIndexOf('.')));
            System.exit(1);
        }

        // Check input file
        File cbvFile = new File(inputFile);
        if (!cbvFile.exists()) {
            System.err.println("Error: Input file does not exist: " + inputFile);
            System.exit(1);
        }
        if (!cbvFile.isFile()) {
            System.err.println("Error: Input path is not a file: " + inputFile);
            System.exit(1);
        }
        if (!cbvFile.canRead()) {
            System.err.println("Error: Cannot read input file: " + inputFile);
            System.exit(1);
        }
        System.out.println("Input file exists and is readable");
        System.out.println("Input file size: " + cbvFile.length() + " bytes");

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
            Cb2Pgn extractor = new Cb2Pgn();
            System.out.println("Starting extraction...");
            String result = extractor.extractCbv(inputFile, outputDir);
            System.out.println("Extraction result: " + result);
        } catch (Exception e) {
            System.err.println("Error during extraction: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }
} 