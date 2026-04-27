using System;
using System.Text;

namespace CoolCalculator
{
    internal class CalculatorPrompt
    {
        // Queue of the Operations
        private OperationsQueue _operations = null;
        private readonly string _initialPrompt;
        private readonly string[] _initialPromptLines;

        //counstructer
        public CalculatorPrompt(string initialPrompt, int maxNumberOfOperationsInQueue)
        {
            // initialize the operation queue
            this._operations = new OperationsQueue(maxNumberOfOperationsInQueue);

            // set the initial prompt
            this._initialPrompt = initialPrompt;

            // split the initial prompt to its lines
            this._initialPromptLines = this._initialPrompt.Split(
                Environment.NewLine.ToCharArray(), // instend of "\n" to be cross platporm
                StringSplitOptions.RemoveEmptyEntries // Enume: the options of delete the tav by split
            );
        }

        public string GetPromptText()
        {
            // object of srting , capacity = how much char i can have. maxCapacity: int.MaxValue this is mean that is can be big as we want
            StringBuilder stringBuilder = new StringBuilder(capacity: 50, maxCapacity: int.MaxValue);
            string promptText;

            // if there is no history
            if (this._operations.IsEmpty)
            {
                // append the first line and the second line
                // containing the text "No history."
                stringBuilder.AppendLine(this._initialPromptLines[0]);

                stringBuilder.AppendLine(
                // is good more then use "+" with stirng
                    String.Format(
                        "{0}\t{1}",
                        // the firsy in {0}
                        this._initialPromptLines[1],
                        // the secenf in {1}
                        "No history."
                ));
                
                // add all the lines 
                for (int i = 1; i < this._initialPromptLines.Length; i++)
                {
                    stringBuilder.AppendLine(this._initialPromptLines[i]);
                }
            }

            // if there is history
            else
            {
                // append the first line and the second line
                // containing the text "History:"
                stringBuilder.AppendLine(this._initialPromptLines[0]);

                stringBuilder.AppendLine(
                    String.Format(
                        "{0}\t{1}",
                        this._initialPromptLines[1],
                        "History:"
                ));

                // for each line get the operation (if there is one) and add it to the line
                string line;
                int operationIndex;

                for (int i = 2; i < this._initialPromptLines.Length; i++)
                {
                    //index of opertion in the 
                    operationIndex = i - 2;

                    // if there is an operation to write next to the current line
                    if (operationIndex < this._operations.Count)
                        line = String.Format(
                            "{0}\t{1}",
                            this._initialPromptLines[i],
                            this._operations[operationIndex]
                            );

                    // if we've already wrote all the operations
                    else
                    {
                        line = this._initialPromptLines[i];
                    }

                    // append the formatted line
                    stringBuilder.AppendLine(line);
                }
            }

            // get the prompt text from the builder
            promptText = stringBuilder.ToString();

            return promptText;
        }
        
        public void AddOperation(string operation)
        {
            this._operations.Enqueue(operation);
        }

    }
}
