using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;



namespace CSharp_Memory
{

    public partial class Form1 : Form
    {
        public int GamePID = 0;
        public IntPtr pVirtualMem = IntPtr.Zero;

        byte[] BytesOpcode = {
            0x00, 0x00, 0x00, 0x00, //0 ~ 3 = BOOL para verificar o estado do hacker 
            0x83, 0x3D, 0xAC, 0x0F, //Esse opcode é basicamente o assembly, porem aqui há algumas coisas a considerar.
            0x63, 0x00, 0x01, 0x74, //Como visto, em assembly é necessário definir o local de retorno em caso de hook's
            0x05, 0xFF, 0x47, 0x24, //Nesse caso eu faço um cast para definir
            0xEB, 0x07, 0x81, 0x47, //Uma coisa simples se torna chata simplesmente por ser em .exe, porem é bem útil entender isso
            0x24, 0xFF, 0xFF, 0x00, //Já que alguns antihackers fazem uma lógica similar para hookar api's dos app's abertos
            0x00, 0x8B, 0x47, 0x24,
            0x68, 0xC2, 0x58, 0x49,
            0x00, 0xC3
        };

        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(uint dwDesiredAccess, [MarshalAs(UnmanagedType.Bool)] bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out int lpNumberOfBytesWritten);

        [DllImport("kernel32.dll")]
        public static extern bool ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint dwSize, out int lpNumberOfBytesRead);

        [DllImport("kernel32.dll")]
        public static extern Int32 CloseHandle(IntPtr hProcess);

        [DllImport("user32.dll", SetLastError = true)]
        public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll")]
        public static extern uint GetWindowThreadProcessId(IntPtr hWnd, out int ProcessId);

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        public static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

        public Form1()
        {
            InitializeComponent();
        }

        public void WriteValue(int Addr, byte[] buffer, uint size)
        {
            IntPtr hProc = OpenProcess(0x001F0FFF, false, GamePID);
            if (hProc != IntPtr.Zero)
            {
                int WritenBytes;
                WriteProcessMemory(hProc, (IntPtr)Addr, buffer, size, out WritenBytes);
                CloseHandle(hProc);
            }
        }

        public void ReadValue(int Addr, [Out] byte[] buffer, uint size)
        {
            IntPtr hProc = OpenProcess(0x001F0FFF, false, GamePID);
            if (hProc != IntPtr.Zero)
            {
                int WritenBytes;
                ReadProcessMemory(hProc, (IntPtr)Addr, buffer, size, out WritenBytes);
                CloseHandle(hProc);
            }
        }
        public void MainHack()
        {
            IntPtr hProc = OpenProcess(0x001F0FFF, false, GamePID);
            if (hProc != IntPtr.Zero)
            {
                pVirtualMem = VirtualAllocEx(hProc, IntPtr.Zero, (uint)BytesOpcode.Length, 0x00001000, 0x40);
                if (pVirtualMem != IntPtr.Zero)//Aloca um bloco de memoria no game 
                {
                    byte[] JmpOpcode = { 0x68, 0x00, 0x00, 0x00, 0x00, 0xC3 };

                    WriteValue(0x004958BC, JmpOpcode, (uint)JmpOpcode.Length);
                    WriteValue(0x004958BD, BitConverter.GetBytes((int)pVirtualMem + 0x4), 4);
                    WriteValue((int)pVirtualMem, BytesOpcode, (uint)BytesOpcode.Length);
                    WriteValue((int)pVirtualMem + 0x6, BitConverter.GetBytes((int)pVirtualMem), 4);
                }
                //Tudo que for alocação de memória que não fique em loop é feito aqui

                CloseHandle(hProc);            
            }
        }
       
        private void Timer_FindGame_Tick(object sender, EventArgs e)
        {            
            if (GetWindowThreadProcessId(FindWindow(null, "Plants vs. Zombies"), out GamePID) != 0)
            {
                MainHack();                
                Timer_FindGame.Enabled = false;
                GroupAll.Enabled = true;
                Label_GameInfo.Text = "Game Encontrado!";
                Label_GameInfo.ForeColor = Color.Green;
            }
        }

        private void NoDelay_CheckedChanged(object sender, EventArgs e)
        {            
            WriteValue((int)pVirtualMem, BitConverter.GetBytes(Convert.ToInt32(NoDelay.Checked)), 4);
        }

        private void FreezeSun_CheckedChanged(object sender, EventArgs e)
        {
            WriteValue(0x0041F4E5, BitConverter.GetBytes(Convert.ToInt32(FreezeSun.Checked ? 0x9090 : 0x0A7E)), 2);
        }
    }
}
