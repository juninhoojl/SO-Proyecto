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
            this.groupLogin.SuspendLayout();
            this.SuspendLayout();
            // 
            // textPassword
            // 
            this.textPassword.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textPassword.Location = new System.Drawing.Point(6, 45);
            this.textPassword.Name = "textPassword";
            this.textPassword.Size = new System.Drawing.Size(121, 22);
            this.textPassword.TabIndex = 1;
            this.textPassword.TextChanged += new System.EventHandler(this.textPassword_TextChanged_1);
            // 
            // buttonLogin
            // 
            this.buttonLogin.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonLogin.Location = new System.Drawing.Point(6, 71);
            this.buttonLogin.Name = "buttonLogin";
            this.buttonLogin.Size = new System.Drawing.Size(153, 23);
            this.buttonLogin.TabIndex = 2;
            this.buttonLogin.Text = "Login";
            this.buttonLogin.UseVisualStyleBackColor = true;
            this.buttonLogin.Click += new System.EventHandler(this.buttonLogin_Click);
            // 
            // textUser
            // 
            this.textUser.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textUser.Location = new System.Drawing.Point(6, 19);
            this.textUser.Name = "textUser";
            this.textUser.Size = new System.Drawing.Size(153, 22);
            this.textUser.TabIndex = 0;
            this.textUser.TextChanged += new System.EventHandler(this.textUser_TextChanged_1);
            // 
            // buttonRegistra
            // 
            this.buttonRegistra.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonRegistra.Location = new System.Drawing.Point(6, 100);
            this.buttonRegistra.Name = "buttonRegistra";
            this.buttonRegistra.Size = new System.Drawing.Size(153, 23);
            this.buttonRegistra.TabIndex = 3;
            this.buttonRegistra.Text = "Registra";
            this.buttonRegistra.UseVisualStyleBackColor = true;
            this.buttonRegistra.Click += new System.EventHandler(this.buttonRegistra_Click);
            // 
            // groupLogin
            // 
            this.groupLogin.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.groupLogin.Controls.Add(this.button1);
            this.groupLogin.Controls.Add(this.buttonRegistra);
            this.groupLogin.Controls.Add(this.textUser);
            this.groupLogin.Controls.Add(this.buttonLogin);
            this.groupLogin.Controls.Add(this.textPassword);
            this.groupLogin.Location = new System.Drawing.Point(12, 12);
            this.groupLogin.Name = "groupLogin";
            this.groupLogin.Size = new System.Drawing.Size(168, 138);
            this.groupLogin.TabIndex = 3;
            this.groupLogin.TabStop = false;
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.Location = new System.Drawing.Point(133, 45);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(26, 21);
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
            this.listView1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listView1.HideSelection = false;
            this.listView1.Location = new System.Drawing.Point(12, 359);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(168, 191);
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
            this.button2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button2.Location = new System.Drawing.Point(12, 156);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(168, 23);
            this.button2.TabIndex = 6;
            this.button2.Text = "Con Musiquita";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // checkedListBox1
            // 
            this.checkedListBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkedListBox1.FormattingEnabled = true;
            this.checkedListBox1.Location = new System.Drawing.Point(12, 185);
            this.checkedListBox1.Name = "checkedListBox1";
            this.checkedListBox1.Size = new System.Drawing.Size(168, 139);
            this.checkedListBox1.TabIndex = 7;
            // 
            // buttonInvitar
            // 
            this.buttonInvitar.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonInvitar.Location = new System.Drawing.Point(12, 330);
            this.buttonInvitar.Name = "buttonInvitar";
            this.buttonInvitar.Size = new System.Drawing.Size(168, 23);
            this.buttonInvitar.TabIndex = 8;
            this.buttonInvitar.Text = "Invitar";
            this.buttonInvitar.UseVisualStyleBackColor = true;
            this.buttonInvitar.Click += new System.EventHandler(this.buttonInvitar_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(-2, 570);
            this.label1.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
            this.label1.MinimumSize = new System.Drawing.Size(1000, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(1000, 16);
            this.label1.TabIndex = 9;
            this.label1.Text = "Teste\\n";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // textBoxMensagem
            // 
            this.textBoxMensagem.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxMensagem.Location = new System.Drawing.Point(780, 340);
            this.textBoxMensagem.Multiline = true;
            this.textBoxMensagem.Name = "textBoxMensagem";
            this.textBoxMensagem.Size = new System.Drawing.Size(196, 75);
            this.textBoxMensagem.TabIndex = 10;
            this.textBoxMensagem.TextChanged += new System.EventHandler(this.textBoxMensagem_TextChanged);
            // 
            // buttonEnvia
            // 
            this.buttonEnvia.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonEnvia.Location = new System.Drawing.Point(780, 421);
            this.buttonEnvia.Name = "buttonEnvia";
            this.buttonEnvia.Size = new System.Drawing.Size(196, 23);
            this.buttonEnvia.TabIndex = 11;
            this.buttonEnvia.Text = "Enviar";
            this.buttonEnvia.UseVisualStyleBackColor = true;
            this.buttonEnvia.Click += new System.EventHandler(this.buttonEnvia_Click);
            // 
            // caixaMensagens
            // 
            this.caixaMensagens.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.caixaMensagens.Location = new System.Drawing.Point(780, 9);
            this.caixaMensagens.Name = "caixaMensagens";
            this.caixaMensagens.ReadOnly = true;
            this.caixaMensagens.Size = new System.Drawing.Size(196, 296);
            this.caixaMensagens.TabIndex = 12;
            this.caixaMensagens.Text = "";
            // 
            // limpia_Chat
            // 
            this.limpia_Chat.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.limpia_Chat.Location = new System.Drawing.Point(780, 311);
            this.limpia_Chat.Name = "limpia_Chat";
            this.limpia_Chat.Size = new System.Drawing.Size(196, 23);
            this.limpia_Chat.TabIndex = 13;
            this.limpia_Chat.Text = "Limpia Chat";
            this.limpia_Chat.UseVisualStyleBackColor = true;
            this.limpia_Chat.Click += new System.EventHandler(this.limpia_Chat_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoValidate = System.Windows.Forms.AutoValidate.Disable;
            this.BackgroundImage = global::Cliente.Properties.Resources.gandalf;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(984, 586);
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
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.groupLogin.ResumeLayout(false);
            this.groupLogin.PerformLayout();
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
    }
}

