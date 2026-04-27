using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoolCalculatorCS.coolStaff
{
    internal class ImplicitTypes
    {
        static void Sain(string[] args)
        {
            // Data Types
            string stringVar = "Hello World!!";
            int intVar = 100;
            float floatVar = 10.2f;
            char charVar = 'A';
            bool boolVar = true;
            Console.WriteLine("intVar: {0}", intVar);

            // DateTime Object
            // assigns default value 01/01/0001 00:00:00
            DateTime dt = new DateTime(); 
            
            //assigns year, month, day
            DateTime dt3 = new DateTime(2015, 12, 31);

            //assigns year, month, day, hour, min, seconds
            DateTime dt4 = new DateTime(2015, 12, 31, 5, 10, 20);

            // operation on DateTime Object
            DateTime dt1 = new DateTime(2015, 12, 20);
            DateTime dt2 = new DateTime(2016, 12, 31, 5, 10, 20);
            TimeSpan time = new TimeSpan(10, 5, 25, 50);

            Console.WriteLine(dt2 + time); // 1/10/2017 10:36:10 AM
            Console.WriteLine(dt2 - dt1); //377.05:10:20
            Console.WriteLine(dt1 == dt2); //False
            Console.WriteLine(dt1 != dt2); //True
            Console.WriteLine(dt1 > dt2); //False
            Console.WriteLine(dt1 < dt2); //True
            Console.WriteLine(dt1 >= dt2); //False
            Console.WriteLine(dt1 <= dt2);//True


            // StringBuilder
            // In C#, the string type is immutable.
            // To solve this problem, C# introduced the
            // StringBuilder in the System.
            StringBuilder sb = new StringBuilder();
            sb.Append("Hello ");
            sb.AppendLine("World!");
            sb.AppendLine("Hello C#");
            Console.WriteLine(sb);

            StringBuilder hello_sb = new StringBuilder("Hello World!");
            hello_sb.Replace("World", "C#");
            Console.WriteLine(hello_sb);//output: Hello C#!

            // Convert String to DateTime
            var str = "5/12/2020";
            DateTime str_dt;

            var isValidDate = DateTime.TryParse(str, out str_dt);

            if (isValidDate)
                Console.WriteLine(str_dt);
            else
                Console.WriteLine($"{str} is not a valid date string");

            // Dynamic Types
            dynamic MyDynamicVar = 100;
            Console.WriteLine("Value: {0}, Type: {1}", MyDynamicVar, MyDynamicVar.GetType());

            MyDynamicVar = "Hello World!!";
            Console.WriteLine("Value: {0}, Type: {1}", MyDynamicVar, MyDynamicVar.GetType());

            MyDynamicVar = true;
            Console.WriteLine("Value: {0}, Type: {1}", MyDynamicVar, MyDynamicVar.GetType());

            MyDynamicVar = DateTime.Now;
            Console.WriteLine("Value: {0}, Type: {1}", MyDynamicVar, MyDynamicVar.GetType());

            //  var
            var i = 10;
            Console.WriteLine("Type of i is {0}", i.GetType());

            var str2 = "Hello World!!";
            Console.WriteLine("Type of str is {0}", str2.GetType());

            var dbl = 100.50d;
            Console.WriteLine("Type of dbl is {0}", dbl.GetType());

            var isValid = true;
            Console.WriteLine("Type of isValid is {0}", isValid.GetType());

            var ano = new { name = "Steve" };
            Console.WriteLine("Type of ano is {0}", ano.GetType());

            var arr = new[] { 1, 10, 20, 30 };
            Console.WriteLine("Type of arr is {0}", arr.GetType());

            var file = new FileInfo("MyFile");
            Console.WriteLine("Type of file is {0}", file.GetType());

            // Anonymous Type
            var student = new { Id = 1, FirstName = "James", LastName = "Bond" };
            Console.WriteLine(student.Id); //output: 1
            Console.WriteLine(student.FirstName); //output: James
            Console.WriteLine(student.LastName); //output: Bond

            // student.Id = 2;//Error: cannot chage value
            // student.FirstName = "Steve";//Error: cannot chage value
            


            return;
        }
    }
}
