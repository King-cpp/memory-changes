
namespace CSharp_Memory
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.GroupAll = new System.Windows.Forms.GroupBox();
            this.NoDelay = new System.Windows.Forms.CheckBox();
            this.FreezeSun = new System.Windows.Forms.CheckBox();
            this.EditSun = new System.Windows.Forms.TextBox();
            this.AddSun = new System.Windows.Forms.Button();
            this.Label_GameInfo = new System.Windows.Forms.Label();
            this.Timer_FindGame = new System.Windows.Forms.Timer(this.components);
            this.GroupAll.SuspendLayout();
            this.SuspendLayout();
            // 
            // GroupAll
            // 
            this.GroupAll.Controls.Add(this.NoDelay);
            this.GroupAll.Controls.Add(this.FreezeSun);
            this.GroupAll.Controls.Add(this.EditSun);
            this.GroupAll.Controls.Add(this.AddSun);
            this.GroupAll.Location = new System.Drawing.Point(12, 12);
            this.GroupAll.Name = "GroupAll";
            this.GroupAll.Size = new System.Drawing.Size(200, 76);
            this.GroupAll.TabIndex = 0;
            this.GroupAll.TabStop = false;
            this.GroupAll.Text = "Úteis";
            // 
            // NoDelay
            // 
            this.NoDelay.AutoSize = true;
            this.NoDelay.Location = new System.Drawing.Point(124, 45);
            this.NoDelay.Name = "NoDelay";
            this.NoDelay.Size = new System.Drawing.Size(74, 19);
            this.NoDelay.TabIndex = 3;
            this.NoDelay.Text = "No Delay";
            this.NoDelay.UseVisualStyleBackColor = true;
            this.NoDelay.CheckedChanged += new System.EventHandler(this.NoDelay_CheckedChanged);
            // 
            // FreezeSun
            // 
            this.FreezeSun.AutoSize = true;
            this.FreezeSun.Location = new System.Drawing.Point(124, 19);
            this.FreezeSun.Name = "FreezeSun";
            this.FreezeSun.Size = new System.Drawing.Size(73, 19);
            this.FreezeSun.TabIndex = 2;
            this.FreezeSun.Text = "Sun 9990";
            this.FreezeSun.UseVisualStyleBackColor = true;
            this.FreezeSun.CheckedChanged += new System.EventHandler(this.FreezeSun_CheckedChanged);
            // 
            // EditSun
            // 
            this.EditSun.Location = new System.Drawing.Point(6, 16);
            this.EditSun.Name = "EditSun";
            this.EditSun.Size = new System.Drawing.Size(100, 23);
            this.EditSun.TabIndex = 1;
            this.EditSun.Text = "10000";
            // 
            // AddSun
            // 
            this.AddSun.Location = new System.Drawing.Point(6, 45);
            this.AddSun.Name = "AddSun";
            this.AddSun.Size = new System.Drawing.Size(100, 23);
            this.AddSun.TabIndex = 0;
            this.AddSun.Text = "Add Sun";
            this.AddSun.UseVisualStyleBackColor = true;
            // 
            // Label_GameInfo
            // 
            this.Label_GameInfo.AutoSize = true;
            this.Label_GameInfo.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.Label_GameInfo.Location = new System.Drawing.Point(10, 90);
            this.Label_GameInfo.Name = "Label_GameInfo";
            this.Label_GameInfo.Size = new System.Drawing.Size(134, 15);
            this.Label_GameInfo.TabIndex = 1;
            this.Label_GameInfo.Text = "Game não encontrado...";
            // 
            // Timer_FindGame
            // 
            this.Timer_FindGame.Enabled = true;
            this.Timer_FindGame.Tick += new System.EventHandler(this.Timer_FindGame_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(224, 107);
            this.Controls.Add(this.Label_GameInfo);
            this.Controls.Add(this.GroupAll);
            this.Name = "Form1";
            this.Text = "Hack";
            this.GroupAll.ResumeLayout(false);
            this.GroupAll.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox GroupAll;
        private System.Windows.Forms.Label Label_GameInfo;
        private System.Windows.Forms.CheckBox NoDelay;
        private System.Windows.Forms.CheckBox FreezeSun;
        private System.Windows.Forms.TextBox EditSun;
        private System.Windows.Forms.Button AddSun;
        private System.Windows.Forms.Timer Timer_FindGame;
    }
}

