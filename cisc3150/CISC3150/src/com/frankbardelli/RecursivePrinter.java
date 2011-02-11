package com.frankbardelli;

public class RecursivePrinter {

    public static void main(String[] args) {
        RecursivePrinter rp = new RecursivePrinter();
        try {
            rp.repeat('*', 15);
            System.out.println();
        } catch (InvalidCountException e) {
            System.err.println("Invalid count supplied");
            e.printStackTrace();
        }
    }

    public RecursivePrinter() {
    }

    public void repeat(char c, int count) throws InvalidCountException {
        if (count == 0) {
            return;
        }
        if (count < 0) {
            throw new InvalidCountException();
        }
        System.out.print(c);
        repeat(c, count - 1);
    }

    class InvalidCountException extends Exception {
    }

}
