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
using System.Threading;


namespace Cliente
{

    public partial class Form1 : Form
    {
        // int logado = 0;
        Socket server;
        Thread atender;
        public Form1()
        {

            CheckForIllegalCrossThreadCalls = false;

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

        }



        // Conecta ao carregar
        private void Form1_Load(object sender, EventArgs e)
        {
            // PRODUCION ###########
            // IPAddress direc = IPAddress.Parse("147.83.117.22");

            // LOCAL ###########
             IPAddress direc = IPAddress.Parse("10.211.55.9");
            // ########### ###########

            IPEndPoint ipep = new IPEndPoint(direc, 50004);

            //listView1.Items.Clear();
            //listView1.Enabled = false;
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

                label1.Text = "Conectado al servidor: "+ direc;
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

            


            ThreadStart ts = delegate { AtenderServidor(); };
            atender = new Thread(ts);
            atender.Start();


        }

        private void AtenderServidor()
        {

            while (true)
            {
                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[200];

                // Limpa toda vez que chama esse botao e preenche do zero


                server.Receive(msg2);
                string[] trozos = Encoding.ASCII.GetString(msg2).Split('/');

                int codigo = Convert.ToInt32(trozos[0]); // Antes da barra

                switch (codigo)
                {

                    case 1: // Resposta ao login

                        if (String.Compare(trozos[1].Split('\0')[0], "1" + textUser.Text) == 0)
                        {
                            label1.Text = "Logueado con sucesso";
                            //MessageBox.Show("Logado com sucesso");
                            Global.logado = 1;
                            textUser.Enabled = false;
                            textPassword.Enabled = false;
                            //listView1.Enabled = true;
                            button1.Enabled = false;
                            buttonRegistra.Text = "Deletar";
                            buttonLogin.Text = "Logout";


                            //buttonConectados.PerformClick();

                        }
                        else if (String.Compare(trozos[1].Split('\0')[0], "2" + textUser.Text) == 0)
                        {
                            label1.Text = "Usuario o contrasena incorrectos";
                            //MessageBox.Show("Usuario ou senha incorretos");
                        }
                        else if (String.Compare(trozos[1].Split('\0')[0], "0" + textUser.Text) == 0)
                        {
                            label1.Text = "Usuario no existe";
                           // MessageBox.Show("Usuario nao existe");
                        }
                        else if (String.Compare(trozos[1].Split('\0')[0], "4" + textUser.Text) == 0)
                        {
                            label1.Text = "Usuario ya logueado en otra secion";
                            //MessageBox.Show("Usuario esta ativo em outra sessao, nao foi possivel logar");
                        }
                        else
                        {
                            label1.Text = "Erro al hacer el login";
                            //MessageBox.Show("Erro ao efetuar login");
                        }

                        break;

                    case 2: // Resposta deslogin
                        if (String.Compare(trozos[1].Split('\0')[0], "0" + textUser.Text) == 0)
                        {
                            label1.Text = "Delogueado con sucesso";
                            //MessageBox.Show("Deslogado com sucesso");
                            Global.logado = 0;
                            textUser.Enabled = true;
                            textPassword.Enabled = true;
                            listView1.Items.Clear();
                            checkedListBox1.Items.Clear();
                            //listView1.Enabled = false;
                            buttonLogin.Text = "Login";
                            buttonRegistra.Text = "Registrar";
                            button1.Enabled = true;
                            textPassword.Text = "";
                            textUser.Text = "";

                        }
                        else
                        {
                            label1.Text = "Erro al desloguear";
                            //MessageBox.Show("Erro ao deslogar");
                        }

                        break;

                    case 3: // Resposta excluir

                        if (String.Compare(trozos[1].Split('\0')[0], "1" + textUser.Text) == 0)
                        {
                            label1.Text = "Usuario borrado con sucesso";
                            //MessageBox.Show("Excluido com sucesso");
                            Global.logado = 0;
                            textUser.Enabled = true;
                            textPassword.Enabled = true;
                            button1.Enabled = true;
                            listView1.Items.Clear();
                            checkedListBox1.Items.Clear();
                            //listView1.Enabled = false;
                            buttonRegistra.Text = "Registrar";
                            buttonLogin.Text = "Login";
                            textPassword.Text = "";
                            textUser.Text = "";

                        }
                        else if (String.Compare(trozos[1].Split('\0')[0], "2" + textUser.Text) == 0)
                        {
                            label1.Text = "Erro ao excluir usuario";
                            //MessageBox.Show("Erro ao excluir usuario");
                        }
                        else // Eh impossivel chegar nesse caso
                        {
                            label1.Text = "Credenciales incorrectas";
                            //MessageBox.Show("Credenciais incorretas");
                        }

                        break;

                    case 4: // Resposta ver usuarios conectados

                        // Ja esta feito o split dentro do trozos

                        //mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                        listView1.Items.Clear();
                        checkedListBox1.Items.Clear();

                        int quantidade = Convert.ToInt32(trozos[1]);
                        trozos[quantidade+1] = trozos[quantidade+1].Split('\0')[0];

                        // a partir do 2
                        for (int i=2; i < quantidade+2; i++)
                        {

                            if (trozos[i].Trim() != "")
                            {
                                // Proprio usuario
                                if (String.Compare(trozos[i], textUser.Text) == 0)
                                {
                                    listView1.Items.Add(trozos[i] + " (tu)");
                                    // string[] teste = { "item1", "item2", "Item3" };
                                    

                                    //checkedListBox1.Items.Add(trozos[i] + " (tu)");
                                    
                                }
                                else
                                {

                                   // string[] teste = { "item1", "item2", "Item3" };
                                    checkedListBox1.Items.Add(trozos[i]);

                                    listView1.Items.Add(trozos[i]);
                                }

                            }

                        }

                        if (quantidade == 1)
                        {
                            label1.Text = quantidade + " jugador conectado! (tu mismo)";
                            //MessageBox.Show(quantidade + " jugador conectado! (tu mismo)");
                        }
                        else
                        {
                            label1.Text = quantidade + " jugadores conectados!";
                            //MessageBox.Show(quantidade + " jugadores conectados!");
                        }


                        break;

                    case 5: // Resposta insere usuario

                        if (String.Compare(trozos[1].Split('\0')[0], "1" + textUser.Text) == 0)
                        {
                            label1.Text = "Registrado com sucesso";
                            //MessageBox.Show("Registrado com sucesso");
                            
                        }
                        else if (String.Compare(trozos[1].Split('\0')[0], "2" + textUser.Text) == 0)
                        {
                            label1.Text = "Usuario ja existe";
                            //MessageBox.Show("Usuario ja existe");
                        }
                        else
                        {
                            label1.Text = "Erro ao registrar usuario";
                            //MessageBox.Show("Erro ao registrar usuario");
                        }

                        break;
                    case 6: // Convite para jogar

                        // So mostra quem convidou
                        // trozos[0] = proprio codigo
                        // trozos[1] = quem chamou
                        // trozos[2] = idgame bd

                        // Resposta
                        // 7/nombre/respuesta/quieninvito/idbasedados

                        dynamic result = MessageBox.Show(trozos[1]+"te ivitou para jugar, \n\t aceptar?", "Invitacion", MessageBoxButtons.YesNo);
                        if (result == DialogResult.Yes)
                        {
                            // Aceptou
                            string mensaje = "7/" + textUser.Text + "/1/" + trozos[1]+"/"+trozos[2]; // logout
                            byte[] msg = Encoding.ASCII.GetBytes(mensaje);
                            server.Send(msg);
                        }
                        else
                        {
                            string mensaje = "7/" + textUser.Text + "/0/" + trozos[1]+"/"+ trozos[2]; // logout
                            byte[] msg = Encoding.ASCII.GetBytes(mensaje);
                            server.Send(msg);
                            // Nao aceptou
                        }
                        // Responde aceitando ou recusando
    
                        break;
                    case 7: // Convite para jogar
                            // Nao existe mais o jogo que tentou entrar
                        MessageBox.Show("La partida ya no esta disponible mas!");
                        // Responde aceitando ou recusando

                        break;
                    case 8: // Convite para jogar
                            // Nao existe mais o jogo que tentou entrar

                        if(String.Compare(trozos[1], "1") == 0) // listo
                        {
                            label1.Text = "Todos los jugadores ya estan";
                            //MessageBox.Show("Todos ya estan!");

                        }
                        else if (String.Compare(trozos[1], "0") == 0)
                        {
                            
                            MessageBox.Show(trozos[2].Split('\0')[0] + " acepto la invitacion! Pero aun faltan personas!");
                        
                        }else if (String.Compare(trozos[1], "2") == 0)
                        {
                            dynamic result2 = MessageBox.Show("Ya estan todos, desea empezar?", "Empezar", MessageBoxButtons.YesNo);
                            if (result2 == DialogResult.Yes)
                            {

                                MessageBox.Show("Eligiste empezar!");
                                // Aceptou
                                // string mensaje = "7/" + textUser.Text + "/1/" + trozos[1] + "/" + trozos[2]; // logout
                                //byte[] msg = Encoding.ASCII.GetBytes(mensaje);
                                //server.Send(msg);
                            }
                            else
                            {
                                MessageBox.Show("Eligiste no empezar!");
                                //string mensaje = "7/" + textUser.Text + "/0/" + trozos[1] + "/" + trozos[2]; // logout
                                //byte[] msg = Encoding.ASCII.GetBytes(mensaje);
                                // server.Send(msg);
                                // Nao aceptou
                            }

                        }
                            break;
                    case 9: // Convite para jogar
                            // Nao existe mais o jogo que tentou entrar
                        
                        //MessageBox.Show("Invitaciones Inviadas!");
                        label1.Text = "Invitaciones Inviadas!";
                        // Responde aceitando ou recusando

                        break;
                    case 99: // No hace nada

                        // Responde aceitando ou recusando
                        break;

                    default:
                        label1.Text = "Mensagem recebida desconhecida";
                        //MessageBox.Show("Mensagem recebida desconhecida");
                        break;
                }

            }

        }
        public static class Global
        {
            public static string texto = "Hello";
            public static int logado = 0;
            public static int musica = 0;

       
            public static SoundPlayer splayer = new SoundPlayer(Properties.Resources.gandalf_reduzido);

          
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
                        byte[] msg = Encoding.ASCII.GetBytes(mensaje);

                        server.Send(msg);

                    }
                }
                else
                {

                    // Mensagem Login
                    string mensaje = "5/" + textUser.Text + "/" + textPassword.Text;

                    // Enviamos ao servidor a mensagem
                    byte[] msg = Encoding.ASCII.GetBytes(mensaje);

                    server.Send(msg);

                }

            // Remove usuario
            
        }

        private void buttonInvitar_Click(object sender, EventArgs e)
        {

            if (checkedListBox1.CheckedItems.Count > 0 && checkedListBox1.CheckedItems.Count <= 5)
            {
                string invitados = "6/"+textUser.Text+"/"+checkedListBox1.CheckedItems.Count.ToString()+"/";
                foreach (int i in checkedListBox1.CheckedIndices)
                {

                    invitados += checkedListBox1.Items[i] + "/";
                    // The indexChecked variable contains the index of the item.
                    //MessageBox.Show("Index#: " + indexChecked.ToString() + ", is checked. Checked state is:" +
                    //                checkedListBox1.GetItemCheckState(indexChecked).ToString() + ".");


                }
                invitados = invitados.TrimEnd(',');
                // MessageBox.Show(invitados);

                byte[] msg = Encoding.ASCII.GetBytes(invitados);

                server.Send(msg);


            }
            else if(checkedListBox1.CheckedItems.Count == 0)
            {

                MessageBox.Show("Selecione por lo menos un jugador!");

            }
            else
            {
                MessageBox.Show("Selecione no mas que 5 jugadore!");

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

                    byte[] msg = Encoding.ASCII.GetBytes(mensaje);

                    server.Send(msg);

                }
                else // Efetua login
                {
                    // Mensagem Login
                    string mensaje = "1/" + textUser.Text + "/" + textPassword.Text;

                    // Enviamos ao servidor a mensagem
                    byte[] msg = Encoding.ASCII.GetBytes(mensaje);

                    server.Send(msg);

                }
 
        }

        // PARA REMOVER DEPOIS
        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }
        private void Form1_Load_1(object sender, EventArgs e)
        {

        }
        // ########


        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {

            string mensaje = "0/" + textUser.Text + "/" + textPassword.Text;

            // Enviamos ao servidor a mensagem
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);

            server.Send(msg);

            atender.Abort();

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
                label1.Text = "Con Musiquita";
                Global.splayer.Stop();
                Global.musica = 0;
            }
            else
            {
                button2.Text = "Sin Musiquita";
                label1.Text = "Sin Musiquita";
                Global.splayer.PlayLooping();
                Global.musica = 1;

            }

        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {




        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        // Funcao para convidar

    }
}
