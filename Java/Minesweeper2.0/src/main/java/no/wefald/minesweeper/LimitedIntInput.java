package no.wefald.minesweeper;

import java.util.Scanner;

public class LimitedIntInput {
    private int numberOfInputs;
    private int[] limitedIntInput;
    private int[][] limits;

    public LimitedIntInput(int numberOfInputs, int[][] limits) {
        this.numberOfInputs = numberOfInputs;
        this.limitedIntInput = new int[numberOfInputs];
        this.limits = limits;

        for (int i = 0; i < numberOfInputs; i++) {
            int lowerLimit = limits[i][0];
            int upperLimit = limits[i][1];

            if (lowerLimit > upperLimit) {
                System.out.println("WARNING: lower limit set higher than upper limit. Lower limit set equal to upper limit");
                limits[i][0] = lowerLimit;
            }
        }
    }

    int[] getLimitedIntInput() {
        while(true) {
            try {
                getUserInput();
                break;
            } catch (NumberFormatException error) {
                System.out.println("Input contained one or more non integer values.");
            } catch (ArrayIndexOutOfBoundsException error) {
                System.out.println("Not enough inputs.");
            } catch (InputOutsideLimitsException error) {
                System.out.println("Input outside limits");
            } catch (Exception error) {
                System.out.println("Some invalid input.");
            }
        }
        return this.limitedIntInput;
    }

    private void getUserInput() throws Exception{
        Scanner inputReader = new Scanner(System.in);
        String userInput[] = inputReader.nextLine().split(" ");
        parseUserInput(userInput);
    }

    private void parseUserInput(String[] userInput) throws Exception{
        int ithInput;

        for(int i = 0; i < this.numberOfInputs; i++) {
            ithInput = Integer.parseInt(userInput[i]);
            if(inputWithinLimits(ithInput, i)) {
                this.limitedIntInput[i] = ithInput;
            } else {
                throw new InputOutsideLimitsException("");
            }
        }
    }

    private boolean inputWithinLimits(int input, int inputNumber) {
        int lowerLimit = limits[inputNumber][0];
        int upperLimit = limits[inputNumber][1];
        return (input >= lowerLimit && input <= upperLimit);
    }

    private class InputOutsideLimitsException extends Exception {
        private InputOutsideLimitsException(String message) {
            super(message);
        }
    }
}