namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador requerida.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén utilizando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben eliminar; false en caso contrario, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido del método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.username = new System.Windows.Forms.TextBox();
            this.buscar = new System.Windows.Forms.Button();
            this.aplicar = new System.Windows.Forms.Button();
            this.nomeuser = new System.Windows.Forms.TextBox();
            this.senhauser = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.remover = new System.Windows.Forms.RadioButton();
            this.adicionar = new System.Windows.Forms.RadioButton();
            this.recuperar = new System.Windows.Forms.RadioButton();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.Location = new System.Drawing.Point(2, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(388, 39);
            this.button1.TabIndex = 4;
            this.button1.Text = "conectar";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button3
            // 
            this.button3.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button3.Location = new System.Drawing.Point(4, 430);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(401, 39);
            this.button3.TabIndex = 10;
            this.button3.Text = "desconectar";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // username
            // 
            this.username.Location = new System.Drawing.Point(5, 254);
            this.username.Name = "username";
            this.username.Size = new System.Drawing.Size(271, 20);
            this.username.TabIndex = 11;
            this.username.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // buscar
            // 
            this.buscar.Location = new System.Drawing.Point(281, 252);
            this.buscar.Name = "buscar";
            this.buscar.Size = new System.Drawing.Size(108, 23);
            this.buscar.TabIndex = 12;
            this.buscar.Text = "Buscar";
            this.buscar.UseVisualStyleBackColor = true;
            this.buscar.Click += new System.EventHandler(this.buscar_Click);
            // 
            // aplicar
            // 
            this.aplicar.Location = new System.Drawing.Point(278, 315);
            this.aplicar.Name = "aplicar";
            this.aplicar.Size = new System.Drawing.Size(108, 47);
            this.aplicar.TabIndex = 13;
            this.aplicar.Text = "Aplicar";
            this.aplicar.UseVisualStyleBackColor = true;
            this.aplicar.Click += new System.EventHandler(this.insere_Click);
            // 
            // nomeuser
            // 
            this.nomeuser.Location = new System.Drawing.Point(70, 315);
            this.nomeuser.Name = "nomeuser";
            this.nomeuser.Size = new System.Drawing.Size(202, 20);
            this.nomeuser.TabIndex = 14;
            this.nomeuser.TextChanged += new System.EventHandler(this.novouser_TextChanged);
            // 
            // senhauser
            // 
            this.senhauser.Location = new System.Drawing.Point(70, 341);
            this.senhauser.Name = "senhauser";
            this.senhauser.Size = new System.Drawing.Size(202, 20);
            this.senhauser.TabIndex = 15;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 318);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 16;
            this.label1.Text = "Username";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 345);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 17;
            this.label4.Text = "Password";
            // 
            // remover
            // 
            this.remover.AutoSize = true;
            this.remover.Location = new System.Drawing.Point(70, 367);
            this.remover.Name = "remover";
            this.remover.Size = new System.Drawing.Size(68, 17);
            this.remover.TabIndex = 19;
            this.remover.TabStop = true;
            this.remover.Text = "Remover";
            this.remover.UseVisualStyleBackColor = true;
            this.remover.CheckedChanged += new System.EventHandler(this.desativar_CheckedChanged);
            // 
            // adicionar
            // 
            this.adicionar.AutoSize = true;
            this.adicionar.Location = new System.Drawing.Point(148, 367);
            this.adicionar.Name = "adicionar";
            this.adicionar.Size = new System.Drawing.Size(69, 17);
            this.adicionar.TabIndex = 20;
            this.adicionar.TabStop = true;
            this.adicionar.Text = "Adicionar";
            this.adicionar.UseVisualStyleBackColor = true;
            // 
            // recuperar
            // 
            this.recuperar.AutoSize = true;
            this.recuperar.Location = new System.Drawing.Point(223, 367);
            this.recuperar.Name = "recuperar";
            this.recuperar.Size = new System.Drawing.Size(75, 17);
            this.recuperar.TabIndex = 21;
            this.recuperar.TabStop = true;
            this.recuperar.Text = "Recuperar";
            this.recuperar.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1163, 669);
            this.Controls.Add(this.recuperar);
            this.Controls.Add(this.adicionar);
            this.Controls.Add(this.remover);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.senhauser);
            this.Controls.Add(this.nomeuser);
            this.Controls.Add(this.aplicar);
            this.Controls.Add(this.buscar);
            this.Controls.Add(this.username);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox username;
        private System.Windows.Forms.Button buscar;
        private System.Windows.Forms.Button aplicar;
        private System.Windows.Forms.TextBox nomeuser;
        private System.Windows.Forms.TextBox senhauser;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.RadioButton remover;
        private System.Windows.Forms.RadioButton adicionar;
        private System.Windows.Forms.RadioButton recuperar;
    }
}

