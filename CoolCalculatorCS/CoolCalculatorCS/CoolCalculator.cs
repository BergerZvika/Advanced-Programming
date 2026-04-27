using System;
using System.IO;
using System.Data;
using System.Text.RegularExpressions;

namespace CoolCalculator
{
    delegate float? CustomOperation(float firstNumber, float secondNumber);

    internal class CoolCalculator
    {
        private static List<char> knownOperations = new List<char> { '+', '-', '*', '/' };
        private static readonly Dictionary<string, CustomOperation> customOperations = new Dictionary<string, CustomOperation>();

static void Sain(string[] args)
{
    string path = Path.Combine(
        Directory.GetCurrentDirectory(),
        @"Resources\CalculatorArt.txt"
    );
    string calculatorArt = File.ReadAllText(path);
    string getOperationMessage = "Please enter an operation or type 'add' to create a custom operation:";
    CalculatorPrompt prompt = new CalculatorPrompt(calculatorArt, 5);

    bool shouldExit = false;
    string input;
    float? answer;

    while (!shouldExit)
    {
        // Print calculator prompt
        Console.WriteLine(prompt.GetPromptText());

        // Prompt user for input
        Console.WriteLine(getOperationMessage);
        input = Console.ReadLine();

        if (input == "quit" || input == "exit")
        {
            shouldExit = true;
        }
        else if (input == "add")
        {
            AddCustomOperation();
        }
        else
        {
            answer = calculateAnswer(input);

            if (answer != null)
            {
                Console.WriteLine($"Answer: {answer}");
                prompt.AddOperation($"{input} = {answer}");
            }
            else
            {
                Console.WriteLine("Could not calculate the answer.");
            }

            Console.ReadKey();
        }

        Console.Clear();
    }
}

        // the primitvi is struct, cant get null
        // the object of class can get nulll.
        // the "?" is mean that if this is not float from return, get "null", its put the flaot into class
        private static float? calculateAnswer(string operation)
        {
            if (!validateTheGivenOperation(operation))
            {
                return null;
            }
            
            float answer;   

            char? mathOperation = null;
            int operationIndex;



            // run in the opertiosn
            foreach (char c in knownOperations)
            {
                // if current char is in the string
                // set the math operation to be the current char 
                operationIndex = operation.IndexOf(c);

                if (operationIndex >= 0)
                {
                    mathOperation = c;
                }
            }
            
            // if no known math operation was found retrun null 
            if (mathOperation == null)
            {
                return null;
            }

            // found a known operation
            else
            {
                // parse the numbers
                string[] operationSplits = operation.Split(mathOperation.ToString().ToCharArray(), StringSplitOptions.RemoveEmptyEntries);

                try
                {
                    float firstNumber = float.Parse(operationSplits[0]);
                    float secondNumber = float.Parse(operationSplits[1]);

                    // Check for custom operations first
                    if (customOperations.TryGetValue(mathOperation.ToString(), out var customOp))
                    {
                        return customOp(firstNumber, secondNumber);
                    }

                    switch (mathOperation)
                    {
                        case '+': answer = firstNumber + secondNumber; break;
                        case '-': answer = firstNumber - secondNumber; break;
                        case '*': answer = firstNumber * secondNumber; break;
                        case '/': answer = firstNumber / secondNumber; break;
                        default: return null;
                    }

                    return answer;
                }
                catch (FormatException)
                {
                    return null;
                }
            }
        }

        private static bool validateTheGivenOperation(string operation)
        {
            // simple cases
            if (operation == null) { return false; }

            if (operation.Length == 0) { return false; }

            // match regex
            string[] knownOperationsForRegex = new string[knownOperations.Count];

            for (int i = 0; i < knownOperations.Count; i++)
            {
                knownOperationsForRegex[i] = String.Format(@"\{0}", knownOperations[i]);
            }

            string numberRegex = @"-?\d*(\.\d+)?";

            string joinedOperations = String.Join("|", knownOperationsForRegex);
            string operationsRegex = String.Format(@"[\\{0}]", joinedOperations);

            string fullRegex = String.Format(@"^{0}\s*{1}\s*{2}$", numberRegex, operationsRegex, numberRegex);

            Regex validOperationRegex = new Regex(fullRegex);

            bool isValid = validOperationRegex.Match(operation).Success;

            return isValid;
        }

        private static void RegisterCustomOperation(string symbol, CustomOperation operation)
        {
            if (!customOperations.ContainsKey(symbol))
            {
                customOperations.Add(symbol, operation);
                Console.WriteLine($"Custom operation '{symbol}' added successfully!");
            }
            else
            {
                Console.WriteLine($"Operation '{symbol}' already exists.");
            }
        }

        private static void AddCustomOperation()
        {
            Console.WriteLine("Enter the symbol for the new operation (e.g. '%', '>'): ");
            string symbol = Console.ReadLine();

            if (customOperations.ContainsKey(symbol))
            {
                Console.WriteLine($"Operation '{symbol}' already exists.");
                return;
            }

            Console.WriteLine("Enter the logic for the operation as a mathematical expression:");
            Console.WriteLine("Use 'x' and 'y' for the operands (e.g., 'x * y + 10').");
            string logic = Console.ReadLine();

            try
            {
                CustomOperation newOperation = (x, y) =>
                {
                    string evaluatedExpression = logic.Replace("x", x.ToString()).Replace("y", y.ToString());
                    System.Data.DataTable table = new System.Data.DataTable();
                    object result = table.Compute(evaluatedExpression, string.Empty);
                    return Convert.ToSingle(result);
                };

                // Register the operation
                RegisterCustomOperation(symbol, newOperation);

                // Add the symbol to known operations
                AddSymbolToKnownOperations(symbol);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to add the operation. Error: {ex.Message}");
            }
        }


        private static void AddSymbolToKnownOperations(string symbol)
        {
            if (!string.IsNullOrEmpty(symbol) && symbol.Length == 1)
            {
                char operationSymbol = symbol[0];

                // Check if the symbol is already known
                if (!knownOperations.Contains(operationSymbol))
                {
                    knownOperations.Add(operationSymbol);
                    Console.WriteLine($"Symbol '{operationSymbol}' added to known operations!");
                }
                else
                {
                    Console.WriteLine($"Symbol '{operationSymbol}' is already a known operation.");
                }
            }
            else
            {
                Console.WriteLine("Invalid symbol. Please provide a single character.");
            }
        }



    }
}
