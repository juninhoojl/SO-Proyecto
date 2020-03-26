namespace WindowsFormsApplication1
{
    partial class main
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
            this.label3 = new System.Windows.Forms.Label();
            this.buscar = new System.Windows.Forms.Button();
            this.username = new System.Windows.Forms.TextBox();
            this.recuperar = new System.Windows.Forms.RadioButton();
            this.remover = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.nomeuser = new System.Windows.Forms.TextBox();
            this.aplicar = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.senhauser = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(35, 36);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(181, 17);
            this.label3.TabIndex = 27;
            this.label3.Text = "Search for registered users";
            // 
            // buscar
            // 
            this.buscar.Location = new System.Drawing.Point(400, 54);
            this.buscar.Margin = new System.Windows.Forms.Padding(4);
            this.buscar.Name = "buscar";
            this.buscar.Size = new System.Drawing.Size(144, 28);
            this.buscar.TabIndex = 26;
            this.buscar.Text = "Find";
            this.buscar.UseVisualStyleBackColor = true;
            this.buscar.Click += new System.EventHandler(this.buscar_Click);
            // 
            // username
            // 
            this.username.Location = new System.Drawing.Point(32, 57);
            this.username.Margin = new System.Windows.Forms.Padding(4);
            this.username.Name = "username";
            this.username.Size = new System.Drawing.Size(360, 22);
            this.username.TabIndex = 25;
            // 
            // recuperar
            // 
            this.recuperar.AutoSize = true;
            this.recuperar.Location = new System.Drawing.Point(157, 199);
            this.recuperar.Margin = new System.Windows.Forms.Padding(4);
            this.recuperar.Name = "recuperar";
            this.recuperar.Size = new System.Drawing.Size(73, 21);
            this.recuperar.TabIndex = 29;
            this.recuperar.TabStop = true;
            this.recuperar.Text = "Enable";
            this.recuperar.UseVisualStyleBackColor = true;
            // 
            // remover
            // 
            this.remover.AutoSize = true;
            this.remover.Location = new System.Drawing.Point(38, 199);
            this.remover.Margin = new System.Windows.Forms.Padding(4);
            this.remover.Name = "remover";
            this.remover.Size = new System.Drawing.Size(92, 21);
            this.remover.TabIndex = 28;
            this.remover.TabStop = true;
            this.remover.Text = "Disenable";
            this.remover.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(35, 147);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(73, 17);
            this.label1.TabIndex = 32;
            this.label1.Text = "Username";
            // 
            // nomeuser
            // 
            this.nomeuser.Location = new System.Drawing.Point(116, 144);
            this.nomeuser.Margin = new System.Windows.Forms.Padding(4);
            this.nomeuser.Name = "nomeuser";
            this.nomeuser.Size = new System.Drawing.Size(268, 22);
            this.nomeuser.TabIndex = 30;
            // 
            // aplicar
            // 
            this.aplicar.Location = new System.Drawing.Point(394, 140);
            this.aplicar.Margin = new System.Windows.Forms.Padding(4);
            this.aplicar.Name = "aplicar";
            this.aplicar.Size = new System.Drawing.Size(144, 58);
            this.aplicar.TabIndex = 34;
            this.aplicar.Text = "Apply";
            this.aplicar.UseVisualStyleBackColor = true;
            this.aplicar.Click += new System.EventHandler(this.aplicar_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(35, 174);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 17);
            this.label4.TabIndex = 36;
            this.label4.Text = "Password";
            // 
            // senhauser
            // 
            this.senhauser.Location = new System.Drawing.Point(116, 169);
            this.senhauser.Margin = new System.Windows.Forms.Padding(4);
            this.senhauser.Name = "senhauser";
            this.senhauser.Size = new System.Drawing.Size(268, 22);
            this.senhauser.TabIndex = 35;
            // 
            // main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(560, 242);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.senhauser);
            this.Controls.Add(this.aplicar);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.nomeuser);
            this.Controls.Add(this.recuperar);
            this.Controls.Add(this.remover);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.buscar);
            this.Controls.Add(this.username);
            this.Name = "main";
            this.Text = "main";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button buscar;
        private System.Windows.Forms.TextBox username;
        private System.Windows.Forms.RadioButton recuperar;
        private System.Windows.Forms.RadioButton remover;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox nomeuser;
        private System.Windows.Forms.Button aplicar;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox senhauser;
    }
}