using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoolCalculatorCS.coolStaff
{
    internal class ClassExample
    {
        class Person
        {
            protected int id;

            public int PersonId
            {
                get { return id; }
                set { id = value; }
            }
        }

        class Student : Person
        {
            public int StudentId
            {
                get { return id; }
                set {
                    if (value > 0)
                        id = value;
                }
            }
        }

        class Student2 : Person
        {
            public int StudentId { get; set; }
        }


        static void Sain(string[] args)
        {
            Student s = new Student();
            s.StudentId = 5;
            Console.WriteLine(s.StudentId);

            s.StudentId = -3;
            Console.WriteLine(s.StudentId);

            Student2 s2 = new Student2();
            s2.StudentId = 3;
            Console.WriteLine(s2.StudentId);

            return;
        }

    }
}
