using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoolCalculator
{
    public delegate void MyDelegate(string message);


    internal class DelegateClass
    {

        public static void Sain(string[] args)
        {
            void Method1(string message)
            {
                Console.WriteLine("Method1: " + message);
            }

            void Method2(string message)
            {
                Console.WriteLine("Method2: " + message);
            }

            MyDelegate myDelegate = Method1;

            myDelegate("Hello from Method1!");

            Console.WriteLine("");
            Console.WriteLine("-----------");
            Console.WriteLine("");

            myDelegate += Method2;

            myDelegate("Hello from both methods!");

            Console.WriteLine("");
            Console.WriteLine("-----------");
            Console.WriteLine("");

            myDelegate -= Method1;
            myDelegate("Hello from method2!");

            return;


        }
    }
}
