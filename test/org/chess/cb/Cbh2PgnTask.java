package org.chess.cb;

public class Cbh2PgnTask {
    static {
        System.loadLibrary("cb2pgn");
    }

    private native int convertToPgn(String fileName, String outputDir);

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java Cbh2PgnTask <input.cbh> <output_dir>");
            System.exit(1);
        }

        String inputFile = args[0];
        String outputDir = args[1];

        Cbh2PgnTask converter = new Cbh2PgnTask();
        try {
            int result = converter.convertToPgn(inputFile, outputDir);
            if (result > 0) {
                System.out.println("Successfully converted " + result + " games");
            } else {
                System.out.println("Conversion failed with error code: " + result);
            }
        } catch (Exception e) {
            System.err.println("Error during conversion: " + e.getMessage());
            e.printStackTrace();
        }
    }
} 