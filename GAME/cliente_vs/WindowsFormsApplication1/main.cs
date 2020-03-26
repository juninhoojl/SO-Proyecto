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
    public partial class main : Form
    {
        Socket server;    
        public main()
        {
            InitializeComponent();
        }

        public Socket setserver(Socket p)
        {
            this.server = p;
            return server;
        }

        private void buscar_Click(object sender, EventArgs e)
        {
            string mensaje = "4/" + username.Text;
            // Enviamos al servidor el nombre tecleado
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            //Recibimos la respuesta del servidor
            byte[] msg2 = new byte[80];
            server.Receive(msg2);
            mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

            MessageBox.Show(mensaje);
        }

        private void aplicar_Click(object sender, EventArgs e)
        {
            if (remover.Checked){ // remover

                string mensaje = "6/" + nomeuser.Text + "/" + senhauser.Text;
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);

                mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                MessageBox.Show(mensaje);

            }
            else{ // recuperar

                string mensaje = "7/" + nomeuser.Text + "/" + senhauser.Text;
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);

                mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                MessageBox.Show(mensaje);

            }
        }



        
    }
}
