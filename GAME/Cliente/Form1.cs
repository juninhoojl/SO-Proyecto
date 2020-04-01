using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace Cliente
{
    public partial class Form1 : Form
    {
        int logado = 0;
        Socket server;
        public Form1()
        {
            
            InitializeComponent();
            Load += new EventHandler(Form1_Load);
        }
        
        // Conecta ao carregar
        private void Form1_Load(object sender, EventArgs e)
        {
            IPAddress direc = IPAddress.Parse("10.211.55.9");
            IPEndPoint ipep = new IPEndPoint(direc, 9000);


            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                // Tentamos conectar usando socket
                server.Connect(ipep);
                this.BackColor = Color.Green;
                MessageBox.Show("Conectado");

            }
            catch (SocketException)
            {
                // Se nao foi possivel
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }

        }

        // Login
        private void buttonLogin_Click(object sender, EventArgs e)
        {

            // Mensagem Login
            string mensaje = "1/" + textUser.Text + "/" + textPassword.Text;

            // Enviamos ao servidor a mensagem
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            //Recibimos la respuesta del servidor
            byte[] msg2 = new byte[80];
            server.Receive(msg2);

            // Toda a linha de mensagem
            mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

            // Se pode logar 1 - sim 2 - credenciais incorretas 3- erro ao logar
            if (String.Compare(mensaje, "1"+textUser.Text) == 0)
            {
                MessageBox.Show("Logado com sucesso");
                logado = 1;
                this.BackColor = Color.Orange;

            }
            else if (String.Compare(mensaje, "2"+textUser.Text) == 0)
            {
                MessageBox.Show("Usuario ou senha incorretos");
            }
            else
            {
                MessageBox.Show("Erro ao efetuar login");
            }

        }




        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

    }
}
