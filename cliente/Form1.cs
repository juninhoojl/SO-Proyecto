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
        // int logado = 0;
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
            IPEndPoint ipep = new IPEndPoint(direc, 9002);

            buttonConectados.Enabled = false;
            listView1.Items.Clear();
            listView1.Enabled = false;
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
                dynamic result = MessageBox.Show("No he podido conectar con el servidor\n\t Cierrar aplicacion?", "GameSO", MessageBoxButtons.YesNo);
                if (result == DialogResult.Yes)
                {
                    Application.Exit();
                }
                // Se nao foi possivel
                return;
            }
        }

        public static class Global
        {
            public static string texto = "Hello";
            public static int logado = 0;
        }

        // 1- Registrado corretamente
        // 2- Usuario ja existe
        // 3- erro ao registrar
        private void buttonRegistra_Click(object sender, EventArgs e)
        {
            // Remove usuario
            if (Global.logado == 1)
            {
                dynamic result = MessageBox.Show("Seguro que quieres\n\t borrar usuario?", "GameSO", MessageBoxButtons.YesNo);
                if (result == DialogResult.Yes) // Somente se quiser deletar
                {

                    string mensaje = "3/" + textUser.Text + "/" + textPassword.Text;

                    // Enviamos ao servidor a mensagem
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                    //Recibimos la respuesta del servidor
                    byte[] msg2 = new byte[80];
                    server.Receive(msg2);

                    // Toda a linha de mensagem
                    mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                    if (String.Compare(mensaje, "1" + textUser.Text) == 0)
                    {
                        MessageBox.Show("Excluido com sucesso");
                        Global.logado = 0;
                        textUser.Enabled = true;
                        textPassword.Enabled = true;
                        buttonConectados.Enabled = false;
                        listView1.Items.Clear();
                        listView1.Enabled = false;
                        buttonRegistra.Text = "Registrar";
                        buttonLogin.Text = "Login";
                        this.BackColor = Color.Purple;

                    }
                    else if (String.Compare(mensaje, "2" + textUser.Text) == 0)
                    {
                        MessageBox.Show("Erro ao excluir usuario");
                    }
                    else // Eh impossivel chegar nesse caso
                    {
                        MessageBox.Show("Credenciais incorretas");
                    }
                }
            }
            else { 

                // Mensagem Login
                string mensaje = "5/" + textUser.Text + "/" + textPassword.Text;

                // Enviamos ao servidor a mensagem
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);

                mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                if (String.Compare(mensaje, "1" + textUser.Text) == 0)
                {
                    MessageBox.Show("Registrado com sucesso");
                    this.BackColor = Color.Orange;
                    buttonLogin.PerformClick();
                }
                else if (String.Compare(mensaje, "2" + textUser.Text) == 0)
                {
                    MessageBox.Show("Usuario ja existe");
                }
                else
                {
                    MessageBox.Show("Erro ao registrar usuario");
                }

            }
        }

        // 1- Logado corretamente
        // 2- Credenciais incorretas
        // 3- Erro ao logar
        // 0- Deslogado ok
        private void buttonLogin_Click(object sender, EventArgs e)
        {
            // Se logado pede logout
            if (Global.logado == 1)
            {
                string mensaje = "2/" + textUser.Text + "/" + textPassword.Text; // logout

                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);

                // Toda a linha de mensagem
                mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                if (String.Compare(mensaje, "0" + textUser.Text) == 0)
                {
                    MessageBox.Show("Deslogado com sucesso");
                    Global.logado = 0;
                    textUser.Enabled = true;
                    textPassword.Enabled = true;
                    buttonConectados.Enabled = false;
                    listView1.Items.Clear();
                    listView1.Enabled = false;
                    buttonLogin.Text = "Login";
                    buttonRegistra.Text = "Registrar";
                    this.BackColor = Color.Blue;

                }
                else
                {
                    MessageBox.Show("Erro ao deslogar");
                }

            }
            else // Efetua login
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

                if (String.Compare(mensaje, "1" + textUser.Text) == 0)
                {
                    MessageBox.Show("Logado com sucesso");
                    Global.logado = 1;
                    textUser.Enabled = false;
                    textPassword.Enabled = false;
                    this.BackColor = Color.Orange;
                    buttonConectados.Enabled = true;
                    listView1.Enabled = true;
                    buttonRegistra.Text = "Deletar";
                    buttonLogin.Text = "Logout";
                    buttonConectados.PerformClick();
                }
                else if (String.Compare(mensaje, "2" + textUser.Text) == 0)
                {
                    MessageBox.Show("Usuario ou senha incorretos");
                }
                else if (String.Compare(mensaje, "0" + textUser.Text) == 0)
                {
                    MessageBox.Show("Usuario nao existe");
                }
                else
                {
                    MessageBox.Show("Erro ao efetuar login");
                }
            }


        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void buttonConectados_Click(object sender, EventArgs e)
        {

            {
                // Mensagem Login
                string mensaje = "4/" + textUser.Text + "/" + textPassword.Text;

                // Enviamos ao servidor a mensagem
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];

                // Limpa toda vez que chama esse botao e preenche do zero

                server.Receive(msg2);

                // Toda a linha de mensagem
                //mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                // Toda a linha de mensagem
                
                mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                listView1.Items.Clear();

                // Remove quantida

                string[] separada = mensaje.Split(new Char[]{'/'});
                //ListViewItem item;

                for (int i = 1; i <= Convert.ToInt32(separada[0]); i++)
                {

                    if (separada[i].Trim() != "")
                    {
                        // Proprio usuario
                        if (String.Compare(separada[i], textUser.Text) == 0)
                        {
                            listView1.Items.Add(separada[i] + " (tu)");
                        }
                        else
                        {
                            listView1.Items.Add(separada[i]);
                        }


                    }


                }

                // ListViewItem item = new ListViewItem(mensaje);
                //listView1.Items.Add(item);
                if (Convert.ToInt32(separada[0])==1)
                {
                    MessageBox.Show(separada[0] + " jugador conectado! (tu mismo)");
                }
                else
                {
                    MessageBox.Show(separada[0] + " jugadores conectados!");
                }
            }
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {

        }
    }
}
