using System;
using System.Windows.Forms;

namespace Cliente
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.textPassword = new System.Windows.Forms.TextBox();
            this.buttonLogin = new System.Windows.Forms.Button();
            this.textUser = new System.Windows.Forms.TextBox();
            this.buttonRegistra = new System.Windows.Forms.Button();
            this.groupLogin = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.listView1 = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.button2 = new System.Windows.Forms.Button();
            this.checkedListBox1 = new System.Windows.Forms.CheckedListBox();
            this.buttonInvitar = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxMensagem = new System.Windows.Forms.TextBox();
            this.buttonEnvia = new System.Windows.Forms.Button();
            this.caixaMensagens = new System.Windows.Forms.RichTextBox();
            this.limpia_Chat = new System.Windows.Forms.Button();
            this.radioPartida = new System.Windows.Forms.RadioButton();
            this.radioTodos = new System.Windows.Forms.RadioButton();
            this.radioOutro = new System.Windows.Forms.RadioButton();
            this.comboUsers = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupLogin.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // textPassword
            // 
            this.textPassword.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textPassword.Location = new System.Drawing.Point(6, 48);
            this.textPassword.Name = "textPassword";
            this.textPassword.Size = new System.Drawing.Size(131, 26);
            this.textPassword.TabIndex = 1;
            this.textPassword.TextChanged += new System.EventHandler(this.textPassword_TextChanged_1);
            // 
            // buttonLogin
            // 
            this.buttonLogin.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonLogin.Location = new System.Drawing.Point(6, 79);
            this.buttonLogin.Name = "buttonLogin";
            this.buttonLogin.Size = new System.Drawing.Size(172, 26);
            this.buttonLogin.TabIndex = 2;
            this.buttonLogin.Text = "Login";
            this.buttonLogin.UseVisualStyleBackColor = true;
            this.buttonLogin.Click += new System.EventHandler(this.buttonLogin_Click);
            // 
            // textUser
            // 
            this.textUser.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textUser.Location = new System.Drawing.Point(6, 17);
            this.textUser.Name = "textUser";
            this.textUser.Size = new System.Drawing.Size(172, 26);
            this.textUser.TabIndex = 0;
            this.textUser.TextChanged += new System.EventHandler(this.textUser_TextChanged_1);
            // 
            // buttonRegistra
            // 
            this.buttonRegistra.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonRegistra.Location = new System.Drawing.Point(6, 111);
            this.buttonRegistra.Name = "buttonRegistra";
            this.buttonRegistra.Size = new System.Drawing.Size(172, 26);
            this.buttonRegistra.TabIndex = 3;
            this.buttonRegistra.Text = "Registra";
            this.buttonRegistra.UseVisualStyleBackColor = true;
            this.buttonRegistra.Click += new System.EventHandler(this.buttonRegistra_Click);
            // 
            // groupLogin
            // 
            this.groupLogin.BackColor = System.Drawing.Color.Transparent;
            this.groupLogin.Controls.Add(this.button1);
            this.groupLogin.Controls.Add(this.buttonRegistra);
            this.groupLogin.Controls.Add(this.textUser);
            this.groupLogin.Controls.Add(this.buttonLogin);
            this.groupLogin.Controls.Add(this.textPassword);
            this.groupLogin.Location = new System.Drawing.Point(8, 2);
            this.groupLogin.Name = "groupLogin";
            this.groupLogin.Size = new System.Drawing.Size(184, 147);
            this.groupLogin.TabIndex = 3;
            this.groupLogin.TabStop = false;
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.Location = new System.Drawing.Point(143, 48);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(35, 26);
            this.button1.TabIndex = 4;
            this.button1.Text = "👁";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.MouseLeave += new System.EventHandler(this.button1_MouseLeave_1);
            this.button1.MouseHover += new System.EventHandler(this.button1_MouseHover_1);
            // 
            // listView1
            // 
            this.listView1.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1});
            this.listView1.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listView1.HideSelection = false;
            this.listView1.Location = new System.Drawing.Point(8, 155);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(184, 216);
            this.listView1.TabIndex = 5;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Jugadores";
            this.columnHeader1.Width = 161;
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button2.Location = new System.Drawing.Point(6, 629);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(186, 26);
            this.button2.TabIndex = 6;
            this.button2.Text = "Con Musiquita";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // checkedListBox1
            // 
            this.checkedListBox1.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkedListBox1.FormattingEnabled = true;
            this.checkedListBox1.Location = new System.Drawing.Point(6, 409);
            this.checkedListBox1.Name = "checkedListBox1";
            this.checkedListBox1.Size = new System.Drawing.Size(184, 193);
            this.checkedListBox1.TabIndex = 7;
            // 
            // buttonInvitar
            // 
            this.buttonInvitar.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonInvitar.Location = new System.Drawing.Point(6, 377);
            this.buttonInvitar.Name = "buttonInvitar";
            this.buttonInvitar.Size = new System.Drawing.Size(186, 26);
            this.buttonInvitar.TabIndex = 8;
            this.buttonInvitar.Text = "Invitar";
            this.buttonInvitar.UseVisualStyleBackColor = true;
            this.buttonInvitar.Click += new System.EventHandler(this.buttonInvitar_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(196, 7);
            this.label1.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
            this.label1.MinimumSize = new System.Drawing.Size(660, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(660, 22);
            this.label1.TabIndex = 9;
            this.label1.Text = "Teste\\n";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // textBoxMensagem
            // 
            this.textBoxMensagem.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxMensagem.Location = new System.Drawing.Point(859, 463);
            this.textBoxMensagem.Multiline = true;
            this.textBoxMensagem.Name = "textBoxMensagem";
            this.textBoxMensagem.Size = new System.Drawing.Size(219, 160);
            this.textBoxMensagem.TabIndex = 10;
            this.textBoxMensagem.TextChanged += new System.EventHandler(this.textBoxMensagem_TextChanged);
            // 
            // buttonEnvia
            // 
            this.buttonEnvia.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonEnvia.Location = new System.Drawing.Point(859, 629);
            this.buttonEnvia.Name = "buttonEnvia";
            this.buttonEnvia.Size = new System.Drawing.Size(219, 26);
            this.buttonEnvia.TabIndex = 11;
            this.buttonEnvia.Text = "Enviar";
            this.buttonEnvia.UseVisualStyleBackColor = true;
            this.buttonEnvia.Click += new System.EventHandler(this.buttonEnvia_Click);
            // 
            // caixaMensagens
            // 
            this.caixaMensagens.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.caixaMensagens.Location = new System.Drawing.Point(859, 36);
            this.caixaMensagens.Name = "caixaMensagens";
            this.caixaMensagens.ReadOnly = true;
            this.caixaMensagens.Size = new System.Drawing.Size(219, 342);
            this.caixaMensagens.TabIndex = 12;
            this.caixaMensagens.Text = "";
            // 
            // limpia_Chat
            // 
            this.limpia_Chat.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.limpia_Chat.Location = new System.Drawing.Point(859, 5);
            this.limpia_Chat.Name = "limpia_Chat";
            this.limpia_Chat.Size = new System.Drawing.Size(219, 25);
            this.limpia_Chat.TabIndex = 13;
            this.limpia_Chat.Text = "Limpia Chat";
            this.limpia_Chat.UseVisualStyleBackColor = true;
            this.limpia_Chat.Click += new System.EventHandler(this.limpia_Chat_Click);
            // 
            // radioPartida
            // 
            this.radioPartida.AutoSize = true;
            this.radioPartida.BackColor = System.Drawing.Color.Transparent;
            this.radioPartida.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radioPartida.Location = new System.Drawing.Point(74, 10);
            this.radioPartida.Name = "radioPartida";
            this.radioPartida.Size = new System.Drawing.Size(77, 22);
            this.radioPartida.TabIndex = 14;
            this.radioPartida.TabStop = true;
            this.radioPartida.Text = "Partida";
            this.radioPartida.UseVisualStyleBackColor = false;
            // 
            // radioTodos
            // 
            this.radioTodos.AutoSize = true;
            this.radioTodos.BackColor = System.Drawing.Color.Transparent;
            this.radioTodos.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radioTodos.Location = new System.Drawing.Point(6, 10);
            this.radioTodos.Name = "radioTodos";
            this.radioTodos.Size = new System.Drawing.Size(68, 22);
            this.radioTodos.TabIndex = 15;
            this.radioTodos.TabStop = true;
            this.radioTodos.Text = "Todos";
            this.radioTodos.UseVisualStyleBackColor = false;
            // 
            // radioOutro
            // 
            this.radioOutro.AutoSize = true;
            this.radioOutro.BackColor = System.Drawing.Color.Transparent;
            this.radioOutro.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radioOutro.Location = new System.Drawing.Point(157, 10);
            this.radioOutro.Name = "radioOutro";
            this.radioOutro.Size = new System.Drawing.Size(56, 22);
            this.radioOutro.TabIndex = 16;
            this.radioOutro.TabStop = true;
            this.radioOutro.Text = "Otro";
            this.radioOutro.UseVisualStyleBackColor = false;
            this.radioOutro.CheckedChanged += new System.EventHandler(this.radioOutro_CheckedChanged);
            // 
            // comboUsers
            // 
            this.comboUsers.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboUsers.FormattingEnabled = true;
            this.comboUsers.Location = new System.Drawing.Point(6, 41);
            this.comboUsers.Name = "comboUsers";
            this.comboUsers.Size = new System.Drawing.Size(207, 26);
            this.comboUsers.TabIndex = 17;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioPartida);
            this.groupBox1.Controls.Add(this.comboUsers);
            this.groupBox1.Controls.Add(this.radioTodos);
            this.groupBox1.Controls.Add(this.radioOutro);
            this.groupBox1.Location = new System.Drawing.Point(859, 384);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(219, 73);
            this.groupBox1.TabIndex = 18;
            this.groupBox1.TabStop = false;
            // 
            // button3
            // 
            this.button3.Font = new System.Drawing.Font("Microsoft YaHei", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button3.Location = new System.Drawing.Point(416, 531);
            this.button3.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(198, 70);
            this.button3.TabIndex = 20;
            this.button3.Text = "JUGAR";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.VisibleChanged += new System.EventHandler(this.button3_Click);
           
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(337, 498);
            this.button4.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(112, 28);
            this.button4.TabIndex = 22;
            this.button4.Text = "MAYOR";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Visible = false;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(454, 498);
            this.button5.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(112, 28);
            this.button5.TabIndex = 23;
            this.button5.Text = "MENOR";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Visible = false;
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(571, 498);
            this.button6.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(112, 28);
            this.button6.TabIndex = 24;
            this.button6.Text = "PASAR TURNO";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Visible = false;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(122, 25);
            this.label9.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(123, 20);
            this.label9.TabIndex = 7;
            this.label9.Text = "PUNTUACIÓN";
            this.label9.Click += new System.EventHandler(this.label9_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(223, 180);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(118, 193);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 8;
            this.pictureBox1.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(356, 180);
            this.pictureBox2.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(118, 193);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 9;
            this.pictureBox2.TabStop = false;
            this.pictureBox2.Click += new System.EventHandler(this.pictureBox2_Click);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.label12);
            this.panel1.Controls.Add(this.label11);
            this.panel1.Controls.Add(this.label10);
            this.panel1.Controls.Add(this.label8);
            this.panel1.Controls.Add(this.label7);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.label6);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.pictureBox2);
            this.panel1.Controls.Add(this.pictureBox1);
            this.panel1.Controls.Add(this.label9);
            this.panel1.Location = new System.Drawing.Point(259, 103);
            this.panel1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(494, 390);
            this.panel1.TabIndex = 21;
            this.panel1.Visible = false;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint_1);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(145, 148);
            this.label12.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(69, 13);
            this.label12.TabIndex = 19;
            this.label12.Text = "puntuación4 ";
            this.label12.Click += new System.EventHandler(this.label12_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(145, 117);
            this.label11.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(66, 13);
            this.label11.TabIndex = 18;
            this.label11.Text = "puntuación3";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(145, 85);
            this.label10.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(66, 13);
            this.label10.TabIndex = 17;
            this.label10.Text = "puntuación2";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(145, 54);
            this.label8.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(66, 13);
            this.label8.TabIndex = 16;
            this.label8.Text = "puntuación1";
            this.label8.Click += new System.EventHandler(this.label8_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(419, 25);
            this.label7.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(14, 13);
            this.label7.TabIndex = 15;
            this.label7.Text = "X";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(322, 25);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(97, 13);
            this.label4.TabIndex = 14;
            this.label4.Text = "TURNO PLAYER: ";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(15, 148);
            this.label6.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(94, 20);
            this.label6.TabIndex = 13;
            this.label6.Text = "PLAYER 4";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(15, 117);
            this.label5.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(94, 20);
            this.label5.TabIndex = 12;
            this.label5.Text = "PLAYER 3";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(15, 85);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(94, 20);
            this.label3.TabIndex = 11;
            this.label3.Text = "PLAYER 2";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(15, 54);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(94, 20);
            this.label2.TabIndex = 10;
            this.label2.Text = "PLAYER 1";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoValidate = System.Windows.Forms.AutoValidate.Disable;
            this.BackgroundImage = global::Cliente.Properties.Resources.gandalf;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1083, 661);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.limpia_Chat);
            this.Controls.Add(this.caixaMensagens);
            this.Controls.Add(this.buttonEnvia);
            this.Controls.Add(this.textBoxMensagem);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonInvitar);
            this.Controls.Add(this.checkedListBox1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.groupLogin);
            this.Cursor = System.Windows.Forms.Cursors.Hand;
            this.DoubleBuffered = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "Gandalf Cards";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load_1);
            this.groupLogin.ResumeLayout(false);
            this.groupLogin.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }


        #endregion

        private System.Windows.Forms.TextBox textPassword;
        private System.Windows.Forms.Button buttonLogin;
        private System.Windows.Forms.TextBox textUser;
        private System.Windows.Forms.Button buttonRegistra;
        private System.Windows.Forms.GroupBox groupLogin;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.Button button1;
        private Button button2;
        private CheckedListBox checkedListBox1;
        private Button buttonInvitar;
        private Label label1;
        private TextBox textBoxMensagem;
        private Button buttonEnvia;
        private RichTextBox caixaMensagens;
        private Button limpia_Chat;
        private RadioButton radioPartida;
        private RadioButton radioTodos;
        private RadioButton radioOutro;
        private ComboBox comboUsers;
        private GroupBox groupBox1;
        private Button button3;
        private Button button4;
        private Button button5;
        private Button button6;
        private Label label9;
        private PictureBox pictureBox1;
        private PictureBox pictureBox2;
        private Panel panel1;
        private Label label2;
        private Label label6;
        private Label label5;
        private Label label3;
        private Label label7;
        private Label label4;
        private Label label8;
        private Label label12;
        private Label label11;
        private Label label10;
    }
}

