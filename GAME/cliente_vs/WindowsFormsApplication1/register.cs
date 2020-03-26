using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace WindowsFormsApplication1
{
    public partial class register : Form
    {
        Socket server;        

        public register()
        {
            InitializeComponent();
        }

       

        private void register_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (senhauser.Text == senhauser2.Text)
            {
                string mensaje = "5/" + nomeuser.Text + "/" + senhauser.Text;
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);
                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);

                mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                MessageBox.Show(mensaje);
                this.Close();
            }
            else
            {
                MessageBox.Show("The passwords given are not the same");
            }
        }

        public Socket setserver (Socket p)
        {
            this.server = p;
            return server;
        }

    
    }
}
