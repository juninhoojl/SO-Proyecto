﻿using System;
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
using Cliente.Properties;

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
            this.MinimizeBox = true;

            // Set the start position of the form to the center of the screen.
            this.StartPosition = FormStartPosition.CenterScreen;
            this.MinimumSize = new Size(1100, 700);
            this.MaximumSize = new Size(1100, 700);

           
        }

        // Conecta ao carregar
        private void Form1_Load(object sender, EventArgs e)
        {

            buttonLogin.Enabled = false;
            buttonRegistra.Enabled = false;
            // Set to no text.
            textPassword.Text = "";
            // The password character is an asterisk.
            textPassword.UseSystemPasswordChar = true;

            ConectServer();

            ThreadStart ts = delegate { AtenderServidor(); };
            atender = new Thread(ts);
            atender.Start();
            buttonEnvia.Enabled = false;
            // Limita tamanho caixa de texto
            textBoxMensagem.MaxLength = 150;
            textPassword.MaxLength = 20;
            textUser.MaxLength = 20;
            radioTodos.Checked = true;
            comboUsers.Enabled = false;
            radioOutro.Enabled = false;
            radioPartida.Enabled = false;

            bmenor.Enabled = false;
            bmayor.Enabled = false;
            bpasarturno.Enabled = false;
            // panel1.Visible = false;
        }


        private int ConectServer()
        {

            // PRODUCION ###########
             IPAddress direc = IPAddress.Parse("147.83.117.22");

            // LOCAL ###########
           // IPAddress direc = IPAddress.Parse("10.211.55.9");
            // ########### ###########

            IPEndPoint ipep = new IPEndPoint(direc, 50004);


            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                // Tentamos conectar usando socket
                server.Connect(ipep);

                AlteraBanner("Conectado al servidor: " + direc);

                //label1.Text = "Conectado al servidor: " + direc;
                MessageBox.Show("Conectado");
                return 0;
            }
            catch (SocketException)
            {
                dynamic result = MessageBox.Show("No he podido conectar con el servidor\n\t Cierrar aplicacion?", "GameSO", MessageBoxButtons.YesNo);
                if (result == DialogResult.Yes)
                {
                    Application.Exit();
                }
                // Se nao foi possivel
                return 1;
            }


        }


        private void EnviaMensagem(String mensagem)
        {
            //string mensaje = "2/" + textUser.Text + "/" + textPassword.Text; // logout
            byte[] msg = Encoding.ASCII.GetBytes(mensagem);
            server.Send(msg);
        }

        private void AlteraBanner(String texto)
        {
            label1.Text = texto;

        }


        private void AtenderServidor()
        {
            byte[] msg2;
            int codigo;
            while (true)
            {
                //Recibimos la respuesta del servidor
                msg2 = new byte[200];
                // Limpa toda vez que chama esse botao e preenche do zero

                server.Receive(msg2);

                string[] trozos = Encoding.ASCII.GetString(msg2).Split('/');

                codigo = Convert.ToInt32(trozos[0]); // Antes da barra

                switch (codigo)
                {

                    case 1: // Resposta ao login

                        if (String.Compare(trozos[1], "1") == 0)
                        {
                            label1.Text = "Logueado con sucesso";
                            Global.logado = 1;
                            buttonEnvia.Enabled = true;
                            textUser.Enabled = false;
                            textPassword.Enabled = false;
                            //listView1.Enabled = true;
                            button1.Enabled = false;
                            buttonRegistra.Text = "Deletar";
                            buttonLogin.Text = "Logout";

                        }
                        else if (String.Compare(trozos[1], "2") == 0)
                        {
                            label1.Text = "Usuario o contrasena incorrectos";
                        }
                        else if (String.Compare(trozos[1], "0") == 0)
                        {
                            label1.Text = "Usuario no existe";
                        }
                        else if (String.Compare(trozos[1], "4") == 0)
                        {
                            label1.Text = "Usuario ya logueado en otra secion";
                        }
                        else
                        {
                            label1.Text = "Erro al hacer el login";
                        }

                        break;

                    case 2: // Resposta deslogin
                        if (String.Compare(trozos[1], "1") == 0)
                        {
                            label1.Text = "Delogueado con sucesso";
                            Global.logado = 0;
                            buttonEnvia.Enabled = false;
                            textUser.Enabled = true;
                            textPassword.Enabled = true;
                            listView1.Items.Clear();
                            checkedListBox1.Items.Clear();
                            buttonLogin.Text = "Login";
                            buttonRegistra.Text = "Registrar";
                            button1.Enabled = true;
                            textPassword.Text = "";
                            textUser.Text = "";
                        }
                        else
                        {
                            label1.Text = "Erro al desloguear";
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
                            buttonEnvia.Enabled = false;
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
                        comboUsers.Items.Clear();
                        int quantidade = Convert.ToInt32(trozos[1]);
                        trozos[quantidade + 1] = trozos[quantidade + 1].Split('\0')[0];
                        radioOutro.Enabled = false;
                        comboUsers.Enabled = false;
                        radioTodos.Checked = true;
                        // a partir do 2
                        for (int i = 2; i < (quantidade * 2) + 2; i += 2)
                        {

                            if (trozos[i].Trim() != "")
                            {
                                // Proprio usuario
                                if (String.Compare(trozos[i], textUser.Text) == 0)
                                {
                                    listView1.Items.Add(trozos[i] + " (tu)");
                                }
                                else
                                {

                                    comboUsers.Items.Add(trozos[i]);

                                    if (String.Compare(trozos[i + 1].Split('\0')[0], "0") == 0)
                                    {
                                        checkedListBox1.Items.Add(trozos[i]);

                                    }
                                    else
                                    {

                                        listView1.Items.Add(trozos[i]);

                                    }




                                    comboUsers.SelectedIndex = 0;
                                    radioOutro.Enabled = true;

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
                        // Alterar esses casos

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

                        dynamic result = MessageBox.Show(trozos[1] + "te ivitou para jugar, \n\t aceptar?", "Invitacion", MessageBoxButtons.YesNo);
                        if (result == DialogResult.Yes)
                        {
                            // Aceptou
                            EnviaMensagem("7/" + textUser.Text + "/1/" + trozos[1] + "/" + trozos[2]);
                        }
                        else
                        {
                            EnviaMensagem("7/" + textUser.Text + "/2/" + trozos[1] + "/" + trozos[2]);
                            // Nao aceptou
                        }
                        // Responde aceitando ou recusando

                        break;
                    case 7: // Convite para jogar
                            // Nao existe mais o jogo que tentou entrar

                        // esse caso esta no 12 agora
                        if (String.Compare(trozos[1], "1") == 0) // Foi inserido na partida
                        {
                            AlteraBanner("Voce foi inserido na partida");
                            Global.partida = 1;
                            buttonInvitar.Text = "Acabar Partida";
                            radioPartida.Enabled = true;
                            checkedListBox1.Enabled = false;
                            buttonLogin.Enabled = false;
                            buttonRegistra.Enabled = false;
                            // Habilita o radiobox para partida
                            // Fazer caso que sai da partida (da para reaproveitar botao convida)

                            //MessageBox.Show("Todos ya estan!");

                        }
                        else // Nao foi inserido
                        {
                            AlteraBanner("La partida ya no esta disponible mas!");

                        }

                        // Responde aceitando ou recusando

                        break;
                    case 8: // Convite para jogar

                        // Acepto pero aun faltan personas
                        if (String.Compare(trozos[1].Split('\0')[0], "0") == 0)
                        {
                            label1.Text = trozos[2].Split('\0')[0] + " acepto la invitacion! Pero aun faltan personas!";

                        }
                        else if (String.Compare(trozos[1].Split('\0')[0], "1") == 0) // Empezo
                        {
                       
                            label1.Text = "Juego ha empezado";
                            //MessageBox.Show("Juego ha empezado");

                        }
                        else if (String.Compare(trozos[1].Split('\0')[0], "2") == 0) // Acabo
                        {

                            label1.Text = "Juego ha acabado";
                            buttonInvitar.Text = "Invitar";
                            // Juego empeza ahora
                            radioTodos.Checked = true;

                            Global.partida = 0;
                            checkedListBox1.Enabled = true;
                            buttonRegistra.Enabled = true;
                            buttonLogin.Enabled = true;
                            radioPartida.Enabled = false;
                            // Habilita as coisas de novo

                        }
                        else if (String.Compare(trozos[1].Split('\0')[0], "3") == 0)
                        {

                            label1.Text = trozos[2].Split('\0')[0] + " no acepto, partida ha sido cancelado";

                            buttonInvitar.Text = "Invitar";
                            // Juego empeza ahora
                            radioTodos.Checked = true;
                            radioPartida.Enabled = false;
                            Global.partida = 0;
                            checkedListBox1.Enabled = true;
                            buttonRegistra.Enabled = true;
                            buttonLogin.Enabled = true;
                            // Habilita as coisas de novo

                        }

                        break;
                    case 9: // Convite para jogar
                            // Nao existe mais o jogo que tentou entrar

                        //MessageBox.Show("Invitaciones Inviadas!");
                        label1.Text = "Invitaciones Inviadas!";
                        Global.partida = 1;
                        buttonInvitar.Text = "Acabar Partida";
                        radioPartida.Enabled = true;
                        checkedListBox1.Enabled = false;
                        buttonLogin.Enabled = false;
                        buttonRegistra.Enabled = false;

                        // Responde aceitando ou recusando
                        // Aqui vai mudar o valor do invitar para sair

                        break;
                    case 10: // Mensagens recebidas

                        label1.Text = "Mensagem recebida!";

                        // MessageBox.Show("Recebeu mensagem de:"+trozos[1]);
                        if (String.Compare(trozos[1], textUser.Text) == 0) // Ele mesmo
                        {
                            caixaMensagens.Text = caixaMensagens.Text + "\n\n" + "Tu:\n" + trozos[3];

                        }
                        else
                        {
                            caixaMensagens.Text = caixaMensagens.Text + "\n\n" + trozos[1] + ":\n" + trozos[3];


                        }

                        break;
                    case 11: // Mensagens enviadas

                        label1.Text = "Mensagenes Inviadas!";

                        break;

                    case 12:
                        int qtdp = Convert.ToInt32(trozos[5]);
                        int iqd;

                        // Se o codigo for zero deixa visivel
                        if (String.Compare(trozos[2], "0") == 0)
                        {
                            //panel1.Visible = true;
                            qtdCartas.Text = Convert.ToString(Global.carta);

                        }

                        // Todas as vezes remove o que ja tem na lista
                        listViewPontos.Items.Clear();

                        labelTurno.Text = trozos[4]; // Que eh o jogador atual

                        // listViewPontos.Items.Add(trozos[1]);
                        // Tratar aqui caso seja o seguinte ou nao
                        for (iqd = 6; iqd <= 5+(2*qtdp); iqd += 2)
                         {
                            string[] itemV = { trozos[iqd], trozos[iqd + 1] };

                            ListViewItem lvi = new ListViewItem(itemV);
                            
                            listViewPontos.Items.Add(lvi);

                            //listViewPontos.Items.Add(+" -> "+trozos[iqd+1]);

                         }


                        // 0    1     2  3   4   5   6     7   8   9 ...
                        string informacaoAnt = "";

                        int resultadoAposta = Convert.ToInt32(trozos[2]);

                        if(resultadoAposta >= 10) // ultima partida
                        {

                            trozos[2] = Convert.ToString(resultadoAposta/10);
                            label1.Text = "FIM DE JOGO, VENCEDOR = " + trozos[4];


                        }


                        if (String.Compare(trozos[2], "1") == 0)

                        //vai conferir se eh maior que 10, dividir por 10 e se for muda o que faz
                        if (String.Compare(trozos[2], "1") == 0)

                            if (String.Compare(trozos[2], "1") == 0)
                        {
                            // 12/juninho/1/KS/jose/2/juninho/10/jose/15 ... -> Disse que era maior e eh maior (acertou)
                            informacaoAnt = trozos[1] + " gano 2 puntos, era mayor!";
                        }
                        else if(String.Compare(trozos[2], "2") == 0)
                        {
                            // 12/juninho/2/KS/jose/2/juninho/10/jose/15 ... ->  Disse que era menor e eh maior
                            informacaoAnt = trozos[1] + " perdio 4 puntos, no era menor!";
                        }
                        else if (String.Compare(trozos[2], "3") == 0)
                        {
                            // 12/juninho/3/KS/jose/2/juninho/10/jose/15 ... -> Disse que era menor e eh menor (acertou)
                            informacaoAnt = trozos[1] + " gano 2 puntos, era menor!";
                        }
                        else if (String.Compare(trozos[2], "4") == 0)
                        {
                            // 12/juninho/4/KS/jose/2/juninho/10/jose/15 ... -> Disse que era maior e eh menor
                            informacaoAnt = trozos[1] + " perdio 4 puntos, no era mayor!";
                        }
                        else if (String.Compare(trozos[2], "5") == 0)
                        {
                            // 12/juninho/5/KS/jose/2/juninho/10/jose/15 ... -> Passou vez
                            informacaoAnt = trozos[1] + " paso turno para "+trozos[4]+" y perdio 2 puntos!";
                        }
                        else // vale zero entao eh a primeira jogada
                        {
                            AlteraBanner("Voce foi inserido na partida");
                            Global.partida = 1;
                            buttonInvitar.Text = "Acabar Partida";
                            radioPartida.Enabled = true;
                            checkedListBox1.Enabled = false;
                            buttonLogin.Enabled = false;
                            buttonRegistra.Enabled = false;
                            informacaoAnt = "Primero turno!";
                        }

                        infoGame.Text = informacaoAnt;

                        string valor = "_"+ trozos[3];

                        object O = Resources.ResourceManager.GetObject(valor); //Return an object from the image chan1.png in the project
                        imgCartaAtual.Image = (Image)O;

                        // vai defininir a anterior se for diferente de zero e de pasa turno
                        if (String.Compare(trozos[2], "0") != 0 && String.Compare(trozos[2], "5") != 0)
                        {
                           
                            object Oa = Resources.ResourceManager.GetObject(Global.cartaAnterior); //Return an object from the image chan1.png in the project
                            imgCartaAnterior.Image = (Image)Oa;
                            Global.carta += 1;
                            qtdCartas.Text = Convert.ToString(Global.carta);

                        }

                        Global.cartaAnterior = valor;

                        //imgCartaAtual.Image = Properties.Resources.;

                        //imgCartaAtual.Image = Properties.Resources.ResourceManager.GetObject("H1");
                        // Se a pessoa nao for ela tem que desabilitar os botoes


                        // se a pessoa que tem que jogar eh ela, habilita
                        if (String.Compare(trozos[4], textUser.Text) == 0)
                        {
                            
                            bmenor.Enabled = true;
                            bmayor.Enabled = true;
                            bpasarturno.Enabled = true;
                            label1.Text = "Tu turno!";
                        }
                        else
                        {
                            label1.Text = "";

                        }

                            // vai ser desabilitado logo ao clicar no botao



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
            public static int partida = 0;
            public static int musica = 0;
            public static string cartaAnterior = "";
            public static int carta = 1;

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
                buttonEnvia.Enabled = true;
            }
            else
            {
                buttonEnvia.Enabled = false;
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
                    EnviaMensagem("3/" + textUser.Text + "/" + textPassword.Text);
                }
            }
            else
            {
                EnviaMensagem("5/" + textUser.Text + "/" + textPassword.Text);
            }

            // Remove usuario

        }

        private void buttonInvitar_Click(object sender, EventArgs e)
        {


            // primeiro confere se a pessoa esta em jogo ou nao, se estiver
            // envia dizendo que acabou
            if (Global.partida == 1)
            {

                EnviaMensagem("8/" + textUser.Text + "/1/");


            }
            else
            {
                if (checkedListBox1.CheckedItems.Count > 0 && checkedListBox1.CheckedItems.Count <= 4)
                {
                    string invitados = "6/" + textUser.Text + "/" + checkedListBox1.CheckedItems.Count.ToString() + "/";
                    foreach (int i in checkedListBox1.CheckedIndices)
                    {

                        invitados += checkedListBox1.Items[i] + "/";

                    }

                    EnviaMensagem(invitados.TrimEnd(','));


                }
                else if (checkedListBox1.CheckedItems.Count == 0)
                {

                    MessageBox.Show("Selecione por lo menos un jugador!");

                }
                else
                {
                    MessageBox.Show("Selecione no mas que 4 jugadore!");

                }

            }



        }



        // 1- Logado corretamente
        // 2- Credenciais incorretas
        // 3- Erro ao logar
        // 0- Deslogado ok
        private void buttonLogin_Click(object sender, EventArgs e)
        {

            // Confere se os tamanhos ok
            // Vamos limitar em 20 por garantia

            // Se logado pede logout
            if (Global.logado == 1)
            {
                EnviaMensagem("2/" + textUser.Text + "/" + textPassword.Text);
            }
            else // Efetua login
            {
                // Mensagem Login
                EnviaMensagem("1/" + textUser.Text + "/" + textPassword.Text);
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {

            // Enviamos ao servidor a mensagem de desconexao
            EnviaMensagem("0/" + textUser.Text + "/" + textPassword.Text);

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


        private void buttonEnvia_Click(object sender, EventArgs e)
        {
            // Ao clicar envia mensagem
            // Tem que ter as pessoas selecionadas tb
            // 3 opcoes:
            // Todos os conectados
            // Todos da partida
            // ou 1 pessoa especifica

            // Envia para todos os conectados

            string mensagem = "";

            if (radioTodos.Checked == true)
            {
                mensagem = "4/" + textUser.Text + "/0/" + textBoxMensagem.Text;
            }
            else if (radioPartida.Checked == true)
            {
                mensagem = "4/" + textUser.Text + "/1/" + textBoxMensagem.Text;

            }
            else if (radioOutro.Checked == true) // ecolhe pessoa 
            {


                mensagem = "4/" + textUser.Text + "/2/" + comboUsers.SelectedItem + "/" + textBoxMensagem.Text;
                AlteraBanner(mensagem);

            }

            // Aqui envia

            EnviaMensagem(mensagem);
            textBoxMensagem.Text = "";

        }

        private void textBoxMensagem_TextChanged(object sender, EventArgs e)
        {

            if (String.IsNullOrEmpty(textBoxMensagem.Text) || String.IsNullOrWhiteSpace(textBoxMensagem.Text) || String.IsNullOrEmpty(textBoxMensagem.Text) || String.IsNullOrWhiteSpace(textBoxMensagem.Text))
            {
                buttonEnvia.Enabled = false;
            }
            else
            {

                if (Global.logado == 1)
                {
                    buttonEnvia.Enabled = true;
                }

            }
        }



        private void limpia_Chat_Click(object sender, EventArgs e)
        {
            caixaMensagens.Text = "";
        }


        // A cada vez que recarrega a lista vai descelecionar o otro(combobox se o item atual nao existir e se estiver selecionado)
        // So vai habilitar selecionar outro se tiver mais de um usuario selecionado (pq senao vai ficar vazio)
        private void radioOutro_CheckedChanged(object sender, EventArgs e)
        {
            // Vai habilitar o checkbox
            if (radioOutro.Checked)
            {
                comboUsers.Enabled = true;
                comboUsers.Enabled = true;
            }
            else
            {

                comboUsers.Enabled = false;
                comboUsers.Enabled = false;

            }
        }

        // 9/juninho/2 -> Acha que a seguinte eh menor
        private void bmenor_Click(object sender, EventArgs e)
        {
            bmenor.Enabled = false;
            bmayor.Enabled = false;
            bpasarturno.Enabled = false;

            string mensagem = "";
            mensagem = "9/" + textUser.Text + "/2/" + textUser.Text;

            EnviaMensagem(mensagem);
        }

        // 9/juninho/3 -> Passa a vez
        private void bpasarturno_Click_1(object sender, EventArgs e)
        {
            bmenor.Enabled = false;
            bmayor.Enabled = false;
            bpasarturno.Enabled = false;

            string mensagem = "";
            mensagem = "9/" + textUser.Text + "/3/" + textUser.Text;
            EnviaMensagem(mensagem);
        }

        // 9/juninho/1 -> Acha que a seguinte eh maior
        private void bmayor_Click(object sender, EventArgs e)
        {
            bmenor.Enabled = false;
            bmayor.Enabled = false;
            bpasarturno.Enabled = false;

            string mensagem = "";
            mensagem = "9/" + textUser.Text + "/1/"+textUser.Text;

            EnviaMensagem(mensagem);
        }

    }
}
