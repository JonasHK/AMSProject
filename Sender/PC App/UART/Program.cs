using System;
using System.IO.Ports;
using System.Threading;
using InTheHand.Net.Bluetooth;

namespace UART
{
    class Program
    {

        static void Main(string[] args)
        {
            SerialPort bt = new SerialPort("COM7", 9600, Parity.None, 8, StopBits.One);
            SerialPort arduino = new SerialPort("COM3", 9600, Parity.None, 8, StopBits.One);
            bt.Open();
            arduino.Open();
            Console.CursorVisible = false;
            

            while (true)
            {
                char data = Convert.ToChar(arduino.ReadChar());
                bt.Write(data.ToString());
                
                Console.Write(data);
                Console.SetCursorPosition(Console.CursorLeft - 1, Console.CursorTop);//Reset console coursor so the output is always in the same place
                Console.CursorVisible = false;                                      // (purely for the looks)
            }
        }

    }
}
