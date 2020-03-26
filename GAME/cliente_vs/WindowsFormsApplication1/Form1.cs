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
    public partial class Form1 : Form
    {
        Socket server;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.1.62");
            IPEndPoint ipep = new IPEndPoint(direc, 9000);


            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
                MessageBox.Show("Conectado al servidor. Bienvenido");

            }
            catch (SocketException)
            {
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.1.62");
            IPEndPoint ipep = new IPEndPoint(direc, 9000);
            

            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
                MessageBox.Show("Conectado");

            }
            catch (SocketException){
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }

        }

  

      

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

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



        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void insere_Click(object sender, EventArgs e)
        {
            main f3 = new main();
            f3.setserver(server);
            f3.ShowDialog();
        }
            //string mensaje = "1/" + username.Text;
            //// Enviamos al servidor el nombre tecleado
            //byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            //server.Send(msg);

            ////Recibimos la respuesta del servidor
            //byte[] msg2 = new byte[80];
            //server.Receive(msg2);
            //mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
            //MessageBox.Show(mensaje);


            
            
            
            //else if (remover.Checked){ // remover

            //    string mensaje = "6/" + nomeuser.Text + "/" + senhauser.Text;
            //    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            //    server.Send(msg);

            //    //Recibimos la respuesta del servidor
            //    byte[] msg2 = new byte[80];
            //    server.Receive(msg2);

            //    mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                
            //}
            //else{ // recuperar

            //    string mensaje = "7/" + nomeuser.Text + "/" + senhauser.Text;
            //    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            //    server.Send(msg);

            //    //Recibimos la respuesta del servidor
            //    byte[] msg2 = new byte[80];
            //    server.Receive(msg2);

            //    mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

            //    MessageBox.Show(mensaje);

            //}


            // Enviamos al servidor el nombre tecleado
        

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void Longitud_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void novouser_TextChanged(object sender, EventArgs e)
        {

        }

        private void desativar_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        public void button1_Click_1(object sender, EventArgs e)
        {
            register f2 = new register();
            f2.setserver(server);
            f2.ShowDialog();
        }

    }
}
