using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Speech.Synthesis;
using System.IO.Ports;
using System.Threading;

namespace BienvenidoACO
{
    public partial class FormDoor : Form
    {
        System.IO.Ports.SerialPort Port;
        bool cerrado = false;

        SpeechSynthesizer boca = new SpeechSynthesizer();


        public FormDoor()
        {
            InitializeComponent();
            Port = new System.IO.Ports.SerialPort();

            Port.PortName = "COM3";
            Port.BaudRate = 9600;
            Port.ReadTimeout = 500;
            try
            {
                Port.Open();
            }catch
            {

            }
            
            
        }

        private void FormDoor_Load(object sender, EventArgs e)
        {

            Thread Hilo = new Thread(EscucharHilo);
            Hilo.Start();
            
        }

        private void EscucharHilo()
        {
            while (!cerrado)
            {
                try
                {
                    string acceso = Port.ReadLine();
                    labelMessage.Invoke(new MethodInvoker(
                        delegate
                        {
                            labelMessage.Text = acceso;
                            boca.SpeakAsync(acceso);
                        }

                        ));
                }
                catch (Exception)
                {

                }
            }
        }

        private void FormDoor_FormClosed(object sender, FormClosedEventArgs e)
        {
            cerrado = true;
            if (Port.IsOpen)
                Port.Close();
        }
    }
}
