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
using System.Media;

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

            // Define the border style of the form to a dialog box.
            this.FormBorderStyle = FormBorderStyle.FixedDialog;

            // Set the MaximizeBox to false to remove the maximize box.
            this.MaximizeBox = false;
            this.MinimizeBox = false;

            // Set the start position of the form to the center of the screen.
            this.StartPosition = FormStartPosition.CenterScreen;
            this.MinimumSize = new Size(1000, 625);
            this.MaximumSize = new Size(1000, 625);


         
            //this.BackgroundImage = new Bitmap(Properties.Resources.background_wood);

        }


        // Conecta ao carregar
        private void Form1_Load(object sender, EventArgs e)
        {
            // PRODUCION ###########
            IPAddress direc = IPAddress.Parse("147.83.117.22");
            IPEndPoint ipep = new IPEndPoint(direc, 50001);
            // ########### ###########

            // LOCAL ###########
            // IPAddress direc = IPAddress.Parse("10.211.55.9");
            // IPEndPoint ipep = new IPEndPoint(direc, 9003);
            // ########### ###########


            buttonConectados.Enabled = false;
            listView1.Items.Clear();
            listView1.Enabled = false;
            buttonLogin.Enabled = false;
            buttonRegistra.Enabled = false;
            // Set to no text.
            textPassword.Text = "";
            // The password character is an asterisk.
            textPassword.UseSystemPasswordChar = true;
            // textPassword.PasswordChar = '*';

            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                // Tentamos conectar usando socket
                server.Connect(ipep);
               
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
            public static int musica = 0;


            public static SoundPlayer splayer = new SoundPlayer(Properties.Resources.gandalf_reduzido);

            

        }


        private void AtenderServidor() // funcion para atender al servidor
        {
            while (true)
            {
                //Recibimos mensaje del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                string respuesta = Encoding.ASCII.GetString(msg2).Split('\0')[0];//netejar de basura

                string[] trozos = respuesta.Split('/');// Codigo/codigo error o numero filas/mensaje
                //MessageBox.Show(respuesta);

                int codigo = Convert.ToInt32(trozos[0]);//Sacamos el codigo correspondiente a que respuesta es

                switch (codigo)
                {
                    case 1:
                        buttonConectados.PerformClick();
                        break;
                    case 2:
                        buttonConectados.PerformClick();
                        break;
                }
            }
        }
        private void textPassword_TextChanged_1(object sender, EventArgs e)
        {
            setButtonVisibility();
        }

        private void textUser_TextChanged_1(object sender, EventArgs e)
        {
            setButtonVisibility();
        }

        private void setButtonVisibility()
        {
            if (String.IsNullOrEmpty(textUser.Text) || String.IsNullOrWhiteSpace(textUser.Text) || String.IsNullOrEmpty(textPassword.Text) || String.IsNullOrWhiteSpace(textPassword.Text))
            {
                buttonLogin.Enabled = false;
                buttonRegistra.Enabled = false;
            }
            else
            {
                buttonLogin.Enabled = true;
                buttonRegistra.Enabled = true;
            }
        }


        // 1- Registrado corretamente
        // 2- Usuario ja existe
        // 3- erro ao registrar
        private void buttonRegistra_Click(object sender, EventArgs e)
        {

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
                            button1.Enabled = true;
                            listView1.Items.Clear();
                            listView1.Enabled = false;
                            buttonRegistra.Text = "Registrar";
                            buttonLogin.Text = "Login";
                            textPassword.Text = "";
                            textUser.Text = "";

                   

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
                else
                {

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

  
            // Remove usuario
            
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
                        button1.Enabled = true;
                        textPassword.Text = "";
                        textUser.Text = "";
                   

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
                
                        buttonConectados.Enabled = true;
                        listView1.Enabled = true;
                        button1.Enabled = false;
                        buttonRegistra.Text = "Deletar";
                        buttonLogin.Text = "Logout";
                     
                    }
                    else if (String.Compare(mensaje, "2" + textUser.Text) == 0)
                    {
                        MessageBox.Show("Usuario ou senha incorretos");
                    }
                    else if (String.Compare(mensaje, "0" + textUser.Text) == 0)
                    {
                        MessageBox.Show("Usuario nao existe");
                    }else if(String.Compare(mensaje, "4" + textUser.Text) == 0) {

                        MessageBox.Show("Usuario esta ativo em outra sessao, nao foi possivel logar");
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

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {

            string mensaje = "0/" + textUser.Text + "/" + textPassword.Text;

            // Enviamos ao servidor a mensagem
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);


        }

        // Botao olho

        private void button1_MouseHover_1(object sender, EventArgs e)
        {
            textPassword.UseSystemPasswordChar = false;
        }

        private void button1_MouseLeave_1(object sender, EventArgs e)
        {
            textPassword.UseSystemPasswordChar = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (Global.musica == 1)
            {
                button2.Text = "Con Musiquita";
                Global.splayer.Stop();
                Global.musica = 0;
            }
            else
            {
                button2.Text = "Sin Musiquita";
                
                Global.splayer.PlayLooping();
                Global.musica = 1;

            }

        }
    }
}
