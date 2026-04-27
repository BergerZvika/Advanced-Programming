using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoolCalculatorCS
{
    internal class linq
    {
        static void Sain(string[] args)
        {
            // LINQ (Language Integrated Query)
            // Sample data: a list of integers
            List<int> numbers = new List<int>() { 6, 5, 3, 4, 9, 1, 7, 10 };

            // Query syntax
            var evenNumbers = from num in numbers
                              where num % 2 == 0
                              select num;


            // Method syntax
            var evenNumbers2 = numbers.Where(num => num % 2 == 0);

            // Output
            Console.WriteLine("Query syntax");
            foreach (var num in evenNumbers)
            {
                Console.WriteLine(num);
            }

            Console.WriteLine("");
            Console.WriteLine("Method syntax");
            foreach (var num in evenNumbers2)
            {
                Console.WriteLine(num);
            }

            // string collection
            IList<string> stringList = new List<string>() {
                "C# Tutorials",
                "VB.NET Tutorials",
                "Learn C++",
                "MVC Tutorials" ,
                "Java"
            };

            var result = from s in stringList
                         where s.Contains("Tutorials")
                         select s;

            Console.WriteLine("");
            Console.WriteLine("List");
            foreach (var s in result)
            {
                Console.WriteLine(s);
            } 
            return;

        }

    }
}
