using System;
using System.Collections.Generic;

namespace CoolCalculator
{
    internal class OperationsQueue
    {
        // List is genreci class that get opject
        private List<string> _operations = null;
        private readonly int _maxQueueSize;
        // by readonly we can put value once and it cant chang forever

        public OperationsQueue(int maxQueueSize)
        {
            this._maxQueueSize = maxQueueSize;
            // use new
            this._operations = new List<string>();
        }
        
        // put opertion
        public void Enqueue(string newOperation)
        {
            int numOfOperations = this._operations.Count;

            // check if a delition is needed , when the 
            if (this._maxQueueSize == numOfOperations)
            {
                // remove the last item - the oldest operation
                this.Dequeue();
            }

            // insert the new operation in index 0 in Queue
            this._operations.Insert(0, newOperation);
        }

        public string Dequeue()
        {
            int numOfOperations = this._operations.Count;
            string operation;

            // if the queue is empty we return null
            if (numOfOperations == 0) 
            {
                operation = null;
            }

            // if the queue is not empty
            else 
            { 
                // get the oldest operation and delete it from the queue
                operation = this._operations[numOfOperations - 1];

                this._operations.RemoveAt(numOfOperations - 1);
            }

            return operation;
        }
        // prperty have get and set
        public int Count
        {
            get { return this._operations.Count; }
        }

        // prperty have get and set
        public bool IsEmpty
        {
            get
            {
                return this.Count == 0;
            }
        }

        //indexer operator to the object, now i can use [] on the class
        public string this[int index]
        {
            // the => is shourtcut to do get
            get => _operations[index];
        }
    }
}
