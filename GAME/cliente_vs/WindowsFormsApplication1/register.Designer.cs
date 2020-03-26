namespace WindowsFormsApplication1
{
    partial class register
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
            this.label4 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.senhauser = new System.Windows.Forms.TextBox();
            this.nomeuser = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.senhauser2 = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(23, 108);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 17);
            this.label4.TabIndex = 21;
            this.label4.Text = "Password";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(23, 74);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(73, 17);
            this.label1.TabIndex = 20;
            this.label1.Text = "Username";
            // 
            // senhauser
            // 
            this.senhauser.Location = new System.Drawing.Point(151, 106);
            this.senhauser.Margin = new System.Windows.Forms.Padding(4);
            this.senhauser.Name = "senhauser";
            this.senhauser.Size = new System.Drawing.Size(268, 22);
            this.senhauser.TabIndex = 19;
            // 
            // nomeuser
            // 
            this.nomeuser.Location = new System.Drawing.Point(151, 74);
            this.nomeuser.Margin = new System.Windows.Forms.Padding(4);
            this.nomeuser.Name = "nomeuser";
            this.nomeuser.Size = new System.Drawing.Size(268, 22);
            this.nomeuser.TabIndex = 18;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(23, 138);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(118, 17);
            this.label2.TabIndex = 23;
            this.label2.Text = "Repeat password";
            // 
            // senhauser2
            // 
            this.senhauser2.Location = new System.Drawing.Point(151, 136);
            this.senhauser2.Margin = new System.Windows.Forms.Padding(4);
            this.senhauser2.Name = "senhauser2";
            this.senhauser2.Size = new System.Drawing.Size(268, 22);
            this.senhauser2.TabIndex = 22;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(224, 179);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(102, 35);
            this.button1.TabIndex = 24;
            this.button1.Text = "REGISTER";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Nirmala UI", 22.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(17, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(272, 51);
            this.label3.TabIndex = 25;
            this.label3.Text = "REGISTRATION";

            // 
            // register
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(443, 234);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.senhauser2);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.senhauser);
            this.Controls.Add(this.nomeuser);
            this.Name = "register";
            this.Text = "Registration";
            this.Load += new System.EventHandler(this.register_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox senhauser;
        private System.Windows.Forms.TextBox nomeuser;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox senhauser2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label3;
    }
}